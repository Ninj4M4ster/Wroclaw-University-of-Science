// autor - Jakub Drzewiecki

#include "funs.h"
#include <stdio.h>

void mastermind(){
  int red, white, prev_red = 0, prev_white = 0, guessed_count = 0, shfl_index = -1, second_shfl_ind;
  char guess[4] = "1111", guesses[8][4];
  int numbers_indexes[4] = {0, 1, 2, 3},
  guessed_numbers[4] = {-1, -1 , -1, -1},
  red_in_guesses[8];

  for(int i = 0; i < 8; i++){
    for(int nmb_index = 0; nmb_index < 4; nmb_index++)
      printf("[%c] ", guess[nmb_index]);
    printf("?\n");

// save value of actual combination of numbers
    for(int nmb_index = 0; nmb_index < 4; nmb_index++){
      guesses[i][nmb_index] = guess[nmb_index];
    }

    printf("red: ");
    scanf("%d", &red);
    printf("white: ");
    scanf("%d", &white);

    red_in_guesses[i] = red;

// result checking
    if(red == 4) {
      printf("I win\n");
      return;
    } else if (red + white > 4 || red + white < prev_white + prev_red || red < guessed_count) {
      printf("You're cheating!");
      return;
    }
// checking if number after shuffling is on a good position
    if(red > prev_red && red + white == 4 && prev_red + prev_white == 4){
      if(shfl_index != -1) {
        guessed_numbers[shfl_index] = 0;
        guessed_count += 1;
        shfl_index = 0;
      }
      if(red > prev_red + 1){
        guessed_numbers[second_shfl_ind] = 0;
        guessed_count += 1;
      }
    }
// checking if number was not changed for a few times and it remains on good position
    int count_same_nmb = 0;
    if(red + white == 4){
      for(int nmb_index = 0; nmb_index < 4; nmb_index++){
        int cmpr_index = nmb_index + 1;
        while(nmb_index != cmpr_index){
          if(cmpr_index == 4)
            cmpr_index = -1;
          if(cmpr_index > -1 && guess[cmpr_index] == guess[nmb_index])
            count_same_nmb += 1;
          cmpr_index += 1;
        }
      }
    }
    if(i > 1 && red > 0 && count_same_nmb == 0){
      int nmb_changed[4] = {0, 0, 0, 0};
      for(int j = i - 1; j >= i - 2; j--) {
        if (red_in_guesses[j] == 0) {
          for (int nmb_index = 0; nmb_index < 4; nmb_index++)
            nmb_changed[nmb_index] = -1;
          break;
        } else {
          for (int nmb_index = 0; nmb_index < 4; nmb_index++) {
            if (guesses[j][nmb_index] != guesses[j + 1][nmb_index])
              nmb_changed[nmb_index] = -1;
          }
        }
      }
      int count_unchanged = 0;
      for(int nmb_index = 0; nmb_index < 4; nmb_index++){
        if(nmb_changed[nmb_index] == 0)
          count_unchanged += 1;
      }
      if(count_unchanged == red - guessed_count){
        for(int nmb_index = 0; nmb_index < 4; nmb_index++){
          if(nmb_changed[nmb_index] == 0 && guessed_numbers[nmb_index] != 0){
            guessed_numbers[nmb_index] = 0;
            guessed_count += 1;
          }
        }
      }
    }
// shuffling numbers
    if(white > 0 && red+white < 4 || white > 1 && red+white == 4){
      if(shfl_index == -1 || shfl_index == 3)
        shfl_index = 0;
      // finding two numbers to shuffle
      while(1){
        if(shfl_index == 4)
          shfl_index = 0;
        if(guessed_numbers[shfl_index] != 0)
          break;
        shfl_index += 1;
      }
      second_shfl_ind = shfl_index;
      while(1){
        if(second_shfl_ind == 4)
          second_shfl_ind = 0;
        if(guessed_numbers[second_shfl_ind] != 0 && second_shfl_ind != shfl_index &&
            guess[shfl_index] != guess[second_shfl_ind])
          break;
        second_shfl_ind += 1;
      }

      char tmp = guess[shfl_index];
      guess[shfl_index] = guess[second_shfl_ind];
      guess[second_shfl_ind] = tmp;
// changing positions of numbers in numbers_indexed
      int first_index = -1, second_index = -1, srch_index = 0;
      while(!(first_index != -1 && second_index != -1) && srch_index < 4){
        if(numbers_indexes[srch_index] == shfl_index)
          first_index = srch_index;
        else if(numbers_indexes[srch_index] == second_shfl_ind)
          second_index = srch_index;
        srch_index += 1;
      }
      numbers_indexes[first_index] = second_shfl_ind;
      numbers_indexes[second_index] = shfl_index;

      int tmp_ind = shfl_index;
      shfl_index = second_shfl_ind;
      second_shfl_ind = tmp_ind;
    }
// if sum of red and white equals 4, we've got all chosen numbers
// else we raise value of numbers that are not chosen by user
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
