#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    // playerPos.pos->x = 5;
    // playerPos.pos->y = 5;
    playerPos.symbol = '*';
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case ' ':  // exit
                // exitMessage = "YOU DID NOT FINISH THE GAME :(";
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
            // case 9:
            //     if (playerSpeed == EXTREME)
            //     {
            //         playerSpeed = SLOW;  // Loop back to the slowest
            //     } 
            //     else
            //     {
            //         playerSpeed = (enum SpeedLevel)(playerSpeed - 1);  // Move to faster speed level
            //     }
            default:
                break;
        }
        mainGameMechsRef->clearInput();
    }
    
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case UP:
        playerPos.pos->y = (playerPos.pos->y -2 + (mainGameMechsRef->getBoardSizeY() - 2)) % (mainGameMechsRef->getBoardSizeY() - 2) + 1; 
        break;
    case DOWN:
        playerPos.pos->y = (playerPos.pos->y % (mainGameMechsRef->getBoardSizeY() - 2)) + 1;
        break;
    case LEFT:
        playerPos.pos->x = (playerPos.pos->x - 2 + (mainGameMechsRef->getBoardSizeX() - 2)) % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
        break;
    case RIGHT:
        playerPos.pos->x = (playerPos.pos->x % (mainGameMechsRef->getBoardSizeX() - 2)) + 1;
        break;
    case STOP:
    default:
        break;
    }
    if (myDir != STOP)
    {
        // moveCount++;
    }          
}

// More methods to be added