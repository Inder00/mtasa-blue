project "Client Directx11 Test"
	language "C++"
	kind "ConsoleApp"
	targetname "directx11test"
	targetdir ("../../bintests/Directx11")
	pchheader "StdInc.h"
	pchsource "StdInc.cpp"
	
	filter {}
		includedirs {
			"../../Shared/sdk",
		}

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
		"Client Directx11", "D3D11", "D3DCompiler", "DXGI"
	}

	filter "architecture:x64"
		flags { "ExcludeFromBuild" }

	filter "system:not windows"
		flags { "ExcludeFromBuild" }
