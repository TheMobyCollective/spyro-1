#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#if !defined(SPLAT) && !defined(M2CTX) && !defined(PERMUTER)
#ifndef INCLUDE_ASM

#define INCLUDE_ASM(FOLDER, NAME)                                              \
  __asm__(".section .text\n"                                                   \
          "\t.set noat\n"                                                      \
          "\t.set noreorder\n"                                                 \
          "\t.align\t2\n"                                                      \
          "\t.globl\t" #NAME "\n"                                              \
          "\t.type " #NAME ", @function\n"                                     \
          "\t.ent\t" #NAME "\n" #NAME ":\n"                                    \
          "\t.include \"" FOLDER "/" #NAME ".s\"\n"                            \
          "\t.set reorder\n"                                                   \
          "\t.set at\n"                                                        \
          "\t.end\t" #NAME "\n"                                                \
          ".end" #NAME ":\n"                                                   \
          "\t.size\t" #NAME ",.end" #NAME "-" #NAME "\n"                       \
          "\t.globl\t" #NAME ".NON_MATCHING\n"                                 \
          "\t" #NAME ".NON_MATCHING"                                           \
          " = " #NAME "\n")

#ifdef _HAS_MASPSX
#define INCLUDE_ASM_REORDER_HACK(FOLDER, NAME)                                 \
  void __maspsx_include_asm_hack_##NAME() {                                    \
    __asm__(".section .text # maspsx-keep\n"                                   \
            "\t.set noat # maspsx-keep\n"                                      \
            "\t.set noreorder # maspsx-keep\n"                                 \
            "\t.align\t2 # maspsx-keep\n"                                      \
            "\t.globl\t" #NAME " # maspsx-keep\n"                              \
            "\t.type " #NAME ", @function # maspsx-keep\n"                     \
            "\t.ent\t" #NAME " # maspsx-keep\n" #NAME ": # maspsx-keep\n"      \
            "__maspsx_include_asm_hack_" #NAME ": # maspsx-keep\n"             \
            "\t.include \"" FOLDER "/" #NAME ".s\" # maspsx-keep\n"            \
            "\t.set reorder # maspsx-keep\n"                                   \
            "\t.set at # maspsx-keep\n"                                        \
            "\t.end\t" #NAME " # maspsx-keep\n"                                \
            ".end" #NAME ": # maspsx-keep\n"                                   \
            "\t.size\t" #NAME ",.end" #NAME "-" #NAME " # maspsx-keep\n"       \
            "\t.globl\t" #NAME ".NON_MATCHING # maspsx-keep\n"                 \
            "\t" #NAME ".NON_MATCHING"                                         \
            " = " #NAME "\n # maspsx-keep");                                   \
  }
#else
#define INCLUDE_ASM_REORDER_HACK(FOLDER, NAME) INCLUDE_ASM(FOLDER, NAME)
#endif

#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)                                           \
  __asm__(".section .rodata\n"                                                 \
          "\t.include \"" FOLDER "/" #NAME ".s\"\n"                            \
          ".section .text")
#endif

#ifndef INCLUDE_ASM_MACRO
#define INCLUDE_ASM_MACRO
__asm__(".include \"macro.inc\"\n");
#endif

#else
#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)
#endif
#endif

#endif