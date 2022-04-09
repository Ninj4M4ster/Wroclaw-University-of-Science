// autor - Jakub Drzewiecki

#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_1_SEM_LIST_3_EX_4_FUNS_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_1_SEM_LIST_3_EX_4_FUNS_H_

struct agent{
  int x;
  int y;
};

struct agent newagent(int x, int y);
void north(struct agent *a);
void south(struct agent *a);
void east(struct agent *a);
void west(struct agent *a);
double distance(struct agent a1, struct agent a2);

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_1_SEM_LIST_3_EX_4_FUNS_H_
