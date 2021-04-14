#include "StdInc.h"

#include "SharedUtil.Defines.h"

MTAEXPORT CDirectx11Base* InitializeDirectx11(CCoreBasicInterface* basicInterface)
{
    return new CDirectx11(basicInterface);
}
