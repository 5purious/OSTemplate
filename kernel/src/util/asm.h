#ifndef ASM_H
#define ASM_H

// 2022 Ian Moffett <ian@kesscoin.com>

#define FULL_HALT __asm__ __volatile__("cli; hlt")
#define CLI __asm__ __volatile__("cli")
#define STI __asm__ __volatile__("sti")

#endif
