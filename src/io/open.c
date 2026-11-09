// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>

int open(const char *filename, int flags, ...) {
  /* TODO: Implement open system call. */
  mode_t mode;
  // mode_t is an integer data type in libc used to store file attirbutes, such
  // as file permissions and file types

  // if flag O_CREAT is set(appeared), get the "mode" argument from the variadic
  // parameters(...)
  if (flags && O_CREAT) {
    // variadic function (which function that can take a variable number of
    // arguments) open() is a variadic function

    va_list args;
    // va_list type to declare a variable that will store the list needed to
    // retrieve the additional arguments

    va_start(args, flags);
    // va_start-Initialize the args variable. This function tells C: 'Start
    // collecting the hidden arguments that lie immediately after the flags
    // argument.

    mode = va_arg(args, mode_t);
    // va_arg(args,mode_t)-retrieve the first hidden argument from the args
    // list, cast it to mode_t, and assign it to "mode".

    va_end(args);
    // use va_end to clean up the va_list. when we use va_start , we must use
    // va_end afterward
  }

  // call system call fro kernel to open the file
  long ret = syscall(__NR_open, filename, flags, mode);
  // in file sýcall_list.h __NR_open <-> 2 => so we can also wirte
  // syscall(2,filename,flags,mode)

  // proces result form kernel
  // ret=file descriptor >=0
  // if ret<0 => ERROR
  if (ret < 0) {
    errno = -ret; // assign postive error code to global variable "errno"
    return -1;
  }

  return (int)ret;
  // return file descriptor
}
