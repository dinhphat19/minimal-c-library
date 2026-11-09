// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <sys/mman.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd,
           off_t offset) {
  /* TODO: Implement mmap(). */

  // imagine 'mmap' is like an application we submit to So to request a mem
  // array(RAM) there are 2 ways to request it: med1: (file mapping)->request a
  // block on RAM and load the exact contents of a file from hard drive into it
  // from then on, instead of using slow read/write calls, you just need to
  // modify the data in RAM, and the OS will automatically save those changes
  // back to the hard drive

  // med2:(request empty space-anonymous): request a completely empty block of
  // RAM that is not tied to any file on the hard drive giving the program total
  // freedom to use it THIS IS EXACTLY THE METHOD MALLOC() FUNCTION USES

  //'void *addr'-target address(which address your RAM array is located),
  //  in pratice, we rarely know which mem region is available
  // so we typically pass NULL to allow the OS to automatically locate and
  // select and appropriate address

  //'length' - length>0 -> number of bytes you wanna request for

  //'prot'(protection) , show us what we allowed to do with the memories
  //allocated
  //-> we pass in protection constant such as:
  // PROT_READ (allowed to read), PROT_WRITE (allowed to write), or use the
  // bitwise OR operator | to combine them (PROT_READ | PROT_WRITE)

  /*
  int flags (Memory attributes):
  This is a super important part that decides what kind of mem array we are
  asking for:
  ->MAP_SHARED: Any changes we make to this memory will be visible to other
  programs, or automatically saved to the hard drive (if we chose Method 1).
  ->MAP_PRIVATE: This memory is a private space (Copy-on-write). Any changes we
  make are only known to our own program.
  ->MAP_ANONYMOUS: This flag tells the Operating System: "I choose Method 2,
  just give me an empty space, do not read any file!". (When building a custom
  malloc, we will combine MAP_PRIVATE | MAP_ANONYMOUS).*/

  /*
  off_t offset (Starting point / Offset):
  If we are mapping a file, at which byte position of the file do we want to
   start copying?-> In practice: If we are just asking for empty space
  (MAP_ANONYMOUS), simply pass 0 here.
  */

  long ret = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);
  // equivalent with syscall(9,addr,length,prot,flags,fd,offset)

  if (ret < 0) {
    errno = -ret;
    return MAP_FAILED;
  }
  return (void *)ret;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags) {
  /* TODO: Implement mremap(). */

  /*
  mremap()-memory remap-> a system call created to change the size of a mem
  block that was previously allocated by mmap()

  realloc() is based on mremap()

  the OS will look at the new size you request to decide its next action:
  ->(new_size<old_size) : the kernel just "cut off" the end of the current mem
  block and releases the excess memory. the starting address of the mem block
  remains unchanged, and the data at the beginning is preserved

  ->(new_size>old_size): 2 situations
          +)situation 1: there is still free space immediately next to my
  memmory region(not yet occupied by anything else) the kernel simply extends
  your region into that free space.The starting address of the memory region
  remains unchanged
          +)situation 2: NO SPACE AVAILABLE next to my mem region. in this case,
  the kernel must find another sufficiently large free area elsewhere in RAM. it
  copies all my existing data to the new location,automatically frees the old
  memory region, and returns the address of the new location to me

  flags- this argument is important because it tells kernell what to do in
  situation 2(NO SPACE AVAILABLE)

  ->MREMAP_MAYMOVE : this is the flag i should use ( its macro value is
  typically 1). It allows the operating system to say: "If there isn't enough
  space to expand your current memory region, feel free to move it somewhere
  else for me."

  If we pass 0 (without this flag), the operating system is not allowed to move
  the memory region elsewhere. If there is no free space adjacent to the current
  region, the operation fails immediately and returns an error.
  */
  if (old_size == new_size)
    return old_address;

  long ret = syscall(__NR_mremap, old_address, old_size, new_size, flags);

  if (ret < 0) {
    errno = -ret;
    return MAP_FAILED;
  }
  return (void *)ret;
}

int munmap(void *addr, size_t length) {
  /* TODO: Implement munmap(). */

  /*
  munmap()-help release and take back access to a mem region that previously
  allocated(mapped) using mmap once munmap() executes successfully, the OS take
  back that mem region. if out program attemps to read from or write to that mem
  region again => end program and seg fault

  void *addr (Starting Address): A pointer to the first address of the memory
  region we want to release. This address must be the original pointer returned
  by mmap or mremap

  length (Size): The number of bytes in the memory region we want to release
  */

  if (length == 0) {
    return -1;
  }

  long ret = syscall(__NR_munmap, addr, length);

  if (ret < 0) {
    errno = -ret;
    return -1;
  }
  return (int)ret;
}
