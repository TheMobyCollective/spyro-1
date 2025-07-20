# Looks for this:
# .align	2
# $LC2:
# .ascii	"THE ADVENTURE BEGINS...\000"
# .align	2
# $LC3:
# .ascii	"ENTERING DEMO MODE...\000"
# turns it into: (Adds the missing .align 2)
# .align	2
# $LC2:
# .ascii	"THE ADVENTURE BEGINS...\000"
# .align	2
# $LC3:
# .ascii	"ENTERING DEMO MODE...\000"
# .align	2

import sys

def fix_section(lines):
    lines = iter(lines)
    for line in lines:
        if line.strip().startswith('.ascii'):
            # Check if the next line is .align 2
            next_line = next(lines, "")
            if next_line.strip().replace("\t", " ").startswith('.align 2'):
                yield line
                yield next_line
            else:
                # If not, add the missing .align 2 after the .ascii line
                yield line
                yield '.align\t2\n'
                yield next_line
        else:
            yield line

lines = sys.stdin.readlines()
for line in fix_section(lines):
    sys.stdout.write(line)