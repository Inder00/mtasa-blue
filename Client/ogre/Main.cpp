#include "StdInc.h"

extern "C" __declspec(dllimport) COgreBase* Init();

COgreBase* Init()
{
    COgre* engine = new COgre();
    return engine;
}
