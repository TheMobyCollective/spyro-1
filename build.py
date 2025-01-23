# I chose python over Make because gcc doesn't keep proper track of dependencies of assembly files
# So you're going to be rebuilding constantly anyway

import os

import hashlib

import colorama
colorama.init()

CC                   = "./tools/gcc2.7.2/cc1"
GCC                  = "mips-linux-gnu-cpp"
AS                   = "mips-linux-gnu-as -EL"
LD                   = "mips-linux-gnu-ld -EL"
OBJCOPY              = "mips-linux-gnu-objcopy"
MASPSX               = "./tools/maspsx/maspsx.py"
REMOVE_SECTIONS      = "./tools/remove_sections.py"

C_FLAGS = "-O2 -G4 -g0 -fverbose-asm -mips1 -mcpu=3000 -fgnu-linker -mno-abicalls -mgpopt -msoft-float -quiet"
AS_FLAGS = "-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -G0 -ggdb"
LD_FLAGS = "-T psx.ld -g -Map build/psx.map --no-check-sections -nostdlib"

USE_MASPSX = True

MODERN_COMPILER = False

if MODERN_COMPILER:
    USE_MASPSX = False
    CC = "/usr/lib/gcc-cross/mips-linux-gnu/12/cc1"
    C_FLAGS = "-Os -G 0 -g3 -fverbose-asm -march=mips1 -mabi=32 -mips1 -mno-llsc -mno-abicalls -mgpopt -msoft-float -fno-builtin -fno-strict-aliasing -fno-exceptions -fschedule-insns -fno-pic -fno-stack-protector -ffreestanding -o-"

# TODO: Add something to compile in  4.7 libraries, they do work

NEW_PSYQ = ""

# NEW_PSYQ += " -Lpsyq/lib"
# NEW_PSYQ += " --start-group"
# NEW_PSYQ += " -lapi -lc -lc2 -lcard -lcd -lcomb -lds -letc -lgpu -lgs -lgte -lgun -lhmd -lmath -lmcrd -lpad -lsio -lspu"
# NEW_PSYQ += " --end-group"

def print_error(message):
    print(colorama.Fore.RED + message + colorama.Style.RESET_ALL)

def print_warning(message):
    print(colorama.Fore.YELLOW + message + colorama.Style.RESET_ALL)

def print_info(message):
    print(colorama.Fore.CYAN + message + colorama.Style.RESET_ALL)

def print_success(message):
    print(colorama.Fore.GREEN + message + colorama.Style.RESET_ALL)

def sha256sum(filename):
    with open(filename, 'rb', buffering=0) as f:
        return hashlib.file_digest(f, 'sha256').hexdigest()

# Runs os.system but with a check for the return code
def system(command):
    if os.system(command) != 0:
        print_error(f"Command failed: {command}")
        exit(1)

