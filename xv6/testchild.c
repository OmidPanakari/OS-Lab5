#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "mmu.h"

#define MAXCNT 20


int
main(int argc, char *argv[])
{
  if (argc <= 3){
      printf(1, "freader: no input file");
      exit();
  }
  

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
  printf(1, "Number of free pages after map: %d\n", get_free_pages_count());
  printf(1, "Reading numbers\n");
  for (int i = 0; i < cnt; i++) 
    printf(1, "%d ", numbers[i]);
  printf(1, "\n");
  exit();
}
