#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "mmu.h"

#define MAXCNT 20
#define MAXLEN 5


int
main(int argc, char *argv[])
{
  if (argc <= 1){
      printf(1, "freader: no input file");
      exit();
  }
  
  int fd = open(argv[1], O_RDONLY);
  char *mapped_addr = (char*)mmap(0, PGSIZE, PROT_READ, MAP_PRIVATE, fd, 0), *temp = mapped_addr;
  int numbers[MAXCNT], cnt = 0;
  numbers[cnt] = 0;
  while (*mapped_addr != '\n') {
    if (*mapped_addr == ' ') {
      cnt++;
      numbers[cnt] = 0;
    }
    else 
      numbers[cnt] = numbers[cnt] * 10 + ((*mapped_addr) - '0');
    mapped_addr ++;
  }
  mapped_addr = temp;
  printf(1, "Writing power3 numbers\n");
  for (int i = 0; i < cnt; i++) {
    numbers[i] = numbers[i] * numbers[i] * numbers[i];
    printf(1, "%d ", numbers[i]);
    char c[MAXLEN];
    int len = 0;
    while(numbers[i] != 0)
    {
      c[len] = '0' + (numbers[i] % 10);
      len++;
      numbers[i] /= 10;
    }
    while(len--) {
      (*mapped_addr) = c[len];
      mapped_addr++;
    }
    (*mapped_addr) = ' ';
  }
  printf(1, "\n");
  exit();
}
