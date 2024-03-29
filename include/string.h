#ifndef STRING_H
#define STRING_H

#include "types.h"

extern uint32_t strlen(const char *buf);
extern char *strcat(char *dest, const char *src);
extern char *strcpy(char *dest, const char *src);
extern int strcmp(const char *a, const char *b);
extern int strncmp(const char *a, const char *b, size_t n);
extern char *strchr(const char *s, int c);
extern char *strstr(const char *haystack, const char *needle);
extern void *memset(void *s, int c, size_t n);
extern void *memcpy(void *dest, const void *src, size_t n);
extern int memcmp(const void *s1, const void *s2, size_t n);
extern void *memmove(void *dest, const void *src, size_t n);
extern void *memchr(const void *s, int c, size_t n);
extern long atol(const char *ptr);

#endif /* STRING_H */