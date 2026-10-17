

# -------------------------------
# Compiler & Toolchain Setup
# -------------------------------
NOCD_FLAG          = $(if ${NOCD},-DNOCD,-DNNOCD)
DEBUG_FLAG          = $(if ${DEBUG},-DDEBUG,-DNDEBUG)
MODERN_COMPILER_FLAG = $(if ${MODERN_COMPILER},-DMODERN_COMPILER,-D_HAS_MASPSX)
NON_MATCHING_FLAG  = $(if ${NON_MATCHING},-DNON_MATCHING,)
NEW_PSYQ_FLAG = $(if ${NEW_PSYQ},-DNEW_PSYQ,)
PSYQ_LIB = $(if ${NEW_PSYQ},-Lpsyq/lib --start-group -lapi -lc -lc2 -lcard -lcd -lcomb -lds -letc -lgpu -lgs -lgte -lgun -lhmd -lmath -lmcrd -lpad -lsio -lspu --end-group,)

CC       = $(if ${MODERN_COMPILER}, "/usr/libexec/gcc-cross/mipsel-linux-gnu/14/cc1", "./tools/gcc2.7.2/cc1")
GCC      = mipsel-linux-gnu-cpp
AS       = mipsel-linux-gnu-as
LD       = mipsel-linux-gnu-ld
OBJCOPY  = mipsel-linux-gnu-objcopy
PYTHON   = python3

MASPSX          = "./tools/maspsx/maspsx.py"
REMOVE_SECTIONS = "./tools/remove_sections.py"
FIX_JTBL_ALIGN  = "./tools/fix_jtbl_align.py"
FIX_STR_ALIGN   = "./tools/fix_str_align.py"
FIX_STR_ALIGN_CMD = $(PYTHON) $(FIX_STR_ALIGN) |

# -------------------------------
# Compilation Flags
# -------------------------------
LD_FLAGS  = -g -EL -T /tmp/psx.ld -g -Map build/psx.map --no-check-sections -nostdlib $(PSYQ_LIB)
C_CLASSIC_FLAGS = -O2 -G8 -g3 -fverbose-asm -mips1 -mcpu=3000 -fgnu-linker -mno-abicalls -mgpopt -msoft-float -quiet -funsigned-char
C_MODERN_FLAGS = -Os -G 0 -g3 -fverbose-asm -mips1 -march=r3000 -mabi=32 -mno-llsc -mno-abicalls -mgpopt -msoft-float -fno-builtin -fno-builtin-function -fno-strict-aliasing -fno-exceptions -fschedule-insns -fno-pic -fno-stack-protector -ffreestanding -Wno-error=int-conversion -o-
C_FLAGS   = $(if ${MODERN_COMPILER},$(C_MODERN_FLAGS),$(C_CLASSIC_FLAGS))
AS_FLAGS  = -EL -Iinclude -Iasm -Iasm/renderers -march=r3000 -mtune=r3000 -no-pad-sections -G0 -ggdb -msoft-float

# -------------------------------
# Targets & Sources
# -------------------------------
TARGET_ELF = build/psx.elf
TARGET_EXE = build/PSX.EXE

OVERLAYS    = $(shell $(PYTHON) tools/overlays/get_overlays.py)
OVERLAY_OBJ = $(shell $(PYTHON) tools/overlays/get_overlay_objects.py)
OVERLAY_LD  = build/overlays.ld
TARGET_OVERLAYS = $(patsubst %, build/wad/%.ovl, $(OVERLAYS))

