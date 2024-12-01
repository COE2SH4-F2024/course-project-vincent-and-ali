#include "Player.h"
#include "Food.h"

Player::Player(GameMechs *thisGMRef, Food *foodObj)
{
    mainGameMechsRef = thisGMRef;
    food = foodObj;
    myDir = STOP;
    specialFood = false;
    objPos start(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPos = new objPosArrayList;
    playerPos->insertHead(start);
    mainGameMechsRef->setScore((playerPos->getSize() - 1));
}

Player::~Player()
{
    // delete any heap members here
    delete playerPos;
}

objPosArrayList *Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    if (input != 0) // if not null character
    {
        switch (input)
        {
        case ' ': // exit
            mainGameMechsRef->setExitTrue();

            break;

        case 'W':
        case 'w':
            if (myDir != DOWN)
                myDir = UP;

            break;
        case 'S':
        case 's':
            if (myDir != UP)
                myDir = DOWN;

            break;
        case 'A':
        case 'a':
            if (myDir != RIGHT)
                myDir = LEFT;

            break;
        case 'D':
        case 'd':
            if (myDir != LEFT)
                myDir = RIGHT;

            break;

        default:
            break;
        }
        mainGameMechsRef->clearInput();
    }
}

void Player::movePlayer()
{
    //getting game board size from GameMech
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();
    //get current x and y
    int thisX = playerPos->getHeadElement().pos->x;
    int thisY = playerPos->getHeadElement().pos->y;
    objPos newPos(thisX, thisY, '*');

    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case UP:
        thisY = (thisY - 2 + (boardSizeY - 2)) % (boardSizeY - 2) + 1; //wrap around in the negative y direction
        break;
    case DOWN:
        thisY = (thisY % (boardSizeY - 2)) + 1; //wrap around in the positive y direction
        break;
    case LEFT:
        thisX = (thisX - 2 + (boardSizeX - 2)) % (boardSizeX - 2) + 1; //wrap around in the negative x direction
        break;
    case RIGHT:
        thisX = (thisX % (boardSizeX - 2)) + 1; //wrap around in the positive x direction
        break;
    case STOP:
    default:
        break;
    }

    if (myDir != STOP)
    {
        newPos.setObjPos(thisX, thisY, '*');
        playerPos->insertHead(newPos); //insert head with new position

        if (!checkFoodConsumption())
        {
            playerPos->removeTail(); // food not consumed
        }
        else
        {
            if (specialFood)
            {
                playerPos->removeTail(); // no size increase
                specialFood = false;

                // increease score by 10
                for (int i = 0; i < 10; i++)
                {
                    mainGameMechsRef->incrementScore();
                    food->generateFood(*playerPos);
                }
            }
            else
            {
                increasePlayerLength(); // do not remove tail, increment score and generate new food.
            }
        }
    }

    // collision
    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag();
    }
}

bool Player::checkFoodConsumption()
{

    for (int i = 0; i < food->getFoodPos()->getSize(); i++)
    {

        if (playerPos->getHeadElement().getObjPos().pos->x == food->getFoodPos()->getElement(i).pos->x && playerPos->getHeadElement().getObjPos().pos->y == food->getFoodPos()->getElement(i).pos->y)
        {
            specialFood = checkSpecialFoodConsumption(i);
            return true;
        }
    }

    return false;
}

void Player::increasePlayerLength()
{
    mainGameMechsRef->incrementScore();
    food->generateFood(*playerPos);
}

// More methods to be added

bool Player::checkSelfCollision()
{

    bool flag = false;
    for (int i = 1; i < playerPos->getSize(); i++)
    {
        if (playerPos->getHeadElement().getObjPos().pos->x == playerPos->getElement(i).getObjPos().pos->x && playerPos->getHeadElement().getObjPos().pos->y == playerPos->getElement(i).getObjPos().pos->y)
        {
            flag = true;
            break;
        }
    }

    return flag;
}

bool Player::checkSpecialFoodConsumption(int i)
{
    if (food->getFoodPos()->getElement(i).symbol == '%')
    {
        return true;
    }
    return false;
}