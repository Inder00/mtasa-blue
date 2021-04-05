project "Client Directx11"
	language "C++"
	kind "SharedLib"
	targetname "directx11"

    DEGFX_Bind()

	filter {}
		includedirs {
		}

	pchheader "StdInc.h"
	pchsource "StdInc.cpp"

	vpaths {
		["Headers/*"] = "**.h",
		["Sources/*"] = "**.cpp",
		["*"] = "premake5.lua"
	}


	files {
		"premake5.lua",
		"**.h",
		"**.cpp"
	}

	links {
		"DiligentGraphicsD3D11", "DiligentGraphicsD3DBase", "D3D11", "D3DCompiler"
	}

	filter "architecture:x64"
		flags { "ExcludeFromBuild" }

	filter "system:not windows"
		flags { "ExcludeFromBuild" }
