/*
** EPITECH PROJECT, 2023
** B-PDG-300-LIL-3-1-PDGRUSH3-ulysse.decottignies
** File description:
** Sdl
*/

#include <iostream>
#include "SDL.hpp"

/*  @author Paul
    @brief initSDL function
    @return int
*/
int Sdl::initSDL()
{
    return SDL_Init(SDL_INIT_VIDEO);
}

/*  @author Paul
    @brief quitSDL function
    @return void
*/
void Sdl::quitSDL()
{
    SDL_Quit();
}

// Window

/*  @author Paul
    @brief createWindow function
    @param const char *title
    @param int x
    @param int y
    @param int w
    @param int h
    @param Uint32 flags
    @return SDL_Window *
*/
SDL_Window *Sdl::createWindow(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    return SDL_CreateWindow(title, x, y, w, h, flags);
}

/*  @author Paul
    @brief destroyWindow function
    @param SDL_Window *window
    @return void
*/
void Sdl::destroyWindow(SDL_Window *window)
{
    SDL_DestroyWindow(window);
}

// Renderer

/*  @author Paul
    @brief createRenderer function
    @param SDL_Window *window
    @param int index
    @param Uint32 flags
    @return SDL_Renderer *
*/
SDL_Renderer *Sdl::createRenderer(SDL_Window *window, int index, Uint32 flags)
{
    return SDL_CreateRenderer(window, index, flags);
}

/*  @author Paul
    @brief destroyRenderer function
    @param SDL_Renderer *renderer
    @return void
*/
void Sdl::destroyRenderer(SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
}

/*  @author Paul
    @brief renderClear function
    @param SDL_Renderer *renderer
    @return void
*/
void Sdl::renderClear(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
}

/*  @author Paul
    @brief renderCopy function
    @param SDL_Renderer *renderer
    @param SDL_Texture *texture
    @param const SDL_Rect *srcrect
    @param const SDL_Rect *dstrect
    @return void
*/
void Sdl::renderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect)
{
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

/*  @author Paul
    @brief renderCopyEx function
    @param SDL_Renderer *renderer
    @param SDL_Texture *texture
    @param const SDL_Rect *srcrect
    @param const SDL_Rect *dstrect
    @param const double angle
    @param const SDL_Point *center
    @param const SDL_RendererFlip flip
    @return void
*/
void Sdl::renderCopyEx(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect, const double angle, const SDL_Point *center, const SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(renderer, texture, srcrect, dstrect, angle, center, flip);
}

/*  @author Paul
    @brief renderPresent function
    @param SDL_Renderer *renderer
    @return void
*/
void Sdl::renderPresent(SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
}

/*  @author Paul
    @brief renderDrawPoint function
    @param SDL_Renderer *renderer
    @param int x
    @param int y
    @return void
*/
void Sdl::renderDrawPoint(SDL_Renderer *renderer, int x, int y)
{
    SDL_RenderDrawPoint(renderer, x, y);
}

/*  @author Paul
    @brief renderDrawColor function
    @param SDL_Renderer *renderer
    @param Uint8 r
    @param Uint8 g
    @param Uint8 b
    @param Uint8 a
    @return void
*/
void Sdl::setRenderDrawColor(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

// Texture

/*  @author Paul
    @brief createTextureFromSurface function
    @param SDL_Renderer *renderer
    @param SDL_Surface *surface
    @return SDL_Texture *
*/
SDL_Texture *Sdl::createTextureFromSurface(SDL_Renderer *renderer, SDL_Surface *surface)
{
    return SDL_CreateTextureFromSurface(renderer, surface);
}

/*  @author Paul
    @brief loadTexture function
    @param SDL_Renderer *renderer
    @param const char *file
    @return SDL_Texture *
*/
SDL_Texture *Sdl::loadTexture(SDL_Renderer *renderer, const char *file)
{
    return IMG_LoadTexture(renderer, file);
}

/*  @author Paul
    @brief destroyTexture function
    @param SDL_Texture *texture
    @return void
*/
void Sdl::destroyTexture(SDL_Texture *texture)
{
    SDL_DestroyTexture(texture);
}

/*  @author Paul
    @brief queryTexture function
    @param SDL_Texture *texture
    @param Uint32 *format
    @param int *access
    @param int *w
    @param int *h
    @return void
*/
void Sdl::queryTexture(SDL_Texture *texture, Uint32 *format, int *access, int *w, int *h)
{
    SDL_QueryTexture(texture, format, access, w, h);
}

// Surface
//  - Init and Quit

/*  @author Paul
    @brief initIMG function
    @return int
*/
int Sdl::initIMG()
{
    return IMG_Init(IMG_INIT_PNG);
}

/*  @author Paul
    @brief quitIMG function
    @return void
*/
void Sdl::quitIMG()
{
    IMG_Quit();
}

//  - Load images

/*  @author Paul
    @brief loadBMP function
    @param const char *file
    @return SDL_Surface *
*/
SDL_Surface *Sdl::loadBMP(const char *file)
{
    return SDL_LoadBMP(file);
}

/*  @author Paul
    @brief loadIMG function
    @param const char *file
    @return SDL_Surface *
*/
SDL_Surface *Sdl::loadIMG(const char *file)
{
    return IMG_Load(file);
}

//  - Other

/*  @author Paul
    @brief freeSurface function
    @param SDL_Surface *surface
    @return void
*/
void Sdl::freeSurface(SDL_Surface *surface)
{
    SDL_FreeSurface(surface);
}

// Font

/*  @author Paul
    @brief initTTF function
    @return int
*/
int Sdl::initTTF()
{
    return TTF_Init();
}

/*  @author Paul
    @brief quitTTF function
    @return void
*/
void Sdl::quitTTF()
{
    TTF_Quit();
}

/*  @author Paul
    @brief quitTTF function
    @return void
*/
TTF_Font *Sdl::openFont(const char *file, int ptsize)
{
    return TTF_OpenFont(file, ptsize);
}

/*  @author Paul
    @brief closeFont function
    @param TTF_Font *font
    @return void
*/
void Sdl::closeFont(TTF_Font *font)
{
    TTF_CloseFont(font);
}

/*  @author Paul
    @brief renderText_Solid function
    @param TTF_Font *font
    @param const char *text
    @param SDL_Color fg
    @return SDL_Surface *
*/
SDL_Surface *Sdl::renderText_Solid(TTF_Font *font, const char *text, SDL_Color fg)
{
    return TTF_RenderText_Solid(font, text, fg);
}

/*  @author Paul
    @brief renderText_Shaded function
    @param TTF_Font *font
    @param const char *text
    @param SDL_Color fg
    @param SDL_Color bg
    @return SDL_Surface *
*/
SDL_Surface *Sdl::renderText_Shaded(TTF_Font *font, const char *text, SDL_Color fg, SDL_Color bg)
{
    return TTF_RenderText_Shaded(font, text, fg, bg);
}

/*  @author Paul
    @brief renderText_Blended function
    @param TTF_Font *font
    @param const char *text
    @param SDL_Color fg
    @return SDL_Surface *
*/
SDL_Surface *Sdl::renderText_Blended(TTF_Font *font, const char *text, SDL_Color fg)
{
    return TTF_RenderText_Blended(font, text, fg);
}
