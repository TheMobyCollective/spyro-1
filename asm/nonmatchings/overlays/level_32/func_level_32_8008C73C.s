.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_32_8008C73C
/* 2CBE504 8008C73C 0800E003 */  jr         $ra
/* 2CBE508 8008C740 00000000 */   nop
.size func_level_32_8008C73C, . - func_level_32_8008C73C
