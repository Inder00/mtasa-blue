#include "StdInc.h"

#include "../sdk/core/CCoreBasicInterface.h"
#include "SharedUtil.Defines.h"
#include <cassert>

MTAEXPORT CDirectx11Base* InitializeDirectx11(CCoreBasicInterface* basicInterface)
{
    return new CDirectx11(basicInterface->GetHookedWindow());
}
