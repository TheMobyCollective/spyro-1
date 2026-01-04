

# -------------------------------
# Compiler & Toolchain Setup
# -------------------------------
NOCD_FLAG          = $(if ${NOCD},-DNOCD,-DNNOCD)
DEBUG_FLAG          = $(if ${DEBUG},-DDEBUG,-DNDEBUG)
MODERN_COMPILER_FLAG = $(if ${MODERN_COMPILER},-DMODERN_COMPILER,-D_HAS_MASPSX)
NON_MATCHING_FLAG  = $(if ${NON_MATCHING},-DNON_MATCHING,)
NEW_PSYQ_FLAG = $(if ${NEW_PSYQ},-D_NEW_PSYQ,)
PSYQ_LIB = $(if ${NEW_PSYQ},-Lpsyq/lib --start-group -lapi -lc -lc2 -lcard -lcd -lcomb -lds -letc -lgpu -lgs -lgte -lgun -lhmd -lmath -lmcrd -lpad -lsio -lspu --end-group,)

CC       = $(if ${MODERN_COMPILER}, "/usr/libexec/gcc-cross/mips-linux-gnu/14/cc1", "./tools/gcc2.7.2/cc1")
GCC      = mips-linux-gnu-cpp
AS       = mips-linux-gnu-as
LD       = mips-linux-gnu-ld
OBJCOPY  = mips-linux-gnu-objcopy
PYTHON   = python3

MASPSX          = "./tools/maspsx/maspsx.py"
REMOVE_SECTIONS = "./tools/remove_sections.py"
FIX_JTBL_ALIGN  = "./tools/fix_jtbl_align.py"
FIX_STR_ALIGN   = "./tools/fix_str_align.py"

# -------------------------------
# Compilation Flags
# -------------------------------
LD_FLAGS  = -g -EL -T /tmp/psx.ld -g -Map build/psx.map --no-check-sections -nostdlib $(PSYQ_LIB)
C_CLASSIC_FLAGS = -O2 -G8 -g3 -fverbose-asm -mips1 -mcpu=3000 -fgnu-linker -mno-abicalls -mgpopt -msoft-float -quiet
C_MODERN_FLAGS = -Os -G 0 -g3 -fverbose-asm -march=mips1 -mabi=32 -mips1 -mno-llsc -mno-abicalls -mgpopt -msoft-float -fno-builtin -fno-builtin-function -fno-strict-aliasing -fno-exceptions -fschedule-insns -fno-pic -fno-stack-protector -ffreestanding -o-
C_FLAGS   = $(if ${MODERN_COMPILER},$(C_MODERN_FLAGS),$(C_CLASSIC_FLAGS))
AS_FLAGS  = -EL -Iinclude -Iasm -Iasm/renderers -march=r3000 -mtune=r3000 -no-pad-sections -G0 -ggdb -msoft-float

# -------------------------------
# Targets & Sources
# -------------------------------
TARGET_ELF = build/psx.elf
TARGET_EXE = build/PSX.EXE

# Define WAD file names
LEVELS = \
	level_0_artisans_home \
	level_1_artisans_stone_hill \
	level_2_artisans_dark_hollow \
	level_3_artisans_town_square \
	level_4_artisans_toasty \
	level_5_artisans_sunny_flight \
	level_6_peace_keepers_home \
	level_7_peace_keepers_dry_canyon \
	level_8_peace_keepers_cliff_town \
	level_9_peace_keepers_ice_cavern \
	level_10_peace_keepers_doctor_shemp \
	level_11_peace_keepers_night_flight \
	level_12_magic_crafters_home \
	level_13_magic_crafters_alpine_ridge \
	level_14_magic_crafters_high_caves \
	level_15_magic_crafters_wizard_peak \
	level_16_magic_crafters_blowhard \
	level_17_magic_crafters_crystal_flight \
	level_18_beast_makers_home \
	level_19_beast_makers_terrace_village \
	level_20_beast_makers_misty_bog \
	level_21_beast_makers_tree_tops \
	level_22_beast_makers_metalhead \
	level_23_beast_makers_wild_flight \
	level_24_dream_weavers_home \
	level_25_dream_weavers_dark_passage \
	level_26_dream_weavers_lofty_castle \
	level_27_dream_weavers_haunted_towers \
	level_28_dream_weavers_jacques \
	level_29_dream_weavers_icy_flight \
	level_30_gnastys_world_gnorc_gnexus \
	level_31_gnastys_world_gnorc_cove \
	level_32_gnastys_world_twilight_harbor \
	level_33_gnastys_world_gnasty_gnorc \
	level_34_gnastys_world_gnastys_loot

