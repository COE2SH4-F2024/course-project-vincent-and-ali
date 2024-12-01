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

void Food::generateFood(objPosArrayList &arr)
{

  srand(time(NULL));

  bool flag = true;
  while (flag)
  {

    // generate x
    int xCoord = rand() % (boardSizeX - 2) + 1;

    // generate y
    int yCoord = rand() % (boardSizeY - 2) + 1;

    // check if it matches player location

    // we need size of array
    for (int i = 0; i < arr.getSize(); i++)
    {
      // check every position on the snake

      if (arr.getElement(i).getObjPos().pos->x == xCoord && arr.getElement(i).getObjPos().pos->y == yCoord)
      {
        // part of the snake overlap with food
        flag = false;
        break;
      }
    }

    // regenerate the food item location
    if (!flag)
    {
      continue;
    }

    flag = true;
    foodPos.pos->x = xCoord;
    foodPos.pos->y = yCoord;
  }
}

objPos Food::getFoodPos() const
{
  return foodPos;
}
