/****************************************************************************************
* OVERLAYS
****************************************************************************************/
OVERLAY main_BSS_END : NOCROSSREFS SUBALIGN(4) {

/* We run the psx.ld through the preprocessor, so we can use macros. */
#define LEVEL(overlay_id, folder) \
        /* Insert the psyq overlay id */ \
        LONG(overlay_id); \
        build/src/overlays/folder/moby.o(.rodata); \
        build/src/overlays/folder/moby.o(.rodata.jtbl); \
        build/src/overlays/folder/particle.o(.rodata); \
        build/src/overlays/folder/particle.o(.rodata.jtbl); \
        build/src/overlays/folder/terminator.o(.rodata); \
        build/src/overlays/folder/terminator.o(.rodata.jtbl); \
        build/src/overlays/folder/moby.o(.text*); \
        build/src/overlays/folder/particle.o(.text*); \
        build/src/overlays/folder/terminator.o(.text*); \
        build/src/overlays/folder/moby.o(.data*); \
        build/src/overlays/folder/particle.o(.data*); \
        build/src/overlays/folder/terminator.o(.data*); \
        build/src/overlays/folder/moby.o(.bss*); \
        build/src/overlays/folder/particle.o(.bss*); \
        build/src/overlays/folder/terminator.o(.bss*); \
        .folder##_end = .; \
        /* Pad to the sector */ \
        . = ALIGN(., 2048);

#define LEVEL_BALLOON(overlay_id, folder) \
        /* Insert the psyq overlay id */ \
        LONG(overlay_id); \
        build/src/overlays/folder/balloonist.o(.rodata.jtbl); \
        build/src/overlays/folder/balloonist.o(.rodata); \
        build/src/overlays/folder/moby.o(.rodata); \
        build/src/overlays/folder/moby.o(.rodata.jtbl); \
        build/src/overlays/folder/particle.o(.rodata); \
        build/src/overlays/folder/particle.o(.rodata.jtbl); \
        build/src/overlays/folder/terminator.o(.rodata); \
        build/src/overlays/folder/terminator.o(.rodata.jtbl); \
        build/src/overlays/folder/balloonist.o(.text*); \
        build/src/overlays/folder/moby.o(.text*); \
        build/src/overlays/folder/particle.o(.text*); \
        build/src/overlays/folder/terminator.o(.text*); \
        build/src/overlays/folder/balloonist.o(.data*); \
        build/src/overlays/folder/moby.o(.data*); \
        build/src/overlays/folder/particle.o(.data*); \
        build/src/overlays/folder/terminator.o(.data*); \
        build/src/overlays/folder/balloonist.o(.bss*); \
        build/src/overlays/folder/moby.o(.bss*); \
        build/src/overlays/folder/particle.o(.bss*); \
        build/src/overlays/folder/terminator.o(.bss*); \
        .folder##_end = .; \
        /* Pad to the sector */ \
        . = ALIGN(., 2048);

#define LEVEL_FLIGHT(overlay_id, folder) \
        /* Insert the psyq overlay id */ \
        LONG(overlay_id); \
        build/src/overlays/folder/flight.o(.rodata); \
        build/src/overlays/folder/flight.o(.rodata.jtbl); \
        build/src/overlays/folder/moby.o(.rodata); \
        build/src/overlays/folder/moby.o(.rodata.jtbl); \
        build/src/overlays/folder/particle.o(.rodata); \
        build/src/overlays/folder/particle.o(.rodata.jtbl); \
        build/src/overlays/folder/terminator.o(.rodata); \
        build/src/overlays/folder/terminator.o(.rodata.jtbl); \
        build/src/overlays/folder/flight.o(.text*); \
        build/src/overlays/folder/moby.o(.text*); \
        build/src/overlays/folder/particle.o(.text*); \
        build/src/overlays/folder/terminator.o(.text*); \
        build/src/overlays/folder/flight.o(.data*); \
        build/src/overlays/folder/moby.o(.data*); \
        build/src/overlays/folder/particle.o(.data*); \
        build/src/overlays/folder/terminator.o(.data*); \
        build/src/overlays/folder/flight.o(.bss*); \
        build/src/overlays/folder/moby.o(.bss*); \
        build/src/overlays/folder/particle.o(.bss*); \
        build/src/overlays/folder/terminator.o(.bss*); \
        .folder##_end = .; \
        /* Pad to the sector */ \
        . = ALIGN(., 2048);

    .level_10 {
        LEVEL_BALLOON(11, level_10)
    }

    .level_11 {
        LEVEL_BALLOON(12, level_11)
    }

    .level_12 {
        LEVEL(13, level_12)
    }

    .level_13 {
        LEVEL_BALLOON(14, level_13)
    }

    .level_14 {
        LEVEL(15, level_14)
    }

    .level_15 {
        LEVEL_FLIGHT(16, level_15)
    }

    .level_20 {
        LEVEL_BALLOON(17, level_20)
    }

    .level_21 {
        LEVEL_BALLOON(18, level_21)
    }

    .level_22 {
        LEVEL_BALLOON(19, level_22)
    }

    .level_23 {
        LEVEL(20, level_23)
    }

    .level_24 {
        LEVEL(21, level_24)
    }

    .level_25 {
        LEVEL_FLIGHT(22, level_25)
    }

    .level_30 {
        LEVEL_BALLOON(23, level_30)
    }

    .level_31 {
        LEVEL(24, level_31)
    }

    .level_32 {
        LEVEL(25, level_32)
    }

    .level_33 {
        LEVEL(26, level_33)
    }

    .level_34 {
        LEVEL(27, level_34)
    }

    .level_35 {
        LEVEL_FLIGHT(28, level_35)
    }

    .level_40 {
        LEVEL_BALLOON(29, level_40)
    }

    .level_41 {
        LEVEL(30, level_41)
    }

    .level_42 {
        LEVEL(31, level_42)
    }

    .level_43 {
        LEVEL(32, level_43)
    }

    .level_44 {
        LEVEL(33, level_44)
    }

    .level_45 {
        LEVEL_FLIGHT(34, level_45)
    }

    .level_50 {
        LEVEL_BALLOON(35, level_50)
    }

    .level_51 {
        LEVEL(36, level_51)
    }

    .level_52 {
        LEVEL(37, level_52)
    }

    .level_53 {
        LEVEL(38, level_53)
    }

    .level_54 {
        LEVEL(39, level_54)
    }

    .level_55 {
        LEVEL_FLIGHT(40, level_55)
    }

    .level_60 {
        LEVEL_BALLOON(41, level_60)
    }

    .level_61 {
        LEVEL(42, level_61)
    }

    .level_62 {
        LEVEL(43, level_62)
    }

    .level_63 {
        LEVEL(44, level_63)
    }

    .level_64 {
        LEVEL(45, level_64)
    }

    /* Probably level 99 here */

    .credits {
        /* Insert the psyq overlay id */
        LONG(47)
        build/src/overlays/credits.o(.rodata*);
        build/src/overlays/credits.o(.text*);
        build/src/overlays/credits.o(.data*);
        build/src/overlays/credits.o(.bss*);
        .credits_end = .;

        /* Pad to the sector */
        . = ALIGN(., 2048);
    }

    .titlescreen {
        /* Insert the psyq overlay id */
        LONG(48)
        build/src/overlays/titlescreen.o(.rodata*);
        build/src/overlays/titlescreen.o(.text*);
        build/src/overlays/titlescreen.o(.data*);
        build/src/overlays/titlescreen.o(.bss*);
        .titlescreen_end = .;

        /* Pad to the sector */
        . = ALIGN(., 2048);
    }
}

