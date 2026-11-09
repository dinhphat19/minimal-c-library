// SPDX-License-Identifier: BSD-3-Clause

#include <internal/essentials.h>
#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

void *malloc(size_t size) {
  /* TODO: Implement malloc(). */
  if (size == 0)
    return NULL;

  void *str =
      mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  /*
  void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t
  offset)
  ->*adrr=0 => pass NULL to allow the OS to automatically locate and select and
  appropriate address
  ->length=size => the number of bytes we want to request from kernel
  ->prot=PROT_READ | PROT_WRITE => permissions of memory block => we can read
  and write in the new allocated mem block
  ->flag=MAP_PRIVATE | MAP_ANONYMOUS => RAM array 's  props : private region for
  my porgram(do not share processes with anothers prog) AND completely emty RAM
  (anonymous mem block and do not read or open any file)
  ->fd=-1 => because flag=MAP_ANONYMOUS (do not open or use any file) so we put
  -1 to show that "there is no file"
  ->offset=0 =>deter. starting position to copy from file , and because there is
  no file => 0
  */

  if (str == MAP_FAILED)
    return NULL;

  /*
  mem_list acts as a memory registry.
  System calls like munmap() and mremap() require the exact size of a memory
  block, but standard C pointers do not store their size. We use mem_list to
  track and look up the size associated with any allocated pointer.
  */

  mem_list_add(str, size);

  return str;
}

void *calloc(size_t nmemb, size_t size) {
  /* TODO: Implement calloc(). */
  if (nmemb == 0 || size == 0)
    return NULL;
  // nmemb-nr of elements
  // size-size of one element
  size_t total_size = nmemb * size;
  void *str = malloc(total_size);
  if (str == NULL)
    return NULL;
  memset(str, 0, total_size);
  return str;
}

void free(void *ptr) {
  /* TODO: Implement free(). */

  if (ptr == NULL)
    return;

  // Look up the pointer in our registry to get its original size (required by
  // OS)
  struct mem_list *str = mem_list_find(ptr);
  if (str == NULL) {
    return;
  }
  int do_free = munmap(ptr, str->len);
  if (do_free == 0) {
    mem_list_del(ptr);
  }
}

void *realloc(void *ptr, size_t size) {
  /* TODO: Implement realloc(). */
  // if we call realloc(NULL,size)=>automatically do malloc(size)
  if (ptr == NULL)
    return malloc(size);
  struct mem_list *str = mem_list_find(ptr);
  if (str == NULL)
    return NULL;
  size_t old_size = str->len;
  void *res = mremap(ptr, old_size, size, MREMAP_MAYMOVE);
  if (res == MAP_FAILED)
    return NULL;
  /*
  After mremap succeeds, the operating system may move the memory region to a
  completely new address (in this case, res -> update the new memory address in
  mem_list).
  */
  mem_list_del(ptr);       // delete old adress
  mem_list_add(res, size); // update new adress with new size

  return res;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
  /* TODO: Implement reallocarray(). */
  if (nmemb == 0 || size == 0)
    return NULL;
  size_t total_size = nmemb * size;
  if (ptr == NULL)
    return malloc(total_size);

  return realloc(ptr, total_size);
}