level_overlay_map = {
    ".level_10": "level_0_artisans_home_code.ovl",
    ".level_11": "level_1_artisans_stone_hill_code.ovl",
    ".level_12": "level_2_artisans_dark_hollow_code.ovl",
    ".level_13": "level_3_artisans_town_square_code.ovl",
    ".level_14": "level_4_artisans_toasty_code.ovl",
    ".level_15": "level_5_artisans_sunny_flight_code.ovl",
    ".level_20": "level_6_peace_keepers_home_code.ovl",
    ".level_21": "level_7_peace_keepers_dry_canyon_code.ovl",
    ".level_22": "level_8_peace_keepers_cliff_town_code.ovl",
    ".level_23": "level_9_peace_keepers_ice_cavern_code.ovl",
    ".level_24": "level_10_peace_keepers_doctor_shemp_code.ovl",
    ".level_25": "level_11_peace_keepers_night_flight_code.ovl",
    ".level_30": "level_12_magic_crafters_home_code.ovl",
    ".level_31": "level_13_magic_crafters_alpine_ridge_code.ovl",
    ".level_32": "level_14_magic_crafters_high_caves_code.ovl",
    ".level_33": "level_15_magic_crafters_wizard_peak_code.ovl",
    ".level_34": "level_16_magic_crafters_blowhard_code.ovl",
    ".level_35": "level_17_magic_crafters_crystal_flight_code.ovl",
    ".level_40": "level_18_beast_makers_home_code.ovl",
    ".level_41": "level_19_beast_makers_terrace_village_code.ovl",
    ".level_42": "level_20_beast_makers_misty_bog_code.ovl",
    ".level_43": "level_21_beast_makers_tree_tops_code.ovl",
    ".level_44": "level_22_beast_makers_metalhead_code.ovl",
    ".level_45": "level_23_beast_makers_wild_flight_code.ovl",
    ".level_50": "level_24_dream_weavers_home_code.ovl",
    ".level_51": "level_25_dream_weavers_dark_passage_code.ovl",
    ".level_52": "level_26_dream_weavers_lofty_castle_code.ovl",
    ".level_53": "level_27_dream_weavers_haunted_towers_code.ovl",
    ".level_54": "level_28_dream_weavers_jacques_code.ovl",
    ".level_55": "level_29_dream_weavers_icy_flight_code.ovl",
    ".level_60": "level_30_gnastys_world_gnorc_gnexus_code.ovl",
    ".level_61": "level_31_gnastys_world_gnorc_cove_code.ovl",
    ".level_62": "level_32_gnastys_world_twilight_harbor_code.ovl",
    ".level_63": "level_33_gnastys_world_gnasty_gnorc_code.ovl",
    ".level_64": "level_34_gnastys_world_gnastys_loot_code.ovl",
}

