.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_64_80086264
/* 5AF602C 80086264 0800E003 */  jr         $ra
/* 5AF6030 80086268 00000000 */   nop
.size func_level_64_80086264, . - func_level_64_80086264
