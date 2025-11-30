.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002BBE0
/* 1C3E0 8002BBE0 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 1C3E4 8002BBE4 01000424 */  addiu      $a0, $zero, 0x1
/* 1C3E8 8002BBE8 0780053C */  lui        $a1, %hi(D_800776BC)
/* 1C3EC 8002BBEC BC76A524 */  addiu      $a1, $a1, %lo(D_800776BC)
/* 1C3F0 8002BBF0 2800BFAF */  sw         $ra, 0x28($sp)
/* 1C3F4 8002BBF4 2400B1AF */  sw         $s1, 0x24($sp)
/* 1C3F8 8002BBF8 F68E010C */  jal        CdSync
/* 1C3FC 8002BBFC 2000B0AF */   sw        $s0, 0x20($sp)
/* 1C400 8002BC00 0780033C */  lui        $v1, %hi(D_800776C4)
/* 1C404 8002BC04 C476638C */  lw         $v1, %lo(D_800776C4)($v1)
/* 1C408 8002BC08 00000000 */  nop
/* 1C40C 8002BC0C 18006010 */  beqz       $v1, .L8002BC70
/* 1C410 8002BC10 21804000 */   addu      $s0, $v0, $zero
/* 1C414 8002BC14 0800622C */  sltiu      $v0, $v1, 0x8
/* 1C418 8002BC18 20004014 */  bnez       $v0, .L8002BC9C
/* 1C41C 8002BC1C 0A00622C */   sltiu     $v0, $v1, 0xA
/* 1C420 8002BC20 05004014 */  bnez       $v0, .L8002BC38
/* 1C424 8002BC24 1B000224 */   addiu     $v0, $zero, 0x1B
/* 1C428 8002BC28 0B006210 */  beq        $v1, $v0, .L8002BC58
/* 1C42C 8002BC2C 10000224 */   addiu     $v0, $zero, 0x10
/* 1C430 8002BC30 27AF0008 */  j          .L8002BC9C
/* 1C434 8002BC34 00000000 */   nop
.L8002BC38:
/* 1C438 8002BC38 0780023C */  lui        $v0, %hi(D_800774B4)
/* 1C43C 8002BC3C B474428C */  lw         $v0, %lo(D_800774B4)($v0)
/* 1C440 8002BC40 00000000 */  nop
/* 1C444 8002BC44 00024230 */  andi       $v0, $v0, 0x200
/* 1C448 8002BC48 14004014 */  bnez       $v0, .L8002BC9C
/* 1C44C 8002BC4C 02000224 */   addiu     $v0, $zero, 0x2
/* 1C450 8002BC50 12000216 */  bne        $s0, $v0, .L8002BC9C
/* 1C454 8002BC54 40000224 */   addiu     $v0, $zero, 0x40
.L8002BC58:
/* 1C458 8002BC58 0780013C */  lui        $at, %hi(D_800774B4)
/* 1C45C 8002BC5C B47422AC */  sw         $v0, %lo(D_800774B4)($at)
/* 1C460 8002BC60 0780013C */  lui        $at, %hi(D_800776C4)
/* 1C464 8002BC64 C47620AC */  sw         $zero, %lo(D_800776C4)($at)
/* 1C468 8002BC68 27AF0008 */  j          .L8002BC9C
/* 1C46C 8002BC6C 00000000 */   nop
.L8002BC70:
/* 1C470 8002BC70 0780053C */  lui        $a1, %hi(D_800776C8)
/* 1C474 8002BC74 C876A58C */  lw         $a1, %lo(D_800776C8)($a1)
/* 1C478 8002BC78 00000000 */  nop
/* 1C47C 8002BC7C 0700A010 */  beqz       $a1, .L8002BC9C
/* 1C480 8002BC80 00000000 */   nop
/* 1C484 8002BC84 0780043C */  lui        $a0, %hi(D_800774B0)
/* 1C488 8002BC88 B074848C */  lw         $a0, %lo(D_800774B0)($a0)
/* 1C48C 8002BC8C FD59010C */  jal        func_800567F4
/* 1C490 8002BC90 00000000 */   nop
/* 1C494 8002BC94 0780013C */  lui        $at, %hi(D_800776C8)
/* 1C498 8002BC98 C87620AC */  sw         $zero, %lo(D_800776C8)($at)
.L8002BC9C:
/* 1C49C 8002BC9C 0780113C */  lui        $s1, %hi(D_800774B4)
/* 1C4A0 8002BCA0 B4743126 */  addiu      $s1, $s1, %lo(D_800774B4)
/* 1C4A4 8002BCA4 0000228E */  lw         $v0, 0x0($s1)
/* 1C4A8 8002BCA8 00000000 */  nop
/* 1C4AC 8002BCAC 10004230 */  andi       $v0, $v0, 0x10
/* 1C4B0 8002BCB0 7C004010 */  beqz       $v0, .L8002BEA4
/* 1C4B4 8002BCB4 02000224 */   addiu     $v0, $zero, 0x2
/* 1C4B8 8002BCB8 1D000212 */  beq        $s0, $v0, .L8002BD30
/* 1C4BC 8002BCBC 05000224 */   addiu     $v0, $zero, 0x5
/* 1C4C0 8002BCC0 78000216 */  bne        $s0, $v0, .L8002BEA4
/* 1C4C4 8002BCC4 00000000 */   nop
/* 1C4C8 8002BCC8 0780023C */  lui        $v0, %hi(D_800774B0)
/* 1C4CC 8002BCCC B074428C */  lw         $v0, %lo(D_800774B0)($v0)
/* 1C4D0 8002BCD0 00000000 */  nop
/* 1C4D4 8002BCD4 C0100200 */  sll        $v0, $v0, 3
/* 1C4D8 8002BCD8 0780013C */  lui        $at, %hi(D_800774B8)
/* 1C4DC 8002BCDC 21082200 */  addu       $at, $at, $v0
/* 1C4E0 8002BCE0 B874248C */  lw         $a0, %lo(D_800774B8)($at)
/* 1C4E4 8002BCE4 2590010C */  jal        CdIntToPos
/* 1C4E8 8002BCE8 1000A527 */   addiu     $a1, $sp, 0x10
/* 1C4EC 8002BCEC 1B000424 */  addiu      $a0, $zero, 0x1B
/* 1C4F0 8002BCF0 1000A527 */  addiu      $a1, $sp, 0x10
/* 1C4F4 8002BCF4 128F010C */  jal        CdControl
/* 1C4F8 8002BCF8 21300000 */   addu      $a2, $zero, $zero
/* 1C4FC 8002BCFC 0780023C */  lui        $v0, %hi(D_800774B0)
/* 1C500 8002BD00 B074428C */  lw         $v0, %lo(D_800774B0)($v0)
/* 1C504 8002BD04 1B000324 */  addiu      $v1, $zero, 0x1B
/* 1C508 8002BD08 0780013C */  lui        $at, %hi(D_800776C4)
/* 1C50C 8002BD0C C47623AC */  sw         $v1, %lo(D_800776C4)($at)
/* 1C510 8002BD10 C0100200 */  sll        $v0, $v0, 3
/* 1C514 8002BD14 0780013C */  lui        $at, %hi(D_800774B8)
/* 1C518 8002BD18 21082200 */  addu       $at, $at, $v0
/* 1C51C 8002BD1C B874228C */  lw         $v0, %lo(D_800774B8)($at)
/* 1C520 8002BD20 0780013C */  lui        $at, %hi(D_800776B8)
/* 1C524 8002BD24 B87622AC */  sw         $v0, %lo(D_800776B8)($at)
/* 1C528 8002BD28 A9AF0008 */  j          .L8002BEA4
/* 1C52C 8002BD2C 00000000 */   nop
.L8002BD30:
/* 1C530 8002BD30 0780023C */  lui        $v0, %hi(D_800774B0)
/* 1C534 8002BD34 B074428C */  lw         $v0, %lo(D_800774B0)($v0)
/* 1C538 8002BD38 0780033C */  lui        $v1, %hi(D_800776B8)
/* 1C53C 8002BD3C B876638C */  lw         $v1, %lo(D_800776B8)($v1)
/* 1C540 8002BD40 C0100200 */  sll        $v0, $v0, 3
/* 1C544 8002BD44 0780013C */  lui        $at, %hi(D_800774BC)
/* 1C548 8002BD48 21082200 */  addu       $at, $at, $v0
/* 1C54C 8002BD4C BC74228C */  lw         $v0, %lo(D_800774BC)($at)
/* 1C550 8002BD50 00000000 */  nop
/* 1C554 8002BD54 2B104300 */  sltu       $v0, $v0, $v1
/* 1C558 8002BD58 45004010 */  beqz       $v0, .L8002BE70
/* 1C55C 8002BD5C 00000000 */   nop
/* 1C560 8002BD60 0780033C */  lui        $v1, %hi(D_800758C8)
/* 1C564 8002BD64 C858638C */  lw         $v1, %lo(D_800758C8)($v1)
/* 1C568 8002BD68 0780023C */  lui        $v0, %hi(D_800776CC)
/* 1C56C 8002BD6C CC76428C */  lw         $v0, %lo(D_800776CC)($v0)
/* 1C570 8002BD70 00000000 */  nop
/* 1C574 8002BD74 2B104300 */  sltu       $v0, $v0, $v1
/* 1C578 8002BD78 22004010 */  beqz       $v0, .L8002BE04
/* 1C57C 8002BD7C 00000000 */   nop
/* 1C580 8002BD80 CB89010C */  jal        rand
/* 1C584 8002BD84 00000000 */   nop
/* 1C588 8002BD88 5555033C */  lui        $v1, (0x55555556 >> 16)
/* 1C58C 8002BD8C 56556334 */  ori        $v1, $v1, (0x55555556 & 0xFFFF)
/* 1C590 8002BD90 18004300 */  mult       $v0, $v1
/* 1C594 8002BD94 0780033C */  lui        $v1, %hi(g_LevelIndex)
/* 1C598 8002BD98 6459638C */  lw         $v1, %lo(g_LevelIndex)($v1)
/* 1C59C 8002BD9C 0780043C */  lui        $a0, %hi(D_8006F05C)
/* 1C5A0 8002BDA0 5CF08424 */  addiu      $a0, $a0, %lo(D_8006F05C)
/* 1C5A4 8002BDA4 40280300 */  sll        $a1, $v1, 1
/* 1C5A8 8002BDA8 2128A300 */  addu       $a1, $a1, $v1
/* 1C5AC 8002BDAC 80280500 */  sll        $a1, $a1, 2
/* 1C5B0 8002BDB0 2128A400 */  addu       $a1, $a1, $a0
/* 1C5B4 8002BDB4 C3270200 */  sra        $a0, $v0, 31
/* 1C5B8 8002BDB8 10380000 */  mfhi       $a3
/* 1C5BC 8002BDBC 2320E400 */  subu       $a0, $a3, $a0
/* 1C5C0 8002BDC0 40180400 */  sll        $v1, $a0, 1
/* 1C5C4 8002BDC4 21186400 */  addu       $v1, $v1, $a0
/* 1C5C8 8002BDC8 23104300 */  subu       $v0, $v0, $v1
/* 1C5CC 8002BDCC 80100200 */  sll        $v0, $v0, 2
/* 1C5D0 8002BDD0 21104500 */  addu       $v0, $v0, $a1
/* 1C5D4 8002BDD4 0000428C */  lw         $v0, 0x0($v0)
/* 1C5D8 8002BDD8 0780033C */  lui        $v1, %hi(D_800758C8)
/* 1C5DC 8002BDDC C858638C */  lw         $v1, %lo(D_800758C8)($v1)
/* 1C5E0 8002BDE0 80100200 */  sll        $v0, $v0, 2
/* 1C5E4 8002BDE4 0780013C */  lui        $at, %hi(D_8006EF9C)
/* 1C5E8 8002BDE8 21082200 */  addu       $at, $at, $v0
/* 1C5EC 8002BDEC 9CEF228C */  lw         $v0, %lo(D_8006EF9C)($at)
/* 1C5F0 8002BDF0 80706324 */  addiu      $v1, $v1, 0x7080
/* 1C5F4 8002BDF4 0780013C */  lui        $at, %hi(D_800776CC)
/* 1C5F8 8002BDF8 CC7623AC */  sw         $v1, %lo(D_800776CC)($at)
/* 1C5FC 8002BDFC 0780013C */  lui        $at, %hi(D_800774B0)
/* 1C600 8002BE00 B07422AC */  sw         $v0, %lo(D_800774B0)($at)
.L8002BE04:
/* 1C604 8002BE04 0780023C */  lui        $v0, %hi(D_800774B0)
/* 1C608 8002BE08 B074428C */  lw         $v0, %lo(D_800774B0)($v0)
/* 1C60C 8002BE0C 00000000 */  nop
/* 1C610 8002BE10 C0100200 */  sll        $v0, $v0, 3
/* 1C614 8002BE14 0780013C */  lui        $at, %hi(D_800774B8)
/* 1C618 8002BE18 21082200 */  addu       $at, $at, $v0
/* 1C61C 8002BE1C B874248C */  lw         $a0, %lo(D_800774B8)($at)
/* 1C620 8002BE20 0780013C */  lui        $at, %hi(D_800776B8)
/* 1C624 8002BE24 B87624AC */  sw         $a0, %lo(D_800776B8)($at)
/* 1C628 8002BE28 2590010C */  jal        CdIntToPos
/* 1C62C 8002BE2C 1000A527 */   addiu     $a1, $sp, 0x10
/* 1C630 8002BE30 0D000424 */  addiu      $a0, $zero, 0xD
/* 1C634 8002BE34 1800A527 */  addiu      $a1, $sp, 0x18
/* 1C638 8002BE38 21300000 */  addu       $a2, $zero, $zero
/* 1C63C 8002BE3C 0780023C */  lui        $v0, %hi(D_800774B0)
/* 1C640 8002BE40 B074428C */  lw         $v0, %lo(D_800774B0)($v0)
/* 1C644 8002BE44 01000324 */  addiu      $v1, $zero, 0x1
/* 1C648 8002BE48 1800A3A3 */  sb         $v1, 0x18($sp)
/* 1C64C 8002BE4C 07004230 */  andi       $v0, $v0, 0x7
/* 1C650 8002BE50 AB8F010C */  jal        CdControlB
/* 1C654 8002BE54 1900A2A3 */   sb        $v0, 0x19($sp)
/* 1C658 8002BE58 1B000424 */  addiu      $a0, $zero, 0x1B
/* 1C65C 8002BE5C 1000A527 */  addiu      $a1, $sp, 0x10
/* 1C660 8002BE60 128F010C */  jal        CdControl
/* 1C664 8002BE64 21300000 */   addu      $a2, $zero, $zero
/* 1C668 8002BE68 A9AF0008 */  j          .L8002BEA4
/* 1C66C 8002BE6C 00000000 */   nop
.L8002BE70:
/* 1C670 8002BE70 AB8E010C */  jal        CdLastCom
/* 1C674 8002BE74 00000000 */   nop
/* 1C678 8002BE78 11000324 */  addiu      $v1, $zero, 0x11
/* 1C67C 8002BE7C 07004314 */  bne        $v0, $v1, .L8002BE9C
/* 1C680 8002BE80 11000424 */   addiu     $a0, $zero, 0x11
/* 1C684 8002BE84 6690010C */  jal        CdPosToInt
/* 1C688 8002BE88 0D022426 */   addiu     $a0, $s1, 0x20D
/* 1C68C 8002BE8C 03004018 */  blez       $v0, .L8002BE9C
/* 1C690 8002BE90 11000424 */   addiu     $a0, $zero, 0x11
/* 1C694 8002BE94 0780013C */  lui        $at, %hi(D_800776B8)
/* 1C698 8002BE98 B87622AC */  sw         $v0, %lo(D_800776B8)($at)
.L8002BE9C:
/* 1C69C 8002BE9C 608F010C */  jal        CdControlF
/* 1C6A0 8002BEA0 21280000 */   addu      $a1, $zero, $zero
.L8002BEA4:
/* 1C6A4 8002BEA4 0780053C */  lui        $a1, %hi(g_Spu + 0x2D0)
/* 1C6A8 8002BEA8 D861A524 */  addiu      $a1, $a1, %lo(g_Spu + 0x2D0)
/* 1C6AC 8002BEAC 0000A48C */  lw         $a0, 0x0($a1)
/* 1C6B0 8002BEB0 00000000 */  nop
/* 1C6B4 8002BEB4 3C008004 */  bltz       $a0, .L8002BFA8
/* 1C6B8 8002BEB8 00000000 */   nop
/* 1C6BC 8002BEBC 40FDA384 */  lh         $v1, -0x2C0($a1)
/* 1C6C0 8002BEC0 5800A28C */  lw         $v0, 0x58($a1)
/* 1C6C4 8002BEC4 00000000 */  nop
/* 1C6C8 8002BEC8 24004104 */  bgez       $v0, .L8002BF5C
/* 1C6CC 8002BECC 21186200 */   addu      $v1, $v1, $v0
/* 1C6D0 8002BED0 2A108300 */  slt        $v0, $a0, $v1
/* 1C6D4 8002BED4 2A004014 */  bnez       $v0, .L8002BF80
/* 1C6D8 8002BED8 00000000 */   nop
/* 1C6DC 8002BEDC 14008014 */  bnez       $a0, .L8002BF30
/* 1C6E0 8002BEE0 00000000 */   nop
/* 1C6E4 8002BEE4 0780043C */  lui        $a0, %hi(D_800776C4)
/* 1C6E8 8002BEE8 C476848C */  lw         $a0, %lo(D_800776C4)($a0)
/* 1C6EC 8002BEEC 00000000 */  nop
/* 1C6F0 8002BEF0 0800822C */  sltiu      $v0, $a0, 0x8
/* 1C6F4 8002BEF4 0E004014 */  bnez       $v0, .L8002BF30
/* 1C6F8 8002BEF8 0A00822C */   sltiu     $v0, $a0, 0xA
/* 1C6FC 8002BEFC 05004014 */  bnez       $v0, .L8002BF14
/* 1C700 8002BF00 1B000224 */   addiu     $v0, $zero, 0x1B
/* 1C704 8002BF04 08008210 */  beq        $a0, $v0, .L8002BF28
/* 1C708 8002BF08 10000224 */   addiu     $v0, $zero, 0x10
/* 1C70C 8002BF0C CCAF0008 */  j          .L8002BF30
/* 1C710 8002BF10 00000000 */   nop
.L8002BF14:
/* 1C714 8002BF14 FF008430 */  andi       $a0, $a0, 0xFF
/* 1C718 8002BF18 21280000 */  addu       $a1, $zero, $zero
/* 1C71C 8002BF1C 128F010C */  jal        CdControl
/* 1C720 8002BF20 21300000 */   addu      $a2, $zero, $zero
/* 1C724 8002BF24 00010224 */  addiu      $v0, $zero, 0x100
.L8002BF28:
/* 1C728 8002BF28 0780013C */  lui        $at, %hi(D_800774B4)
/* 1C72C 8002BF2C B47422AC */  sw         $v0, %lo(D_800774B4)($at)
.L8002BF30:
/* 1C730 8002BF30 0780033C */  lui        $v1, %hi(g_Spu + 0x2D0)
/* 1C734 8002BF34 D861638C */  lw         $v1, %lo(g_Spu + 0x2D0)($v1)
/* 1C738 8002BF38 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 1C73C 8002BF3C 0780013C */  lui        $at, %hi(g_Spu + 0x328)
/* 1C740 8002BF40 306220AC */  sw         $zero, %lo(g_Spu + 0x328)($at)
/* 1C744 8002BF44 0780013C */  lui        $at, %hi(g_Spu + 0x2D0)
/* 1C748 8002BF48 D86122AC */  sw         $v0, %lo(g_Spu + 0x2D0)($at)
/* 1C74C 8002BF4C 0780013C */  lui        $at, %hi(g_Spu + 0x10)
/* 1C750 8002BF50 185F23A4 */  sh         $v1, %lo(g_Spu + 0x10)($at)
/* 1C754 8002BF54 E1AF0008 */  j          .L8002BF84
/* 1C758 8002BF58 00000000 */   nop
.L8002BF5C:
/* 1C75C 8002BF5C 2A106400 */  slt        $v0, $v1, $a0
/* 1C760 8002BF60 07004014 */  bnez       $v0, .L8002BF80
/* 1C764 8002BF64 FFFF0224 */   addiu     $v0, $zero, -0x1
/* 1C768 8002BF68 5800A0AC */  sw         $zero, 0x58($a1)
/* 1C76C 8002BF6C 40FDA4A4 */  sh         $a0, -0x2C0($a1)
/* 1C770 8002BF70 0780013C */  lui        $at, %hi(g_Spu + 0x12)
/* 1C774 8002BF74 1A5F24A4 */  sh         $a0, %lo(g_Spu + 0x12)($at)
/* 1C778 8002BF78 E3AF0008 */  j          .L8002BF8C
/* 1C77C 8002BF7C 0000A2AC */   sw        $v0, 0x0($a1)
.L8002BF80:
/* 1C780 8002BF80 40FDA3A4 */  sh         $v1, -0x2C0($a1)
.L8002BF84:
/* 1C784 8002BF84 0780013C */  lui        $at, %hi(g_Spu + 0x12)
/* 1C788 8002BF88 1A5F23A4 */  sh         $v1, %lo(g_Spu + 0x12)($at)
.L8002BF8C:
/* 1C78C 8002BF8C 0780043C */  lui        $a0, %hi(g_Spu)
/* 1C790 8002BF90 085F8424 */  addiu      $a0, $a0, %lo(g_Spu)
/* 1C794 8002BF94 C0000224 */  addiu      $v0, $zero, 0xC0
/* 1C798 8002BF98 1673010C */  jal        SpuSetCommonAttr
/* 1C79C 8002BF9C 000082AC */   sw        $v0, 0x0($a0)
/* 1C7A0 8002BFA0 F2AF0008 */  j          .L8002BFC8
/* 1C7A4 8002BFA4 00000000 */   nop
.L8002BFA8:
/* 1C7A8 8002BFA8 0780033C */  lui        $v1, %hi(D_800774B4)
/* 1C7AC 8002BFAC B4746324 */  addiu      $v1, $v1, %lo(D_800774B4)
/* 1C7B0 8002BFB0 0000628C */  lw         $v0, 0x0($v1)
/* 1C7B4 8002BFB4 00000000 */  nop
/* 1C7B8 8002BFB8 00024230 */  andi       $v0, $v0, 0x200
/* 1C7BC 8002BFBC 02004010 */  beqz       $v0, .L8002BFC8
/* 1C7C0 8002BFC0 00010224 */   addiu     $v0, $zero, 0x100
/* 1C7C4 8002BFC4 000062AC */  sw         $v0, 0x0($v1)
.L8002BFC8:
/* 1C7C8 8002BFC8 2800BF8F */  lw         $ra, 0x28($sp)
/* 1C7CC 8002BFCC 2400B18F */  lw         $s1, 0x24($sp)
/* 1C7D0 8002BFD0 2000B08F */  lw         $s0, 0x20($sp)
/* 1C7D4 8002BFD4 3000BD27 */  addiu      $sp, $sp, 0x30
/* 1C7D8 8002BFD8 0800E003 */  jr         $ra
/* 1C7DC 8002BFDC 00000000 */   nop
.size func_8002BBE0, . - func_8002BBE0
