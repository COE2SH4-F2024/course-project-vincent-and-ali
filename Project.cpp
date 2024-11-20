#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}
//Copied and Pasted from PPA3
void DrawScreen(void)
{
    MacUILib_clearScreen();
    int i, j, k;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (i == 0 || i == 10 - 1 || j == 0 || j == 20 - 1)
            {
                MacUILib_printf("#");
            }
            else if (i == 3 && j == 5)
            {
                MacUILib_printf("+");
            }
            
            // else if (i == player.y && j == player.x)
            // {
            //     MacUILib_printf("%c", player.symbol);
            // }
            // else
            // {
            //     int foundItem = 0;
            //     for (k = 0; k < 5; k++)
            //     {
            //         if (i == itemList[k].y && j == itemList[k].x)
            //         {
            //             MacUILib_printf("%c", itemList[k].symbol);
            //             foundItem = 1;
            //             break;
            //         }
            //     }
            else 
            {
                MacUILib_printf(" ");
            }
            // } 
        }
        MacUILib_printf("\n");
    }    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
