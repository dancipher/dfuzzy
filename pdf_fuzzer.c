#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NUM_FILES 800
#define SIZE 6250577

int main (void)
{
  FILE *in, *out, *lout;
  unsigned int n, i, j;
  char * buf = malloc(SIZE);
  char * backup = malloc(SIZE);
  char outfile[1024];
  int rn, rn2, rn3, rn4;
  int rbyte;
  int numwrites;

  in = fopen("good.pdf", "r");
  n = read(fileno(in), buf, SIZE);
  memcpy(backup, buf, n);

  lout = fopen("list", "w");

  srand(time(NULL));
  
  for (i=0;i<NUM_FILES;i++) {
    numwrites = rand() % 16;
    numwrites++;
    printf("[+] Writing %d bytes\n", numwrites);
    for (j=0;j<numwrites;j++)
    {
      rbyte = rand() % 257;
      if (rbyte == 256)
	rbyte = -1;
      rn = rand() % n - 1;
      printf("[+] buf[%d] = %d\n", rn, rbyte);
      buf[rn] = rbyte;
    }
    
    sprintf(outfile, "bad-%d.pdf", i);
    out = fopen(outfile, "w");
    write(fileno(out), buf, n);
    fclose(out);
    fprintf(lout, "%s\n", outfile);
    memcpy(buf, backup, n);
  }
}

