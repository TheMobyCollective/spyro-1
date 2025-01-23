.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_60_80085CE0
/* 51EE2A8 80085CE0 0800E003 */  jr         $ra
/* 51EE2AC 80085CE4 00000000 */   nop
.size func_level_60_80085CE0, . - func_level_60_80085CE0
