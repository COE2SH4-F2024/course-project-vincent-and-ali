#include "Player.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    // playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    // playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    // playerPos.symbol = '*';

    objPos start(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPos = new objPosArrayList;
    playerPos->insertHead(start);

    // objPos second(start.pos->x + 1, start.pos->y, '*');
    // objPos third(start.pos->x + 2, start.pos->y, '*');
    // objPos forth(start.pos->x + 3, start.pos->y, '*');
    // objPos fifth(start.pos->x + 4, start.pos->y, '*');
    // playerPos->insertTail(second);
    // playerPos->insertTail(third);
    // playerPos->insertTail(forth);
    // playerPos->insertTail(fifth);
}

Player::~Player()
{
    // delete any heap members here
    delete playerPos;
}

objPosArrayList* Player::getPlayerPos() const
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
        // case 27: // loseFlag:
        //     mainGameMechsRef->setLoseFlag();
        //     break;

        case 49: // increment score
            mainGameMechsRef->incrementScore();
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

    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    int newX = playerPos->getHeadElement().pos->x;
    int newY = playerPos->getHeadElement().pos->y;
    objPos newPos(newX, newY, '*');
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case UP:
        // playerPos.pos->y = (playerPos.pos->y - 2 + (mainGameMechsRef->getBoardSizeY() - 2)) % (mainGameMechsRef->getBoardSizeY() - 2) + 1;
        
        newY = (newY - 2 + (boardSizeY - 2)) % (boardSizeY - 2) + 1;
        break;
    case DOWN:
        // playerPos.pos->y = (playerPos.pos->y % (mainGameMechsRef->getBoardSizeY() - 2)) + 1;

        newY = (newY % (boardSizeY - 2)) + 1;
        break;
    case LEFT:
        // playerPos.pos->x = (playerPos.pos->x - 2 + (mainGameMechsRef->getBoardSizeX() - 2)) % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
        
        newX = (newX - 2 + (boardSizeX - 2)) % (boardSizeX - 2) + 1;
        break;
    case RIGHT:
        // playerPos.pos->x = (playerPos.pos->x % (mainGameMechsRef->getBoardSizeX() - 2)) + 1;
        
        newX = (newX % (boardSizeX - 2)) + 1;
        break;
    case STOP:
    default:
        break;
    }
    if (myDir != STOP)
    {
        newPos.setObjPos(newX, newY, '*');
        playerPos->insertHead(newPos);
        playerPos->removeTail();
    }
}

// More methods to be added