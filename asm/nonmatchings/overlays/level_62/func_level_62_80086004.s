.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_62_80086004
/* 56D4DCC 80086004 0800E003 */  jr         $ra
/* 56D4DD0 80086008 00000000 */   nop
.size func_level_62_80086004, . - func_level_62_80086004
