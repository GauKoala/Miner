#include "Texture.h"
#include "Variables.h"
#include "constant.h"
#include "Buttons.h"
#include "function1.h"
#include <sstream>
#include <fstream>
using namespace std;
vector <vector<LButton> > Buttons(3, vector<LButton>(2));
LButton face;

///Khoi tao man hinh
bool init()
{
	bool success = true;

	//khoi tao SDL
	SDL_Init(SDL_INIT_VIDEO) < 0;
    //ti le ve renderer
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //tao cua so cho minesweepers
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //Thiet lap mau
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //khoi tao anh dang PNG
    int imgFlags = IMG_INIT_PNG;
    IMG_Init(imgFlags);

    //Khoi tao thu vien SDL_ttf  (ve ky tu va font chu)
    TTF_Init() == -1;
    //Khoi tao SDL_mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	return success;
}

///Khoi tao menu, cac hien thi trong do min
bool loadmedia()
{
    bool success = true;
    // Mo tep ki tu
    Tiles_image.loadFromFile("mat/images/square.jpg");
    //Cac o tren do min
    for (int i = 0;i < 12;++i)
    {
        Tilesprites[i].x = i * TILE_SIZE;
        Tilesprites[i].y = 0;
        Tilesprites[i].w = TILE_SIZE;
        Tilesprites[i].h = TILE_SIZE;
    }
    //digits - anh kich thuoc 280x46
    Digits.loadFromFile("mat/images/Untitled1.png");
    //sprites
    for (int i = 0;i < 10;i++)
    {
        Digitsprites[i].x = i * 28;
        Digitsprites[i].y = 0;
        Digitsprites[i].w = 28;
        Digitsprites[i].h = 46;
    }
    // man easy
    easyTable.loadFromFile("mat/images/easy.png");
    //medium
    mediumTable.loadFromFile("mat/images/medium.png");
    //hard
    hardTable.loadFromFile("mat/images/hard.png");
    //face win
    winFace.loadFromFile("mat/images/winface.png");
    //facelose
    loseFace.loadFromFile("mat/images/loseface.png");
    //mat luc choi
    playingFace.loadFromFile("mat/images/playingface.png");
    //font chu
    gFont = TTF_OpenFont("mat/font.ttf", 20); // font kich thuoc 20
    //load text
    SDL_Color textcolor1 = { 255,255,255 }; // mau trang
    menu.loadFromRenderedText("START", textcolor1);

    menu1.loadFromRenderedText("EXIT", textcolor1);

    SDL_Color color = { 255,0,0 }; // mau do
    menuColor.loadFromRenderedText("START", color);
    menu1Color.loadFromRenderedText("EXIT", color);
    //Load music
    loseMusic = Mix_LoadMUS("mat/audio/scratch.wav");
    //Load sound effects
    winMusic = Mix_LoadMUS("mat/audio/beat.wav");

    click = Mix_LoadWAV("mat/audio/click.wav");
    return success;
}

/// Hien thi menu
bool loadMenuMedia()
{
    bool success = true;
    //background cua menu
    menuTheme.loadFromFile("mat/images/menu.png");
    //mode game
    levelTheme.loadFromFile("mat/images/mode.jpg");
    //load choice text;
    SDL_Color textColor = { 255,255,255 };
    easyChoice.loadFromRenderedText("EASY MODE", textColor);
    mediumChoice.loadFromRenderedText("MEDIUM MODE", textColor);

    hardChoice.loadFromRenderedText("HARD MODE", textColor);

    SDL_Color textcolor = { 255,0,0 };
    easyChoiceColor.loadFromRenderedText("EASY MODE", textcolor);
    mediumChoiceColor.loadFromRenderedText("MEDIUM MODE", textcolor);

    hardChoiceColor.loadFromRenderedText("HARD MODE", textcolor);
    return success;
}

