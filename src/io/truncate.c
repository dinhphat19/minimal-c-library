// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <unistd.h>

int truncate(const char *path, off_t length) {
  /* TODO: Implement truncate(). */
  int ret = syscall(__NR_truncate, path, length);
  // in file syscall_list.h __NR_lseek <-> 76 => so we can also wirte
  // syscall(76,path,lenght)
  if (ret < 0) {
    errno = -ret;
    return -1;
  }
  return 0;
}
