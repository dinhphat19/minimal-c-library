// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence) {
  /* TODO: Implement lseek(). */
  long ret = syscall(__NR_lseek, fd, offset, whence);
  // in file syscall_list.h __NR_lseek <-> 8 => so we can also wirte
  // syscall(8,fd,offset,whence)

  if (ret < 0) {
    errno = -ret;
    return -1;
  }

  return (off_t)ret;
}
