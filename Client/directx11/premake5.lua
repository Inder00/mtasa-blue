project "Client Directx11"
	language "C++"
	kind "SharedLib"
	targetname "directx11"
	targetdir(buildpath("mta"))

    DEGFX_Bind()

	-- TODO remove unnecessary
	filter {}
		includedirs {
			"../../Shared/sdk",
			".",
			"../sdk",
			"../../vendor/tinygettext",
			"../../vendor/zlib",
			"../../vendor/jpeg-9d",
			"../../vendor/pthreads/include",
			"../../vendor/sparsehash/src/",
			"../../vendor/detours/4.0.1/src",
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
		"DiligentGraphicsD3D11", "DiligentGraphicsD3DBase", "D3D11", "D3DCompiler", "DXGI"
	}

	filter "architecture:x64"
		flags { "ExcludeFromBuild" }

	filter "system:not windows"
		flags { "ExcludeFromBuild" }