//initialization games
void CreateBoard()
{
	srand(time(0));
	int mine = 0;
	//Initialization
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		for (int j = 0;j < BOARD_SIZE_Y;j++)
		{
			sBoard[i][j] = 10;
			board[i][j] = 0;
		}
	}

	//Random mines in board
	while (mine < NumberOfMines)
	{
		int i = rand() % BOARD_SIZE_X;
		int j = rand() % BOARD_SIZE_Y;
		if (board[i][j] == 9) continue;
		board[i][j] = 9;
		mine++;
	}

	//Calculate the number of mines around each cell
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		for (int j = 0;j < BOARD_SIZE_Y;j++)
		{
			if (board[i][j] == 9) continue;
			for (int x = -1;x <= 1;x++)
			{
				for (int y = -1;y <= 1;y++)
				{
					int xpos = i + x;
					int ypos = j + y;
					if (xpos < 0 || xpos>BOARD_SIZE_X - 1 || ypos<0 || ypos>BOARD_SIZE_Y - 1) continue;
					if (board[xpos][ypos] == 9) board[i][j]++;
				}
			}
		}
	}
}

void setButtonPosition()
{
	face.setPosition(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
	for (int i = 0;i < BOARD_SIZE_X;++i)
	{
		for (int j = 0;j < BOARD_SIZE_Y;++j)
		{
			Buttons[i][j].setPosition(i * TILE_SIZE + distance_x, j * TILE_SIZE + distance_y);
		}
	}
}

void createMenu()
{
	menuTheme.render(0, 0);
	menu.render(300, 430);
	menu1.render(500, 430);
	SDL_RenderPresent(renderer);
}

void createModeMenu()
{
	levelTheme.render(0, 0);
	easyChoice.render(300, 150);
	mediumChoice.render(300, 200);
	hardChoice.render(300, 250);
}

void showMenu()
{
	bool startInside = false;
	bool exitInside = false;
	bool isMenuShowing = true;
	SDL_Event event;
	createMenu();
	while (isMenuShowing)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				mainLoop = false;
				isMenuShowing = false;
			}

			// vi tri chuot
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x > 300 && x < 300 + menu.getWidth() && y > 430 && y < 430 + menu.getHeight()) startInside = true;
				else startInside = false;
				if (x > 500 && x < 500 + menu1.getWidth() && y > 430 && y < 430 + menu1.getHeight()) exitInside = true;
				else exitInside = false;
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (startInside == true)
						{
							start = true;
							isMenuShowing = false;
						}
						if (exitInside == true)
						{
							mainLoop = false;
							isMenuShowing = false;

						}
					}
				}
				if (event.type == SDL_MOUSEMOTION)
				{
					if (startInside == true)
					{
						menuColor.render(300, 430);
					}
					else menu.render(300, 430);
					if (exitInside == true)
					{
						menu1Color.render(500, 430);

					}
					else menu1.render(500, 430);
				}

			}
			SDL_RenderPresent(renderer);
		}
	}
}

void showModeChoice()
{
	bool easyInside = false;
	bool mediumInside = false;
	bool hardInside = false;
	SDL_Event event;
	createModeMenu();
	while (isChoosing)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				mainLoop = false;
				isChoosing = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x > 300 && x < 300 + easyChoice.getWidth() && y > 150 && y < 150 + easyChoice.getHeight()) easyInside = true;
				else easyInside = false;
				if (x > 300 && x < 300 + mediumChoice.getWidth() && y > 200 && y < 200 + mediumChoice.getHeight()) mediumInside = true;
				else mediumInside = false;
				if (x > 300 && x < 300 + hardChoice.getWidth() && y > 250 && y < 250 + hardChoice.getHeight()) hardInside = true;
				else hardInside = false;
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (easyInside == true)
						{
							isRunning = true;
							isChoosing = false;
							easy = true;
							medium = false;
							hard = false;
							SDL_SetWindowSize(window, 294, 436);
							setGameMode(9, 9, 10, 21, 163, 25, 80, 235, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y);
							CreateBoard();
						}
						if (mediumInside == true)
						{
							isRunning = true;
							isChoosing = false;
							easy = false;
							medium = true;
							hard = false;
							SDL_SetWindowSize(window, 488, 630);
							setGameMode(16, 16, 40, 21, 163, 25, 80, 430, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y);
							CreateBoard();
						}
						if (hardInside == true)
						{
							isRunning = true;
							isChoosing = false;
							easy = false;
							medium = false;
							hard = true;
							SDL_SetWindowSize(window, 880, 632);
							setGameMode(30, 16, 99, 21, 163, 25, 80, 820, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y);
							CreateBoard();
						}
					}
				}
				if (event.type == SDL_MOUSEMOTION)
				{
					if (easyInside == true) easyChoiceColor.render(300, 150);
					else easyChoice.render(300, 150);
					if (mediumInside == true) mediumChoiceColor.render(300, 200);
					else mediumChoice.render(300, 200);
					if (hardInside == true) hardChoiceColor.render(300, 250);
					else hardChoice.render(300, 250);
				}
			}
			SDL_RenderPresent(renderer);
		}
	}
}