/* Symbols for unused cut levels */
    func_level_0_80082068 = 0x80082068;
    func_level_0_80080548 = 0x80080548;
    func_level_0_8007D8E0 = 0x8007D8E0;
    func_level_0_80081568 = 0x80081568;
    func_level_0_80080A0C = 0x80080A0C;
    func_level_0_8007ADB8 = 0x8007ADB8;
    func_level_0_8007AEF4 = 0x8007AEF4;
    func_level_0_8007AF38 = 0x8007AF38;
    func_level_0_8007CED8 = 0x8007CED8;
    func_level_1_8007BFF0 = 0x8007BFF0;
    func_level_1_8007B070 = 0x8007B070;
    func_level_1_8007AC8C = 0x8007AC8C;
    func_level_1_8007B8AC = 0x8007B8AC;
    func_level_1_8007B144 = 0x8007B144;
    func_level_2_8007F490 = 0x8007F490;
    func_level_2_8007D970 = 0x8007D970;
    func_level_2_8007AD08 = 0x8007AD08;
    func_level_2_8007E990 = 0x8007E990;
    func_level_2_8007DE34 = 0x8007DE34;
    func_level_3_8007C7B0 = 0x8007C7B0;
    func_level_3_8007B0AC = 0x8007B0AC;
    func_level_3_8007ACC8 = 0x8007ACC8;
    func_level_3_8007BC50 = 0x8007BC50;
    func_level_3_8007B180 = 0x8007B180;
    func_level_4_8007C204 = 0x8007C204;
    func_level_4_8007B08C = 0x8007B08C;
    func_level_4_8007ACA8 = 0x8007ACA8;
    func_level_4_8007B9F0 = 0x8007B9F0;
    func_level_4_8007B160 = 0x8007B160;
    func_level_7_8007F2F4 = 0x8007F2F4;
    func_level_7_8007D970 = 0x8007D970;
    func_level_7_8007AD08 = 0x8007AD08;
    func_level_7_8007E8E4 = 0x8007E8E4;
    func_level_7_8007DE34 = 0x8007DE34;
    func_level_9_8007C204 = 0x8007C204;
    func_level_9_8007B08C = 0x8007B08C;
    func_level_9_8007ACA8 = 0x8007ACA8;
    func_level_9_8007B9F0 = 0x8007B9F0;
    func_level_9_8007B160 = 0x8007B160;
    func_level_99_8007C654 = 0x8007C654;
    func_level_99_8007B0C0 = 0x8007B0C0;
    func_level_99_8007ACDC = 0x8007ACDC;
    func_level_99_8007BC44 = 0x8007BC44;
    func_level_99_8007B194 = 0x8007B194;