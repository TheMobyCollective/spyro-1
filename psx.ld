
#define DEFINE_SECTIONS(sec) \
    build/asm/data/game.data.o(sec); \
    build/asm/data/math.data.o(sec); \
    build/asm/data/save_header.o(sec); \
    build/asm/data/game.sdata.o(sec); \
    build/src/strings.o(sec); \
    build/asm/data/titlescreen_data.o(sec); \
    build/asm/data/pad_act_align.o(sec); \
    build/asm/data/unknown_data.o(sec); \
    build/asm/data/sony_text.o(sec); \
    build/asm/data/game.sbss.o(sec); \
    build/asm/data/game.bss.o(sec); \
    build/src/main.o(sec); \
    build/src/initialization.o(sec); \
    build/src/loaders.o(sec); \
    build/src/cd.o(sec); \
    build/asm/order_table.o(sec); \
    build/asm/memory.o(sec); \
    build/asm/math.o(sec); \
    build/asm/images.o(sec); \
    build/asm/system_time.o(sec); \
    build/src/gamestates/draw.o(sec); \
    build/asm/renderers/r_moby.o(sec); \
    build/asm/renderers/r_pete.o(sec); \
    build/asm/renderers/r_environment.o(sec); \
    build/src/environment.o(sec); \
    build/src/crash_demo.o(sec); \
    build/src/completion.o(sec); \
    build/src/music.o(sec); \
    build/src/cutscene.o(sec); \
    build/src/gamestates/init.o(sec); \
    build/src/cheats.o(sec); \
    build/asm/data/entrance_stones.o(sec); \
    build/src/gamestates/update.o(sec); \
    build/src/camera.o(sec); \
    build/src/moby_interpolation_check.o(sec); \
    build/src/rand.o(sec); \
    build/src/moby_helpers.o(sec); \
    build/src/pete.o(sec); \
    build/asm/collision.o(sec); \
    build/asm/renderers/r_cyclorama.o(sec); \
    build/src/cyclorama.o(sec); \
    build/asm/moby_lists.o(sec); \
    build/asm/42CC4.o(sec); \
    build/asm/particle_alloc.o(sec); \
    build/src/gamepad.o(sec); \
    build/src/hud.o(sec); \
    build/src/spu.o(sec); \
    build/src/special_surfaces.o(sec); \
    build/asm/renderers/r_particles.o(sec); \
    build/src/specular_and_metal.o(sec); \
    build/asm/renderers/r_flame.o(sec); \
    build/src/checkpoint.o(sec); \
    build/src/save_file.o(sec); \
    build/asm/renderers/r_shadows.o(sec); \
    build/asm/overlay_space_pointer.o(sec); \
    build/src/overlay_pointers.o(sec); \
    build/src/4BEF8.o(sec);

