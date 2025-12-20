
.include "macro.inc"

.section .data

/* Unknown data, I'm not sure what to attribute it to */
/* It got added after July, and exists in Foil too */
dlabel D_8006FCD4 
/* 604D4 8006FCD4 0000524A */ .word 0x4A520000
/* 604D8 8006FCD8 DE7BC618 */ .word 0x18C67BDE
/* 604DC 8006FCDC 6B2D630C */ .word 0x0C632D6B
/* 604E0 8006FCE0 F75E9C73 */ .word 0x739C5EF7
/* 604E4 8006FCE4 EF3D0821 */ .word 0x21083DEF
/* 604E8 8006FCE8 FF7F2104 */ .word 0x04217FFF
/* 604EC 8006FCEC 84103967 */ .word 0x67391084
/* 604F0 8006FCF0 B5564A29 */ .word 0x294A56B5
.size D_8006FCD4, . - D_8006FCD4
