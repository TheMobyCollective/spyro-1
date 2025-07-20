# Looks for this:
# .section .rodata
# .align	3
# turns it into:
# .section .rodata.jtbl
# .align 3

import sys

def fix_section(lines):
    lines = iter(lines)
    for line in lines:
        if line.strip().startswith('.section .rodata'): # Hold the line, if the next line is .align 3
            next_line = next(lines, "")
            if next_line.strip().replace("\t", " ").startswith('.align 3'):
                yield '.section .rodata.jtbl\n'
                yield next_line
            else:
                yield line
                yield next_line
        elif line.strip().replace("\t", " ").startswith('.align 3'):
            # If we are here, it means the previous line was not .section .rodata
            yield '.section .rodata\n'
            yield line
        else:
            yield line

lines = sys.stdin.readlines()
for line in fix_section(lines):
    sys.stdout.write(line)