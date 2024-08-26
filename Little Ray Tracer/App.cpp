#include "App.h"

App::App() {
    isRunning = true;
    window = NULL;
    renderer = NULL;

} // App

bool App::onInitalize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    window = SDL_CreateWindow("Little RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (window != NULL) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        m_Image.intialize(1280, 720, renderer);

        for (int i = 0; i < 1280; ++i) {
            for (int j = 0; j < 720; ++j) {
                double red = (static_cast<double>(i) / 1280.0) * 255.0;
                double green = (static_cast<double>(j) / 720.0) * 255.0;
                m_Image.setPixel(i, j, red, green, 0.0);

            } // for

        } // for

    } else
        return false;

    return true;

} // onInitalize

int App::onExecute() {
    SDL_Event event;
    if (onInitalize() == false)
        return -1;

    while (isRunning) {
        while (SDL_PollEvent(&event) != NULL)
            OnEvent(&event);

        OnLoop();
        OnRender();

    } // while

} // onExecute

void App::OnEvent(SDL_Event* event) {
    if (event->type == SDL_QUIT)
        isRunning = false;

} // OnEvent

void App::OnLoop() {


} // OnLoop

void App::OnRender() {
    //Set BG Color to while
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Display the image
    m_Image.displayImage();

    // show the result
    SDL_RenderPresent(renderer);

} // OnRender

void App::OnExit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    window = NULL;

    SDL_Quit();

} // OnExit