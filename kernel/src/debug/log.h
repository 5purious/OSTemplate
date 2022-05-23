#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

typedef enum {
   S_WARNING,
   S_INFO,
   S_PANIC
} STATUS;


void log(const char* format, STATUS status, ...);


#endif
