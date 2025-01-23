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
    .main 0x80010000 : AT(header_END) SUBALIGN(2)
    {
        FILL(0x00000000);
        main_RODATA_START = .;
        build/asm/data/names.rodata.o(.rodata);
        build/asm/data/names.rodata.o(.rodata.jtbl);
        build/asm/data/balloonist_dialogue.rodata.o(.rodata);
        build/asm/data/balloonist_dialogue.rodata.o(.rodata.jtbl);
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
        build/asm/data/overlay_pointer.rodata.o(.rodata);
        build/asm/data/overlay_pointer.rodata.o(.rodata.jtbl);
        build/src/overlay_pointers.o(.rodata);
        build/src/overlay_pointers.o(.rodata.jtbl);

        /* for old psyq */
        build/asm/data/psyq.rodata.o(.rodata*);

        /* for new psyq */
        /* *libapi.a:*(.rdata .rdata.*)
        *libgte.a:*(.rdata .rdata.*)
        *libspu.a:*(.rdata .rdata.*)
        *libetc.a:*(.rdata .rdata.*)
        *libgpu.a:*(.rdata .rdata.*)
        *libc.a:*(.rdata .rdata.*)
        *libc2.a:*(.rdata .rdata.*)
        *libcd.a:*(.rdata .rdata.*)
        *libmcrd.a:*(.rdata .rdata.*)
        *libcard.a:*(.rdata .rdata.*)
        *libpad.a:*(.rdata .rdata.*) */

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

        /* for old psyq */
        build/asm/psyq.o(.text);

        /* for new psyq */
        /* build/asm/psyq.libsn.o(.text);
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
        *libpad.a:*(.text .text.*) */

        . = ALIGN(., 4);
        main_TEXT_END = .;
        main_TEXT_SIZE = ABSOLUTE(main_TEXT_END - main_TEXT_START);
        main_DATA_START = .;
        game_data = .;
        build/asm/data/game.data.o(.data);

        math_data = .;
        build/asm/data/math.data.o(.data);

        save_header = .;
        build/asm/data/save_header.o(.data);

        images = .;
        build/asm/images.o(.data);
        system_time = .;
        build/asm/system_time.o(.data);
        renderers_r_moby = .;
        build/asm/renderers/r_moby.o(.data);
        renderers_r_pete = .;
        build/asm/renderers/r_pete.o(.data);
        renderers_r_environment = .;
        build/asm/renderers/r_environment.o(.data);
        environment = .;
        build/src/environment.o(.data);
        completion = .;
        build/src/completion.o(.data);
        music = .;
        build/src/music.o(.data);
        gamestates_init = .;
        build/src/gamestates/init.o(.data);
        names_data = .;
        build/asm/data/names.data.o(.data);
        balloonist_dialogue_data = .;
        build/asm/data/balloonist_dialogue.data.o(.data);
        loaders = .;
        build/src/loaders.o(.data);
        gamestates_draw = .;
        build/src/gamestates/draw.o(.data);
        crash_demo = .;
        build/src/crash_demo.o(.data);
        gamestates_update = .;
        build/src/gamestates/update.o(.data);
        pete = .;
        build/src/pete.o(.data);
        special_surfaces = .;
        build/src/special_surfaces.o(.data);
        overlay_pointer_rodata = .;
        build/asm/data/overlay_pointer.rodata.o(.data);
        overlay_pointers = .;
        build/src/overlay_pointers.o(.data);
        sony_text = .;
        build/asm/data/sony_text.o(.data);
        cheats_data = .;
        build/src/cheats.o(.data);
        build/asm/data/cheats.data.o(.data);
        camera = .;
        build/src/camera.o(.data);
        moby_interpolation_check = .;
        build/src/moby_interpolation_check.o(.data);
        build/src/rand.o(.data);
        moby_helpers = .;
        build/src/moby_helpers.o(.data);
        collision = .;
        build/asm/collision.o(.data);
        renderers_r_cyclorama = .;
        build/asm/renderers/r_cyclorama.o(.data);
        cyclorama = .;
        build/src/cyclorama.o(.data);
        moby_lists = .;
        build/asm/moby_lists.o(.data);
        _42CC4 = .;
        build/asm/42CC4.o(.data);
        particle_alloc = .;
        build/asm/particle_alloc.o(.data);
        gamepad = .;
        build/src/gamepad.o(.data);
        hud = .;
        build/src/hud.o(.data);
        _spu = .;
        build/src/spu.o(.data);
        renderers_r_particles = .;
        build/asm/renderers/r_particles.o(.data);
        specular_and_metal = .;
        build/src/specular_and_metal.o(.data);
        renderers_r_flame = .;
        build/asm/renderers/r_flame.o(.data);
        checkpoint = .;
        build/src/checkpoint.o(.data);
        save_file = .;
        build/src/save_file.o(.data);
        renderers_r_shadows = .;
        build/asm/renderers/r_shadows.o(.data);
        _4BEF8 = .;
        build/src/4BEF8.o(.data);
        psyq_data = .;

        /* for old psyq */

        build/asm/data/psyq.data.o(.data);

        /* for new psyq */
        /* build/asm/data/psyq.sqrt_tbl.o(.data);
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
        *libpad.a:*(.data .data.*) */


        build/src/main.o(.data);
        initialization = .;
        build/src/initialization.o(.data);
        cd = .;
        build/src/cd.o(.data);
        order_table = .;
        build/asm/order_table.o(.data);
        memory = .;
        build/asm/memory.o(.data);
        . = ALIGN(., 4);
        main_DATA_END = .;
        main_DATA_SIZE = ABSOLUTE(main_DATA_END - main_DATA_START);
        main_SDATA_START = .;

        /* Technically, it'd be more optimal to offset this value, because you can offset it negatively in the code */
        /* But that's not what most developers did */
        _gp = .;

        build/asm/data/game.sdata.o(.sdata);
        build/asm/data/names.sdata.o(.sdata);
        build/asm/data/balloonist_dialogue.sdata.o(.sdata);
        build/asm/data/initialization.sdata.o(.sdata);
        build/asm/data/gamestates/draw.sdata.o(.sdata);
        . = ALIGN(., 4);
        main_SDATA_END = .;
        main_SDATA_SIZE = ABSOLUTE(main_SDATA_END - main_SDATA_START);

        /* Padding for the .exe */
        . = ALIGN(., 2048);
    }

    .main_bss main_SDATA_END (NOLOAD) : AT(main_SDATA_END) SUBALIGN(2)
    {
        FILL(0x00000000);
        main_SBSS_START = .;

        /* for old psyq */
        build/asm/data/psyq.sbss.o(.sbss);

        /* for new psyq */
        /* *libapi.a:*(.sbss .sbss.*)
        *libgte.a:*(.sbss .sbss.*)
        *libspu.a:*(.sbss .sbss.*)
        *libetc.a:*(.sbss .sbss.*)
        *libgpu.a:*(.sbss .sbss.*)
        *libc.a:*(.sbss .sbss.*)
        *libc2.a:*(.sbss .sbss.*)
        *libcd.a:*(.sbss .sbss.*)
        *libmcrd.a:*(.sbss .sbss.*)
        *libcard.a:*(.sbss .sbss.*)
        *libpad.a:*(.sbss .sbss.*) */

        build/asm/data/game.sbss.o(.sbss);
        . = ALIGN(., 4);
        main_SBSS_END = .;
        main_SBSS_SIZE = ABSOLUTE(main_SBSS_END - main_SBSS_START);
        main_BSS_START = .;
        build/asm/data/names.rodata.o(.bss);
        build/asm/data/balloonist_dialogue.rodata.o(.bss);
        build/src/loaders.o(.bss);
        build/src/gamestates/draw.o(.bss);
        build/src/crash_demo.o(.bss);
        build/src/gamestates/update.o(.bss);
        build/src/pete.o(.bss);
        build/src/special_surfaces.o(.bss);
        build/asm/data/overlay_pointer.rodata.o(.bss);
        build/src/overlay_pointers.o(.bss);

        /* for old psyq */
        build/asm/data/psyq.bss.o(.bss);

        /* for new psyq */
        /* *libapi.a:*(.bss .bss.*)
        *libgte.a:*(.bss .bss.*)
        *libspu.a:*(.bss .bss.*)
        *libetc.a:*(.bss .bss.*)
        *libgpu.a:*(.bss .bss.*)
        *libc.a:*(.bss .bss.*)
        *libc2.a:*(.bss .bss.*)
        *libcd.a:*(.bss .bss.*)
        *libmcrd.a:*(.bss .bss.*)
        *libcard.a:*(.bss .bss.*)
        *libpad.a:*(.bss .bss.*) */


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

    INCLUDE overlays.ld

    /* /DISCARD/ :
    {
        *(*);
    } */
}
