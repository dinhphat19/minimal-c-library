#include <errno.h>
#include <internal/syscall.h>
#include <time.h>
#include <unistd.h>

// in reality, kernel doesn't have any system call named "sleep"
// therefore, the standard "sleep()" function in C is actually just a 'wrapper'
// written to call 'nanosleep'for convenience

// we initialize 2 variables type 'struct timespec' which we declared in time.h
// request: variable to store the requested sleep time
// remain: variable to store the remaining sleep time, (in case the process is
// interrupted midway by another sys signal)

unsigned int sleep(unsigned int seconds) {
  struct timespec request;
  struct timespec remain;
  request.tv_sec = (long)seconds;
  request.tv_nsec = 0;
  int ret = nanosleep(&request, &remain);

  if (ret < 0) {
    return remain.tv_sec;
  }
  return 0;
}
