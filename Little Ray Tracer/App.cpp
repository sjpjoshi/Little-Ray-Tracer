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

    window = SDL_CreateWindow("Little RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (window != NULL) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        m_Image.intialize(1280, 720, renderer);
        
        // Test the camera class.
        LRT::Camera testCamera;
        testCamera.SetPosition(qbVector<double>(std::vector<double>{0.0, 0.0, 0.0}));
        testCamera.SetLookAt(qbVector<double>(std::vector<double>{0.0, 2.0, 0.0}));
        testCamera.SetUp(qbVector<double>(std::vector<double>{0.0, 0.0, 1.0}));
        testCamera.SetLength(1.0);
        testCamera.SetHorzSize(1.0);
        testCamera.SetAspect(1.0);
        testCamera.UpdateCameraGeometry();

        // Get the screen centre and U,V vectors and display.
        auto screenCentre = testCamera.GetScreenCentre();
        auto screenU = testCamera.GetU();
        auto screenV = testCamera.GetV();

        // And display to the terminal.
        std::cout << "Camera screen centre:" << std::endl;
        printVector(screenCentre);
        std::cout << "\nCamera U vector:" << std::endl;
        printVector(screenU);
        std::cout << "\nCamera V vector:" << std::endl;
        printVector(screenV); 
        
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

    // Render the scene
    m_Scene.Render(m_Image); 

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

void App::printVector(const qbVector<double>& inputVector) {
    int nRows = inputVector.GetNumDims();
    for (int i = 0; i < nRows; ++i) 
        std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(i) << std::endl;

   

} // printVector