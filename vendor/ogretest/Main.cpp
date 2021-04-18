#include "StdInc.h"
#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>

#include "base/COgreBase.h"

int main(int argc, char* argv[])
{
    HINSTANCE module = LoadLibrary(TEXT("D:\\VISUAL STUDIO\\mtasa-blue\\Bin\\MTA\\MtaOgre_d.dll"));
    if (!module)
    {
        printf("Failed to load MtaOgre_d.dll");
        return -1;
    }
    typedef COgreBase* (*PFNINITIALIZER)();
    PFNINITIALIZER pfnInit = (PFNINITIALIZER)(GetProcAddress(module, "Init"));
    COgreBase*     pOgre = pfnInit();
    pOgre->init();

    return 0;
}
