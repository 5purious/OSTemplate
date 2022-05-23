#include <drivers/video/Framebuffer.h>
#include <util/string.h>

static void(*write_callback)(const char* str, size_t n_length) = NULL;


void framebuffer_init(void(*root_write)(const char* str, size_t n_length)) {
    if (write_callback != NULL) return;
    write_callback = root_write;
}


void kwrite(const char* str) {
    write_callback(str, strlen(str));
}
