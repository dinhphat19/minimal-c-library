// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source) {
  /* TODO: Implement strcpy(). */
  size_t k = strlen(source);
  for (size_t i = 0; i < k; i++) {
    destination[i] = source[i];
  }
  destination[k] = '\0';
  return destination;
}

char *strncpy(char *destination, const char *source, size_t len) {
  /* TODO: Implement strncpy(). */
  size_t i;
  // copy until len is reached or '\0'  is met in source
  for (i = 0; i < len && source[i] != '\0'; i++) {
    destination[i] = source[i];
  }
  // if len(source)<len, we fill destination with '\0' in the remain spaces
  for (; i < len; i++)
    destination[i] = '\0';
  return destination;
}

char *strcat(char *destination, const char *source) {
  /* TODO: Implement strcat(). */
  size_t x = strlen(destination);
  size_t y = strlen(source);
  for (size_t i = 0; i < y; i++) {
    destination[x + i] = source[i];
  }
  destination[x + y] = '\0';
  return destination;
}

char *strncat(char *destination, const char *source, size_t len) {
  /* TODO: Implement strncat(). */
  size_t x = strlen(destination);
  size_t i;
  // copy until len is reached or '\0'  is met in source
  for (i = 0; i < len && source[i] != '\0'; i++) {
    destination[x + i] = source[i];
  }
  // end the string imediately after the last character added
  destination[x + i] = '\0';
  return destination;
}

int strcmp(const char *str1, const char *str2) {
  /* TODO: Implement strcmp(). */

  // while run until str1 end AND two characters of 2 strings still remai equal
  while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
    str1++;
    str2++;
  }
  // unsigned char forces byte values to stay in the positive range(0->255)
  // make sure that larger byte codes always sort after smaller ones as required
  return (unsigned char)(*str1) - (unsigned char)(*str2);
}

int strncmp(const char *str1, const char *str2, size_t len) {
  /* TODO: Implement strncmp(). */
  while (len > 0 && *str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
    str1++;
    str2++;
    len--;
  }
  // if we have len character equal then return 0
  if (len == 0) {
    return 0;
  }
  return (unsigned char)(*str1) - (unsigned char)(*str2);
}

size_t strlen(const char *str) {
  size_t i = 0;

  for (; *str != '\0'; str++, i++)
    ;

  return i;
}

char *strchr(const char *str, int c) {
  /* TODO: Implement strchr(). */
  while (*str != '\0' && (*str) != (char)c) {
    str++;
  }
  if (*str == '\0')
    return NULL;
  return (char *)str;
}

char *strrchr(const char *str, int c) {
  /* TODO: Implement strrchr(). */
  const char *pointer = NULL;
  while (*str != '\0') {
    if (*str == (char)c)
      pointer = str;
    str++;
  }
  return (char *)pointer;
}

char *strstr(const char *haystack, const char *needle) {
  /* TODO: Implement strstr(). */
  if (*needle == '\0')
    return (char *)haystack;

  while (*haystack != '\0') {
    const char *h = haystack;
    const char *n = needle;
    while (*h != '\0' && *n != '\0' && *h == *n) {
      h++;
      n++;
    }
    // if we are able to pass all characters in needle => which means we found
    // the "needle" substring in haystack
    if (*n == '\0') {
      return (char *)haystack;
    }
    haystack++;
  }
  return NULL; // not found
}

char *strrstr(const char *haystack, const char *needle) {
  /* TODO: Implement strrstr(). */
  if (*needle == '\0') {
    return (char *)haystack;
  }
  const char *pointer = NULL;
  while (*haystack != '\0') {
    const char *h = haystack;
    const char *n = needle;

    while (*h != '\0' && *n != '\0' && *h == *n) {
      h++;
      n++;
    }

    if (*n == '\0') {
      pointer = haystack;
    }
    haystack++;
  }
  return (char *)pointer;
}

void *memcpy(void *destination, const void *source, size_t num) {
  /* TODO: Implement memcpy(). */
  char *d = (char *)destination;
  const char *s = (const char *)source;
  for (size_t i = 0; i < num; i++) {
    *d++ = *s++;
  }
  return destination;
}

void *memmove(void *destination, const void *source, size_t num) {
  /* TODO: Implement memmove(). */
  // if num=0 or destination=source=> return dest
  if (destination == source || num == 0)
    return destination;
  char *dest = (char *)destination;
  const char *src = (const char *)source;
  // CAZ1: when dest is before src->forward copy(from start to end)
  // or when the 2 memory blocks are completely separated
  if (dest < src) {
    for (size_t i = 0; i < num; i++) {
      dest[i] = src[i];
    }
  } else {
    for (size_t i = num; i > 0; i--) {
      dest[i - 1] = src[i - 1];
    }
	// CAZ2: when dest is after src and overlapping->backward copy(from end to
  	// start)
  }
  return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num) {
  /* TODO: Implement memcmp(). */
  const char *s1 = ptr1;
  const char *s2 = ptr2;
  while (num > 0 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
    s1++;
    s2++;
    num--;
  }
  if (num == 0)
    return 0;
  return (unsigned char)(*s1) - (unsigned char)(*s2);
}

void *memset(void *source, int value, size_t num) {
  /* TODO: Implement memset(). */
  char *src = source;
  for (size_t i = 0; i < num; i++) {
    src[i] = (unsigned char)value;
  }
  return source;
}
