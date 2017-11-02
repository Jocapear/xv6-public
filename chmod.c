#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  char permissions[4];
  if(argc != 3){
    printf(2, "Usage: chmod permissions failed\n");
    exit();
  }

  permissions[0] = argv[1][0] - '0';
  if(chmod(permissions, argv[2]) < 0)
    printf(2, "chmod %s %s: failed\n", argv[1], argv[2]);
  exit();
}