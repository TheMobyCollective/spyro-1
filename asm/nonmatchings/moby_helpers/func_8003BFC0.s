.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003BFC0
/* 2C7C0 8003BFC0 A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 2C7C4 8003BFC4 4000B4AF */  sw         $s4, 0x40($sp)
/* 2C7C8 8003BFC8 6800B48F */  lw         $s4, 0x68($sp)
/* 2C7CC 8003BFCC 4C00B7AF */  sw         $s7, 0x4C($sp)
/* 2C7D0 8003BFD0 6C00B78F */  lw         $s7, 0x6C($sp)
/* 2C7D4 8003BFD4 3C00B3AF */  sw         $s3, 0x3C($sp)
/* 2C7D8 8003BFD8 21988000 */  addu       $s3, $a0, $zero
/* 2C7DC 8003BFDC 3000B0AF */  sw         $s0, 0x30($sp)
/* 2C7E0 8003BFE0 2180A000 */  addu       $s0, $a1, $zero
/* 2C7E4 8003BFE4 4800B6AF */  sw         $s6, 0x48($sp)
/* 2C7E8 8003BFE8 21B0C000 */  addu       $s6, $a2, $zero
/* 2C7EC 8003BFEC 3400B1AF */  sw         $s1, 0x34($sp)
/* 2C7F0 8003BFF0 2188E000 */  addu       $s1, $a3, $zero
/* 2C7F4 8003BFF4 4400B5AF */  sw         $s5, 0x44($sp)
/* 2C7F8 8003BFF8 21A80000 */  addu       $s5, $zero, $zero
/* 2C7FC 8003BFFC 5000BFAF */  sw         $ra, 0x50($sp)
/* 2C800 8003C000 0900822A */  slti       $v0, $s4, 0x9
/* 2C804 8003C004 05004014 */  bnez       $v0, .L8003C01C
/* 2C808 8003C008 3800B2AF */   sw        $s2, 0x38($sp)
/* 2C80C 8003C00C 0780123C */  lui        $s2, %hi(D_8006CBCC)
/* 2C810 8003C010 CCCB5226 */  addiu      $s2, $s2, %lo(D_8006CBCC)
/* 2C814 8003C014 16F00008 */  j          .L8003C058
/* 2C818 8003C018 07000424 */   addiu     $a0, $zero, 0x7
.L8003C01C:
/* 2C81C 8003C01C 0700822A */  slti       $v0, $s4, 0x7
/* 2C820 8003C020 05004014 */  bnez       $v0, .L8003C038
/* 2C824 8003C024 0500822A */   slti      $v0, $s4, 0x5
/* 2C828 8003C028 0780123C */  lui        $s2, %hi(D_8006CBB4)
/* 2C82C 8003C02C B4CB5226 */  addiu      $s2, $s2, %lo(D_8006CBB4)
/* 2C830 8003C030 16F00008 */  j          .L8003C058
/* 2C834 8003C034 05000424 */   addiu     $a0, $zero, 0x5
.L8003C038:
/* 2C838 8003C038 05004014 */  bnez       $v0, .L8003C050
/* 2C83C 8003C03C 01000424 */   addiu     $a0, $zero, 0x1
/* 2C840 8003C040 0780123C */  lui        $s2, %hi(D_8006CBA4)
/* 2C844 8003C044 A4CB5226 */  addiu      $s2, $s2, %lo(D_8006CBA4)
/* 2C848 8003C048 16F00008 */  j          .L8003C058
/* 2C84C 8003C04C 03000424 */   addiu     $a0, $zero, 0x3
.L8003C050:
/* 2C850 8003C050 0780123C */  lui        $s2, %hi(D_80075280)
/* 2C854 8003C054 80525226 */  addiu      $s2, $s2, %lo(D_80075280)
.L8003C058:
/* 2C858 8003C058 01000592 */  lbu        $a1, 0x1($s0)
/* 2C85C 8003C05C 0000238E */  lw         $v1, 0x0($s1)
/* 2C860 8003C060 00000000 */  nop
/* 2C864 8003C064 2A107400 */  slt        $v0, $v1, $s4
/* 2C868 8003C068 16004014 */  bnez       $v0, .L8003C0C4
/* 2C86C 8003C06C 2A108300 */   slt       $v0, $a0, $v1
/* 2C870 8003C070 1000A427 */  addiu      $a0, $sp, 0x10
/* 2C874 8003C074 00290500 */  sll        $a1, $a1, 4
/* 2C878 8003C078 0800A524 */  addiu      $a1, $a1, 0x8
/* 2C87C 8003C07C 21280502 */  addu       $a1, $s0, $a1
/* 2C880 8003C080 E35D000C */  jal        VecSub
/* 2C884 8003C084 0C006626 */   addiu     $a2, $s3, 0xC
/* 2C888 8003C088 2120C002 */  addu       $a0, $s6, $zero
/* 2C88C 8003C08C C05D000C */  jal        VecCopy
/* 2C890 8003C090 1000A527 */   addiu     $a1, $sp, 0x10
/* 2C894 8003C094 01000292 */  lbu        $v0, 0x1($s0)
/* 2C898 8003C098 00000392 */  lbu        $v1, 0x0($s0)
/* 2C89C 8003C09C 01004224 */  addiu      $v0, $v0, 0x1
/* 2C8A0 8003C0A0 010002A2 */  sb         $v0, 0x1($s0)
/* 2C8A4 8003C0A4 FF004230 */  andi       $v0, $v0, 0xFF
/* 2C8A8 8003C0A8 2B104300 */  sltu       $v0, $v0, $v1
/* 2C8AC 8003C0AC 03004014 */  bnez       $v0, .L8003C0BC
/* 2C8B0 8003C0B0 0100B526 */   addiu     $s5, $s5, 0x1
/* 2C8B4 8003C0B4 010000A2 */  sb         $zero, 0x1($s0)
/* 2C8B8 8003C0B8 0100B526 */  addiu      $s5, $s5, 0x1
.L8003C0BC:
/* 2C8BC 8003C0BC B0F00008 */  j          .L8003C2C0
/* 2C8C0 8003C0C0 000020AE */   sw        $zero, 0x0($s1)
.L8003C0C4:
/* 2C8C4 8003C0C4 33004010 */  beqz       $v0, .L8003C194
/* 2C8C8 8003C0C8 1000A427 */   addiu     $a0, $sp, 0x10
/* 2C8CC 8003C0CC 00290500 */  sll        $a1, $a1, 4
/* 2C8D0 8003C0D0 0800A524 */  addiu      $a1, $a1, 0x8
/* 2C8D4 8003C0D4 21280502 */  addu       $a1, $s0, $a1
/* 2C8D8 8003C0D8 E35D000C */  jal        VecSub
/* 2C8DC 8003C0DC 0C006626 */   addiu     $a2, $s3, 0xC
/* 2C8E0 8003C0E0 0000228E */  lw         $v0, 0x0($s1)
/* 2C8E4 8003C0E4 1000A48F */  lw         $a0, 0x10($sp)
/* 2C8E8 8003C0E8 FFFF4224 */  addiu      $v0, $v0, -0x1
/* 2C8EC 8003C0EC 23308202 */  subu       $a2, $s4, $v0
/* 2C8F0 8003C0F0 1A008600 */  div        $zero, $a0, $a2
/* 2C8F4 8003C0F4 0200C014 */  bnez       $a2, .L8003C100
/* 2C8F8 8003C0F8 00000000 */   nop
/* 2C8FC 8003C0FC 0D000700 */  break      7
.L8003C100:
/* 2C900 8003C100 FFFF0124 */  addiu      $at, $zero, -0x1
/* 2C904 8003C104 0400C114 */  bne        $a2, $at, .L8003C118
/* 2C908 8003C108 0080013C */   lui       $at, (0x80000000 >> 16)
/* 2C90C 8003C10C 02008114 */  bne        $a0, $at, .L8003C118
/* 2C910 8003C110 00000000 */   nop
/* 2C914 8003C114 0D000600 */  break      6
.L8003C118:
/* 2C918 8003C118 12200000 */  mflo       $a0
/* 2C91C 8003C11C 1400A38F */  lw         $v1, 0x14($sp)
/* 2C920 8003C120 00000000 */  nop
/* 2C924 8003C124 1A006600 */  div        $zero, $v1, $a2
/* 2C928 8003C128 0200C014 */  bnez       $a2, .L8003C134
/* 2C92C 8003C12C 00000000 */   nop
/* 2C930 8003C130 0D000700 */  break      7
.L8003C134:
/* 2C934 8003C134 FFFF0124 */  addiu      $at, $zero, -0x1
/* 2C938 8003C138 0400C114 */  bne        $a2, $at, .L8003C14C
/* 2C93C 8003C13C 0080013C */   lui       $at, (0x80000000 >> 16)
/* 2C940 8003C140 02006114 */  bne        $v1, $at, .L8003C14C
/* 2C944 8003C144 00000000 */   nop
/* 2C948 8003C148 0D000600 */  break      6
.L8003C14C:
/* 2C94C 8003C14C 12180000 */  mflo       $v1
/* 2C950 8003C150 1800A28F */  lw         $v0, 0x18($sp)
/* 2C954 8003C154 00000000 */  nop
/* 2C958 8003C158 1A004600 */  div        $zero, $v0, $a2
/* 2C95C 8003C15C 0200C014 */  bnez       $a2, .L8003C168
/* 2C960 8003C160 00000000 */   nop
/* 2C964 8003C164 0D000700 */  break      7
.L8003C168:
/* 2C968 8003C168 FFFF0124 */  addiu      $at, $zero, -0x1
/* 2C96C 8003C16C 0400C114 */  bne        $a2, $at, .L8003C180
/* 2C970 8003C170 0080013C */   lui       $at, (0x80000000 >> 16)
/* 2C974 8003C174 02004114 */  bne        $v0, $at, .L8003C180
/* 2C978 8003C178 00000000 */   nop
/* 2C97C 8003C17C 0D000600 */  break      6
.L8003C180:
/* 2C980 8003C180 12100000 */  mflo       $v0
/* 2C984 8003C184 1000A4AF */  sw         $a0, 0x10($sp)
/* 2C988 8003C188 1400A3AF */  sw         $v1, 0x14($sp)
/* 2C98C 8003C18C ACF00008 */  j          .L8003C2B0
/* 2C990 8003C190 1800A2AF */   sw        $v0, 0x18($sp)
.L8003C194:
/* 2C994 8003C194 00290500 */  sll        $a1, $a1, 4
/* 2C998 8003C198 0800A524 */  addiu      $a1, $a1, 0x8
/* 2C99C 8003C19C 21280502 */  addu       $a1, $s0, $a1
/* 2C9A0 8003C1A0 E35D000C */  jal        VecSub
/* 2C9A4 8003C1A4 0C006626 */   addiu     $a2, $s3, 0xC
/* 2C9A8 8003C1A8 0000228E */  lw         $v0, 0x0($s1)
/* 2C9AC 8003C1AC 1000A48F */  lw         $a0, 0x10($sp)
/* 2C9B0 8003C1B0 FFFF4224 */  addiu      $v0, $v0, -0x1
/* 2C9B4 8003C1B4 23308202 */  subu       $a2, $s4, $v0
/* 2C9B8 8003C1B8 1A008600 */  div        $zero, $a0, $a2
/* 2C9BC 8003C1BC 0200C014 */  bnez       $a2, .L8003C1C8
/* 2C9C0 8003C1C0 00000000 */   nop
/* 2C9C4 8003C1C4 0D000700 */  break      7
.L8003C1C8:
/* 2C9C8 8003C1C8 FFFF0124 */  addiu      $at, $zero, -0x1
/* 2C9CC 8003C1CC 0400C114 */  bne        $a2, $at, .L8003C1E0
/* 2C9D0 8003C1D0 0080013C */   lui       $at, (0x80000000 >> 16)
/* 2C9D4 8003C1D4 02008114 */  bne        $a0, $at, .L8003C1E0
/* 2C9D8 8003C1D8 00000000 */   nop
/* 2C9DC 8003C1DC 0D000600 */  break      6
.L8003C1E0:
/* 2C9E0 8003C1E0 12200000 */  mflo       $a0
/* 2C9E4 8003C1E4 1400A38F */  lw         $v1, 0x14($sp)
/* 2C9E8 8003C1E8 00000000 */  nop
/* 2C9EC 8003C1EC 1A006600 */  div        $zero, $v1, $a2
/* 2C9F0 8003C1F0 0200C014 */  bnez       $a2, .L8003C1FC
/* 2C9F4 8003C1F4 00000000 */   nop
/* 2C9F8 8003C1F8 0D000700 */  break      7
.L8003C1FC:
/* 2C9FC 8003C1FC FFFF0124 */  addiu      $at, $zero, -0x1
/* 2CA00 8003C200 0400C114 */  bne        $a2, $at, .L8003C214
/* 2CA04 8003C204 0080013C */   lui       $at, (0x80000000 >> 16)
/* 2CA08 8003C208 02006114 */  bne        $v1, $at, .L8003C214
/* 2CA0C 8003C20C 00000000 */   nop
/* 2CA10 8003C210 0D000600 */  break      6
.L8003C214:
/* 2CA14 8003C214 12180000 */  mflo       $v1
/* 2CA18 8003C218 1800A28F */  lw         $v0, 0x18($sp)
/* 2CA1C 8003C21C 00000000 */  nop
/* 2CA20 8003C220 1A004600 */  div        $zero, $v0, $a2
/* 2CA24 8003C224 0200C014 */  bnez       $a2, .L8003C230
/* 2CA28 8003C228 00000000 */   nop
/* 2CA2C 8003C22C 0D000700 */  break      7
.L8003C230:
/* 2CA30 8003C230 FFFF0124 */  addiu      $at, $zero, -0x1
/* 2CA34 8003C234 0400C114 */  bne        $a2, $at, .L8003C248
/* 2CA38 8003C238 0080013C */   lui       $at, (0x80000000 >> 16)
/* 2CA3C 8003C23C 02004114 */  bne        $v0, $at, .L8003C248
/* 2CA40 8003C240 00000000 */   nop
/* 2CA44 8003C244 0D000600 */  break      6
.L8003C248:
/* 2CA48 8003C248 12100000 */  mflo       $v0
/* 2CA4C 8003C24C 1000A4AF */  sw         $a0, 0x10($sp)
/* 2CA50 8003C250 1400A3AF */  sw         $v1, 0x14($sp)
/* 2CA54 8003C254 1800A2AF */  sw         $v0, 0x18($sp)
/* 2CA58 8003C258 0000228E */  lw         $v0, 0x0($s1)
/* 2CA5C 8003C25C 1000A427 */  addiu      $a0, $sp, 0x10
/* 2CA60 8003C260 80100200 */  sll        $v0, $v0, 2
/* 2CA64 8003C264 21105200 */  addu       $v0, $v0, $s2
/* 2CA68 8003C268 00004684 */  lh         $a2, 0x0($v0)
/* 2CA6C 8003C26C F05D000C */  jal        VecMult
/* 2CA70 8003C270 21288000 */   addu      $a1, $a0, $zero
/* 2CA74 8003C274 2000B027 */  addiu      $s0, $sp, 0x20
/* 2CA78 8003C278 0000228E */  lw         $v0, 0x0($s1)
/* 2CA7C 8003C27C 21200002 */  addu       $a0, $s0, $zero
/* 2CA80 8003C280 80100200 */  sll        $v0, $v0, 2
/* 2CA84 8003C284 21105200 */  addu       $v0, $v0, $s2
/* 2CA88 8003C288 02004684 */  lh         $a2, 0x2($v0)
/* 2CA8C 8003C28C F05D000C */  jal        VecMult
/* 2CA90 8003C290 2128C002 */   addu      $a1, $s6, $zero
/* 2CA94 8003C294 1000A427 */  addiu      $a0, $sp, 0x10
/* 2CA98 8003C298 21288000 */  addu       $a1, $a0, $zero
/* 2CA9C 8003C29C D65D000C */  jal        VecAdd
/* 2CAA0 8003C2A0 21300002 */   addu      $a2, $s0, $zero
/* 2CAA4 8003C2A4 1000A427 */  addiu      $a0, $sp, 0x10
/* 2CAA8 8003C2A8 B25D000C */  jal        VecShiftRight
/* 2CAAC 8003C2AC 0A000524 */   addiu     $a1, $zero, 0xA
.L8003C2B0:
/* 2CAB0 8003C2B0 0000228E */  lw         $v0, 0x0($s1)
/* 2CAB4 8003C2B4 00000000 */  nop
/* 2CAB8 8003C2B8 01004224 */  addiu      $v0, $v0, 0x1
/* 2CABC 8003C2BC 000022AE */  sw         $v0, 0x0($s1)
.L8003C2C0:
/* 2CAC0 8003C2C0 0400E232 */  andi       $v0, $s7, 0x4
/* 2CAC4 8003C2C4 02004014 */  bnez       $v0, .L8003C2D0
/* 2CAC8 8003C2C8 00000000 */   nop
/* 2CACC 8003C2CC 1800A0AF */  sw         $zero, 0x18($sp)
.L8003C2D0:
/* 2CAD0 8003C2D0 1000A48F */  lw         $a0, 0x10($sp)
/* 2CAD4 8003C2D4 1400A58F */  lw         $a1, 0x14($sp)
/* 2CAD8 8003C2D8 6B5A000C */  jal        Atan2Fast
/* 2CADC 8003C2DC 00000000 */   nop
/* 2CAE0 8003C2E0 1000A427 */  addiu      $a0, $sp, 0x10
/* 2CAE4 8003C2E4 21280000 */  addu       $a1, $zero, $zero
/* 2CAE8 8003C2E8 7F5C000C */  jal        VecMagnitude
/* 2CAEC 8003C2EC 460062A2 */   sb        $v0, 0x46($s3)
/* 2CAF0 8003C2F0 1800A48F */  lw         $a0, 0x18($sp)
/* 2CAF4 8003C2F4 6B5A000C */  jal        Atan2Fast
/* 2CAF8 8003C2F8 21284000 */   addu      $a1, $v0, $zero
/* 2CAFC 8003C2FC 0C006426 */  addiu      $a0, $s3, 0xC
/* 2CB00 8003C300 21288000 */  addu       $a1, $a0, $zero
/* 2CB04 8003C304 1000A627 */  addiu      $a2, $sp, 0x10
/* 2CB08 8003C308 23100200 */  negu       $v0, $v0
/* 2CB0C 8003C30C 40004224 */  addiu      $v0, $v0, 0x40
/* 2CB10 8003C310 D65D000C */  jal        VecAdd
/* 2CB14 8003C314 450062A2 */   sb        $v0, 0x45($s3)
/* 2CB18 8003C318 21206002 */  addu       $a0, $s3, $zero
/* 2CB1C 8003C31C 794A010C */  jal        func_800529E4
/* 2CB20 8003C320 02000524 */   addiu     $a1, $zero, 0x2
/* 2CB24 8003C324 2110A002 */  addu       $v0, $s5, $zero
/* 2CB28 8003C328 5000BF8F */  lw         $ra, 0x50($sp)
/* 2CB2C 8003C32C 4C00B78F */  lw         $s7, 0x4C($sp)
/* 2CB30 8003C330 4800B68F */  lw         $s6, 0x48($sp)
/* 2CB34 8003C334 4400B58F */  lw         $s5, 0x44($sp)
/* 2CB38 8003C338 4000B48F */  lw         $s4, 0x40($sp)
/* 2CB3C 8003C33C 3C00B38F */  lw         $s3, 0x3C($sp)
/* 2CB40 8003C340 3800B28F */  lw         $s2, 0x38($sp)
/* 2CB44 8003C344 3400B18F */  lw         $s1, 0x34($sp)
/* 2CB48 8003C348 3000B08F */  lw         $s0, 0x30($sp)
/* 2CB4C 8003C34C 5800BD27 */  addiu      $sp, $sp, 0x58
/* 2CB50 8003C350 0800E003 */  jr         $ra
/* 2CB54 8003C354 00000000 */   nop
.size func_8003BFC0, . - func_8003BFC0
