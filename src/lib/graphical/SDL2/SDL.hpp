/*
** EPITECH PROJECT, 2023
** B-PDG-300-LIL-3-1-PDGRUSH3-ulysse.decottignies
** File description:
** Sdl
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Sdl {
    public:
        //  SDL

        /// @author Paul
        /// @brief initSDL function
        /// @param void
        /// @return int
        static int initSDL();

        /// @author Paul
        /// @brief quitSDL function
        /// @param void
        /// @return void
        static void quitSDL();

        //  Window

        /// @author Paul
        /// @brief createWindow function
        /// @param const char *title
        /// @param int x
        /// @param int y
        /// @param int w
        /// @param int h
        /// @param Uint32 flags
        /// @return SDL_Window *
        static SDL_Window *createWindow(const char *title, int x, int y, int w, int h, Uint32 flags);

        /// @author Paul
        /// @brief destroyWindow function
        /// @param SDL_Window *window
        /// @return void
        static void destroyWindow(SDL_Window *window);

        //  Renderer

        /// @author Paul
        /// @brief createRenderer function
        /// @param SDL_Window *window
        /// @param int index
        /// @param Uint32 flags
        /// @return SDL_Renderer *
        static SDL_Renderer *createRenderer(SDL_Window *window, int index, Uint32 flags);

        /// @author Paul
        /// @brief destroyRenderer function
        /// @param SDL_Renderer *renderer
        /// @return void
        static void destroyRenderer(SDL_Renderer *renderer);

        /// @author Paul
        /// @brief renderClear function
        /// @param SDL_Renderer *renderer
        /// @return void
        static void renderClear(SDL_Renderer *renderer);

        /// @author Paul
        /// @brief renderCopy function
        /// @param SDL_Renderer *renderer
        /// @param SDL_Texture *texture
        /// @param const SDL_Rect *srcrect
        /// @param const SDL_Rect *dstrect
        /// @return void
        static void renderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect);

        /// @author Paul
        /// @brief renderCopyEx function
        /// @param SDL_Renderer *renderer
        /// @param SDL_Texture *texture
        /// @param const SDL_Rect *srcrect
        /// @param const SDL_Rect *dstrect
        /// @param const double angle
        /// @param const SDL_Point *center
        /// @param const SDL_RendererFlip flip
        /// @return void
        static void renderCopyEx(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect, const double angle, const SDL_Point *center, const SDL_RendererFlip flip);

        /// @author Paul
        /// @brief renderPresent function
        /// @param SDL_Renderer *renderer
        /// @return void
        static void renderPresent(SDL_Renderer *renderer);

        /// @author Paul
        /// @brief renderDrawPoint function
        /// @param SDL_Renderer *renderer
        /// @param int x
        /// @param int y
        /// @return void
        static void renderDrawPoint(SDL_Renderer *renderer, int x, int y);

        /// @author Paul
        /// @brief renderDrawColor function
        /// @param SDL_Renderer *renderer
        /// @param Uint8 r
        /// @param Uint8 g
        /// @param Uint8 b
        /// @param Uint8 a
        /// @return void
        static void setRenderDrawColor(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        //  Texture

        /// @author Paul
        /// @brief createTextureFromSurface function
        /// @param SDL_Renderer *renderer
        /// @param SDL_Surface *surface
        /// @return SDL_Texture *
        static SDL_Texture *createTextureFromSurface(SDL_Renderer *renderer, SDL_Surface *surface);

        /// @author Paul
        /// @brief loadTexture function
        /// @param SDL_Renderer *renderer
        /// @param const char *file
        /// @return void
        static SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *file);

        /// @brief destroyTexture function
        /// @param SDL_Texture *texture
        /// @return void
        static void destroyTexture(SDL_Texture *texture);

        /// @author Paul
        /// @brief queryTexture function
        /// @param SDL_Texture *texture
        /// @param Uint32 *format
        /// @param int *access
        /// @param int *w
        /// @param int *h
        /// @return void
        static void queryTexture(SDL_Texture *texture, Uint32 *format, int *access, int *w, int *h);

        //  Surface

        /// @author Paul
        /// @brief initIMG function
        /// @param void
        /// @return int
        static int initIMG();

        /// @author Paul
        /// @brief quitIMG function
        /// @param void
        /// @return void
        static void quitIMG();

        /// @author Paul
        /// @brief loadBMP function
        /// @param const char *file
        /// @return SDL_Surface *
        static SDL_Surface *loadBMP(const char *file);

        /// @author Paul
        /// @brief loadIMG function
        /// @param const char *file
        /// @return SDL_Surface *
        static SDL_Surface *loadIMG(const char *file);

        /// @author Paul
        /// @brief freeSurface function
        /// @param SDL_Surface *surface
        /// @return void
        static void freeSurface(SDL_Surface *surface);

        //  Font

        /// @author Paul
        /// @brief initTTF function
        /// @param void
        /// @return int
        static int initTTF();

        /// @author Paul
        /// @brief quitTTF function
        /// @param void
        /// @return void
        static void quitTTF();

        /// @author Paul
        /// @brief openFont function
        /// @param const char *file
        /// @param int ptsize
        /// @return TTF_Font *
        static TTF_Font *openFont(const char *file, int ptsize);

        /// @author Paul
        /// @brief closeFont function
        /// @param TTF_Font *font
        /// @return void
        static void closeFont(TTF_Font *font);

        /// @author Paul
        /// @brief renderText_Solid function
        /// @param TTF_Font *font
        /// @param const char *text
        /// @param SDL_Color fg
        /// @return SDL_Surface *
        static SDL_Surface *renderText_Solid(TTF_Font *font, const char *text, SDL_Color fg);

        /// @author Paul
        /// @brief renderText_Shaded function
        /// @param TTF_Font *font
        /// @param const char *text
        /// @param SDL_Color fg
        /// @param SDL_Color bg
        /// @return SDL_Surface *
        static SDL_Surface *renderText_Shaded(TTF_Font *font, const char *text, SDL_Color fg, SDL_Color bg);

        /// @author Paul
        /// @brief renderText_Blended function
        /// @param TTF_Font *font
        /// @param const char *text
        /// @param SDL_Color fg
        /// @return SDL_Surface *
        static SDL_Surface *renderText_Blended(TTF_Font *font, const char *text, SDL_Color fg);
};
