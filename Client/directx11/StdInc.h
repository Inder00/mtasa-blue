#define DILIGENT_DEVELOPMENT

#include <d3d11.h>
#include <diligentCore/Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h>
#include <diligentCore/Platforms/Interface/NativeWindow.h>
#include <diligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <diligentCore/Platforms/Win32/interface/Win32NativeWindow.h>
#include <diligentCore/Common/interface/BasicMath.hpp>

using namespace Diligent;

#include <cassert>
#include <vector>
#include <thread>

#include "../sdk/core/CCoreBasicInterface.h"
#include "Main.h"
#include "logic/Vertex.h"

class CDirectx11;

#include "CMesh.h"
#include "CDirectx11.h"


