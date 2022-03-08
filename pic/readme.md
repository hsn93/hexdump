# hexdump
printf utility i use to debug memory related c softwares.


```c
#include "hexdump.h"
int main(int argc, char *argv[])
{
  const char hello[] = "Hello World !";
  char *mem = malloc(512);
  strcpy(mem + 10, hello);
  hex_dump_highlight(mem, 512, 10, sizeof(hello));
}
```

![Image](pic/hexdump.jpg "hd")
![Image](pic/hexdump.jpg "hd_highlight")
