project "MtaOgre"
	language "C++"
	kind "SharedLib"
	targetname "MtaOgre"
	targetdir(buildpath("mta"))

	defines { "OGRE_TEST", "DEBUG",}
	links { "RenderSystem_Direct3D11", "ogre", "OgreHlmsUnlit","OgreHlmsPbs", "dxgi.lib", "dxguid.lib" }

	vpaths {
		["Headers"] = {"../../vendor/ogre/include/*.h","../../vendor/ogre/include/threading/*.h"},
		["Sources"] = {"../../vendor/ogre/src/*.cpp","../../vendor/ogre/src/threading/*.cpp",},
		["*"] = "premake5.lua"
	}
	
	pchheader "StdInc.h"
	pchsource "StdInc.cpp"


	filter {}
		includedirs {
			".",
			"../../vendor/ogre/include",
			"../../vendor/ogre/include/threading",
			"../../vendor/ogre/src",
			"../../vendor/OgreHlmsUnlit/include",
			"../../vendor/OgreHlmsPbs/include",
			"../../vendor/RenderSystem_Direct3D11/include",
	}

	files {
		"premake5.lua",
		"**.cpp",
		"**.h",
		"../../Client/mods/deathmatch/logic/ogre/**.h",
		"../../Client/mods/deathmatch/logic/ogre/**.cpp",
	}

	removeincludedirs {
		path.join(dxdir, "Include")
	}
