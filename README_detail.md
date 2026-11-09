# Mini-libc: A Minimal C Standard Library

A lightweight, zero-dependency implementation of the C standard library built from scratch in **C** and **x86_64 Assembly**. Developed for the Operating Systems course (UPB ACS), this project completely bypasses the standard GNU C Library (`glibc`) to interact directly with the Linux kernel.

## Key Features & Architecture
- **Direct Kernel System Calls:** Implements a custom syscall wrapper using **x86_64 inline assembly** (`syscall` instruction) to transition from user space to kernel space, handling I/O (`read`, `write`, `open`, `close`, `lseek`) and process control (`exit`, `sleep`, `nanosleep`).
- **Custom Memory Allocator:** Features a standalone implementation of dynamic memory management (`malloc`, `calloc`, `realloc`, `free`) utilizing the Linux `mmap` and `munmap` system calls to allocate pages directly from the kernel.
- **String & Memory Utilities:** Complete scratch-built implementation of POSIX `<string.h>` utilities (e.g., `strlen`, `strcpy`, `strchr`, `memset`, `memcpy`, `memmove`) ensuring strict memory safety and byte-level manipulation without external dependencies.
- **Library Compilation:** Supports building as both a static library (`libc.a`) and a shared object (`libc.so`), defining a custom application binary interface (ABI) for statically linked minimal executables.

## Tech Stack
- **Languages:** C, x86_64 Assembly (NASM / Inline GCC)
- **Tools:** GCC, Make, Linux syscalls, strace
- **Core Concepts:** User/Kernel Space Boundary, System Calls, Virtual Memory Allocation, File Descriptors, ABI.

## Build Instructions
To compile the minimal C library:
make