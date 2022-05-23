#include <stdint.h>
#include <stddef.h>
#include <stivale2.h>
#include <drivers/video/Framebuffer.h>
#include <debug/log.h>

static uint8_t stack[4000];

void* get_tag(struct stivale2_struct* stivale2_struct, uint64_t id) {
    struct stivale2_tag* curTag = (void*)stivale2_struct->tags;

    while (1) {
        if (!(curTag)) {
            // End.
            return NULL;
        }

        if (curTag->identifier == id) {
            return curTag;
        }

        curTag = (void*)curTag->next;
    }
}

static struct stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },

    .flags = 0
};


static struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t)&terminal_hdr_tag
    },

    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0
};




__attribute__((section(".stivale2hdr"), used)) static struct stivale2_header stivale_hdr = {
    .entry_point = 0,
    .stack = (uintptr_t)stack,
     .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
     .tags = (uintptr_t)&framebuffer_hdr_tag
};


void _start(struct stivale2_struct* stivale2_struct) {
    struct stivale2_struct_tag_terminal* term_str_tag = get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);

   
    void(*root_write)(const char* str, size_t nlength) = (void*)term_str_tag->term_write;
    framebuffer_init(root_write);

    log("Hello!", S_INFO);

    while (1)
        __asm__ __volatile__("hlt");
}
