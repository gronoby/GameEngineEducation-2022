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
#include "InputHandler.h"


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
    InputHandler* inputHandler = new InputHandler();

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    srand(time(0));

    CubeGameObject* objects[100];
    for (int i = 0; i < 100; i++) {
        int a = rand() % 3;
        if (a == 0)
            objects[i] = new MoveCube();
        else if (a == 1)
            objects[i] = new JumpCube();
        else {
            objects[i] = new ControledCube();
        }
        renderThread->EnqueueCommand(RC_CreateCubeRenderObject, objects[i]->GetRenderProxy());
        objects[i]->SetPosition(6.0f * (i % 10) - 25.f, -50.0f, (i / 10) * 6.f);
    }

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
            inputHandler->Update();
            timer.Tick();
            
            for (auto& object : objects) {
                object->Move(timer.TotalTime());
                object->Jump(timer.TotalTime());
                if (inputHandler->GetInputState().test(eIC_GoRight)) {
                    object->Control(timer.DeltaTime(), eIC_GoRight);
                }
                if (inputHandler->GetInputState().test(eIC_GoLeft)) {
                    object->Control(timer.DeltaTime(), eIC_GoLeft);
                }
            }

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
