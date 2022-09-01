#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "screen.h"
#include "temps.h"

void Init()
{
    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
}

void Quit()
{
    TTF_Quit();
    SDL_Quit();
}

void createMainWindow(Window *window)
{
    SDL_WM_SetCaption("Time",NULL);
    window->surface = SDL_SetVideoMode(window->position.w,window->position.h,32,SDL_HWSURFACE|SDL_NOFRAME);
    if(window->surface == NULL)
    {
        fprintf(stderr,"Erreur: %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SetWindowPos(FindWindow("SDL_app","Time"),HWND_TOPMOST,1024-window->position.w,768-window->position.h,window->position.w,window->position.h,SWP_SHOWWINDOW);
}

void createText(Text *text, const char *content, const char *fontPath, int size, SDL_Color color)
{
    text->font = TTF_OpenFont(fontPath,size);

    strcpy(text->content,content);
    text->color = color;
}

Window* createTextWindow(const Text *text)
{
    Window *textWindow = (Window*) malloc(sizeof(Window));
    textWindow->surface = TTF_RenderText_Blended(text->font,text->content,text->color);
    textWindow->content = NULL;
    return textWindow;
}

void destroyTextWindow(Text *text, Window *textWindow)
{
    TTF_CloseFont(text->font);
    SDL_FreeSurface(textWindow->surface);
    free(textWindow);
}

void showTextWindow(Window *mainWindow, Window *textWindow)
{
    textWindow->position.x = (mainWindow->surface->w - textWindow->surface->w)/2;
    textWindow->position.y = (mainWindow->surface->h - textWindow->surface->h)/2;
    SDL_FillRect(mainWindow->surface,NULL,SDL_MapRGB(mainWindow->surface->format,0,0,0));
    SDL_BlitSurface(textWindow->surface,NULL,mainWindow->surface,&(textWindow->position));
}

void updateTimeText(Text *text)
{
    TEMPS time;
    obtenirTemps(&time);

    char h[3] = "", m[3] = "";

    h[0] = (time.heure)/10 + '0';
    h[1] = (time.heure)%10 + '0';
    h[2] = '\0';

    m[0] = (time.minute)/10 + '0';
    m[1] = (time.minute)%10 + '0';
    m[2] = '\0';

    sprintf(text->content,"%s:%s",h,m);
}

void updateTextWindow(Window *mainWindow, Window *textWindow, const Text *text)
{
    SDL_FreeSurface(textWindow->surface);
    textWindow->surface = TTF_RenderText_Blended(text->font,text->content,text->color);
    showTextWindow(mainWindow,textWindow);
    SDL_Flip(mainWindow->surface);
}

void waitForASecond()
{
    int actualTimestamp = SDL_GetTicks();
    static int lastTimestamp = 0;

    if(actualTimestamp-lastTimestamp >= 1000)
        lastTimestamp = actualTimestamp;
    else
        SDL_Delay(1000 - (actualTimestamp - lastTimestamp));
    
}

void Screen()
{
    int runProgram = 1;
    SDL_Event event;

    Window mainScreen = {
            NULL,
            {
                0,
                0,
                150,
                75
            },
            NULL
        };

    Text timeText;

    Init();

    createMainWindow(&mainScreen);

    createText(&timeText,"09:05","font\\DS-DIGIB.TTF",60,(SDL_Color){255,43,43});

    mainScreen.content = createTextWindow(&timeText);

    while(runProgram)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                runProgram = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        runProgram = 0;
                        continue;
                    default:
                        break;
                }
                break;
        }

        updateTimeText(&timeText);

        updateTextWindow(&mainScreen,mainScreen.content,&timeText);

        waitForASecond();
    }

    destroyTextWindow(&timeText,mainScreen.content);

    Quit();
}
