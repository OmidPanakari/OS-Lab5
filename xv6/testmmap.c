#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "mmu.h"

#define SEED 2434
#define MULT 63423
#define BASE 93462
#define RNDCNT 10
#define FNAME "temp.txt"

int gen_rand(int high)
{
  static int res = SEED;
  res = (res * MULT + BASE) % high;
  return res;
}

void execute(char *pname)
{
  int pid = fork();
  if (pid == 0)
  {
    char *argv[2] = {pname, FNAME};
    exec(pname, argv);
  }
  else 
    wait();
}

int
main(int argc, char *argv[])
{ 
  // Generate random numbers
  int fd = open(FNAME, O_CREATE | O_WRONLY);
  for (int i = 0; i < RNDCNT; i++) {
    int rnd = gen_rand(100);
    printf(fd, "%d ", rnd);
    printf(1, "%d ", rnd);
  }
  printf(fd, "\n");
  printf(1, "\n");
  close(fd);
  
  // Execute test processes
  // Reader
  execute("freader");

  // Power2 writer
  execute("p2writer");

  // Power3 writer
  execute("p3writer");

  exit();
}
