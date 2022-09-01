#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

typedef struct Window Window;
struct Window
{
    SDL_Surface *surface;
    SDL_Rect position;
    Window *content;
};

typedef struct Text
{
    char content[8];
    TTF_Font *font;
    int size;
    SDL_Color color;
} Text;

void Screen();
