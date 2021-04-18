project "Ogre test"
	language "C++"
	kind "ConsoleApp"
	targetname "OgreTest"
	targetdir(buildpath("ogretest"))

	links { }
	
	pchheader "StdInc.h"
	pchsource "StdInc.cpp"

	vpaths {
		["Headers/*"] = {"**.h"},
		["Sources/*"] = {"**.cpp"},
		["*"] = "premake5.lua"
	}

	filter {}
		includedirs {
			".",
			"../../Client/ogre/headers"
	}

	files {
		"premake5.lua",
		"**.h",
		"**.cpp",
	}

	removeincludedirs {
		path.join(dxdir, "Include")
	}