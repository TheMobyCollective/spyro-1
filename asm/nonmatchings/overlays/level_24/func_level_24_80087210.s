.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_24_80087210
/* 23897D8 80087210 0800E003 */  jr         $ra
/* 23897DC 80087214 00000000 */   nop
.size func_level_24_80087210, . - func_level_24_80087210
