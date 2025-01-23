.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_12_80085594
/* F00B5C 80085594 0800E003 */  jr         $ra
/* F00B60 80085598 00000000 */   nop
.size func_level_12_80085594, . - func_level_12_80085594
