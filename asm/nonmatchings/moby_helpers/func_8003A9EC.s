.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003A9EC
/* 2B1EC 8003A9EC 2130A000 */  addu       $a2, $a1, $zero
/* 2B1F0 8003A9F0 0500C014 */  bnez       $a2, .L8003AA08
/* 2B1F4 8003A9F4 21388000 */   addu      $a3, $a0, $zero
/* 2B1F8 8003A9F8 1800E28C */  lw         $v0, 0x18($a3)
/* 2B1FC 8003A9FC 00000000 */  nop
/* 2B200 8003AA00 1E004010 */  beqz       $v0, .L8003AA7C
/* 2B204 8003AA04 00000000 */   nop
.L8003AA08:
/* 2B208 8003AA08 1800E28C */  lw         $v0, 0x18($a3)
/* 2B20C 8003AA0C 0100033C */  lui        $v1, (0x10000 >> 16)
/* 2B210 8003AA10 24104300 */  and        $v0, $v0, $v1
/* 2B214 8003AA14 05004010 */  beqz       $v0, .L8003AA2C
/* 2B218 8003AA18 5000C228 */   slti      $v0, $a2, 0x50
/* 2B21C 8003AA1C 03004010 */  beqz       $v0, .L8003AA2C
/* 2B220 8003AA20 00000000 */   nop
/* 2B224 8003AA24 93EA0008 */  j          .L8003AA4C
/* 2B228 8003AA28 1000C624 */   addiu     $a2, $a2, 0x10
.L8003AA2C:
/* 2B22C 8003AA2C 2100C228 */  slti       $v0, $a2, 0x21
/* 2B230 8003AA30 03004014 */  bnez       $v0, .L8003AA40
/* 2B234 8003AA34 00000000 */   nop
/* 2B238 8003AA38 93EA0008 */  j          .L8003AA4C
/* 2B23C 8003AA3C FEFFC624 */   addiu     $a2, $a2, -0x2
.L8003AA40:
/* 2B240 8003AA40 0300C018 */  blez       $a2, .L8003AA50
/* 2B244 8003AA44 83280600 */   sra       $a1, $a2, 2
/* 2B248 8003AA48 FFFFC624 */  addiu      $a2, $a2, -0x1
.L8003AA4C:
/* 2B24C 8003AA4C 83280600 */  sra        $a1, $a2, 2
.L8003AA50:
/* 2B250 8003AA50 1800A324 */  addiu      $v1, $a1, 0x18
/* 2B254 8003AA54 001B0300 */  sll        $v1, $v1, 12
/* 2B258 8003AA58 18000224 */  addiu      $v0, $zero, 0x18
/* 2B25C 8003AA5C 23104500 */  subu       $v0, $v0, $a1
/* 2B260 8003AA60 80110200 */  sll        $v0, $v0, 6
/* 2B264 8003AA64 A000043C */  lui        $a0, 0xa0
/* 2B268 8003AA68 21104400 */  addu       $v0, $v0, $a0
/* 2B26C 8003AA6C 21186200 */  addu       $v1, $v1, $v0
/* 2B270 8003AA70 18006324 */  addiu      $v1, $v1, 0x18
/* 2B274 8003AA74 23186500 */  subu       $v1, $v1, $a1
/* 2B278 8003AA78 4C00E3AC */  sw         $v1, 0x4C($a3)
.L8003AA7C:
/* 2B27C 8003AA7C 0800E003 */  jr         $ra
/* 2B280 8003AA80 2110C000 */   addu      $v0, $a2, $zero
.size func_8003A9EC, . - func_8003A9EC
