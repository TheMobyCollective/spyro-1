# Takes the assembly source code from stdin and removes sections that are defined in the game.sbss file
# then outputs the modified source code to stdout
# Usage: cat camera.s | python3 tools/remove_sections.py > camera.s

import sys

sections_to_remove = ['.sbss', '.bss']

def remove_sections(lines):
    lines = iter(lines)
    for line in lines:
        if line.strip().startswith('.section'):
            if "\t" in line.strip():
                section_name = line.strip().split('\t')[1].split(",")[0].strip()
            else:
                section_name = line.strip().split(' ')[1].split(",")[0].strip()
            if section_name in sections_to_remove:
                line = next(lines)
                while ":" in line or ".space" in line or ".align" in line or ".type" in line or ".size" in line or ".globl" in line:
                    line = next(lines, "")
                yield line
            else:
                yield line
        else:
            yield line

lines = sys.stdin.readlines()
for line in remove_sections(lines):
    sys.stdout.write(line)