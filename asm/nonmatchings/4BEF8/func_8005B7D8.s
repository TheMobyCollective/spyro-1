.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8005B7D8
/* 4BFD8 8005B7D8 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 4BFDC 8005B7DC 2000B2AF */  sw         $s2, 0x20($sp)
/* 4BFE0 8005B7E0 21900000 */  addu       $s2, $zero, $zero
/* 4BFE4 8005B7E4 2400B3AF */  sw         $s3, 0x24($sp)
/* 4BFE8 8005B7E8 0780133C */  lui        $s3, %hi(D_80076378)
/* 4BFEC 8005B7EC 78637326 */  addiu      $s3, $s3, %lo(D_80076378)
/* 4BFF0 8005B7F0 0880033C */  lui        $v1, %hi(D_8007A714)
/* 4BFF4 8005B7F4 14A76324 */  addiu      $v1, $v1, %lo(D_8007A714)
/* 4BFF8 8005B7F8 0780043C */  lui        $a0, %hi(D_80076B90)
/* 4BFFC 8005B7FC 906B848C */  lw         $a0, %lo(D_80076B90)($a0)
/* 4C000 8005B800 58020224 */  addiu      $v0, $zero, 0x258
/* 4C004 8005B804 2800BFAF */  sw         $ra, 0x28($sp)
/* 4C008 8005B808 1C00B1AF */  sw         $s1, 0x1C($sp)
/* 4C00C 8005B80C 1800B0AF */  sw         $s0, 0x18($sp)
/* 4C010 8005B810 0000668C */  lw         $a2, 0x0($v1)
/* 4C014 8005B814 2080113C */  lui        $s1, (0x80200000 >> 16)
/* 4C018 8005B818 1000A2AF */  sw         $v0, 0x10($sp)
/* 4C01C 8005B81C 0000638C */  lw         $v1, 0x0($v1)
/* 4C020 8005B820 0780023C */  lui        $v0, %hi(_stacksize)
/* 4C024 8005B824 A455428C */  lw         $v0, %lo(_stacksize)($v0)
/* 4C028 8005B828 0880073C */  lui        $a3, %hi(D_8007A710)
/* 4C02C 8005B82C 10A7E78C */  lw         $a3, %lo(D_8007A710)($a3)
/* 4C030 8005B830 23802302 */  subu       $s0, $s1, $v1
/* 4C034 8005B834 23800302 */  subu       $s0, $s0, $v1
/* 4C038 8005B838 23800202 */  subu       $s0, $s0, $v0
/* 4C03C 8005B83C 4059000C */  jal        CDLoadSync
/* 4C040 8005B840 21280002 */   addu      $a1, $s0, $zero
/* 4C044 8005B844 00080526 */  addiu      $a1, $s0, 0x800
/* 4C048 8005B848 0780023C */  lui        $v0, %hi(_stacksize)
/* 4C04C 8005B84C A455428C */  lw         $v0, %lo(_stacksize)($v0)
/* 4C050 8005B850 0000038E */  lw         $v1, 0x0($s0)
/* 4C054 8005B854 23882202 */  subu       $s1, $s1, $v0
/* 4C058 8005B858 23882302 */  subu       $s1, $s1, $v1
/* 4C05C 8005B85C 0880013C */  lui        $at, %hi(D_800785FC)
/* 4C060 8005B860 FC8531AC */  sw         $s1, %lo(D_800785FC)($at)
/* 4C064 8005B864 0000068E */  lw         $a2, 0x0($s0)
/* 4C068 8005B868 565A000C */  jal        Memcpy
/* 4C06C 8005B86C 21202002 */   addu      $a0, $s1, $zero
.L8005B870:
/* 4C070 8005B870 0400028E */  lw         $v0, 0x4($s0)
/* 4C074 8005B874 00000000 */  nop
/* 4C078 8005B878 0F004010 */  beqz       $v0, .L8005B8B8
/* 4C07C 8005B87C 00000000 */   nop
/* 4C080 8005B880 0880043C */  lui        $a0, %hi(D_800785FC)
/* 4C084 8005B884 FC85848C */  lw         $a0, %lo(D_800785FC)($a0)
/* 4C088 8005B888 01005226 */  addiu      $s2, $s2, 0x1
/* 4C08C 8005B88C 21208200 */  addu       $a0, $a0, $v0
/* 4C090 8005B890 F84C000C */  jal        func_800133E0
/* 4C094 8005B894 00F88424 */   addiu     $a0, $a0, -0x800
/* 4C098 8005B898 0800038E */  lw         $v1, 0x8($s0)
/* 4C09C 8005B89C 00000000 */  nop
/* 4C0A0 8005B8A0 80180300 */  sll        $v1, $v1, 2
/* 4C0A4 8005B8A4 21187300 */  addu       $v1, $v1, $s3
/* 4C0A8 8005B8A8 000062AC */  sw         $v0, 0x0($v1)
/* 4C0AC 8005B8AC 4000422A */  slti       $v0, $s2, 0x40
/* 4C0B0 8005B8B0 EFFF4014 */  bnez       $v0, .L8005B870
/* 4C0B4 8005B8B4 08001026 */   addiu     $s0, $s0, 0x8
.L8005B8B8:
/* 4C0B8 8005B8B8 BE6D010C */  jal        AllocateBuffers
/* 4C0BC 8005B8BC 21200000 */   addu      $a0, $zero, $zero
/* 4C0C0 8005B8C0 2800BF8F */  lw         $ra, 0x28($sp)
/* 4C0C4 8005B8C4 2400B38F */  lw         $s3, 0x24($sp)
/* 4C0C8 8005B8C8 2000B28F */  lw         $s2, 0x20($sp)
/* 4C0CC 8005B8CC 1C00B18F */  lw         $s1, 0x1C($sp)
/* 4C0D0 8005B8D0 1800B08F */  lw         $s0, 0x18($sp)
/* 4C0D4 8005B8D4 3000BD27 */  addiu      $sp, $sp, 0x30
/* 4C0D8 8005B8D8 0800E003 */  jr         $ra
/* 4C0DC 8005B8DC 00000000 */   nop
.size func_8005B7D8, . - func_8005B7D8
