# Needed because there's a split between special_surfaces.c and overlay_pointers.c
# And this falls in there
.globl	g_OverlaySpacePointer
.section .rodata
.align	2
g_OverlaySpacePointer:
.word	main_BSS_END
