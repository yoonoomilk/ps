#ifndef _INC_MMAN
#define _INC_MMAN

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXEC 0x4
#define PROT_NONE 0x0

#define MAP_SHARED 0x01
#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20

void* mmap(void* addr, size_t length, int prot, int flags, int fd, int offset);

int munmap(void* addr, size_t length);

int mprotect(void* addr, size_t len, int prot);

#ifdef __cplusplus
}
#endif

#endif /* _INC_MMAN */