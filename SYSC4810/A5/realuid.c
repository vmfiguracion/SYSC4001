/* realuid.c  */

/* A program that changes the real user id to root */
#include <stdlib.h>
#include <unistd.h>

void main() {
  setuid(0); 
  system("/bin/sh");
}