# And which level number they corrospond to
# for the overlay sections
LEVEL_NUMBERS = \
	10 11 12 13 14 15 \
	20 21 22 23 24 25 \
	30 31 32 33 34 35 \
	40 41 42 43 44 45 \
	50 51 52 53 54 55 \
	60 61 62 63 64

# Generate object names and their section numbers
TARGET_OVERLAYS = $(patsubst %, build/wad/%_code.ovl, $(LEVELS)) build/wad/credits.ovl build/wad/titlescreen_code.ovl
OVERLAY_SECTIONS  = $(foreach n, $(LEVEL_NUMBERS), .level_$(n))

# Input is one of TARGET_OVERLAYS' values and it returns the OVERLAY_SECTIONS entry at the same index
define LEVEL_TO_SECTION
    $(strip
			$(foreach idx, $(shell seq 1 $(words $(TARGET_OVERLAYS))), \
        $(if $(filter $(word $(idx),$(TARGET_OVERLAYS)),$(1)), \
            $(word $(idx),$(OVERLAY_SECTIONS)) \
        ) \
    	) \
		)
endef

SRC_C  = $(shell find src -type f -name '*.c')
SRC_S  = $(shell find asm -type f -name '*.s' | grep -v asm/nonmatchings)

OBJ_C  = $(SRC_C:src/%.c=build/src/%.o)
OBJ_S  = $(SRC_S:asm/%.s=build/asm/%.o)
DEPENDS = $(OBJ_C:.o=.o.d)

# -------------------------------
# Dependency Handling
# -------------------------------
-include $(DEPENDS)

# -------------------------------
# Directories Setup
# -------------------------------
$(OBJ_C): | create_dirs

create_dirs:
	@mkdir -p build/asm build/src $(sort $(dir $(OBJ_C))) $(sort $(dir $(OBJ_S))) build/wad

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

build/src/%.o: src/%.c
	@echo "\e[0;36m[Compiling] $<\e[0m"
		
	@$(GCC) $(MODERN_COMPILER_FLAG) $(NEW_PSYQ_FLAG) $(DEBUG_FLAG) $(NON_MATCHING_FLAG) -Iinclude -Ipsyq/include -ffreestanding -MT $@ -MMD -MP -MF $@.d $< | \
		$(CC) $(C_FLAGS) |\
		$(MASPSX_COMMAND) \
		$(PYTHON) $(REMOVE_SECTIONS) | \
		$(PYTHON) $(FIX_STR_ALIGN) | \
		$(PYTHON) $(FIX_JTBL_ALIGN) | \
		$(AS) $(AS_FLAGS) -o $@

build/asm/%.o: asm/%.s
	@echo "\e[0;34m[Assembling] $<\e[0m"
	@$(AS) $(AS_FLAGS) -o $@ $<

# -------------------------------
# Linking
# -------------------------------

# Main ELF
$(TARGET_ELF): $(OBJ_C) $(OBJ_S) psx.ld overlays.ld
	@echo "\e[0;32m[Linking] $@\e[0m"
	@gcc -E -P -x assembler-with-cpp -c psx.ld $(NEW_PSYQ_FLAG) -o /tmp/psx.ld
	@$(LD) $(LD_FLAGS) -o $@

# Main executable
$(TARGET_EXE): $(TARGET_ELF)
	@echo "\e[0;32m[Copying] $< → $@\e[0m"
	@$(OBJCOPY) --only-section=.header --only-section=.main -O binary $< $@

# Overlays
build/wad/credits.ovl: $(TARGET_ELF)
	@echo "\e[0;32m[Copying] $< → $@\e[0m"
	@$(OBJCOPY) --only-section=.credits -O binary $< $@

build/wad/titlescreen_code.ovl: $(TARGET_ELF)
	@echo "\e[0;32m[Copying] $< → $@\e[0m"
	@$(OBJCOPY) --only-section=.titlescreen -O binary $< $@

build/wad/%_code.ovl: $(TARGET_ELF)
	@echo "\e[0;32m[Copying] $< → $@\e[0m"
	@$(OBJCOPY) --only-section=$(strip $(call LEVEL_TO_SECTION,$@)) -O binary $< $@

# -------------------------------
# Cleaning
# -------------------------------
clean:
	@echo "\e[0;31m[Cleaning] Removing build artifacts...\e[0m"
	@rm -f $(OBJ_C) $(OBJ_S) $(DEPENDS) $(TARGET_ELF) $(TARGET_EXE) $(TARGET_OVERLAYS)