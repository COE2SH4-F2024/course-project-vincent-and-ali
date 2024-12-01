#include "Food.h"
#include <iostream>
using namespace std;

Food::Food()
{
  foodBucket = new objPosArrayList;
  boardSizeX = 30; // default size according to manual
  boardSizeY = 15;
}
Food::Food(GameMechs &m)
{
  boardSizeX = m.getBoardSizeX();
  boardSizeY = m.getBoardSizeY();
  foodBucket = new objPosArrayList;
}

Food::~Food()
{
  delete foodBucket;
}

void Food::generateFood(objPosArrayList &arr)
{

  // remove previous positions before regenerating new ones
  while (foodBucket->getSize() > 0)
  {
    foodBucket->removeTail();
  }

  for (int i = 0; i < 5; i++)
  { // generate 5 food items

    srand(time(NULL));
    bool flag = true;
    while (flag)
    {

      // generate x
      int xCoord = rand() % (boardSizeX - 2) + 1;
      // generate y
      int yCoord = rand() % (boardSizeY - 2) + 1;

      // check if it matches player location
      for (int i = 0; i < arr.getSize(); i++)
      {
        if (arr.getElement(i).getObjPos().pos->x == xCoord && arr.getElement(i).getObjPos().pos->y == yCoord)
        {
          flag = false;
          break;
        }
      }

      // check if Xcoord and Ycoord overlap with other food positions in foodBcuket
      for (int k = 0; k < foodBucket->getSize(); k++)
      {
        if (foodBucket->getElement(k).pos->x == xCoord && foodBucket->getElement(k).pos->y == yCoord)
        {
          flag = false;
          break;
        }
      }

      // regenerate the food item location if needed
      if (!flag)
      {
        flag = true;
        continue;
      }

      foodPos.pos->x = xCoord;
      foodPos.pos->y = yCoord;
      foodPos.symbol = (65 + i);
      if (int(foodPos.symbol) > 68)
      {
        foodPos.symbol = '%'; // special food
      }
      foodBucket->insertTail(foodPos);
      flag = false;
    }
  }
}

objPosArrayList *Food::getFoodPos() const
{
  return foodBucket;
}
