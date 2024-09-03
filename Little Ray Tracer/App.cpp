#include "App.h"
#include "qbLinAlg/qbVector.h"

App::App() {
    isRunning = true;
    window = NULL;
    renderer = NULL;

} // App

bool App::onInitalize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    int xSize = 1280;
    int ySize = 720;

    window = SDL_CreateWindow("Little RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xSize, ySize, SDL_WINDOW_SHOWN); 

    if (window != NULL) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        m_Image.intialize(xSize, ySize, renderer); 
         
        // set bg to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer); 
        
        m_Scene.Render(m_Image);

        //// Setup a texture
        //LRT::Texture::Checker testTexture;
        //testTexture.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
        //                                          M_PI / 4.0, // Angle
        //                                          qbVector<double>{std::vector<double>{4.0, 4.0}});

        //for (int y = 0; y < ySize; ++y) {
        //    for (int x = 0; x < xSize; ++x) {
        //        // Compute uv
        //        double u = (static_cast<double>(x) / (static_cast<double>(xSize) / 2.0)) - 1;
        //        double v = (static_cast<double>(y) / (static_cast<double>(ySize) / 2.0)) - 1;
        //        qbVector<double> uvCoords{ std::vector<double> {u, v} };

        //        // get the color from the texture
        //        qbVector<double> pixelCoords = testTexture.getColor(uvCoords); 
        //         
        //        // Update this pixels of the image
        //        m_Image.setPixel(x, y, pixelCoords.GetElement(0), pixelCoords.GetElement(1), pixelCoords.GetElement(2));

        //    } // for

        //} // for

        m_Image.displayImage(); 

        SDL_RenderPresent(renderer);

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
    ////Set BG Color to while
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderClear(renderer);

    //// Render the scene
    //m_Scene.Render(m_Image); 

    //// Display the image
    //m_Image.displayImage();

    //// show the result
    //SDL_RenderPresent(renderer);

} // OnRender

void App::OnExit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    window = NULL;

    SDL_Quit();

} // OnExit

void App::printVector(const qbVector<double>& inputVector) {
    int nRows = inputVector.GetNumDims();
    for (int i = 0; i < nRows; ++i) 
        std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(i) << std::endl;

} // printVector