#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player *myPlayer;
GameMechs *myMech;

int main(void)
{

    Initialize();

    while (exitFlag == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;
    myMech = new GameMechs();
    myPlayer = new Player(myMech);
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        myMech->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{

    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    exitFlag = myMech->getExitFlagStatus();
    if (myMech->getLoseFlagStatus() == true)
    {
        exitFlag = true;
    }
}

// Copied and Pasted from PPA3
void DrawScreen(void)
{
    MacUILib_clearScreen();
    int i, j, k;
    for (i = 0; i < myMech->getBoardSizeY(); i++)
    {
        for (j = 0; j < myMech->getBoardSizeX(); j++)
        {
            if (i == 0 || i == myMech->getBoardSizeY() - 1 || j == 0 || j == myMech->getBoardSizeX() - 1)
            {
                MacUILib_printf("#");
            }
            else
            {
                bool isSnake = false;
                for (int k = 0; k < myPlayer->getPlayerPos()->getSize(); k++)
                {
                    if (i == myPlayer->getPlayerPos()->getElement(k).pos->y && j == myPlayer->getPlayerPos()->getElement(k).pos->x)
                    {
                        MacUILib_printf("%c", myPlayer->getPlayerPos()->getHeadElement().symbol);
                        isSnake = true;
                        break;
                    }
                }
                if (!isSnake)
                {
                    MacUILib_printf(" ");
                }
                
                
            }

            // else if (i == myPlayer->getPlayerPos()->getHeadElement().pos->y && j == myPlayer->getPlayerPos()->getHeadElement().pos->x)
            // {
            //     MacUILib_printf("%c", myPlayer->getPlayerPos()->getHeadElement().symbol);
            // }
            // else
            // {
            //     MacUILib_printf(" ");
            // }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d \n", myMech->getScore());

    if (myMech->getLoseFlagStatus() == true)
    {
        MacUILib_printf("YOU LOST THE GAME \n");
    }
    else if (exitFlag == true)
    {
        MacUILib_printf("YOU DID NOT FINISH THE GAME :( \n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_uninit();
    delete myMech;
    delete myPlayer;
}
