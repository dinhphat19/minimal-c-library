#ifndef __TIME_H__
#define __TIME_H__ 1

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>

struct timespec {
    long tv_sec; //second
    long tv_nsec; //nanosecond
};

int nanosleep(const struct timespec *req, struct timespec *rem);

#ifdef __cplusplus
}
#endif

#endif
