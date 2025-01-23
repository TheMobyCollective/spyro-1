.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_21_8008D600
/* 1B41BC8 8008D600 0800E003 */  jr         $ra
/* 1B41BCC 8008D604 00000000 */   nop
.size func_level_21_8008D600, . - func_level_21_8008D600
