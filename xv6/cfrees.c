#include "types.h"
#include "stat.h"
#include "user.h"


int
main(int argc, char *argv[])
{
  printf(1, "%d\n", get_free_pages_count());
  exit();
}
