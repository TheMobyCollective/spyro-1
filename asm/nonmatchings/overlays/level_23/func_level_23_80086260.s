.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_23_80086260
/* 20A5828 80086260 0800E003 */  jr         $ra
/* 20A582C 80086264 00000000 */   nop
.size func_level_23_80086260, . - func_level_23_80086260
