#include "Food.h"

Food::Food()
{
  boardSizeX = 30; // default size according to manual
  boardSizeY = 15;
  foodPos.symbol = '1';
}

Food::Food(GameMechs &m)
{
  boardSizeX = m.getBoardSizeX();
  boardSizeY = m.getBoardSizeY();
  foodPos.symbol = '1';
}

Food::~Food()
{
}

void Food::generateFood(objPos blockOff)
{

  srand(time(NULL));

  int flag = 1;
  while (flag)
  {

    // generate x
    int xCoord = rand() % (boardSizeX - 2) + 1;

    // generate y
    int yCoord = rand() % (boardSizeY - 2) + 1;

    // check if it matches player location
    if (blockOff.pos->x == xCoord && blockOff.pos->y == yCoord)
    {
      continue;
    }

    flag = 0;
    foodPos.pos->x = xCoord;
    foodPos.pos->y = yCoord;
  }
}

objPos Food::getFoodPos() const
{
  return foodPos;
}