//ingame func
void handleEvent()
{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				isRunning = false;
				mainLoop = false;
			}
			for (int i = 0; i < BOARD_SIZE_X; i++)
			{
				for (int j = 0; j < BOARD_SIZE_Y; j++)
				{
					Buttons[i][j].handleEvent(&e);
				}
			}

		}
}

void reveal(int i, int j)
{
	if (sBoard[i][j] == 10 || sBoard[i][j] == 11)
	{
		if (sBoard[i][j] == 11)
		{
			return;
		}
		sBoard[i][j] = board[i][j];
		if (sBoard[i][j] != 9) CountTileLeft--;
		if (sBoard[i][j] == 0)
		{
			for (int x = -1;x <= 1;x++)
			{
				for (int y = -1;y <= 1;y++)
				{
					int xpos = i + x;
					int ypos = j + y;
					if (xpos<0 || xpos>BOARD_SIZE_X - 1 || ypos<0 || ypos>BOARD_SIZE_Y - 1) continue;
					reveal(xpos, ypos);
				}
			}
		}
	}
}

void isPlayerWinning()
{
	if (CountTileLeft == NumberOfMines) isWinning = true;
}

void GameManager()
{
	//if we lose
	if (lose == true)
	{
		loseFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
		for (int i = 0;i < BOARD_SIZE_X;i++)
		{
			for (int j = 0;j < BOARD_SIZE_Y;j++)
			{
				Buttons[i][j].loseRender(i, j);
			}
		}
	}
	//if we win
	if (isWinning == true)
	{
		winFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
	}
}

void MineManager()
{
	int n = mineCountLeft;
	if (mineCountLeft < 10)
	{
		Digits.render(digit_x, digit_y, &Digitsprites[0]);
		for (int i = 0;i <= 9;i++)
		{
			if (i == mineCountLeft) Digits.render(digit_x + 28, digit_y, &Digitsprites[i]);
		}
	}

	else
	{
		int i = 0;
		while (n > 0)
		{
			int x = n % 10;
			n /= 10;
			Digits.render(digit_x + (1 - i) * 28, digit_y, &Digitsprites[x]);
			i++;
		}
	}
}

void setGameMode(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y)
{
	BOARD_SIZE_X = x;
	BOARD_SIZE_Y = y;
	NumberOfMines = n;
	mineCountLeft = n;
	CountTileLeft = x * y;
	distance_x = dx;
	distance_y = dy;
	digit_x = d1x;
	digit_y = d1y;
	Buttons.resize(BOARD_SIZE_X);
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		Buttons[i].resize(BOARD_SIZE_Y);
	}
	sBoard.resize(BOARD_SIZE_X);
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		sBoard[i].resize(BOARD_SIZE_Y);
	}
	board.resize(BOARD_SIZE_X);
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		board[i].resize(BOARD_SIZE_Y);
	}
}

void renderButton()
{
	for (int i = 0;i < BOARD_SIZE_X;i++)
	{
		for (int j = 0;j < BOARD_SIZE_Y;j++)
		{
			Buttons[i][j].render(i, j);
		}
	}
}

void renderGame()
{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		loseMusic = Mix_LoadMUS("mat/audio/scratch.wav");
		winMusic = Mix_LoadMUS("mat/audio/beat.wav");
		click = Mix_LoadWAV("mat/audio/click.wav");
	if (easy == true || medium == true || hard == true )
	{
		if (easy == true)
		{
			easyTable.render(0, 50);
		}
		if (medium == true)
		{
			mediumTable.render(0, 50);
		}
		if (hard == true)
		{
			hardTable.render(0, 50);
		}
	}
	playingFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
	renderButton();
	MineManager();
	isPlayerWinning();
	GameManager();
	SDL_RenderPresent(renderer);
}

//close SDL
void close()
{
	//Free loaded images
	Tiles_image.free();
	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}
