// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
#include "INIReader.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();

    GameObject* cube = new CubeGameObject();
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();
    INIReader reader("../actionmap.ini");
    if (reader.ParseError() < 0) {
        return 1;
    }
    const std::string Left = reader.Get("Keyboard", "GoLeft", "A");
    const char codeLeft = toupper(Left[0]);
    const std::string Right = reader.Get("Keyboard", "GoRight", "D");
    const char codeRight = toupper(Right[0]);
    const std::string Up = reader.Get("Keyboard", "GoUp", "W");
    const char codeUp = toupper(Up[0]);
    const std::string Down = reader.Get("Keyboard", "GoDown", "S");
    const char codeDown = toupper(Down[0]);
    float speedx = 0.f;
    float speedy = 0.f;
    
    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            
        }
        else
        {

            if (GetAsyncKeyState(codeLeft) & 0x8000)
            {
                speedx = -1.f;
            }
            else if (GetAsyncKeyState(codeRight) & 0x8000) {
                speedx = 1.f;
            }
            else if (GetAsyncKeyState(codeUp) & 0x8000) {
                speedy = 1.f;
            }
            else if (GetAsyncKeyState(codeDown) & 0x8000) {
                speedy = -1.f;
            }

            float t = 0.f;
            timer.Tick();
            t = sin(timer.TotalTime()) * 2;
            cube->AddPosition(speedx * timer.DeltaTime(), 0.0f, speedy * timer.DeltaTime());
            speedx = 0.f;
            speedy = 0.f;
            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
