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
        build/src/strings.o(.rodata);
        build/src/strings.o(.rodata.jtbl);
        build/src/loaders.o(.rodata);
        build/src/loaders.o(.rodata.jtbl);
        build/src/gamestates/draw.o(.rodata);
        build/src/gamestates/draw.o(.rodata.jtbl);
        build/src/crash_demo.o(.rodata);
        build/src/crash_demo.o(.rodata.jtbl);
        build/src/gamestates/update.o(.rodata);
        build/src/gamestates/update.o(.rodata.jtbl);
        build/src/pete.o(.rodata);
        build/src/pete.o(.rodata.jtbl);
        build/src/special_surfaces.o(.rodata);
        build/src/special_surfaces.o(.rodata.jtbl);

        /* Putting overlay_pointer's .sdata here is cleaner than */
        /* Having the pointer in a seperate assembly file */
        build/src/overlay_pointers.o(.sdata);
        build/src/overlay_pointers.o(.rodata);
        build/src/overlay_pointers.o(.rodata.jtbl);

        #ifndef _NEW_PSYQ

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

        build/src/main.o(.rodata);
        build/src/main.o(.rodata.jtbl);
        build/src/initialization.o(.rodata);
        build/src/initialization.o(.rodata.jtbl);
        build/src/cd.o(.rodata);
        build/src/cd.o(.rodata.jtbl);
        build/asm/order_table.o(.rodata);
        build/asm/order_table.o(.rodata.jtbl);
        build/asm/memory.o(.rodata);
        build/asm/memory.o(.rodata.jtbl);
        build/asm/math.o(.rodata);
        build/asm/math.o(.rodata.jtbl);
        build/asm/images.o(.rodata);
        build/asm/images.o(.rodata.jtbl);
        
        build/asm/system_time.o(.rodata);
        build/asm/system_time.o(.rodata.jtbl);

        build/asm/renderers/r_moby.o(.rodata);
        build/asm/renderers/r_moby.o(.rodata.jtbl);
        build/asm/renderers/r_pete.o(.rodata);
        build/asm/renderers/r_pete.o(.rodata.jtbl);
        build/asm/renderers/r_environment.o(.rodata);
        build/asm/renderers/r_environment.o(.rodata.jtbl);

        build/src/environment.o(.rodata);
        build/src/environment.o(.rodata.jtbl);
        build/src/completion.o(.rodata);
        build/src/completion.o(.rodata.jtbl);
        build/src/music.o(.rodata);
        build/src/music.o(.rodata.jtbl);
        build/src/cutscene.o(.rodata);
        build/src/cutscene.o(.rodata.jtbl);
        build/src/gamestates/init.o(.rodata);
        build/src/gamestates/init.o(.rodata.jtbl);
        build/src/cheats.o(.rodata);
        build/src/cheats.o(.rodata.jtbl);
        build/src/camera.o(.rodata);
        build/src/camera.o(.rodata.jtbl);
        build/src/moby_interpolation_check.o(.rodata);
        build/src/moby_interpolation_check.o(.rodata.jtbl);
        build/src/rand.o(.rodata);
        build/src/rand.o(.rodata.jtbl);
        build/src/moby_helpers.o(.rodata);
        build/src/moby_helpers.o(.rodata.jtbl);
        build/asm/collision.o(.rodata);
        build/asm/collision.o(.rodata.jtbl);
        build/asm/renderers/r_cyclorama.o(.rodata);
        build/asm/renderers/r_cyclorama.o(.rodata.jtbl);
        build/src/cyclorama.o(.rodata);
        build/src/cyclorama.o(.rodata.jtbl);
        build/asm/moby_lists.o(.rodata);
        build/asm/moby_lists.o(.rodata.jtbl);
        build/asm/42CC4.o(.rodata);
        build/asm/42CC4.o(.rodata.jtbl);
        build/asm/particle_alloc.o(.rodata);
        build/asm/particle_alloc.o(.rodata.jtbl);
        build/src/gamepad.o(.rodata);
        build/src/gamepad.o(.rodata.jtbl);
        build/src/hud.o(.rodata);
        build/src/hud.o(.rodata.jtbl);
        build/src/spu.o(.rodata);
        build/src/spu.o(.rodata.jtbl);
        build/asm/renderers/r_particles.o(.rodata);
        build/asm/renderers/r_particles.o(.rodata.jtbl);
        build/src/specular_and_metal.o(.rodata);
        build/src/specular_and_metal.o(.rodata.jtbl);
        build/asm/renderers/r_flame.o(.rodata);
        build/asm/renderers/r_flame.o(.rodata.jtbl);
        build/src/checkpoint.o(.rodata);
        build/src/checkpoint.o(.rodata.jtbl);
        build/src/save_file.o(.rodata);
        build/src/save_file.o(.rodata.jtbl);
        build/asm/renderers/r_shadows.o(.rodata);
        build/asm/renderers/r_shadows.o(.rodata.jtbl);
        build/src/4BEF8.o(.rodata);
        build/src/4BEF8.o(.rodata.jtbl);
        . = ALIGN(., 4);
        main_RODATA_END = .;
        main_RODATA_SIZE = ABSOLUTE(main_RODATA_END - main_RODATA_START);
        main_TEXT_START = .;
        build/src/main.o(.text*);
        build/src/initialization.o(.text);
        build/src/loaders.o(.text);
        build/src/cd.o(.text);

        build/asm/order_table.o(.text);
        build/asm/memory.o(.text);
        build/asm/math.o(.text);
        build/asm/images.o(.text);

        build/asm/system_time.o(.text);

        build/src/gamestates/draw.o(.text);

        build/asm/renderers/r_moby.o(.text);
        build/asm/renderers/r_pete.o(.text);
        build/asm/renderers/r_environment.o(.text);

        build/src/environment.o(.text);
        build/src/crash_demo.o(.text);
        build/src/completion.o(.text);
        build/src/music.o(.text);
        build/src/cutscene.o(.text);
        build/src/gamestates/init.o(.text);
        build/src/cheats.o(.text);
        build/src/gamestates/update.o(.text);
        build/src/camera.o(.text);
        build/src/moby_interpolation_check.o(.text);
        build/src/rand.o(.text);
        build/src/moby_helpers.o(.text);
        build/src/pete.o(.text);
        build/asm/collision.o(.text);
        build/asm/renderers/r_cyclorama.o(.text);
        build/src/cyclorama.o(.text);
        build/asm/moby_lists.o(.text);
        build/asm/42CC4.o(.text);
        build/asm/particle_alloc.o(.text);
        build/src/gamepad.o(.text);
        build/src/hud.o(.text);
        build/src/spu.o(.text);
        build/src/special_surfaces.o(.text);
        build/asm/renderers/r_particles.o(.text);
        build/src/specular_and_metal.o(.text);
        build/asm/renderers/r_flame.o(.text);
        build/src/checkpoint.o(.text);
        build/src/save_file.o(.text);
        build/asm/renderers/r_shadows.o(.text);
        build/src/overlay_pointers.o(.text);
        build/src/4BEF8.o(.text);

        #ifndef _NEW_PSYQ

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
        build/asm/data/game.data.o(.data);
        build/asm/data/math.data.o(.data);
        build/asm/data/save_header.o(.data);
        build/asm/images.o(.data);

        build/asm/system_time.o(.data);

        build/asm/renderers/r_moby.o(.data);
        build/asm/renderers/r_pete.o(.data);
        build/asm/renderers/r_environment.o(.data);

        build/src/environment.o(.data);
        build/src/completion.o(.data);
        build/src/music.o(.data);
        build/src/cutscene.o(.data);
        build/src/gamestates/init.o(.data);
        build/src/strings.o(.data);
        build/asm/data/titlescreen_data.o(.data);
        build/asm/data/pad_act_align.o(.data);
        build/asm/data/unknown_data.o(.data);
        build/src/loaders.o(.data);
        build/src/gamestates/draw.o(.data);
        build/src/crash_demo.o(.data);
        build/src/gamestates/update.o(.data);
        build/src/pete.o(.data);
        build/src/special_surfaces.o(.data);
        build/src/overlay_pointers.o(.data);
        build/asm/data/sony_text.o(.data);
        build/src/cheats.o(.data);
        build/asm/data/entrance_stones.o(.data);
        build/src/camera.o(.data);
        build/src/moby_interpolation_check.o(.data);
        build/src/rand.o(.data);
        build/src/moby_helpers.o(.data);
        build/asm/collision.o(.data);
        build/asm/renderers/r_cyclorama.o(.data);
        build/src/cyclorama.o(.data);
        build/asm/moby_lists.o(.data);
        build/asm/42CC4.o(.data);
        build/asm/particle_alloc.o(.data);
        build/src/gamepad.o(.data);
        build/src/hud.o(.data);
        build/src/spu.o(.data);
        build/asm/renderers/r_particles.o(.data);
        build/src/specular_and_metal.o(.data);
        build/asm/renderers/r_flame.o(.data);
        build/src/checkpoint.o(.data);
        build/src/save_file.o(.data);
        build/asm/renderers/r_shadows.o(.data);
        build/src/4BEF8.o(.data);

        psyq_data = .;

        #ifndef _NEW_PSYQ
        /* for old psyq */

        build/asm/data/psyq.data.o(.data);

        #else

        /* for new psyq */
        build/asm/data/psyq.sqrt_tbl.o(.data);
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


        build/src/main.o(.data);
        build/src/initialization.o(.data);
        build/src/cd.o(.data);
        build/asm/order_table.o(.data);
        build/asm/memory.o(.data);
        . = ALIGN(., 4);
        main_DATA_END = .;
        main_DATA_SIZE = ABSOLUTE(main_DATA_END - main_DATA_START);
        main_SDATA_START = .;

        /* Technically, it'd be more optimal to offset this value, because you can offset it negatively in the code */
        /* But that's not what most developers did */
        _gp = .;

        build/asm/data/game.sdata.o(.sdata);
        build/src/strings.o(.sdata);
        build/asm/data/initialization.sdata.o(.sdata);
        build/src/gamestates/draw.o(.sdata);
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
        
        #ifndef _NEW_PSYQ

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

        build/asm/data/game.sbss.o(.sbss);
        . = ALIGN(., 4);
        main_SBSS_END = .;
        main_SBSS_SIZE = ABSOLUTE(main_SBSS_END - main_SBSS_START);
        main_BSS_START = .;
        build/src/strings.o(.bss);
        build/src/loaders.o(.bss);
        build/src/gamestates/draw.o(.bss);
        build/src/crash_demo.o(.bss);
        build/src/gamestates/update.o(.bss);
        build/src/pete.o(.bss);
        build/src/special_surfaces.o(.bss);
        build/src/overlay_pointers.o(.bss);

        #ifndef _NEW_PSYQ

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


        build/src/main.o(.bss);
        build/src/initialization.o(.bss);
        build/src/cd.o(.bss);
        build/asm/order_table.o(.bss);
        build/asm/memory.o(.bss);
        build/asm/math.o(.bss);
        build/asm/images.o(.bss);
        build/asm/system_time.o(.bss);
        build/asm/renderers/r_moby.o(.bss);
        build/asm/renderers/r_pete.o(.bss);
        build/asm/renderers/r_environment.o(.bss);
        build/src/environment.o(.bss);
        build/src/completion.o(.bss);
        build/src/music.o(.bss);
        build/src/cutscene.o(.bss);
        build/src/gamestates/init.o(.bss);
        build/src/cheats.o(.bss);
        build/src/camera.o(.bss);
        build/src/moby_interpolation_check.o(.bss);
        build/src/rand.o(.bss);
        build/src/moby_helpers.o(.bss);
        build/asm/collision.o(.bss);
        build/asm/renderers/r_cyclorama.o(.bss);
        build/src/cyclorama.o(.bss);
        build/asm/moby_lists.o(.bss);
        build/asm/42CC4.o(.bss);
        build/asm/particle_alloc.o(.bss);
        build/src/gamepad.o(.bss);
        build/src/hud.o(.bss);
        build/src/spu.o(.bss);
        build/asm/renderers/r_particles.o(.bss);
        build/src/specular_and_metal.o(.bss);
        build/asm/renderers/r_flame.o(.bss);
        build/src/checkpoint.o(.bss);
        build/src/save_file.o(.bss);
        build/asm/renderers/r_shadows.o(.bss);
        build/src/4BEF8.o(.bss);
        build/asm/data/game.bss.o(.bss);
        . = ALIGN(., 4);
        main_BSS_END = .;
        main_BSS_SIZE = ABSOLUTE(main_BSS_END - main_BSS_START);
    }

    . = ALIGN(., 4);

    .overlay_load_addr = .;

    /* Now it's time for the overlays */

    /* INCLUDE overlays.ld */
#include "overlays.ld"

    /* /DISCARD/ :
    {
        *(*);
    } */
}
