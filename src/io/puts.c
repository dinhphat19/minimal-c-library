#include <internal/io.h>
#include <stdio.h>
#include <string.h>

int puts(char *str) {
  // in linux/unix: "EVERYTHING IS A FILE"
  // everything-including hard drives, mice, keyboards,etc-is treated lika a
  // 'file'
  //=> to interact with a monitor or keyboard(output|input),we use exact same
  //'open','read','write' commands as we would do with a regular .txt file

  int len = strlen(str);

  // when a C prog starts, the OS automatically opens 3 basic human-interface
  // files
  //  and assigns them 3 default file descriptors(fd)
  // fd=0(stdin)-represent keyboard(input)(if u call read() , prog will wait for
  // you to type in input form keyboard) scanf() is based on fd=0

  // fd=1(stdout)-represent monitor(output)(if u call write(),
  //  prog will print the result out on the monitor without writting them in
  //  hard drive )
  // puts() and printf() are based on this fd

  // fd=2(stderr)-still also print out on the monitor, but for errors

  // we use write() function from io.h to print out on the monitor sting *str
  // and automatocally add '\n' at the end so we use fd=1 because we want to
  // print 'str' out

  int ret = (int)write(1, str, len);
  int ret1 = (int)write(1, "\n", 1);

  // if we successfully printed string 'str' with '\n' out then return 0
  if (ret >= 0 && ret1 >= 0) {
    return 0;
  }
  return -1;
}
