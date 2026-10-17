from get_overlay_objects import get_overlays, overlay_obj_name

print("OVERLAY main_BSS_END : NOCROSSREFS SUBALIGN(4) {")
for overlay_index, overlay_name, files, padding_garbage in get_overlays():
    print("    ." + overlay_name + " {")
    print("        LONG(" + str(overlay_index) + ");")
    for section in [".rodata", ".text", ".data", ".bss"]:
        for file in files:
            print("        " + overlay_obj_name(overlay_name, file) + "(" + section + "*);")
            if section == ".rodata" and file in ["balloonist.c", "flight.c"]:
                for byte in padding_garbage:
                    print("        BYTE(" + hex(byte) + ");")
    print("        ." + overlay_name + "_end = .;")
    print("        . = ALIGN(., 2048);")
    print("    }")
    print()
print("}")
