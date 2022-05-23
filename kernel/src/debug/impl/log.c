#include <debug/log.h>
#include <util/string.h>
#include <stdarg.h>
#include <drivers/video/Framebuffer.h>


void log(const char* format, STATUS status, ...) {
  va_list ptr;

  size_t args = 0;

  for (size_t i = 0; i < strlen(format); ++i) {
    if (format[i] == '%') {
      switch (format[i + 1]) {
      case 's':
      case 'd':
        ++args;
        i += 2;
        break;
      }
    }
  }

  // A hacky way to get rid of the warning: second parameter of 'va_start' not last named argument
  STATUS s = status;
  status ^= status;
  status += args;
  va_start(ptr, status);

  int color = 0xFFEA00;

  switch (s) {
  case S_WARNING:
    kwrite("\e[1;35m[WARNING] ");
    break;
  case S_INFO:
    kwrite("\e[1;36m[INFO] ");
    break;
  case S_PANIC:
    kwrite("\e[1;31m** KERNEL PANIC **\n");
    break;
  }

  for (size_t i = 0; i < strlen(format); ++i) {
    if (format[i] == '%') {
      switch (format[i + 1]) {
      case 's':
        {
          const char* arg = va_arg(ptr, const char*);

          for (size_t j = 0; j < strlen(arg); ++j) {
            char terminated[2] = {arg[j], 0x0};
            kwrite(terminated);
          }

          ++i;

        }

        continue;
      case 'd':
        {
          int arg = va_arg(ptr, int);

          kwrite(dec2str(arg));
        }
        ++i;
        continue;
      case 'x':
        {
          int arg = va_arg(ptr, int);
          kwrite((char*)hex2str(arg));
          ++i;
          continue;
        }
      }
    }

    char terminated[2] = {format[i], 0x0};
    kwrite(terminated);
  }
}
