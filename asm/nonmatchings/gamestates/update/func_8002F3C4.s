.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002F3C4
/* 1FBC4 8002F3C4 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1FBC8 8002F3C8 1000BFAF */  sw         $ra, 0x10($sp)
/* 1FBCC 8002F3CC 47B2000C */  jal        func_8002C91C
/* 1FBD0 8002F3D0 00000000 */   nop
/* 1FBD4 8002F3D4 1000BF8F */  lw         $ra, 0x10($sp)
/* 1FBD8 8002F3D8 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1FBDC 8002F3DC 0800E003 */  jr         $ra
/* 1FBE0 8002F3E0 00000000 */   nop
.size func_8002F3C4, . - func_8002F3C4
