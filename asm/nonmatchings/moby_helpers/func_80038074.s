.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038074
/* 28874 80038074 21208500 */  addu       $a0, $a0, $a1
/* 28878 80038078 00018324 */  addiu      $v1, $a0, 0x100
/* 2887C 8003807C 02006104 */  bgez       $v1, .L80038088
/* 28880 80038080 21106000 */   addu      $v0, $v1, $zero
/* 28884 80038084 FF018224 */  addiu      $v0, $a0, 0x1FF
.L80038088:
/* 28888 80038088 03120200 */  sra        $v0, $v0, 8
/* 2888C 8003808C 00120200 */  sll        $v0, $v0, 8
/* 28890 80038090 0800E003 */  jr         $ra
/* 28894 80038094 23106200 */   subu      $v0, $v1, $v0
.size func_80038074, . - func_80038074
