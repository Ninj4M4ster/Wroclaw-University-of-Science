// autor - Jakub Drzewiecki

#include "funs.h"
#include <stdio.h>

void mastermind(){
  int red, white, prev_red = 0, prev_white = 0, guessed_count = 0, shfl_index = -1;
  char guess[4] = "1111";
  int guesses[8], numbers_indexes[4] = {0, 1, 2, 3},
  guessed_numbers[4] = {-1, -1 , -1, -1};

  for(int i=0; i<8; i++){
    for(int nmb_index=0; nmb_index<4; nmb_index++)
      printf("[%c] ", guess[nmb_index]);
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
    } else if (red + white > 4 || red + white < prev_white + prev_red || red < guessed_count) {
      printf("You're cheating!");
      return;
    }
    if(white > prev_white && red + white == 4 && prev_red + prev_white == 4){
      if(shfl_index != -1) {
        guessed_numbers[shfl_index] = 0;
        guessed_count += 1;
      }
    }
    if(white > 0){
      if(shfl_index == -1 || shfl_index == 3)
        shfl_index = 0;
      char tmp = guess[shfl_index];
      guess[shfl_index] = guess[shfl_index + 1];
      guess[shfl_index + 1] = tmp;
// changing positions of numbers in numbers_indexed
      int first_index = -1, second_index = -1, srch_index = 0;
      while(!(first_index != -1 && second_index != -1) && srch_index < 4){
        if(numbers_indexes[srch_index] == shfl_index)
          first_index = srch_index;
        else if(numbers_indexes[srch_index] == shfl_index + 1)
          second_index = srch_index;
        srch_index += 1;
      }
      numbers_indexes[first_index] += 1;
      numbers_indexes[second_index] -= 1;

      shfl_index += 1;
    }
// if sum of red and white equals 4, we've got all chosen numbers
    if(red + white < 4){
      for(int nmb_index = red + white; nmb_index < 4; nmb_index++)
        guess[numbers_indexes[nmb_index]] += 1;
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
