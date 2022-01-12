#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "mmu.h"

#define SEED 2434
#define MULT 63423
#define BASE 93462
#define RNDCNT 10
#define CHILDCNT 3
#define FNAME "testfork.txt"

int
main(int argc, char *argv[])
{ 
  char *addr = 0;
  // Get file
  int fd = open(FNAME, O_CREATE | O_WRONLY);
  addr = (char*)mmap(0, PGSIZE, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);

  // Init data on map
  printf(1, "parent: writing 0 on vm\n");
  (*addr) = '0';
  
  // Forking childeren
  for (int i = 1; i < CHILDCNT; i++) {
    printf(1, "parent: running child: %d\n", i);
    int pid = fork();
    if (pid == 0) {
      printf(1, "child: value before write: %c\n", *addr);
      (*addr) = (char)('0' + i);
      printf(1, "child: value after write: %c\n", *addr);
      exit();
    }
    else
      wait();
    printf(1, "parent: value of vm after running child %d: %c\n", i, *addr);
  }

  exit();
}