SECTIONS
{
    /****************************************************************************************
     * HEADER
     ****************************************************************************************/
    .header : AT(0) SUBALIGN(2)
    {
        FILL(0x00000000);
        header_DATA_START = .;
        header = .;
        build/asm/header.o(.data);
        header_DATA_END = .;
        header_DATA_SIZE = ABSOLUTE(header_DATA_END - header_DATA_START);
        header_END = .;
    }


    /****************************************************************************************
     * MAIN
     ****************************************************************************************/
    .main 0x80010000 : AT(header_END) SUBALIGN(4)
    {
        FILL(0x00000000);
        main_RODATA_START = .;

        DEFINE_SECTIONS(.rodata*)

        #ifndef NEW_PSYQ

        /* for old psyq */
        build/asm/data/psyq.rodata.o(.rodata*);

        #else

        /* for new psyq */
        *libapi.a:*(.rdata .rdata.*)
        *libgte.a:*(.rdata .rdata.*)
        *libspu.a:*(.rdata .rdata.*)
        *libetc.a:*(.rdata .rdata.*)
        *libgpu.a:*(.rdata .rdata.*)
        *libc.a:*(.rdata .rdata.*)
        *libc2.a:*(.rdata .rdata.*)
        *libcd.a:*(.rdata .rdata.*)
        *libmcrd.a:*(.rdata .rdata.*)
        *libcard.a:*(.rdata .rdata.*)
        *libpad.a:*(.rdata .rdata.*)
        
        #endif

        . = ALIGN(., 4);
        main_RODATA_END = .;
        main_RODATA_SIZE = ABSOLUTE(main_RODATA_END - main_RODATA_START);
        main_TEXT_START = .;
        DEFINE_SECTIONS(.text*)

        #ifndef NEW_PSYQ

        /* for old psyq */
        build/asm/psyq.o(.text);

        #else

        /* for new psyq */
        build/asm/psyq.libsn.o(.text);
        *libapi.a:*(.text .text.*)
        *libgte.a:*(.text .text.*)
        *libspu.a:*(.text .text.*)
        *libetc.a:*(.text .text.*)
        *libgpu.a:*(.text .text.*)
        *libc.a:*(.text .text.*)
        *libc2.a:*(.text .text.*)
        *libcd.a:*(.text .text.*)
        *libmcrd.a:*(.text .text.*)
        *libcard.a:*(.text .text.*)
        *libpad.a:*(.text .text.*)

        #endif

        . = ALIGN(., 4);
        main_TEXT_END = .;
        main_TEXT_SIZE = ABSOLUTE(main_TEXT_END - main_TEXT_START);
        main_DATA_START = .;
        DEFINE_SECTIONS(.data)

        #ifndef NEW_PSYQ

        /* for old psyq */
        build/asm/data/psyq.data.o(.data);

        #else

        /* for new psyq */
        *libapi.a:*(.data .data.*)
        *libgte.a:*(.data .data.*)
        *libspu.a:*(.data .data.*)
        *libetc.a:*(.data .data.*)
        *libgpu.a:*(.data .data.*)
        *libc.a:*(.data .data.*)
        *libc2.a:*(.data .data.*)
        *libcd.a:*(.data .data.*)
        *libmcrd.a:*(.data .data.*)
        *libcard.a:*(.data .data.*)
        *libpad.a:*(.data .data.*)

        #endif

        . = ALIGN(., 4);
        main_DATA_END = .;
        main_DATA_SIZE = ABSOLUTE(main_DATA_END - main_DATA_START);
        main_SDATA_START = .;

        /* Technically, it'd be more optimal to offset this value, because you can offset it negatively in the code */
        /* But that's not what most developers did */
        _gp = .;

        DEFINE_SECTIONS(.sdata)
        . = ALIGN(., 4);
        main_SDATA_END = .;
        main_SDATA_SIZE = ABSOLUTE(main_SDATA_END - main_SDATA_START);

        /* Padding for the .exe */
        . = ALIGN(., 2048);
        EXE_TEXT_SIZE = . - 0x80010000;
    }

    .main_bss main_SDATA_END (NOLOAD) : AT(main_SDATA_END) SUBALIGN(4)
    {
        FILL(0x00000000);
        main_SBSS_START = .;
        
        #ifndef NEW_PSYQ

        /* for old psyq */
        build/asm/data/psyq.sbss.o(.sbss);

        #else

        /* for new psyq */
        *libapi.a:*(.sbss .sbss.*)
        *libgte.a:*(.sbss .sbss.*)
        *libspu.a:*(.sbss .sbss.*)
        *libetc.a:*(.sbss .sbss.*)
        *libgpu.a:*(.sbss .sbss.*)
        *libc.a:*(.sbss .sbss.*)
        *libc2.a:*(.sbss .sbss.*)
        *libcd.a:*(.sbss .sbss.*)
        *libmcrd.a:*(.sbss .sbss.*)
        *libcard.a:*(.sbss .sbss.*)
        *libpad.a:*(.sbss .sbss.*)

        #endif

        DEFINE_SECTIONS(.sbss)

        . = ALIGN(., 4);
        main_SBSS_END = .;
        main_SBSS_SIZE = ABSOLUTE(main_SBSS_END - main_SBSS_START);
        main_BSS_START = .;

        #ifndef NEW_PSYQ

        /* for old psyq */
        build/asm/data/psyq.bss.o(.bss);

        #else

        /* for new psyq */
        *libapi.a:*(.bss .bss.*)
        *libgte.a:*(.bss .bss.*)
        *libspu.a:*(.bss .bss.*)
        *libetc.a:*(.bss .bss.*)
        *libgpu.a:*(.bss .bss.*)
        *libc.a:*(.bss .bss.*)
        *libc2.a:*(.bss .bss.*)
        *libcd.a:*(.bss .bss.*)
        *libmcrd.a:*(.bss .bss.*)
        *libcard.a:*(.bss .bss.*)
        *libpad.a:*(.bss .bss.*)

        #endif

        DEFINE_SECTIONS(.bss)
        
        . = ALIGN(., 4);
        main_BSS_END = .;
        main_BSS_SIZE = ABSOLUTE(main_BSS_END - main_BSS_START);
    }

    . = ALIGN(., 4);

    .overlay_load_addr = .;

    /* Now it's time for the overlays */

    /* overlays.ld gets generated by make using tools/overlays/generate_overlay_ld.py */
#include "overlays.ld"

    /* Symbols for test levels that weren't included on the disc */
    /* So we can't really match them either ¯\_(ツ)_/¯ */
    Terminator_LEVEL_0 = 0x80082068;
    SpawnMoby_LEVEL_0 = 0x80080548;
    UpdateMoby_LEVEL_0 = 0x8007D8E0;
    SpawnParticle_LEVEL_0 = 0x80081568;
    UpdateParticle_LEVEL_0 = 0x80080A0C;
    BalloonistEnter_LEVEL_0 = 0x8007ADB8;
    BalloonistExit_LEVEL_0 = 0x8007AEF4;
    BalloonistUpdate_LEVEL_0 = 0x8007AF38;
    BalloonistDraw_LEVEL_0 = 0x8007CED8;
    Terminator_LEVEL_1 = 0x8007BFF0;
    SpawnMoby_LEVEL_1 = 0x8007B070;
    UpdateMoby_LEVEL_1 = 0x8007AC8C;
    SpawnParticle_LEVEL_1 = 0x8007B8AC;
    UpdateParticle_LEVEL_1 = 0x8007B144;
    Terminator_LEVEL_2 = 0x8007F490;
    SpawnMoby_LEVEL_2 = 0x8007D970;
    UpdateMoby_LEVEL_2 = 0x8007AD08;
    SpawnParticle_LEVEL_2 = 0x8007E990;
    UpdateParticle_LEVEL_2 = 0x8007DE34;
    Terminator_LEVEL_3 = 0x8007C7B0;
    SpawnMoby_LEVEL_3 = 0x8007B0AC;
    UpdateMoby_LEVEL_3 = 0x8007ACC8;
    SpawnParticle_LEVEL_3 = 0x8007BC50;
    UpdateParticle_LEVEL_3 = 0x8007B180;
    Terminator_LEVEL_4 = 0x8007C204;
    SpawnMoby_LEVEL_4 = 0x8007B08C;
    UpdateMoby_LEVEL_4 = 0x8007ACA8;
    SpawnParticle_LEVEL_4 = 0x8007B9F0;
    UpdateParticle_LEVEL_4 = 0x8007B160;
    Terminator_LEVEL_7 = 0x8007F2F4;
    SpawnMoby_LEVEL_7 = 0x8007D970;
    UpdateMoby_LEVEL_7 = 0x8007AD08;
    SpawnParticle_LEVEL_7 = 0x8007E8E4;
    UpdateParticle_LEVEL_7 = 0x8007DE34;
    Terminator_LEVEL_9 = 0x8007C204;
    SpawnMoby_LEVEL_9 = 0x8007B08C;
    UpdateMoby_LEVEL_9 = 0x8007ACA8;
    SpawnParticle_LEVEL_9 = 0x8007B9F0;
    UpdateParticle_LEVEL_9 = 0x8007B160;
    Terminator_LEVEL_99 = 0x8007C654;
    SpawnMoby_LEVEL_99 = 0x8007B0C0;
    UpdateMoby_LEVEL_99 = 0x8007ACDC;
    SpawnParticle_LEVEL_99 = 0x8007BC44;
    UpdateParticle_LEVEL_99 = 0x8007B194;

    /* /DISCARD/ :
    {
        *(*);
    } */

    /* Debug sections for GDB */
    /*.debug_info 0 : {
        *(.debug_info)
    }

    .debug_abbrev 0 : {
        *(.debug_abbrev)
    }

    .debug_line 0 : {
        *(.debug_line)
    }

    .debug_str 0 : {
        *(.debug_str)
    }

    .debug_aranges 0 : {
        *(.debug_aranges)
    }*/
}