def link_files():
    print_info("[1] Linking build/psx.elf")

    system(" ".join([LD, LD_FLAGS, NEW_PSYQ, "-o build/psx.elf"]))

    print_info("[2] Extracting PSX.EXE")
    
    # Take the main executable
    system(OBJCOPY + " --only-section=.header --only-section=.main -O binary build/psx.elf build/PSX.EXE")

    print_info("[3] Extracting overlays")

    for section, overlay in level_overlay_map.items():
        system(OBJCOPY + " --only-section=" + section + " -O binary build/psx.elf build/wad/" + overlay)

    # Get the titlescreen overlay
    system(OBJCOPY + " --only-section=.titlescreen -O binary build/psx.elf build/wad/titlescreen_code.ovl")

    # Get the credits overlay
    system(OBJCOPY + " --only-section=.credits -O binary build/psx.elf build/wad/credits.ovl")

    # Verify the SHA-256 of the PSX.EXE
    print_info("Verifying SHA-256 of PSX.EXE")
    sum = sha256sum("build/PSX.EXE")

    if sum.upper() != "A533D75CAB8AFAAE6107EC35A02A9A5FE979A92C7C955F9CF1EE50F693A1B998":
        print_warning("BUILT NON-MATCHING EXECUTABLE")
        print_warning("PSX.EXE SHA-256: " + sum)
    else:
        print_success("Successfully built a matching executable")
        print_success("PSX.EXE SHA-256: " + sum)

    if not os.environ.get("SKIP_OVERLAY"):
        overlay_sha256s = {
            "level_0_artisans_home_code.ovl": "7df6cf2f3ed4a71a123f03621019470bd6fe0cd243f75b1e8c3a115e6b1fcb55",
            "level_1_artisans_stone_hill_code.ovl": "876c0145649bb5b26921858d4d677468463974901dcc416dcba5ccea25caa069",
            "level_2_artisans_dark_hollow_code.ovl": "9920aa47b94005166f457b5b36df6dedd1f2400f91698bac21cdb01d8590ef32",
            "level_3_artisans_town_square_code.ovl": "9bc923cc8d27703537b81b01f51fde351e58aabee87d38a8afc630f1031878a5",
            "level_4_artisans_toasty_code.ovl": "3b412fceb81e9ab60eef189fc3292387efae0886f4ed0ada0e169f9a190eb049",
            "level_5_artisans_sunny_flight_code.ovl": "42b4e8a637ff91f87b884a9beea3266299d01ae36d36b437436d247f78812f59",
            "level_6_peace_keepers_home_code.ovl": "299f4822489c48736c9f46bb9556e82952fc1693f5f9f42bc2e6415c1908aebc",
            "level_7_peace_keepers_dry_canyon_code.ovl": "8aa4036028de3ea9cdc6ee93b4d96cb7dc2b9fa5f818b6e748c0c2bda946cc0f",
            "level_8_peace_keepers_cliff_town_code.ovl": "25f0fc287cc8b6b5b70d960630025e009e0e425f7af723dadf008605af5b0286",
            "level_9_peace_keepers_ice_cavern_code.ovl": "a50a830556b071b7b7afd6f30232b7e4d8be2ab3329dff24a4332e19ed5ff5a6",
            "level_10_peace_keepers_doctor_shemp_code.ovl": "73c7fd7ba2083507edbeca38393c825072ec2bd92e0bbbe9c3df5f5010aa8de9",
            "level_11_peace_keepers_night_flight_code.ovl": "3891e7af5f83825dbebc80952e173fbbea8125653d4b00fc7b1980a1128b873a",
            "level_12_magic_crafters_home_code.ovl": "98e135e18876ea094ca9484b33cfb38438e2b99b72ee4d6d66e907722c744a1d",
            "level_13_magic_crafters_alpine_ridge_code.ovl": "f7c9a174f64959fb53b4058f9786df223a9c142b2289563ca31edc6a24c6d383",
            "level_14_magic_crafters_high_caves_code.ovl": "6c153366d9b3dd6d25a7aa8e8d1ea6708bdf97b04ee35912b11df0f8b9913140",
            "level_15_magic_crafters_wizard_peak_code.ovl": "5d3996111567ffac6eca08d340f2f691824bb7969ba2a0cd95e9346ccfe157e1",
            "level_16_magic_crafters_blowhard_code.ovl": "1ee0030607139491b6d076c389837d5b6c0a38e87d324fec2e14b58b47f95aef",
            "level_17_magic_crafters_crystal_flight_code.ovl": "e8d91a7c5f9f5d06b95ac01ade6fa4423485fd3d5dd75dd0dc15cc8319d46a59",
            "level_18_beast_makers_home_code.ovl": "6bed996a20df44803ec4eefe434294082c3f5814ce56080e0594bab95eeb287f",
            "level_19_beast_makers_terrace_village_code.ovl": "285fc63da6b536af2b41c19e41d1db03a980007226dc55e5d930a1998f39c50e",
            "level_20_beast_makers_misty_bog_code.ovl": "3b37eb8b4b0f5fb74e7d263670705e20c807f2d8f1bbf03f34a461eb1c3e2ff6",
            "level_21_beast_makers_tree_tops_code.ovl": "f7363f0f2a03e6ddcc906fd68c914905c3704e49e058220941ac9a0ece488405",
            "level_22_beast_makers_metalhead_code.ovl": "97a960c4c4e9f6933d3dc4ab19a31987a105f33dfdfd98433021977e7778543f",
            "level_23_beast_makers_wild_flight_code.ovl": "5069a570d9cce769fed272d8c8fe24a56ade3317370fe5c688ebb43126570e97",
            "level_24_dream_weavers_home_code.ovl": "dcbe76c16c51393e784037af420c7fb7c00cecd526ed4d890ae5f1b257cdb352",
            "level_25_dream_weavers_dark_passage_code.ovl": "a8b99270c37a37363824cf1fd2081c092968abef62df9e74d70ae0017b984727",
            "level_26_dream_weavers_lofty_castle_code.ovl": "e0f1f9e14726e4ca9d41e9e8bca112290263f00ce85413a7e389ab59c9e358c3",
            "level_27_dream_weavers_haunted_towers_code.ovl": "e714a2c4aff4a7e8d4980fa091540f4fdcd320b4fe4c532fa8c6c3d36fd7fbfc",
            "level_28_dream_weavers_jacques_code.ovl": "e09f6cb0adeb6275b04549507ed5d8424c1f6045ecfde0f50424f6ba58713f49",
            "level_29_dream_weavers_icy_flight_code.ovl": "67de47f547e65d4345401dedbb988b38c0de61648c903ab98d1a64f64fce9f0e",
            "level_30_gnastys_world_gnorc_gnexus_code.ovl": "16b6a88de15db049ee69c53fea4fbd21a3725fce4effa97cd9851467a2ea9d64",
            "level_31_gnastys_world_gnorc_cove_code.ovl": "1d6f62cc80f515c73efc50b9c8435a36cb51b5e2bcea8823005ce05ed856fad9",
            "level_32_gnastys_world_twilight_harbor_code.ovl": "55d0845c750c0fcbd13d69633d1481d288bb3b02ce33bf60e3b17866111739dd",
            "level_33_gnastys_world_gnasty_gnorc_code.ovl": "9b8b9677df191c917ed45896192db86c82cdcad2853ba1cd7dfd6feca3be43a4",
            "level_34_gnastys_world_gnastys_loot_code.ovl": "2117b3b14116b98035d9b003df3f299ef127ee34558f700af2be9fcb7e165a6e",
            "credits.ovl": "e618244a02844943729d49494dd82ca69c5fb6298784174155e673ece8a914c9",
            "titlescreen_code.ovl": "8ee66fe644407bf15f93af1615045fbaca17fe3daa9f3b67f38bee2277a94c7c",
        }

        # Verify the SHA-256 of the overlays
        print_info("Verifying SHA-256 of overlays")
        for overlay, sha256 in overlay_sha256s.items():
            sum = sha256sum("build/wad/" + overlay)

            if sum.upper() != sha256.upper():
                print_warning(f"Overlay {overlay} SHA-256: {sum}")
            else:
                print_success(f"Overlay {overlay} SHA-256: {sum}")

