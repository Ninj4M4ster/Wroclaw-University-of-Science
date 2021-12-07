// autor - Jakub Drzewiecki

#include "funs.h"
#include <stdio.h>

void mastemind(){
  int red, white, prev_red = 0, prev_white = 0;
  char guess[4] = "1111";
  int guesses[8];

  for(int i=0; i<8; i++){
    for(int j=0; j<4; j++)
      printf("[%c] ", guess[j]);
    printf("\n");

    guesses[i] = guess - "0000";

    printf("red: ");
    scanf("%d", &red);
    printf("white: ");
    scanf("%d", &white);

    if(red == 4) {
      printf("I win\n");
      return;
    } else if(prev_red > red){
      printf("You are cheating!\n");
      return;
    }
    if()


  }
  printf("You win");
  return;
}