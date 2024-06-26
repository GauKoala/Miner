#include "Texture.h"
#include "Variables.h"

extern SDL_Window* window = NULL;
extern SDL_Renderer* renderer = NULL;
extern TTF_Font* gFont = NULL;

LTexture::LTexture(SDL_Texture* _mTexture, int _mWidth, int _mHeight)
{
	//Initialize
	mTexture = _mTexture;
	mWidth = _mWidth;
	mHeight = _mHeight;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    //Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    //Get image dimensions
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}


bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    //Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    //Get image dimensions
    mWidth = textSurface->w;
    mHeight = textSurface->h;

    //Get rid of old surface
    SDL_FreeSurface(textSurface);
	//Return success
	return mTexture != NULL;
}


void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
