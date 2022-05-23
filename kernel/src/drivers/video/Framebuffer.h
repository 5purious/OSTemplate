#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

// 2022 Ian Moffett

#include <stddef.h>

void framebuffer_init(void(*root_write)(const char* str, size_t n_length));
void kwrite(const char* str);


#endif