object_files = []

def assemble_file(file):
    # Remove .s from the file name
    out = file[:-2] + ".o"

    # Create the output directory if it doesn't exist
    os.makedirs(os.path.dirname("build/" + out), exist_ok=True)

    system(AS + " " + AS_FLAGS + " -o build/" + out + " " + file)

    object_files.append("build/" + out)

def build_file(file):
    # Remove .c from the file name
    file = file[:-2]
    out = file + ".o"
    out_s = file + ".s"

    # Create the output directory if it doesn't exist
    os.makedirs(os.path.dirname("build/" + out), exist_ok=True)

    debug_build = os.environ.get("DEBUG")

    system(GCC + ("" if not debug_build else " -DDEBUG") + ("" if not MODERN_COMPILER else " -DMODERN_COMPILER") + ("" if not USE_MASPSX else " -D_HAS_MASPSX") + " -ffreestanding -Iinclude -Ipsyq/include -MMD -MP -MF build/" + file + ".o.d " + file + ".c | " + CC + " " + C_FLAGS + (" | python3 " + MASPSX + " -G4 --aspsx-version 2.56 --expand-div" if USE_MASPSX else "") + " | python3 " + REMOVE_SECTIONS + " > build/" + out_s)
    system(AS + " " + AS_FLAGS + " -o build/" + out + " build/" + out_s)

    object_files.append("build/" + out)


def collect_c_files():
    files = []
    for root, _, filenames in os.walk("src"):
        for filename in filenames:
                if filename.endswith(".c"):
                    if os.environ.get("SKIP_OVERLAY") and "overlays" in root:
                        continue
                    files.append(os.path.join(root, filename))
    return files

def collect_asm_files():
    files = []
    for root, _, filenames in os.walk("asm"):
        if "nonmatchings" in root:
            continue
        for filename in filenames:
            if filename.endswith(".s"):
                files.append(os.path.join(root, filename))
    return files

# Make sure the build/ and build/wad/ directories exist
os.makedirs("build/wad", exist_ok=True)

# You can skip compiling the source code and only link the files by calling LINK_ONLY=1 python build.py
if not os.environ.get("LINK_ONLY"):
    asm_files = collect_asm_files()
    c_files = collect_c_files()

    idx = 0
    for file in c_files:
        idx += 1
        print_info(f"Compiling {idx}/{len(c_files)}: {file}")
        build_file(file)

    idx = 0
    for file in asm_files:
        idx += 1
        print_info(f"Assembling {idx}/{len(asm_files)}: {file}")
        assemble_file(file)

link_files()