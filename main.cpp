#include "Texture.h"
#include "Buttons.h"
#include "Variables.h"
#include "constant.h"
#include "function1.h"
using namespace std;


int WinMain()
{
	//Start up SDL and create window
	init();
    loadmedia();
    loadMenuMedia();
    showMenu();
    while (mainLoop)
    {
        if (isChoosing)
        {
            showModeChoice();
        }
        while (isRunning)
        {
            handleEvent();
            setButtonPosition();
            renderGame();
        }
    }
	//Free resources and close SDL
	close();
	return 0;
}




