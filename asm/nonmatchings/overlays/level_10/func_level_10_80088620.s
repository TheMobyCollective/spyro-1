.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_10_80088620
/* 8003E8 80088620 0800E003 */  jr         $ra
/* 8003EC 80088624 00000000 */   nop
.size func_level_10_80088620, . - func_level_10_80088620
