
.include "macro.inc"

.section .data

dlabel D_8006FCCC
/* 604CC 8006FCCC */          .byte 0x00
/* 604CC 8006FCCD */          .byte 0x01
/* 604CC 8006FCCE */          .byte 0xFF
/* 604CC 8006FCCF */          .byte 0xFF
/* 604CC 8006FCD0 */          .byte 0xFF
/* 604CC 8006FCD1 */          .byte 0xFF
.size D_8006FCCC, . - D_8006FCCC
