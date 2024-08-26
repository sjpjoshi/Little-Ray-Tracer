#pragma once
#ifndef APP_H
#define APP_H

#include "Image.hpp"

// libs
#include "SDL2/SDL.h"

class App {
public:
    App();

    int onExecute();
    bool onInitalize();
    void OnEvent(SDL_Event* event);
    void OnLoop();
    void OnRender();
    void OnExit();

private:    
    Image m_Image;

    //SDL 2 Variables
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

}; // App

#endif