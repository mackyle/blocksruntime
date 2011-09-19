/*
   Test your installation by running:

     clang -o sample -fblocks sample.c -lBlocksRuntime && ./sample

   The above line should result in:

     Hello world

   If you have everything correctly installed.
*/

#include <stdio.h>
#include <Block.h>

int main()
{
  __block int i = 0;
  void (^block)() = ^{
    printf("Hello world\n");
  };
  void (^block2)() = Block_copy(block);
  block2();
  Block_release(block2);
  return i;
}
