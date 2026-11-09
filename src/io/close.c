// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <unistd.h>

int close(int fd) {
  /* TODO: Implement close(). */
  // call syscall
  long ret = syscall(__NR_close, fd);
  // in file syscall_list.h __NR_close <-> 3 => so we can also wirte
  // syscall(3,fd)

  if (ret < 0) {
    errno = -ret;
    return -1;
  }
  return 0;
}