SRC_C  = $(wildcard src/*.c) $(wildcard src/gamestates/*.c)
SRC_S  = $(shell find asm -type f -name '*.s' | grep -v asm/nonmatchings)

OBJ_C  = $(SRC_C:src/%.c=build/src/%.o)
OBJ_S  = $(SRC_S:asm/%.s=build/asm/%.o)
DEPENDS = $(OBJ_C:.o=.o.d) $(OVERLAY_OBJ:.o=.o.d)

# -------------------------------
# Dependency Handling
# -------------------------------
-include $(DEPENDS)

# -------------------------------
# Directories Setup
# -------------------------------
$(OBJ_C) $(OVERLAY_OBJ) $(OVERLAY_LD): | create_dirs

create_dirs:
	@mkdir -p build/asm build/src $(sort $(dir $(OBJ_C) $(OVERLAY_OBJ))) $(sort $(dir $(OBJ_S))) build/wad

# -------------------------------
# Build Targets
# -------------------------------

all: $(TARGET_OVERLAYS) $(TARGET_EXE)
	@echo "\e[0;32m[Verifying] SHA-256 checksums...\e[0m"
	@sha256sum -c sha256sum.txt

non_matching: $(TARGET_OVERLAYS) $(TARGET_EXE)

# -------------------------------
# Compilation
# -------------------------------

# Only use MASPSX for non-modern compilers
MASPSX_COMMAND = $(if ${MODERN_COMPILER},,$(PYTHON) $(MASPSX) -G4 --aspsx-version 2.56 --expand-div |)

# Overlay Specific Flags (-G0)
build/src/overlays/%.o: C_FLAGS := $(subst -G8,-G0,$(C_FLAGS))


# For the padding garbage, skip the align (it's handled in the LD instead)
build/src/overlays/LEVEL_%.o: FIX_STR_ALIGN_CMD :=

# Strip overlay functions based on the classes they're configured to include
build/src/overlays/%/moby_spawn.o     build/src/overlays/%/moby_update.o:     STRIP_CLASSES = moby
build/src/overlays/%/particle_spawn.o build/src/overlays/%/particle_update.o: STRIP_CLASSES = particle
OVERLAY_STRIP = $(if $(STRIP_CLASSES),$(PYTHON) tools/overlays/strip_overlay_function.py "$$($(PYTHON) tools/overlays/get_overlay_$(STRIP_CLASSES)_classes.py $*)" |)

define OVERLAY_SOURCE
build/src/overlays/%/$(1).o: src/overlays/$(1).c
	@echo "\e[0;36m[Compiling/$$*] $$< \e[0m"
	@$$(GCC) -DOVERLAY_NAME=$$* -DIS_$$* $$(MODERN_COMPILER_FLAG) $$(NEW_PSYQ_FLAG) $$(DEBUG_FLAG) $$(NON_MATCHING_FLAG) -Iinclude -Ipsyq/include -ffreestanding -MT $$@ -MMD -MP -MF $$@.d $$< | \
		$$(OVERLAY_STRIP) \
		$$(CC) $$(C_FLAGS) | \
		$$(MASPSX_COMMAND) \
		$$(FIX_STR_ALIGN_CMD) \
		$$(PYTHON) $$(REMOVE_SECTIONS) | \
		$$(PYTHON) $$(FIX_JTBL_ALIGN) | \
		$$(AS) $$(AS_FLAGS) -o $$@
endef

$(foreach src,$(basename $(notdir $(wildcard src/overlays/*.c))),$(eval $(call OVERLAY_SOURCE,$(src))))

build/src/%.o: src/%.c
	@echo "\e[0;36m[Compiling] $<\e[0m"
		
	@$(GCC) $(MODERN_COMPILER_FLAG) $(NEW_PSYQ_FLAG) $(DEBUG_FLAG) $(NON_MATCHING_FLAG) -Iinclude -Ipsyq/include -ffreestanding -MT $@ -MMD -MP -MF $@.d $< | \
		$(CC) $(C_FLAGS) |\
		$(MASPSX_COMMAND) \
		$(PYTHON) $(REMOVE_SECTIONS) | \
		$(FIX_STR_ALIGN_CMD) \
		$(PYTHON) $(FIX_JTBL_ALIGN) | \
		$(AS) $(AS_FLAGS) -o $@

build/asm/%.o: asm/%.s
	@echo "\e[0;34m[Assembling] $<\e[0m"
	@$(AS) $(AS_FLAGS) -o $@ $<

# -------------------------------
# Linking
# -------------------------------

# Main ELF
$(TARGET_ELF): $(OBJ_C) $(OVERLAY_OBJ) $(OBJ_S) psx.ld $(OVERLAY_LD)
	@echo "\e[0;32m[Linking] $@\e[0m"
	@gcc -E -P -x assembler-with-cpp -c psx.ld -Ibuild $(NEW_PSYQ_FLAG) -o /tmp/psx.ld
	@$(LD) $(LD_FLAGS) -o $@

# Main executable
$(TARGET_EXE): $(TARGET_ELF)
	@echo "\e[0;32m[Copying] $< → $@\e[0m"
	@$(OBJCOPY) --only-section=.header --only-section=.main -O binary $< $@

# Overlay linker script from the yaml
$(OVERLAY_LD): overlays/overlays.yaml tools/overlays/generate_overlay_ld.py tools/overlays/get_overlay_objects.py
	@echo "\e[0;32m[Generating] $@\e[0m"
	@$(PYTHON) tools/overlays/generate_overlay_ld.py > $@

# The overlays themselves
define OVERLAY_RULE
build/wad/$(1).ovl: $$(TARGET_ELF)
	@echo "\e[0;32m[Copying] $$< → $$@\e[0m"
	@$$(OBJCOPY) --only-section=.$(1) -O binary $$< $$@
endef

$(foreach overlay, $(OVERLAYS), $(eval $(call OVERLAY_RULE,$(overlay))))

# -------------------------------
# Cleaning
# -------------------------------
clean:
	@echo "\e[0;31m[Cleaning] Removing build artifacts...\e[0m"
	@rm -f $(OBJ_C) $(OVERLAY_OBJ) $(OBJ_S) $(DEPENDS) $(OVERLAY_LD) $(TARGET_ELF) $(TARGET_EXE) $(TARGET_OVERLAYS)