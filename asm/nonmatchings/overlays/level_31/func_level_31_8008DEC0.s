.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_31_8008DEC0
/* 2A0CC88 8008DEC0 0800E003 */  jr         $ra
/* 2A0CC8C 8008DEC4 00000000 */   nop
.size func_level_31_8008DEC0, . - func_level_31_8008DEC0
