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
  objPos foodPos; // holds most recent food position
  int boardSizeX;
  int boardSizeY;

public:
  Food();
  Food(GameMechs &m);
  ~Food();

  void generateFood(objPos blockOff); // blockOff = playersPosition so avoid generating here // generate foodpositions
  objPos getFoodPos() const;

  // More methods should be added here getter for food position
};

#endif