#pragma once
#ifndef APP_H
#define APP_H

#include "Image.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Flat.hpp"
#include "Checker.hpp"

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
    void printVector(const qbVector<double>& inputVector);

private:    
    Image m_Image;
    LRT::Scene m_Scene;

    //SDL2 Variables
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

}; // App

#endif