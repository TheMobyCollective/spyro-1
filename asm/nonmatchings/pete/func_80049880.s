.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80049880
/* 3A080 80049880 0880023C */  lui        $v0, %hi(g_Spyro + 0x1A4)
/* 3A084 80049884 FC8B428C */  lw         $v0, %lo(g_Spyro + 0x1A4)($v0)
/* 3A088 80049888 0880063C */  lui        $a2, %hi(g_Spyro + 0x1B0)
/* 3A08C 8004988C 088CC68C */  lw         $a2, %lo(g_Spyro + 0x1B0)($a2)
/* 3A090 80049890 00000000 */  nop
/* 3A094 80049894 23104600 */  subu       $v0, $v0, $a2
/* 3A098 80049898 FF0F4530 */  andi       $a1, $v0, 0xFFF
/* 3A09C 8004989C 0108A228 */  slti       $v0, $a1, 0x801
/* 3A0A0 800498A0 03004014 */  bnez       $v0, .L800498B0
/* 3A0A4 800498A4 C0210500 */   sll       $a0, $a1, 7
/* 3A0A8 800498A8 00F0A524 */  addiu      $a1, $a1, -0x1000
/* 3A0AC 800498AC C0210500 */  sll        $a0, $a1, 7
.L800498B0:
/* 3A0B0 800498B0 0880033C */  lui        $v1, %hi(g_Spyro + 0x1A8)
/* 3A0B4 800498B4 008C638C */  lw         $v1, %lo(g_Spyro + 0x1A8)($v1)
/* 3A0B8 800498B8 0880073C */  lui        $a3, %hi(g_Spyro + 0x1B4)
/* 3A0BC 800498BC 0C8CE78C */  lw         $a3, %lo(g_Spyro + 0x1B4)($a3)
/* 3A0C0 800498C0 0880023C */  lui        $v0, %hi(g_Spyro + 0x1BC)
/* 3A0C4 800498C4 148C428C */  lw         $v0, %lo(g_Spyro + 0x1BC)($v0)
/* 3A0C8 800498C8 23186700 */  subu       $v1, $v1, $a3
/* 3A0CC 800498CC FF0F6530 */  andi       $a1, $v1, 0xFFF
/* 3A0D0 800498D0 00190200 */  sll        $v1, $v0, 4
/* 3A0D4 800498D4 23208300 */  subu       $a0, $a0, $v1
/* 3A0D8 800498D8 83210400 */  sra        $a0, $a0, 6
/* 3A0DC 800498DC 21104400 */  addu       $v0, $v0, $a0
/* 3A0E0 800498E0 0880013C */  lui        $at, %hi(g_Spyro + 0x1BC)
/* 3A0E4 800498E4 148C22AC */  sw         $v0, %lo(g_Spyro + 0x1BC)($at)
/* 3A0E8 800498E8 83110200 */  sra        $v0, $v0, 6
/* 3A0EC 800498EC 2130C200 */  addu       $a2, $a2, $v0
/* 3A0F0 800498F0 0108A228 */  slti       $v0, $a1, 0x801
/* 3A0F4 800498F4 0880013C */  lui        $at, %hi(g_Spyro + 0x1B0)
/* 3A0F8 800498F8 088C26AC */  sw         $a2, %lo(g_Spyro + 0x1B0)($at)
/* 3A0FC 800498FC 03004014 */  bnez       $v0, .L8004990C
/* 3A100 80049900 C0210500 */   sll       $a0, $a1, 7
/* 3A104 80049904 00F0A524 */  addiu      $a1, $a1, -0x1000
/* 3A108 80049908 C0210500 */  sll        $a0, $a1, 7
.L8004990C:
/* 3A10C 8004990C 0880033C */  lui        $v1, %hi(g_Spyro + 0x1AC)
/* 3A110 80049910 048C638C */  lw         $v1, %lo(g_Spyro + 0x1AC)($v1)
/* 3A114 80049914 0880083C */  lui        $t0, %hi(g_Spyro + 0x1B8)
/* 3A118 80049918 108C088D */  lw         $t0, %lo(g_Spyro + 0x1B8)($t0)
/* 3A11C 8004991C 0880023C */  lui        $v0, %hi(g_Spyro + 0x1C0)
/* 3A120 80049920 188C428C */  lw         $v0, %lo(g_Spyro + 0x1C0)($v0)
/* 3A124 80049924 23186800 */  subu       $v1, $v1, $t0
/* 3A128 80049928 FF0F6530 */  andi       $a1, $v1, 0xFFF
/* 3A12C 8004992C 00190200 */  sll        $v1, $v0, 4
/* 3A130 80049930 23208300 */  subu       $a0, $a0, $v1
/* 3A134 80049934 83210400 */  sra        $a0, $a0, 6
/* 3A138 80049938 21104400 */  addu       $v0, $v0, $a0
/* 3A13C 8004993C 0880013C */  lui        $at, %hi(g_Spyro + 0x1C0)
/* 3A140 80049940 188C22AC */  sw         $v0, %lo(g_Spyro + 0x1C0)($at)
/* 3A144 80049944 83110200 */  sra        $v0, $v0, 6
/* 3A148 80049948 2118E200 */  addu       $v1, $a3, $v0
/* 3A14C 8004994C 0108A228 */  slti       $v0, $a1, 0x801
/* 3A150 80049950 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* 3A154 80049954 0C8C23AC */  sw         $v1, %lo(g_Spyro + 0x1B4)($at)
/* 3A158 80049958 02004014 */  bnez       $v0, .L80049964
/* 3A15C 8004995C 03110600 */   sra       $v0, $a2, 4
/* 3A160 80049960 00F0A524 */  addiu      $a1, $a1, -0x1000
.L80049964:
/* 3A164 80049964 0880013C */  lui        $at, %hi(g_Spyro + 0x10)
/* 3A168 80049968 688A22A0 */  sb         $v0, %lo(g_Spyro + 0x10)($at)
/* 3A16C 8004996C 03110300 */  sra        $v0, $v1, 4
/* 3A170 80049970 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* 3A174 80049974 698A22A0 */  sb         $v0, %lo(g_Spyro + 0x11)($at)
/* 3A178 80049978 0880023C */  lui        $v0, %hi(g_Spyro + 0x1C4)
/* 3A17C 8004997C 1C8C428C */  lw         $v0, %lo(g_Spyro + 0x1C4)($v0)
/* 3A180 80049980 C0190500 */  sll        $v1, $a1, 7
/* 3A184 80049984 00210200 */  sll        $a0, $v0, 4
/* 3A188 80049988 23186400 */  subu       $v1, $v1, $a0
/* 3A18C 8004998C 83190300 */  sra        $v1, $v1, 6
/* 3A190 80049990 21104300 */  addu       $v0, $v0, $v1
/* 3A194 80049994 0880013C */  lui        $at, %hi(g_Spyro + 0x1C4)
/* 3A198 80049998 1C8C22AC */  sw         $v0, %lo(g_Spyro + 0x1C4)($at)
/* 3A19C 8004999C 83110200 */  sra        $v0, $v0, 6
/* 3A1A0 800499A0 21100201 */  addu       $v0, $t0, $v0
/* 3A1A4 800499A4 0880013C */  lui        $at, %hi(g_Spyro + 0x1B8)
/* 3A1A8 800499A8 108C22AC */  sw         $v0, %lo(g_Spyro + 0x1B8)($at)
/* 3A1AC 800499AC 03110200 */  sra        $v0, $v0, 4
/* 3A1B0 800499B0 0880013C */  lui        $at, %hi(g_Spyro + 0x12)
/* 3A1B4 800499B4 6A8A22A0 */  sb         $v0, %lo(g_Spyro + 0x12)($at)
/* 3A1B8 800499B8 0800E003 */  jr         $ra
/* 3A1BC 800499BC 00000000 */   nop
.size func_80049880, . - func_80049880
