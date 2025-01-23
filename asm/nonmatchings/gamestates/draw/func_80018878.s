.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80018878
/* 9078 80018878 0800E003 */  jr         $ra
/* 907C 8001887C 00000000 */   nop
.size func_80018878, . - func_80018878
