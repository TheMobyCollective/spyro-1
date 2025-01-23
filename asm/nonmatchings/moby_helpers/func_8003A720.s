.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003A720
/* 2AF20 8003A720 10000224 */  addiu      $v0, $zero, 0x10
/* 2AF24 8003A724 FF000324 */  addiu      $v1, $zero, 0xFF
/* 2AF28 8003A728 500082A0 */  sb         $v0, 0x50($a0)
/* 2AF2C 8003A72C 04000224 */  addiu      $v0, $zero, 0x4
/* 2AF30 8003A730 470082A0 */  sb         $v0, 0x47($a0)
/* 2AF34 8003A734 01000224 */  addiu      $v0, $zero, 0x1
/* 2AF38 8003A738 20000524 */  addiu      $a1, $zero, 0x20
/* 2AF3C 8003A73C 3F0082A0 */  sb         $v0, 0x3F($a0)
/* 2AF40 8003A740 7F000224 */  addiu      $v0, $zero, 0x7F
/* 2AF44 8003A744 520083A0 */  sb         $v1, 0x52($a0)
/* 2AF48 8003A748 480080A0 */  sb         $zero, 0x48($a0)
/* 2AF4C 8003A74C 490080A0 */  sb         $zero, 0x49($a0)
/* 2AF50 8003A750 3C0080A0 */  sb         $zero, 0x3C($a0)
/* 2AF54 8003A754 3D0080A0 */  sb         $zero, 0x3D($a0)
/* 2AF58 8003A758 3E0080A0 */  sb         $zero, 0x3E($a0)
/* 2AF5C 8003A75C 400080A0 */  sb         $zero, 0x40($a0)
/* 2AF60 8003A760 410085A0 */  sb         $a1, 0x41($a0)
/* 2AF64 8003A764 430083A0 */  sb         $v1, 0x43($a0)
/* 2AF68 8003A768 4A0083A0 */  sb         $v1, 0x4A($a0)
/* 2AF6C 8003A76C 530083A0 */  sb         $v1, 0x53($a0)
/* 2AF70 8003A770 180080AC */  sw         $zero, 0x18($a0)
/* 2AF74 8003A774 440080A0 */  sb         $zero, 0x44($a0)
/* 2AF78 8003A778 450080A0 */  sb         $zero, 0x45($a0)
/* 2AF7C 8003A77C 460080A0 */  sb         $zero, 0x46($a0)
/* 2AF80 8003A780 1C0080AC */  sw         $zero, 0x1C($a0)
/* 2AF84 8003A784 570080A0 */  sb         $zero, 0x57($a0)
/* 2AF88 8003A788 540082A0 */  sb         $v0, 0x54($a0)
/* 2AF8C 8003A78C 380080A4 */  sh         $zero, 0x38($a0)
/* 2AF90 8003A790 4B0085A0 */  sb         $a1, 0x4B($a0)
/* 2AF94 8003A794 0800E003 */  jr         $ra
/* 2AF98 8003A798 4C0080AC */   sw        $zero, 0x4C($a0)
.size func_8003A720, . - func_8003A720
