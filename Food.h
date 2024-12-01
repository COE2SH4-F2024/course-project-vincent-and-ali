#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{
private:
  objPos foodPos; //
  int boardSizeX;
  int boardSizeY;
  objPosArrayList *foodBucket;

public:
  Food();
  Food(GameMechs &m);
  ~Food();

  void generateFood(objPosArrayList &arr);

  objPosArrayList *getFoodPos() const;

  // More methods should be added here getter for food position
};

#endif