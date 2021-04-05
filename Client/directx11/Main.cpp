#include "StdInc.h"

__declspec(dllexport) CDirectx11Base* InitializeDirectx11(HWND nativeWindowHandle)
{
    return new CDirectx11(nativeWindowHandle);
}
