.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8005637C
/* 46B7C 8005637C 68FFBD27 */  addiu      $sp, $sp, -0x98
/* 46B80 80056380 8400B5AF */  sw         $s5, 0x84($sp)
/* 46B84 80056384 21A80000 */  addu       $s5, $zero, $zero
/* 46B88 80056388 7C00B3AF */  sw         $s3, 0x7C($sp)
/* 46B8C 8005638C 21980000 */  addu       $s3, $zero, $zero
/* 46B90 80056390 8C00B7AF */  sw         $s7, 0x8C($sp)
/* 46B94 80056394 01001724 */  addiu      $s7, $zero, 0x1
/* 46B98 80056398 0780023C */  lui        $v0, %hi(g_Camera + 0x50)
/* 46B9C 8005639C 206E4224 */  addiu      $v0, $v0, %lo(g_Camera + 0x50)
/* 46BA0 800563A0 9000BEAF */  sw         $fp, 0x90($sp)
/* 46BA4 800563A4 07801E3C */  lui        $fp, %hi(g_Spu + 0x2C)
/* 46BA8 800563A8 345FDE27 */  addiu      $fp, $fp, %lo(g_Spu + 0x2C)
/* 46BAC 800563AC 8000B4AF */  sw         $s4, 0x80($sp)
/* 46BB0 800563B0 0400D427 */  addiu      $s4, $fp, 0x4
/* 46BB4 800563B4 8800B6AF */  sw         $s6, 0x88($sp)
/* 46BB8 800563B8 1000D627 */  addiu      $s6, $fp, 0x10
/* 46BBC 800563BC 9400BFAF */  sw         $ra, 0x94($sp)
/* 46BC0 800563C0 7800B2AF */  sw         $s2, 0x78($sp)
/* 46BC4 800563C4 7400B1AF */  sw         $s1, 0x74($sp)
/* 46BC8 800563C8 7000B0AF */  sw         $s0, 0x70($sp)
/* 46BCC 800563CC 00004294 */  lhu        $v0, 0x0($v0)
/* 46BD0 800563D0 21880000 */  addu       $s1, $zero, $zero
/* 46BD4 800563D4 02110200 */  srl        $v0, $v0, 4
/* 46BD8 800563D8 6800A2A3 */  sb         $v0, 0x68($sp)
.L800563DC:
/* 46BDC 800563DC 0780013C */  lui        $at, %hi(g_Spu + 0x36)
/* 46BE0 800563E0 21083100 */  addu       $at, $at, $s1
/* 46BE4 800563E4 3E5F2394 */  lhu        $v1, %lo(g_Spu + 0x36)($at)
/* 46BE8 800563E8 00000000 */  nop
/* 46BEC 800563EC 40006230 */  andi       $v0, $v1, 0x40
/* 46BF0 800563F0 06004010 */  beqz       $v0, .L8005640C
/* 46BF4 800563F4 01006230 */   andi      $v0, $v1, 0x1
/* 46BF8 800563F8 0780013C */  lui        $at, %hi(g_Spu + 0x36)
/* 46BFC 800563FC 21083100 */  addu       $at, $at, $s1
/* 46C00 80056400 3E5F20A4 */  sh         $zero, %lo(g_Spu + 0x36)($at)
/* 46C04 80056404 E5590108 */  j          .L80056794
/* 46C08 80056408 1C009426 */   addiu     $s4, $s4, 0x1C
.L8005640C:
/* 46C0C 8005640C E0004010 */  beqz       $v0, .L80056790
/* 46C10 80056410 04807702 */   sllv      $s0, $s7, $s3
/* 46C14 80056414 7472010C */  jal        SpuGetKeyStatus
/* 46C18 80056418 21200002 */   addu      $a0, $s0, $zero
/* 46C1C 8005641C 0780013C */  lui        $at, %hi(g_Spu + 0x36)
/* 46C20 80056420 21083100 */  addu       $at, $at, $s1
/* 46C24 80056424 3E5F2494 */  lhu        $a0, %lo(g_Spu + 0x36)($at)
/* 46C28 80056428 21184000 */  addu       $v1, $v0, $zero
/* 46C2C 8005642C 02008230 */  andi       $v0, $a0, 0x2
/* 46C30 80056430 09004010 */  beqz       $v0, .L80056458
/* 46C34 80056434 FF006230 */   andi      $v0, $v1, 0xFF
/* 46C38 80056438 03000824 */  addiu      $t0, $zero, 0x3
/* 46C3C 8005643C 0F004814 */  bne        $v0, $t0, .L8005647C
/* 46C40 80056440 00000000 */   nop
/* 46C44 80056444 0780013C */  lui        $at, %hi(g_Spu + 0x40)
/* 46C48 80056448 21083100 */  addu       $at, $at, $s1
/* 46C4C 8005644C 485F238C */  lw         $v1, %lo(g_Spu + 0x40)($at)
/* 46C50 80056450 6D590108 */  j          .L800565B4
/* 46C54 80056454 25A8B002 */   or        $s5, $s5, $s0
.L80056458:
/* 46C58 80056458 04005710 */  beq        $v0, $s7, .L8005646C
/* 46C5C 8005645C 00000000 */   nop
/* 46C60 80056460 03000824 */  addiu      $t0, $zero, 0x3
/* 46C64 80056464 05004814 */  bne        $v0, $t0, .L8005647C
/* 46C68 80056468 00000000 */   nop
.L8005646C:
/* 46C6C 8005646C 02008234 */  ori        $v0, $a0, 0x2
/* 46C70 80056470 0780013C */  lui        $at, %hi(g_Spu + 0x36)
/* 46C74 80056474 21083100 */  addu       $at, $at, $s1
/* 46C78 80056478 3E5F22A4 */  sh         $v0, %lo(g_Spu + 0x36)($at)
.L8005647C:
/* 46C7C 8005647C 0780013C */  lui        $at, %hi(g_Spu + 0x36)
/* 46C80 80056480 21083100 */  addu       $at, $at, $s1
/* 46C84 80056484 3E5F2394 */  lhu        $v1, %lo(g_Spu + 0x36)($at)
/* 46C88 80056488 00000000 */  nop
/* 46C8C 8005648C 01006230 */  andi       $v0, $v1, 0x1
/* 46C90 80056490 BF004010 */  beqz       $v0, .L80056790
/* 46C94 80056494 1C006330 */   andi      $v1, $v1, 0x1C
/* 46C98 80056498 08000224 */  addiu      $v0, $zero, 0x8
/* 46C9C 8005649C 0E006210 */  beq        $v1, $v0, .L800564D8
/* 46CA0 800564A0 09006228 */   slti      $v0, $v1, 0x9
/* 46CA4 800564A4 05004010 */  beqz       $v0, .L800564BC
/* 46CA8 800564A8 04000224 */   addiu     $v0, $zero, 0x4
/* 46CAC 800564AC 08006210 */  beq        $v1, $v0, .L800564D0
/* 46CB0 800564B0 00200224 */   addiu     $v0, $zero, 0x2000
/* 46CB4 800564B4 C4590108 */  j          .L80056710
/* 46CB8 800564B8 00000000 */   nop
.L800564BC:
/* 46CBC 800564BC 10000224 */  addiu      $v0, $zero, 0x10
/* 46CC0 800564C0 89006210 */  beq        $v1, $v0, .L800566E8
/* 46CC4 800564C4 00000000 */   nop
/* 46CC8 800564C8 C4590108 */  j          .L80056710
/* 46CCC 800564CC 00000000 */   nop
.L800564D0:
/* 46CD0 800564D0 C2590108 */  j          .L80056708
/* 46CD4 800564D4 2200A2A7 */   sh        $v0, 0x22($sp)
.L800564D8:
/* 46CD8 800564D8 21206002 */  addu       $a0, $s3, $zero
/* 46CDC 800564DC 21283E02 */  addu       $a1, $s1, $fp
/* 46CE0 800564E0 AD76010C */  jal        SpuGetVoiceVolume
/* 46CE4 800564E4 0200A624 */   addiu     $a2, $a1, 0x2
/* 46CE8 800564E8 0780013C */  lui        $at, %hi(g_Spu + 0x28)
/* 46CEC 800564EC 21083100 */  addu       $at, $at, $s1
/* 46CF0 800564F0 305F258C */  lw         $a1, %lo(g_Spu + 0x28)($at)
/* 46CF4 800564F4 00000000 */  nop
/* 46CF8 800564F8 5500A290 */  lbu        $v0, 0x55($a1)
/* 46CFC 800564FC 00000000 */  nop
/* 46D00 80056500 80920200 */  sll        $s2, $v0, 10
/* 46D04 80056504 02004016 */  bnez       $s2, .L80056510
/* 46D08 80056508 5800B027 */   addiu     $s0, $sp, 0x58
/* 46D0C 8005650C 00401224 */  addiu      $s2, $zero, 0x4000
.L80056510:
/* 46D10 80056510 21200002 */  addu       $a0, $s0, $zero
/* 46D14 80056514 0780063C */  lui        $a2, %hi(g_Camera + 0x28)
/* 46D18 80056518 F86DC624 */  addiu      $a2, $a2, %lo(g_Camera + 0x28)
/* 46D1C 8005651C E35D000C */  jal        VecSub
/* 46D20 80056520 0C00A524 */   addiu     $a1, $a1, 0xC
/* 46D24 80056524 21200002 */  addu       $a0, $s0, $zero
/* 46D28 80056528 7F5C000C */  jal        VecMagnitude
/* 46D2C 8005652C 01000524 */   addiu     $a1, $zero, 0x1
/* 46D30 80056530 21804000 */  addu       $s0, $v0, $zero
/* 46D34 80056534 2A101202 */  slt        $v0, $s0, $s2
/* 46D38 80056538 52004014 */  bnez       $v0, .L80056684
/* 46D3C 8005653C 21300000 */   addu      $a2, $zero, $zero
/* 46D40 80056540 D4FFC427 */  addiu      $a0, $fp, -0x2C
/* 46D44 80056544 0780013C */  lui        $at, %hi(g_Spu + 0x2E)
/* 46D48 80056548 21083100 */  addu       $at, $at, $s1
/* 46D4C 8005654C 365F2294 */  lhu        $v0, %lo(g_Spu + 0x2E)($at)
/* 46D50 80056550 21202402 */  addu       $a0, $s1, $a0
/* 46D54 80056554 00140200 */  sll        $v0, $v0, 16
/* 46D58 80056558 43140200 */  sra        $v0, $v0, 17
/* 46D5C 8005655C 2E0082A4 */  sh         $v0, 0x2E($a0)
/* 46D60 80056560 2200A2A7 */  sh         $v0, 0x22($sp)
/* 46D64 80056564 0780013C */  lui        $at, %hi(g_Spu + 0x2C)
/* 46D68 80056568 21083100 */  addu       $at, $at, $s1
/* 46D6C 8005656C 345F2294 */  lhu        $v0, %lo(g_Spu + 0x2C)($at)
/* 46D70 80056570 00000000 */  nop
/* 46D74 80056574 00140200 */  sll        $v0, $v0, 16
/* 46D78 80056578 432C0200 */  sra        $a1, $v0, 17
/* 46D7C 8005657C 2118A000 */  addu       $v1, $a1, $zero
/* 46D80 80056580 2C0083A4 */  sh         $v1, 0x2C($a0)
/* 46D84 80056584 2200A287 */  lh         $v0, 0x22($sp)
/* 46D88 80056588 00000000 */  nop
/* 46D8C 8005658C 40004228 */  slti       $v0, $v0, 0x40
/* 46D90 80056590 1B004010 */  beqz       $v0, .L80056600
/* 46D94 80056594 2000A3A7 */   sh        $v1, 0x20($sp)
/* 46D98 80056598 4000A228 */  slti       $v0, $a1, 0x40
/* 46D9C 8005659C 18004010 */  beqz       $v0, .L80056600
/* 46DA0 800565A0 04107702 */   sllv      $v0, $s7, $s3
/* 46DA4 800565A4 0780013C */  lui        $at, %hi(g_Spu + 0x40)
/* 46DA8 800565A8 21083100 */  addu       $at, $at, $s1
/* 46DAC 800565AC 485F238C */  lw         $v1, %lo(g_Spu + 0x40)($at)
/* 46DB0 800565B0 25A8A202 */  or         $s5, $s5, $v0
.L800565B4:
/* 46DB4 800565B4 02006010 */  beqz       $v1, .L800565C0
/* 46DB8 800565B8 7F000224 */   addiu     $v0, $zero, 0x7F
/* 46DBC 800565BC 000062A0 */  sb         $v0, 0x0($v1)
.L800565C0:
/* 46DC0 800565C0 40000224 */  addiu      $v0, $zero, 0x40
/* 46DC4 800565C4 0780013C */  lui        $at, %hi(g_Spu + 0x36)
/* 46DC8 800565C8 21083100 */  addu       $at, $at, $s1
/* 46DCC 800565CC 3E5F22A4 */  sh         $v0, %lo(g_Spu + 0x36)($at)
/* 46DD0 800565D0 FF000224 */  addiu      $v0, $zero, 0xFF
/* 46DD4 800565D4 0780013C */  lui        $at, %hi(g_Spu + 0x40)
/* 46DD8 800565D8 21083100 */  addu       $at, $at, $s1
/* 46DDC 800565DC 485F20AC */  sw         $zero, %lo(g_Spu + 0x40)($at)
/* 46DE0 800565E0 0780013C */  lui        $at, %hi(g_Spu + 0x28)
/* 46DE4 800565E4 21083100 */  addu       $at, $at, $s1
/* 46DE8 800565E8 305F20AC */  sw         $zero, %lo(g_Spu + 0x28)($at)
/* 46DEC 800565EC 0780013C */  lui        $at, %hi(g_Spu + 0x35)
/* 46DF0 800565F0 21083100 */  addu       $at, $at, $s1
/* 46DF4 800565F4 3D5F22A0 */  sb         $v0, %lo(g_Spu + 0x35)($at)
/* 46DF8 800565F8 E5590108 */  j          .L80056794
/* 46DFC 800565FC 1C009426 */   addiu     $s4, $s4, 0x1C
.L80056600:
/* 46E00 80056600 0780043C */  lui        $a0, %hi(g_Spu + 0x324)
/* 46E04 80056604 2C628424 */  addiu      $a0, $a0, %lo(g_Spu + 0x324)
/* 46E08 80056608 0780013C */  lui        $at, %hi(g_Spu + 0x2C)
/* 46E0C 8005660C 21083100 */  addu       $at, $at, $s1
/* 46E10 80056610 345F2384 */  lh         $v1, %lo(g_Spu + 0x2C)($at)
/* 46E14 80056614 0000828C */  lw         $v0, 0x0($a0)
/* 46E18 80056618 00000000 */  nop
/* 46E1C 8005661C 18006200 */  mult       $v1, $v0
/* 46E20 80056620 0780013C */  lui        $at, %hi(g_Spu + 0x2E)
/* 46E24 80056624 21083100 */  addu       $at, $at, $s1
/* 46E28 80056628 365F2384 */  lh         $v1, %lo(g_Spu + 0x2E)($at)
/* 46E2C 8005662C 12400000 */  mflo       $t0
/* 46E30 80056630 03130800 */  sra        $v0, $t0, 12
/* 46E34 80056634 0780013C */  lui        $at, %hi(g_Spu + 0x2C)
/* 46E38 80056638 21083100 */  addu       $at, $at, $s1
/* 46E3C 8005663C 345F22A4 */  sh         $v0, %lo(g_Spu + 0x2C)($at)
/* 46E40 80056640 0000828C */  lw         $v0, 0x0($a0)
/* 46E44 80056644 00000000 */  nop
/* 46E48 80056648 18006200 */  mult       $v1, $v0
/* 46E4C 8005664C 21206002 */  addu       $a0, $s3, $zero
/* 46E50 80056650 0780013C */  lui        $at, %hi(g_Spu + 0x2C)
/* 46E54 80056654 21083100 */  addu       $at, $at, $s1
/* 46E58 80056658 345F2584 */  lh         $a1, %lo(g_Spu + 0x2C)($at)
/* 46E5C 8005665C 12400000 */  mflo       $t0
/* 46E60 80056660 03130800 */  sra        $v0, $t0, 12
/* 46E64 80056664 00340200 */  sll        $a2, $v0, 16
/* 46E68 80056668 0780013C */  lui        $at, %hi(g_Spu + 0x2E)
/* 46E6C 8005666C 21083100 */  addu       $at, $at, $s1
/* 46E70 80056670 365F22A4 */  sh         $v0, %lo(g_Spu + 0x2E)($at)
/* 46E74 80056674 9D76010C */  jal        SpuSetVoiceVolume
/* 46E78 80056678 03340600 */   sra       $a2, $a2, 16
/* 46E7C 8005667C E5590108 */  j          .L80056794
/* 46E80 80056680 1C009426 */   addiu     $s4, $s4, 0x1C
.L80056684:
/* 46E84 80056684 0780013C */  lui        $at, %hi(g_Spu + 0x28)
/* 46E88 80056688 21083100 */  addu       $at, $at, $s1
/* 46E8C 8005668C 305F228C */  lw         $v0, %lo(g_Spu + 0x28)($at)
/* 46E90 80056690 0780043C */  lui        $a0, %hi(g_Camera + 0x28)
/* 46E94 80056694 F86D848C */  lw         $a0, %lo(g_Camera + 0x28)($a0)
/* 46E98 80056698 0780053C */  lui        $a1, %hi(g_Camera + 0x2C)
/* 46E9C 8005669C FC6DA58C */  lw         $a1, %lo(g_Camera + 0x2C)($a1)
/* 46EA0 800566A0 0C00438C */  lw         $v1, 0xC($v0)
/* 46EA4 800566A4 1000428C */  lw         $v0, 0x10($v0)
/* 46EA8 800566A8 23206400 */  subu       $a0, $v1, $a0
/* 46EAC 800566AC AD5A000C */  jal        Atan2
/* 46EB0 800566B0 23284500 */   subu      $a1, $v0, $a1
/* 46EB4 800566B4 2000A427 */  addiu      $a0, $sp, 0x20
/* 46EB8 800566B8 21280002 */  addu       $a1, $s0, $zero
/* 46EBC 800566BC 6800A893 */  lbu        $t0, 0x68($sp)
/* 46EC0 800566C0 21384002 */  addu       $a3, $s2, $zero
/* 46EC4 800566C4 23104800 */  subu       $v0, $v0, $t0
/* 46EC8 800566C8 FF004630 */  andi       $a2, $v0, 0xFF
/* 46ECC 800566CC 0780083C */  lui        $t0, %hi(g_Spu + 0x38)
/* 46ED0 800566D0 405F0825 */  addiu      $t0, $t0, %lo(g_Spu + 0x38)
/* 46ED4 800566D4 21102802 */  addu       $v0, $s1, $t0
/* 46ED8 800566D8 215B010C */  jal        func_80056C84
/* 46EDC 800566DC 1000A2AF */   sw        $v0, 0x10($sp)
/* 46EE0 800566E0 C4590108 */  j          .L80056710
/* 46EE4 800566E4 00000000 */   nop
.L800566E8:
/* 46EE8 800566E8 0780013C */  lui        $at, %hi(g_Spu + 0x2E)
/* 46EEC 800566EC 21083100 */  addu       $at, $at, $s1
/* 46EF0 800566F0 365F2294 */  lhu        $v0, %lo(g_Spu + 0x2E)($at)
/* 46EF4 800566F4 00000000 */  nop
/* 46EF8 800566F8 2200A2A7 */  sh         $v0, 0x22($sp)
/* 46EFC 800566FC 0780013C */  lui        $at, %hi(g_Spu + 0x2C)
/* 46F00 80056700 21083100 */  addu       $at, $at, $s1
/* 46F04 80056704 345F2294 */  lhu        $v0, %lo(g_Spu + 0x2C)($at)
.L80056708:
/* 46F08 80056708 00000000 */  nop
/* 46F0C 8005670C 2000A2A7 */  sh         $v0, 0x20($sp)
.L80056710:
/* 46F10 80056710 2000A287 */  lh         $v0, 0x20($sp)
/* 46F14 80056714 0780033C */  lui        $v1, %hi(g_Spu + 0x324)
/* 46F18 80056718 2C62638C */  lw         $v1, %lo(g_Spu + 0x324)($v1)
/* 46F1C 8005671C 00000000 */  nop
/* 46F20 80056720 18004300 */  mult       $v0, $v1
/* 46F24 80056724 12480000 */  mflo       $t1
/* 46F28 80056728 2200A287 */  lh         $v0, 0x22($sp)
/* 46F2C 8005672C 00000000 */  nop
/* 46F30 80056730 18004300 */  mult       $v0, $v1
/* 46F34 80056734 03000824 */  addiu      $t0, $zero, 0x3
/* 46F38 80056738 1C00A8AF */  sw         $t0, 0x1C($sp)
/* 46F3C 8005673C 04107702 */  sllv       $v0, $s7, $s3
/* 46F40 80056740 1800A2AF */  sw         $v0, 0x18($sp)
/* 46F44 80056744 03130900 */  sra        $v0, $t1, 12
/* 46F48 80056748 2000A2A7 */  sh         $v0, 0x20($sp)
/* 46F4C 8005674C 12180000 */  mflo       $v1
/* 46F50 80056750 03130300 */  sra        $v0, $v1, 12
/* 46F54 80056754 2200A2A7 */  sh         $v0, 0x22($sp)
/* 46F58 80056758 0000828E */  lw         $v0, 0x0($s4)
/* 46F5C 8005675C 0000C38E */  lw         $v1, 0x0($s6)
/* 46F60 80056760 00000000 */  nop
/* 46F64 80056764 21104300 */  addu       $v0, $v0, $v1
/* 46F68 80056768 000082AE */  sw         $v0, 0x0($s4)
/* 46F6C 8005676C 0000C0AE */  sw         $zero, 0x0($s6)
/* 46F70 80056770 1C00A28F */  lw         $v0, 0x1C($sp)
/* 46F74 80056774 00000000 */  nop
/* 46F78 80056778 10004234 */  ori        $v0, $v0, 0x10
/* 46F7C 8005677C 1C00A2AF */  sw         $v0, 0x1C($sp)
/* 46F80 80056780 0000828E */  lw         $v0, 0x0($s4)
/* 46F84 80056784 1800A427 */  addiu      $a0, $sp, 0x18
/* 46F88 80056788 EB71010C */  jal        SpuSetVoiceAttr
/* 46F8C 8005678C 2C00A2A7 */   sh        $v0, 0x2C($sp)
.L80056790:
/* 46F90 80056790 1C009426 */  addiu      $s4, $s4, 0x1C
.L80056794:
/* 46F94 80056794 1C00D626 */  addiu      $s6, $s6, 0x1C
/* 46F98 80056798 01007326 */  addiu      $s3, $s3, 0x1
/* 46F9C 8005679C 1800622A */  slti       $v0, $s3, 0x18
/* 46FA0 800567A0 0EFF4014 */  bnez       $v0, .L800563DC
/* 46FA4 800567A4 1C003126 */   addiu     $s1, $s1, 0x1C
/* 46FA8 800567A8 0780043C */  lui        $a0, %hi(g_Spu + 0x334)
/* 46FAC 800567AC 3C628424 */  addiu      $a0, $a0, %lo(g_Spu + 0x334)
/* 46FB0 800567B0 0000838C */  lw         $v1, 0x0($a0)
/* 46FB4 800567B4 21100000 */  addu       $v0, $zero, $zero
/* 46FB8 800567B8 25187500 */  or         $v1, $v1, $s5
/* 46FBC 800567BC 000083AC */  sw         $v1, 0x0($a0)
/* 46FC0 800567C0 9400BF8F */  lw         $ra, 0x94($sp)
/* 46FC4 800567C4 9000BE8F */  lw         $fp, 0x90($sp)
/* 46FC8 800567C8 8C00B78F */  lw         $s7, 0x8C($sp)
/* 46FCC 800567CC 8800B68F */  lw         $s6, 0x88($sp)
/* 46FD0 800567D0 8400B58F */  lw         $s5, 0x84($sp)
/* 46FD4 800567D4 8000B48F */  lw         $s4, 0x80($sp)
/* 46FD8 800567D8 7C00B38F */  lw         $s3, 0x7C($sp)
/* 46FDC 800567DC 7800B28F */  lw         $s2, 0x78($sp)
/* 46FE0 800567E0 7400B18F */  lw         $s1, 0x74($sp)
/* 46FE4 800567E4 7000B08F */  lw         $s0, 0x70($sp)
/* 46FE8 800567E8 9800BD27 */  addiu      $sp, $sp, 0x98
/* 46FEC 800567EC 0800E003 */  jr         $ra
/* 46FF0 800567F0 00000000 */   nop
.size func_8005637C, . - func_8005637C
