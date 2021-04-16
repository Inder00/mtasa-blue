-- Credits: https://gist.github.com/JSandusky/ffe5f4a334600a4263dd0671ded2c948
--[[ 
Usage:
    
    // setup the paths and build options
    DEGFX_InitPaths(...)
    DEGFX_InitRenderers(...)
    
    // add the projects to build
    DEGFX_IncludeProjects()
    
    // In an active project that needs to reference DE-GFX
    DEGFX_Bind()
    
    example:
        project "MyProject"
            DEGFX_Bind()
]]--

local degfx_baseDir = "bin/"
local degfx_diligentSourceDir = "vendor/diligentCore/"

local degfx_windows = true
local degfx_android = false

local degfx_useGL = false
local degfx_useD3D11 = false
local degfx_useD3D12 = false
local degfx_useVulkan = false

local degfx_engineD3D11 = ""
local degfx_engineD3DBase = ""
local degfx_engineD3D12 = ""
local degfx_engineGL = ""
local degfx_engineVulkan = ""

function DEGFX_InitPaths(deSrcDir, baseDir)
    degfx_diligentSourceDir = deSrcDir
    degfx_baseDir = baseDir
end

function DEGFX_InitRenderers(useD3D11, useD3D12, useVulkan)
    degfx_useD3D11 = useD3D11
    degfx_useD3D12 = useD3D12
    degfx_useGL = false
    degfx_useVulkan = useVulkan
    degfx_engineD3D11 = degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/interface"
    degfx_engineD3DBase = degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include"
    degfx_engineGL = degfx_diligentSourceDir .. "Graphics/GraphicsEngineOpenGL/include"
    degfx_engineVulkan = degfx_diligentSourceDir .. "Graphics/GraphicsEngineVulkan/interface"
end

function DEGFX_AttachDefines()
    if degfx_windows then
        defines { "PLATFORM_WIN32", "DILIGENT_DEVELOPMENT" }
    end
    if degfx_android then
        defines { "PLATFORM_ANDROID", "DILIGENT_DEVELOPMENT" }
    end
    
    if degfx_useD3D11 then
        defines { "D3D11_SUPPORTED", "DILIGENT_DEVELOPMENT" }
    end
    if degfx_useD3D12 then
        defines { "D3D11_SUPPORTED", "DILIGENT_DEVELOPMENT" }
    end
    if degfx_useVulkan then
        defines { "VULKAN_SUPPORTED", "DILIGENT_DEVELOPMENT" }
    end
end

