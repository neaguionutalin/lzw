#include <stdio.h>
#include <stdlib.h>

struct threeNum
{
  int n1, n2, n3, n4, n5, n6;
};

int main()
{
  int n;
  struct threeNum num;
  FILE *fptr;
  if((fptr = fopen("/home/user/Desktop/cw3-cs0019-bit-lzw-abcristian-master/test_data/rnd_1","rb")) == NULL){
    printf("Error opening file");
    exit(1);
  }

  char data[2];
  char buf[2];
  for(int i=0;i<2;++i){
    int buf[2];
    fread(buf,2,1,fptr);
    data[i] = (buf[0] << 8) | buf[1];
  }
  printf("%c",data[1]);

  fclose(fptr);

  return 0;
}
