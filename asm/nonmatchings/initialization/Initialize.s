.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel Initialize
/* 2FC0 800127C0 B8FFBD27 */  addiu      $sp, $sp, -0x48
/* 2FC4 800127C4 4000BFAF */  sw         $ra, 0x40($sp)
/* 2FC8 800127C8 3C00B5AF */  sw         $s5, 0x3C($sp)
/* 2FCC 800127CC 3800B4AF */  sw         $s4, 0x38($sp)
/* 2FD0 800127D0 3400B3AF */  sw         $s3, 0x34($sp)
/* 2FD4 800127D4 3000B2AF */  sw         $s2, 0x30($sp)
/* 2FD8 800127D8 2C00B1AF */  sw         $s1, 0x2C($sp)
/* 2FDC 800127DC AA48000C */  jal        GraphicsInitialize
/* 2FE0 800127E0 2800B0AF */   sw        $s0, 0x28($sp)
/* 2FE4 800127E4 1849000C */  jal        MemoryCardInitialize
/* 2FE8 800127E8 21880000 */   addu      $s1, $zero, $zero
/* 2FEC 800127EC F248000C */  jal        GamepadInitialize
/* 2FF0 800127F0 20FF1224 */   addiu     $s2, $zero, -0xE0
/* 2FF4 800127F4 5756010C */  jal        SpuInitialize
/* 2FF8 800127F8 00000000 */   nop
/* 2FFC 800127FC 2049000C */  jal        CDInitialize
/* 3000 80012800 00000000 */   nop
/* 3004 80012804 5B49000C */  jal        MusicInitialize
/* 3008 80012808 00000000 */   nop
/* 300C 8001280C D488010C */  jal        InitGeom
/* 3010 80012810 00000000 */   nop
/* 3014 80012814 00010424 */  addiu      $a0, $zero, 0x100
/* 3018 80012818 8689010C */  jal        SetGeomOffset
/* 301C 8001281C 78000524 */   addiu     $a1, $zero, 0x78
/* 3020 80012820 8E89010C */  jal        SetGeomScreen
/* 3024 80012824 55010424 */   addiu     $a0, $zero, 0x155
/* 3028 80012828 0880103C */  lui        $s0, %hi(D_800785D8)
/* 302C 8001282C D8851026 */  addiu      $s0, $s0, %lo(D_800785D8)
/* 3030 80012830 0880023C */  lui        $v0, %hi(func_titlescreen_8007DDE8)
/* 3034 80012834 E8DD4224 */  addiu      $v0, $v0, %lo(func_titlescreen_8007DDE8)
/* 3038 80012838 000002AE */  sw         $v0, 0x0($s0)
/* 303C 8001283C 0880013C */  lui        $at, %hi(D_800785DC)
/* 3040 80012840 DC8522AC */  sw         $v0, %lo(D_800785DC)($at)
/* 3044 80012844 F176010C */  jal        VSync
/* 3048 80012848 FFFF0424 */   addiu     $a0, $zero, -0x1
/* 304C 8001284C 21A04000 */  addu       $s4, $v0, $zero
/* 3050 80012850 B27D010C */  jal        SetDispMask
/* 3054 80012854 21200000 */   addu      $a0, $zero, $zero
/* 3058 80012858 21280000 */  addu       $a1, $zero, $zero
/* 305C 8001285C 0500063C */  lui        $a2, (0x5A000 >> 16)
/* 3060 80012860 0000048E */  lw         $a0, 0x0($s0)
/* 3064 80012864 01000224 */  addiu      $v0, $zero, 0x1
/* 3068 80012868 0780013C */  lui        $at, %hi(g_DB + 0x6D)
/* 306C 8001286C 4D6F22A0 */  sb         $v0, %lo(g_DB + 0x6D)($at)
/* 3070 80012870 0780013C */  lui        $at, %hi(g_DB + 0xF1)
/* 3074 80012874 D16F22A0 */  sb         $v0, %lo(g_DB + 0xF1)($at)
/* 3078 80012878 455A000C */  jal        Memset
/* 307C 8001287C 00A0C634 */   ori       $a2, $a2, (0x5A000 & 0xFFFF)
.L80012880:
/* 3080 80012880 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* 3084 80012884 F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* 3088 80012888 0000058E */  lw         $a1, 0x0($s0)
/* 308C 8001288C C95F000C */  jal        func_80017F24
/* 3090 80012890 21304002 */   addu      $a2, $s2, $zero
/* 3094 80012894 1800A427 */  addiu      $a0, $sp, 0x18
/* 3098 80012898 0000058E */  lw         $a1, 0x0($s0)
/* 309C 8001289C 00030224 */  addiu      $v0, $zero, 0x300
/* 30A0 800128A0 1C00A2A7 */  sh         $v0, 0x1C($sp)
/* 30A4 800128A4 F0000224 */  addiu      $v0, $zero, 0xF0
/* 30A8 800128A8 1800A0A7 */  sh         $zero, 0x18($sp)
/* 30AC 800128AC 1A00A0A7 */  sh         $zero, 0x1A($sp)
/* 30B0 800128B0 8A7E010C */  jal        LoadImage
/* 30B4 800128B4 1E00A2A7 */   sh        $v0, 0x1E($sp)
/* 30B8 800128B8 D97D010C */  jal        DrawSync
/* 30BC 800128BC 21200000 */   addu      $a0, $zero, $zero
/* 30C0 800128C0 F176010C */  jal        VSync
/* 30C4 800128C4 21200000 */   addu      $a0, $zero, $zero
/* 30C8 800128C8 0780043C */  lui        $a0, %hi(g_DB + 0xE0)
/* 30CC 800128CC C06F8424 */  addiu      $a0, $a0, %lo(g_DB + 0xE0)
/* 30D0 800128D0 0C80010C */  jal        PutDispEnv
/* 30D4 800128D4 00000000 */   nop
/* 30D8 800128D8 03002016 */  bnez       $s1, .L800128E8
/* 30DC 800128DC 00000000 */   nop
/* 30E0 800128E0 B27D010C */  jal        SetDispMask
/* 30E4 800128E4 01000424 */   addiu     $a0, $zero, 0x1
.L800128E8:
/* 30E8 800128E8 01003126 */  addiu      $s1, $s1, 0x1
/* 30EC 800128EC 0800222A */  slti       $v0, $s1, 0x8
/* 30F0 800128F0 E3FF4014 */  bnez       $v0, .L80012880
/* 30F4 800128F4 20005226 */   addiu     $s2, $s2, 0x20
/* 30F8 800128F8 4349000C */  jal        WadInitialize
/* 30FC 800128FC 58021024 */   addiu     $s0, $zero, 0x258
/* 3100 80012900 00080624 */  addiu      $a2, $zero, 0x800
/* 3104 80012904 0780113C */  lui        $s1, %hi(D_80076B90)
/* 3108 80012908 906B3126 */  addiu      $s1, $s1, %lo(D_80076B90)
/* 310C 8001290C 0880133C */  lui        $s3, %hi(D_8007A6E8)
/* 3110 80012910 E8A67326 */  addiu      $s3, $s3, %lo(D_8007A6E8)
/* 3114 80012914 0000248E */  lw         $a0, 0x0($s1)
/* 3118 80012918 0000678E */  lw         $a3, 0x0($s3)
/* 311C 8001291C 0180053C */  lui        $a1, %hi(D_800113A0)
/* 3120 80012920 A013A58C */  lw         $a1, %lo(D_800113A0)($a1)
/* 3124 80012924 4059000C */  jal        CDLoadSync
/* 3128 80012928 1000B0AF */   sw        $s0, 0x10($sp)
/* 312C 8001292C 0780123C */  lui        $s2, %hi(D_80076C00)
/* 3130 80012930 006C5226 */  addiu      $s2, $s2, %lo(D_80076C00)
/* 3134 80012934 21204002 */  addu       $a0, $s2, $zero
/* 3138 80012938 0180053C */  lui        $a1, %hi(D_800113A0)
/* 313C 8001293C A013A58C */  lw         $a1, %lo(D_800113A0)($a1)
/* 3140 80012940 565A000C */  jal        Memcpy
/* 3144 80012944 D0010624 */   addiu     $a2, $zero, 0x1D0
/* 3148 80012948 0400063C */  lui        $a2, (0x40000 >> 16)
/* 314C 8001294C 0000248E */  lw         $a0, 0x0($s1)
/* 3150 80012950 0780033C */  lui        $v1, %hi(_stacksize)
/* 3154 80012954 A455638C */  lw         $v1, %lo(_stacksize)($v1)
/* 3158 80012958 1C80023C */  lui        $v0, (0x801C0000 >> 16)
/* 315C 8001295C 1000B0AF */  sw         $s0, 0x10($sp)
/* 3160 80012960 0000678E */  lw         $a3, 0x0($s3)
/* 3164 80012964 23A84300 */  subu       $s5, $v0, $v1
/* 3168 80012968 0000428E */  lw         $v0, 0x0($s2)
/* 316C 8001296C 2128A002 */  addu       $a1, $s5, $zero
/* 3170 80012970 4059000C */  jal        CDLoadSync
/* 3174 80012974 21384700 */   addu      $a3, $v0, $a3
/* 3178 80012978 0000248E */  lw         $a0, 0x0($s1)
/* 317C 8001297C 0880063C */  lui        $a2, %hi(D_8007A6E4)
/* 3180 80012980 E4A6C68C */  lw         $a2, %lo(D_8007A6E4)($a2)
/* 3184 80012984 0880073C */  lui        $a3, %hi(D_8007A6E0)
/* 3188 80012988 E0A6E78C */  lw         $a3, %lo(D_8007A6E0)($a3)
/* 318C 8001298C 0180053C */  lui        $a1, %hi(D_800113A0)
/* 3190 80012990 A013A58C */  lw         $a1, %lo(D_800113A0)($a1)
/* 3194 80012994 4059000C */  jal        CDLoadSync
/* 3198 80012998 1000B0AF */   sw        $s0, 0x10($sp)
/* 319C 8001299C 0000248E */  lw         $a0, 0x0($s1)
/* 31A0 800129A0 0880063C */  lui        $a2, %hi(D_8007A6D4)
/* 31A4 800129A4 D4A6C68C */  lw         $a2, %lo(D_8007A6D4)($a2)
/* 31A8 800129A8 0880073C */  lui        $a3, %hi(D_8007A6D0)
/* 31AC 800129AC D0A6E78C */  lw         $a3, %lo(D_8007A6D0)($a3)
/* 31B0 800129B0 0880023C */  lui        $v0, %hi(D_8007A6D4)
/* 31B4 800129B4 D4A6428C */  lw         $v0, %lo(D_8007A6D4)($v0)
/* 31B8 800129B8 1000B0AF */  sw         $s0, 0x10($sp)
/* 31BC 800129BC 2398A202 */  subu       $s3, $s5, $v0
/* 31C0 800129C0 4059000C */  jal        CDLoadSync
/* 31C4 800129C4 21286002 */   addu      $a1, $s3, $zero
.L800129C8:
/* 31C8 800129C8 F176010C */  jal        VSync
/* 31CC 800129CC FFFF0424 */   addiu     $a0, $zero, -0x1
/* 31D0 800129D0 23105400 */  subu       $v0, $v0, $s4
/* 31D4 800129D4 D2004228 */  slti       $v0, $v0, 0xD2
/* 31D8 800129D8 05004010 */  beqz       $v0, .L800129F0
/* 31DC 800129DC 21280000 */   addu      $a1, $zero, $zero
/* 31E0 800129E0 F176010C */  jal        VSync
/* 31E4 800129E4 21200000 */   addu      $a0, $zero, $zero
/* 31E8 800129E8 724A0008 */  j          .L800129C8
/* 31EC 800129EC 00000000 */   nop
.L800129F0:
/* 31F0 800129F0 0880023C */  lui        $v0, %hi(D_800785D8)
/* 31F4 800129F4 D8854224 */  addiu      $v0, $v0, %lo(D_800785D8)
/* 31F8 800129F8 0000448C */  lw         $a0, 0x0($v0)
/* 31FC 800129FC 0500063C */  lui        $a2, (0x5A000 >> 16)
/* 3200 80012A00 00A0C634 */  ori        $a2, $a2, (0x5A000 & 0xFFFF)
/* 3204 80012A04 455A000C */  jal        Memset
/* 3208 80012A08 21884000 */   addu      $s1, $v0, $zero
/* 320C 80012A0C 21800000 */  addu       $s0, $zero, $zero
.L80012A10:
/* 3210 80012A10 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* 3214 80012A14 F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* 3218 80012A18 01001026 */  addiu      $s0, $s0, 0x1
/* 321C 80012A1C 23301000 */  negu       $a2, $s0
/* 3220 80012A20 0000258E */  lw         $a1, 0x0($s1)
/* 3224 80012A24 C95F000C */  jal        func_80017F24
/* 3228 80012A28 40310600 */   sll       $a2, $a2, 5
/* 322C 80012A2C 1800A427 */  addiu      $a0, $sp, 0x18
/* 3230 80012A30 0000258E */  lw         $a1, 0x0($s1)
/* 3234 80012A34 00030224 */  addiu      $v0, $zero, 0x300
/* 3238 80012A38 1C00A2A7 */  sh         $v0, 0x1C($sp)
/* 323C 80012A3C F0000224 */  addiu      $v0, $zero, 0xF0
/* 3240 80012A40 1800A0A7 */  sh         $zero, 0x18($sp)
/* 3244 80012A44 1A00A0A7 */  sh         $zero, 0x1A($sp)
/* 3248 80012A48 8A7E010C */  jal        LoadImage
/* 324C 80012A4C 1E00A2A7 */   sh        $v0, 0x1E($sp)
/* 3250 80012A50 D97D010C */  jal        DrawSync
/* 3254 80012A54 21200000 */   addu      $a0, $zero, $zero
/* 3258 80012A58 F176010C */  jal        VSync
/* 325C 80012A5C 21200000 */   addu      $a0, $zero, $zero
/* 3260 80012A60 0780043C */  lui        $a0, %hi(g_DB + 0xE0)
/* 3264 80012A64 C06F8424 */  addiu      $a0, $a0, %lo(g_DB + 0xE0)
/* 3268 80012A68 0C80010C */  jal        PutDispEnv
/* 326C 80012A6C 00000000 */   nop
/* 3270 80012A70 0800022A */  slti       $v0, $s0, 0x8
/* 3274 80012A74 E6FF4014 */  bnez       $v0, .L80012A10
/* 3278 80012A78 00000000 */   nop
/* 327C 80012A7C F176010C */  jal        VSync
/* 3280 80012A80 FFFF0424 */   addiu     $a0, $zero, -0x1
/* 3284 80012A84 21A04000 */  addu       $s4, $v0, $zero
/* 3288 80012A88 FAFF103C */  lui        $s0, (0xFFFA6000 >> 16)
/* 328C 80012A8C 00601036 */  ori        $s0, $s0, (0xFFFA6000 & 0xFFFF)
/* 3290 80012A90 21807002 */  addu       $s0, $s3, $s0
/* 3294 80012A94 21200002 */  addu       $a0, $s0, $zero
/* 3298 80012A98 21280000 */  addu       $a1, $zero, $zero
/* 329C 80012A9C 0500063C */  lui        $a2, (0x5A000 >> 16)
/* 32A0 80012AA0 455A000C */  jal        Memset
/* 32A4 80012AA4 00A0C634 */   ori       $a2, $a2, (0x5A000 & 0xFFFF)
/* 32A8 80012AA8 21900000 */  addu       $s2, $zero, $zero
/* 32AC 80012AAC 20FF1124 */  addiu      $s1, $zero, -0xE0
/* 32B0 80012AB0 21206002 */  addu       $a0, $s3, $zero
.L80012AB4:
/* 32B4 80012AB4 21280002 */  addu       $a1, $s0, $zero
/* 32B8 80012AB8 C95F000C */  jal        func_80017F24
/* 32BC 80012ABC 21302002 */   addu      $a2, $s1, $zero
/* 32C0 80012AC0 1800A427 */  addiu      $a0, $sp, 0x18
/* 32C4 80012AC4 21280002 */  addu       $a1, $s0, $zero
/* 32C8 80012AC8 00030224 */  addiu      $v0, $zero, 0x300
/* 32CC 80012ACC 1C00A2A7 */  sh         $v0, 0x1C($sp)
/* 32D0 80012AD0 F0000224 */  addiu      $v0, $zero, 0xF0
/* 32D4 80012AD4 1800A0A7 */  sh         $zero, 0x18($sp)
/* 32D8 80012AD8 1A00A0A7 */  sh         $zero, 0x1A($sp)
/* 32DC 80012ADC 8A7E010C */  jal        LoadImage
/* 32E0 80012AE0 1E00A2A7 */   sh        $v0, 0x1E($sp)
/* 32E4 80012AE4 D97D010C */  jal        DrawSync
/* 32E8 80012AE8 21200000 */   addu      $a0, $zero, $zero
/* 32EC 80012AEC F176010C */  jal        VSync
/* 32F0 80012AF0 21200000 */   addu      $a0, $zero, $zero
/* 32F4 80012AF4 0780043C */  lui        $a0, %hi(g_DB + 0xE0)
/* 32F8 80012AF8 C06F8424 */  addiu      $a0, $a0, %lo(g_DB + 0xE0)
/* 32FC 80012AFC 0C80010C */  jal        PutDispEnv
/* 3300 80012B00 20003126 */   addiu     $s1, $s1, 0x20
/* 3304 80012B04 01005226 */  addiu      $s2, $s2, 0x1
/* 3308 80012B08 0800422A */  slti       $v0, $s2, 0x8
/* 330C 80012B0C E9FF4014 */  bnez       $v0, .L80012AB4
/* 3310 80012B10 21206002 */   addu      $a0, $s3, $zero
/* 3314 80012B14 03000224 */  addiu      $v0, $zero, 0x3
/* 3318 80012B18 0780013C */  lui        $at, %hi(g_LoadStage)
/* 331C 80012B1C 645822AC */  sw         $v0, %lo(g_LoadStage)($at)
/* 3320 80012B20 0780013C */  lui        $at, %hi(D_8007566C)
/* 3324 80012B24 6C5620AC */  sw         $zero, %lo(D_8007566C)($at)
.L80012B28:
/* 3328 80012B28 5951000C */  jal        func_80014564
/* 332C 80012B2C 00000000 */   nop
/* 3330 80012B30 0780023C */  lui        $v0, %hi(g_LoadStage)
/* 3334 80012B34 6458428C */  lw         $v0, %lo(g_LoadStage)($v0)
/* 3338 80012B38 00000000 */  nop
/* 333C 80012B3C 0A004228 */  slti       $v0, $v0, 0xA
/* 3340 80012B40 F9FF4014 */  bnez       $v0, .L80012B28
/* 3344 80012B44 00000000 */   nop
.L80012B48:
/* 3348 80012B48 F176010C */  jal        VSync
/* 334C 80012B4C FFFF0424 */   addiu     $a0, $zero, -0x1
/* 3350 80012B50 23105400 */  subu       $v0, $v0, $s4
/* 3354 80012B54 D2004228 */  slti       $v0, $v0, 0xD2
/* 3358 80012B58 05004010 */  beqz       $v0, .L80012B70
/* 335C 80012B5C FAFF023C */   lui       $v0, (0xFFFA6000 >> 16)
/* 3360 80012B60 F176010C */  jal        VSync
/* 3364 80012B64 21200000 */   addu      $a0, $zero, $zero
/* 3368 80012B68 D24A0008 */  j          .L80012B48
/* 336C 80012B6C 00000000 */   nop
.L80012B70:
/* 3370 80012B70 21800000 */  addu       $s0, $zero, $zero
/* 3374 80012B74 00604234 */  ori        $v0, $v0, (0xFFFA6000 & 0xFFFF)
/* 3378 80012B78 21886202 */  addu       $s1, $s3, $v0
.L80012B7C:
/* 337C 80012B7C 21206002 */  addu       $a0, $s3, $zero
/* 3380 80012B80 21282002 */  addu       $a1, $s1, $zero
/* 3384 80012B84 01001026 */  addiu      $s0, $s0, 0x1
/* 3388 80012B88 23301000 */  negu       $a2, $s0
/* 338C 80012B8C C95F000C */  jal        func_80017F24
/* 3390 80012B90 40310600 */   sll       $a2, $a2, 5
/* 3394 80012B94 1800A427 */  addiu      $a0, $sp, 0x18
/* 3398 80012B98 21282002 */  addu       $a1, $s1, $zero
/* 339C 80012B9C 00030224 */  addiu      $v0, $zero, 0x300
/* 33A0 80012BA0 1C00A2A7 */  sh         $v0, 0x1C($sp)
/* 33A4 80012BA4 F0000224 */  addiu      $v0, $zero, 0xF0
/* 33A8 80012BA8 1800A0A7 */  sh         $zero, 0x18($sp)
/* 33AC 80012BAC 1A00A0A7 */  sh         $zero, 0x1A($sp)
/* 33B0 80012BB0 8A7E010C */  jal        LoadImage
/* 33B4 80012BB4 1E00A2A7 */   sh        $v0, 0x1E($sp)
/* 33B8 80012BB8 D97D010C */  jal        DrawSync
/* 33BC 80012BBC 21200000 */   addu      $a0, $zero, $zero
/* 33C0 80012BC0 F176010C */  jal        VSync
/* 33C4 80012BC4 21200000 */   addu      $a0, $zero, $zero
/* 33C8 80012BC8 0780043C */  lui        $a0, %hi(g_DB + 0xE0)
/* 33CC 80012BCC C06F8424 */  addiu      $a0, $a0, %lo(g_DB + 0xE0)
/* 33D0 80012BD0 0C80010C */  jal        PutDispEnv
/* 33D4 80012BD4 00000000 */   nop
/* 33D8 80012BD8 0800022A */  slti       $v0, $s0, 0x8
/* 33DC 80012BDC E7FF4014 */  bnez       $v0, .L80012B7C
/* 33E0 80012BE0 00000000 */   nop
/* 33E4 80012BE4 B27D010C */  jal        SetDispMask
/* 33E8 80012BE8 21200000 */   addu      $a0, $zero, $zero
/* 33EC 80012BEC 0780023C */  lui        $v0, %hi(g_DB + 0x6D)
/* 33F0 80012BF0 4D6F4224 */  addiu      $v0, $v0, %lo(g_DB + 0x6D)
/* 33F4 80012BF4 000040A0 */  sb         $zero, 0x0($v0)
/* 33F8 80012BF8 0780013C */  lui        $at, %hi(g_DB + 0xF1)
/* 33FC 80012BFC D16F20A0 */  sb         $zero, %lo(g_DB + 0xF1)($at)
/* 3400 80012C00 0C80010C */  jal        PutDispEnv
/* 3404 80012C04 73004424 */   addiu     $a0, $v0, 0x73
/* 3408 80012C08 2000A427 */  addiu      $a0, $sp, 0x20
/* 340C 80012C0C 21280000 */  addu       $a1, $zero, $zero
/* 3410 80012C10 21300000 */  addu       $a2, $zero, $zero
/* 3414 80012C14 21380000 */  addu       $a3, $zero, $zero
/* 3418 80012C18 00021024 */  addiu      $s0, $zero, 0x200
/* 341C 80012C1C E0010224 */  addiu      $v0, $zero, 0x1E0
/* 3420 80012C20 2000A0A7 */  sh         $zero, 0x20($sp)
/* 3424 80012C24 2200A0A7 */  sh         $zero, 0x22($sp)
/* 3428 80012C28 2400B0A7 */  sh         $s0, 0x24($sp)
/* 342C 80012C2C 3E7E010C */  jal        ClearImage
/* 3430 80012C30 2600A2A7 */   sh        $v0, 0x26($sp)
/* 3434 80012C34 D97D010C */  jal        DrawSync
/* 3438 80012C38 21200000 */   addu      $a0, $zero, $zero
/* 343C 80012C3C B27D010C */  jal        SetDispMask
/* 3440 80012C40 01000424 */   addiu     $a0, $zero, 0x1
/* 3444 80012C44 1800A427 */  addiu      $a0, $sp, 0x18
/* 3448 80012C48 2128A002 */  addu       $a1, $s5, $zero
/* 344C 80012C4C 00010224 */  addiu      $v0, $zero, 0x100
/* 3450 80012C50 1800B0A7 */  sh         $s0, 0x18($sp)
/* 3454 80012C54 1A00A0A7 */  sh         $zero, 0x1A($sp)
/* 3458 80012C58 1C00B0A7 */  sh         $s0, 0x1C($sp)
/* 345C 80012C5C 8A7E010C */  jal        LoadImage
/* 3460 80012C60 1E00A2A7 */   sh        $v0, 0x1E($sp)
/* 3464 80012C64 D97D010C */  jal        DrawSync
/* 3468 80012C68 21200000 */   addu      $a0, $zero, $zero
/* 346C 80012C6C 0780033C */  lui        $v1, %hi(_stacksize)
/* 3470 80012C70 A455638C */  lw         $v1, %lo(_stacksize)($v1)
/* 3474 80012C74 2080023C */  lui        $v0, (0x80200000 >> 16)
/* 3478 80012C78 23104300 */  subu       $v0, $v0, $v1
/* 347C 80012C7C 0880013C */  lui        $at, %hi(D_800785FC)
/* 3480 80012C80 FC8522AC */  sw         $v0, %lo(D_800785FC)($at)
/* 3484 80012C84 F66D010C */  jal        func_8005B7D8
/* 3488 80012C88 00000000 */   nop
/* 348C 80012C8C CEB4000C */  jal        func_8002D338
/* 3490 80012C90 00000000 */   nop
/* 3494 80012C94 0F000224 */  addiu      $v0, $zero, 0xF
/* 3498 80012C98 0780013C */  lui        $at, %hi(D_80075918)
/* 349C 80012C9C 185922AC */  sw         $v0, %lo(D_80075918)($at)
/* 34A0 80012CA0 5CB4000C */  jal        func_8002D170
/* 34A4 80012CA4 00000000 */   nop
/* 34A8 80012CA8 02000224 */  addiu      $v0, $zero, 0x2
/* 34AC 80012CAC 0780013C */  lui        $at, %hi(g_DeltaTime)
/* 34B0 80012CB0 CC5622AC */  sw         $v0, %lo(g_DeltaTime)($at)
/* 34B4 80012CB4 00800234 */  ori        $v0, $zero, 0x8000
/* 34B8 80012CB8 0780013C */  lui        $at, %hi(g_UnprocessedFrames)
/* 34BC 80012CBC 605720AC */  sw         $zero, %lo(g_UnprocessedFrames)($at)
/* 34C0 80012CC0 0880013C */  lui        $at, %hi(g_Environment + 0x24)
/* 34C4 80012CC4 CC8522AC */  sw         $v0, %lo(g_Environment + 0x24)($at)
/* 34C8 80012CC8 4000BF8F */  lw         $ra, 0x40($sp)
/* 34CC 80012CCC 3C00B58F */  lw         $s5, 0x3C($sp)
/* 34D0 80012CD0 3800B48F */  lw         $s4, 0x38($sp)
/* 34D4 80012CD4 3400B38F */  lw         $s3, 0x34($sp)
/* 34D8 80012CD8 3000B28F */  lw         $s2, 0x30($sp)
/* 34DC 80012CDC 2C00B18F */  lw         $s1, 0x2C($sp)
/* 34E0 80012CE0 2800B08F */  lw         $s0, 0x28($sp)
/* 34E4 80012CE4 4800BD27 */  addiu      $sp, $sp, 0x48
/* 34E8 80012CE8 0800E003 */  jr         $ra
/* 34EC 80012CEC 00000000 */   nop
.size Initialize, . - Initialize
