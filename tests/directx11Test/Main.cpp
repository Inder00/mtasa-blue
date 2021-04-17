#include "StdInc.h"
#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>

#include <assert.h>
#include "../../Client/sdk/core/CCoreBasicInterface.h"

#include "./../Client/directx11/headers/DiligentCore.h"

using namespace Diligent;

#include "./../Client/directx11/base/CDirectx11Base.h"
#include "./../Client/directx11/logic/utils/Vertex.h"



static bool global_windowDidResize = false;

class CCore : public CCoreBasicInterface
{
public:
    CCore(HWND window) : m_window(window){};

    HWND GetHookedWindow() { return m_window; }

private:
    HWND m_window;
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    LRESULT result = 0;
    switch (msg)
    {
        case WM_KEYDOWN:
        {
            if (wparam == VK_ESCAPE)
                DestroyWindow(hwnd);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        case WM_SIZE:
        {
            global_windowDidResize = true;
            break;
        }
        default:
            result = DefWindowProcW(hwnd, msg, wparam, lparam);
    }
    return result;
}

HWND CreateWin(HINSTANCE hInstance)
{
    // Open a window
    HWND hwnd;
    {
        WNDCLASSEXW winClass = {};
        winClass.cbSize = sizeof(WNDCLASSEXW);
        winClass.style = CS_HREDRAW | CS_VREDRAW;
        winClass.lpfnWndProc = &WndProc;
        winClass.hInstance = hInstance;
        winClass.hIcon = LoadIconW(0, IDI_APPLICATION);
        winClass.hCursor = LoadCursorW(0, IDC_ARROW);
        winClass.lpszClassName = L"MyWindowClass";
        winClass.hIconSm = LoadIconW(0, IDI_APPLICATION);

        if (!RegisterClassExW(&winClass))
        {
            MessageBoxA(0, "RegisterClassEx failed", "Fatal Error", MB_OK);
            return 0;
        }

        RECT initialRect = {0, 0, 800, 600};
        AdjustWindowRectEx(&initialRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
        LONG initialWidth = initialRect.right - initialRect.left;
        LONG initialHeight = initialRect.bottom - initialRect.top;

        hwnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, winClass.lpszClassName, L"Test window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
                               initialWidth, initialHeight, 0, 0, hInstance, 0);

        if (!hwnd)
        {
            MessageBoxA(0, "CreateWindowEx failed", "Fatal Error", MB_OK);
            return 0;
        }
    }
    return hwnd;
}

void PumpMessage(HWND hookedWindow)
{
    MSG msg;

    unsigned int uiUnusedMessageId = 0x3039;
    PostMessage(hookedWindow, uiUnusedMessageId, 0, 0);
    PeekMessage(&msg, NULL, uiUnusedMessageId, uiUnusedMessageId, PM_REMOVE);
    PeekMessage(&msg, NULL, uiUnusedMessageId, uiUnusedMessageId, PM_REMOVE);
}


std::vector<ColorVertex> CubeVerts = {
    {float3(-1, -1, -1), float4(1, 0, 0, 1)}, {float3(-1, 1, -1), float4(0, 1, 0, 1)},
    {float3(1, 1, -1), float4(0, 0, 1, 1)}, {float3(1, -1, -1), float4(1, 1, 1, 1)},

    {float3(-1, -1, 1), float4(1, 1, 0, 1)}, {float3(-1, 1, 1), float4(0, 1, 1, 1)},
    {float3(1, 1, 1), float4(1, 0, 1, 1)}, {float3(1, -1, 1), float4(0.2f, 0.2f, 0.2f, 1)},
};

CObjectBase* pObject = nullptr;

void start(CDirectx11Base* directx11)
{
    CMeshBase* pMesh = directx11->CreateMesh(CubeVerts, {2, 0, 1, 2, 3, 0, 4, 6, 5, 4, 7, 6, 0, 7, 4, 0, 3, 7, 1, 0, 4, 1, 4, 5, 1, 5, 2, 5, 6, 2, 3, 6, 7, 3, 2, 6});
    directx11->CreateModel(0, pMesh);

    pObject = directx11->CreateObject(0, {-300, -300, -100});
}

int i = 0;

int main()
{
    HINSTANCE module = LoadLibrary(TEXT("./../../Bin/MTA/directx11_d.dll"));

    typedef CDirectx11Base* (*PFNINITIALIZER)(CCoreBasicInterface*);
    PFNINITIALIZER pfnInit = (PFNINITIALIZER)(GetProcAddress(module, "InitializeDirectx11"));

    HWND win = CreateWin(GetModuleHandle(nullptr));
    CDirectx11Base* directx11 = pfnInit(new CCore(win));

    bool bStart = false;
    while (true)
    {
        printf(".");
        MSG msg = {};
        while (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                int a = 5;
            }
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        directx11->DoPulse();
        if (!bStart)
        {
            bStart = true;
            start(directx11);
        }
        i++;
        pObject->SetPosition(float3(sin(i / 50.0f) * 100.0f, cos(i / 50.0f) * 100.0f, cos(i / 20.0f) * 100.0f));
        // PumpMessage(win);
        Sleep(10);
    }
}
