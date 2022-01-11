// autor - Jakub Drzewiecki

#include "funs.h"
#include <stdio.h>

void mastermind(){
  int red, white, prev_red = 0, prev_white = 0, guessed_count = 0;
  char guess[4] = "1111";
  int guesses[8], potentially_guessed_numbers[4] = {-1, -1, -1, -1},
  numbers_indexes[4] = {0, 1, 2, 3};

  for(int i=0; i<8; i++){
    for(int j=0; j<4; j++)
      printf("[%c] ", guess[j]);
    printf("\n");

    guesses[i] = guess - "0000";

    printf("red: ");
    scanf("%d", &red);
    printf("white: ");
    scanf("%d", &white);

// result checking
    if(red == 4) {
      printf("I win\n");
      return;
    } else if (red + white > 4 || red + white < prev_white + prev_red){
      printf("You're cheating!");
      return;
    }

    if(red + white < 4){                    // if sum of red and white equals 4, we've got all chosen numbers
      for(int number_index = 0; number_index < 4; number_index++){
        if(potentially_guessed_numbers[number_index] == 0)
          continue;
        guess[number_index] += 1;
      }
    }
    prev_white = white;
    prev_red = red;
  }
  printf("You win");
  return;
}

int main(){
  mastermind();
}