function DEGFX_DeepDependency()
    dependson { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc" }
    links { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc" }
    includedirs {
        degfx_diligentSourceDir .. "Primitives/interface",
        degfx_diligentSourceDir .. "Common/interface",
        degfx_diligentSourceDir .. "Platforms/interface",
        degfx_diligentSourceDir .. "Platforms/Basic/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngine/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngine/include",
        degfx_diligentSourceDir .. "Graphics/GraphicsTools/include",
        degfx_diligentSourceDir .. "Graphics/GraphicsAccessories/interface",
    }
end

function DEGFX_AttachD3D11()
    defines { "D3D11_SUPPORTED" }
    links { "DiligentGraphicsD3D11", "DiligentGraphicsD3DBase" }
    dependson { "DiligentGraphicsD3D11", "DiligentGraphicsD3DBase" }
    includedirs { 
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineBase/include"
    }
end

function DEGFX_AttachD3D12()
    defines { "D3D12_SUPPORTED" }
    links { "DiligentGraphicsD3D12", "DiligentGraphicsD3DBase" }
    dependson { "DiligentGraphicsD3D12", "DiligentGraphicsD3DBase" }
    includedirs { 
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D12/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineBase/include"
    }
end

function DEGFX_AttachOpenGL()
    defines { "GL_SUPPORTED" }
    links { "DiligentGraphicsGL", "DiligentGraphicsD3DBase" }
    dependson { "DiligentGraphicsGL", "DiligentGraphicsD3DBase" }
    includedirs { 
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineOpenGL/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineBase/include"
    }
end

function DEGFX_AttachVulkan()
    defines { "VULKAN_SUPPORTED" }
    links { "DiligentGraphicsVulkan", "DiligentGraphicsD3DBase" }
    dependson { "DiligentGraphicsVulkan", "DiligentGraphicsD3DBase" }
    includedirs { 
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineVulkan/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineBase/include"
    }
end

function DEGFX_Bind()
    if degfx_windows then
        defines { "PLATFORM_WIN32" }
        dependson { "DiligentPlatformWin" }
        links { "DiligentPlatformWin" }
        includedirs { degfx_diligentSourceDir .. "Graphics/Platforms/Win32/interface" }
    elseif degfx_android then
        defines { "PLATFORM_ANDROID" }
        dependson { "DiligentPlatformAndroid" }
        links { "DiligentPlatformAndroid" }
        includedirs { degfx_diligentSourceDir .. "Graphics/Platforms/Android/interface" }
    end
    
    DEGFX_AttachDefines()
    
    dependson {
        "DiligentPrimitives",
        "DiligentCoreCommon",
        "DiligentGraphicsTools",
        "DiligentGraphicsAcc",
        "DiligentPlatformBasic",
        "DiligentGraphics"
    }
    links {
        "DiligentPrimitives",
        "DiligentCoreCommon",
        "DiligentGraphicsTools",
        "DiligentGraphicsAcc",
        "DiligentPlatformBasic",
        "DiligentGraphics"
    } 
    
    includedirs {
        degfx_diligentSourceDir .. "Primitives/interface",
        degfx_diligentSourceDir .. "Common/interface",
        degfx_diligentSourceDir .. "Common/include",
        
        degfx_diligentSourceDir .. "Graphics/Platforms/Basic/interface",
        degfx_diligentSourceDir .. "Graphics/Graphics/GraphicsAccessories/interface",
        degfx_diligentSourceDir .. "Graphics/Graphics/GraphicsTools/include",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngine/interface"
    }
    
    if degfx_useD3D11 or degfx_useD3D12 then
        DEGFX_AttachD3D11()
    end
    if degfx_useD3D11 then
        DEGFX_AttachD3D12()
    end
    if degfx_useVulkan then
        DEGFX_AttachVulkan()
    end
end
        
function DEGFX_IncludeProjects()
    
    project "DiligentCoreCommon"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        dependson {  "DiligentPlatformBasic", "DiligentPrimitives" }
        links { "DiligentPlatformBasic", "DiligentPrimitives" }
        
        files {
            degfx_diligentSourceDir .. "Common/src/**.cpp"
        }
        removefiles {
            degfx_diligentSourceDir .. "Common/src/pch.cpp"
        }
        
        includedirs {
            degfx_diligentSourceDir .. "Common/include",
            degfx_diligentSourceDir .. "Common/interface",
            degfx_diligentSourceDir .. "Platforms/interface",
            degfx_diligentSourceDir .. "Primitives/interface"
        }
        
        DEGFX_AttachDefines()
        
    project "DiligentPrimitives"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"

        files {
            degfx_diligentSourceDir .. "Primitives/src/**.cpp"
        }
        includedirs {
            degfx_diligentSourceDir .. "Primitives/interface"
        }
        
    project "DiligentGraphics"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        dependson { "DiligentCoreCommon", "DiligentPrimitives", "DiligentPlatformBasic", "DiligentPlatformWin" }
        links { "DiligentCoreCommon", "DiligentPrimitives", "DiligentPlatformBasic", "DiligentPlatformWin" }
        
        files {
            degfx_diligentSourceDir .. "Graphics/GraphicsEngine/src/**.cpp",
            degfx_diligentSourceDir .. "Platforms/interface/**.hpp"
        }
        includedirs {
            degfx_diligentSourceDir .. "Common/interface",
            degfx_diligentSourceDir .. "Platforms/interface",
            degfx_diligentSourceDir .. "Primitives/interface",
            degfx_diligentSourceDir .. "Platforms/Basic/interface",
            
            degfx_diligentSourceDir .. "Graphics/GraphicsEngine/include",
            degfx_diligentSourceDir .. "Graphics/GraphicsEngine/interface",        
            degfx_diligentSourceDir .. "Graphics/GraphicsAccessories/interface"
        }
        
        DEGFX_AttachDefines()
        
    project "DiligentGraphicsAcc"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        dependson { "DiligentCoreCommon", "DiligentPrimitives", "DiligentPlatformBasic", "DiligentPlatformWin" }
        links { "DiligentCoreCommon", "DiligentPrimitives", "DiligentPlatformBasic", "DiligentPlatformWin" }
        
        files {
            degfx_diligentSourceDir .. "Graphics/GraphicsAccessories/**.cpp",
            degfx_diligentSourceDir .. "Common/interface/**.hpp"
        }
        
        includedirs { 
            degfx_diligentSourceDir .. "Graphics/GraphicsAccessories/interface",
            degfx_diligentSourceDir .. "Primitives/interface",
            degfx_diligentSourceDir .. "Platforms/Basic/interface",
            degfx_diligentSourceDir .. "Common/interface"
        }
        
        DEGFX_AttachDefines()

    project "DiligentGraphicsD3DBase"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        
        files {
            degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/src/**.cpp",
            degfx_diligentSourceDir .. "ThirdParty/DirectXShaderCompiler/**.h",
            degfx_diligentSourceDir .. "ThirdParty/GPUOpenShaderUtils/DXBCChecksum.cpp",
            degfx_diligentSourceDir .. "ThirdParty/GPUOpenShaderUtils/DXBCChecksum.h",
            degfx_diligentSourceDir .. "Graphics/ShaderTools/include/**.hpp",
            degfx_diligentSourceDir .. "Graphics/ShaderTools/src/ShaderToolsCommon.cpp",
            degfx_diligentSourceDir .. "Graphics/ShaderTools/src/HLSLUtils.cpp",
            degfx_diligentSourceDir .. "Graphics/ShaderTools/src/GLSLUtils.cpp",
            degfx_diligentSourceDir .. "Graphics/ShaderTools/src/DXBCUtils.cpp",
            degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface/**.h",
            degfx_diligentSourceDir .. "Graphics/HLSL2GLSLConverterLib/*.h",
            degfx_diligentSourceDir .. "Graphics/HLSL2GLSLConverterLib/*.hpp",
            degfx_diligentSourceDir .. "Graphics/HLSL2GLSLConverterLib/*.cpp",
        }
        
        includedirs {
            degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
            degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
            degfx_diligentSourceDir .. "ThirdParty/DirectXShaderCompiler",
            degfx_diligentSourceDir .. "Graphics/ShaderTools/include",
            degfx_diligentSourceDir .. "Graphics/HLSL2GLSLConverterLib/include",
            degfx_diligentSourceDir .. "Graphics/HLSL2GLSLConverterLib/interface",
        }
        
        DEGFX_AttachDefines()
        DEGFX_DeepDependency()
        
    project "DiligentGraphicsTools"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        dependson { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc" }
        links { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc" }
        
        files {
            degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/**.cpp",
            degfx_diligentSourceDir .. "Graphics/GraphicsTools/interface/**.cpp",
        }
        includedirs {
            degfx_diligentSourceDir .. "Primitives/interface",
            degfx_diligentSourceDir .. "Common/interface",
            degfx_diligentSourceDir .. "Platforms/Basic/interface",
            degfx_diligentSourceDir .. "Graphics/GraphicsEngine/interface",
            degfx_diligentSourceDir .. "Graphics/GraphicsTools/include",
            degfx_diligentSourceDir .. "Graphics/GraphicsTools/interface",
            degfx_diligentSourceDir .. "Graphics/GraphicsAccessories/interface",
        }
        
        if degfx_useD3D11 or degfx_useD3D12 then
            includedirs { degfx_engineD3DBase }
        end
        if degfx_useD3D11 == false then
            removefiles { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/*D3D11.cpp" }
        else
            includedirs { 
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/interface",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/include" 
            }
        end
        
        if degfx_useD3D12 == false then
            removefiles { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/*D3D12.cpp" }
        else
            includedirs { 
                degfx_engineD3D12,
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D12/include" 
            }
        end
        
        if degfx_useGL == false then
            removefiles { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/*GL.cpp" }
        end
        
        DEGFX_AttachDefines()
        
    project "DiligentPlatformBasic"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        dependson { "DiligentPrimitives" }
        links { "DiligentPrimitives" }

        DEGFX_AttachDefines()
        
        files {
            degfx_diligentSourceDir .. "Platforms/Basic/src/**.cpp",
            degfx_diligentSourceDir .. "Platforms/Basic/interface/**.h"
        }
        
        removefiles { degfx_diligentSourceDir .. "Platforms/Basic/src/pch.cpp" }
        
        includedirs {
            degfx_diligentSourceDir .. "Platforms/Basic/interface",
            degfx_diligentSourceDir .. "Platforms/interface",
            degfx_diligentSourceDir .. "Primitives/interface"
        }
        

    if degfx_windows then
        project "DiligentPlatformWin"
            kind "StaticLib"
            language "C++"
            cppdialect "C++11"
            characterset "MBCS"
            dependson { "DiligentPlatformBasic", "DiligentPrimitives"  }
            links { "DiligentPlatformBasic", "DiligentPrimitives" }
            
            files { degfx_diligentSourceDir .. "Platforms/Win32/src/**.cpp" }
            
            removefiles { degfx_diligentSourceDir .. "Platforms/Win32/src/pch.cpp" }
            
            includedirs { 
                degfx_diligentSourceDir .. "Platforms/Win32/interface",
                degfx_diligentSourceDir .. "Platforms/interface",
                degfx_diligentSourceDir .. "Primitives/interface"
            }
    end
    
    if degfx_useD3D11 then
        project "DiligentGraphicsD3D11"
            kind "StaticLib"
            language "C++"
            cppdialect "C++11"
            characterset "MBCS"
            dependson { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc", "DiligentGraphics", "DiligentGraphicsD3DBase" }
            links { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc", "DiligentGraphics", "DiligentGraphicsD3DBase" }
            
            files {
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/src/**.cpp",
                degfx_diligentSourceDir .. "Graphics/ShaderTools/include/**.hpp",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface/**.h",
            }
            includedirs {
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/include",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/interface",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
                degfx_diligentSourceDir .. "Graphics/ShaderTools/include",
            }
            
            DEGFX_AttachDefines()
            DEGFX_DeepDependency()
    end
    
    if degfx_useD3D12 then
        project "DiligentGraphicsD3D12"
            kind "StaticLib"
            language "C++"
            cppdialect "C++11"
            characterset "MBCS"
            dependson { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc", "DiligentGraphics", "DiligentGraphicsD3DBase" }
            links { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc", "DiligentGraphics", "DiligentGraphicsD3DBase" }
            
            files { degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D12/src/**.cpp" }
            includedirs {
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D12/include",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D12/interface",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
            }
            
            DEGFX_AttachDefines()
            DEGFX_DeepDependency()
    end
end