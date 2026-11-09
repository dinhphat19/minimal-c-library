// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <unistd.h>

int ftruncate(int fd, off_t length) {
  /* TODO: Implement ftruncate(). */
  int ret = syscall(__NR_ftruncate, fd, length);
  // in file syscall_list.h __NR_lseek <-> 77 => so we can also wirte
  // syscall(77,fd,lenght)
  if (ret < 0) {
    errno = -ret;
    return -1;
  }
  return 0;
}
