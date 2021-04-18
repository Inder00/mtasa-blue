project "ogre"
	targetname "ogre"
	language "C++"
	kind "StaticLib"
	
	links { "zlib" }
	defines { "WIN32", "_WINDOWS", "_MT", "_USRDLL", 'CMAKE_INTDIR="Debug"', "OGREMAIN_STATIC_DEFINE",
		"OGRE_NO_ZIP_ARCHIVE" -- Seems like it uses a bit different zlib version
	}

	vpaths {
		["Headers"] = {"include/*.h","include/threading/*.h"},
		["Sources"] = {"src/*.cpp","src/threading/*.cpp"},
		["*"] = "premake5.lua"
	}
	-- warnings: 4661;4251;4275
	--[[
		..\Dependencies\lib\zzip.lib
..\Dependencies\lib\zlib.lib
	]]
	pchheader "OgreStableHeaders.h"
	pchsource "StdInc.cpp"

	filter {}
		includedirs {
			"OgreMain/include/Threading",
			"OgreMain/src",
			"OgreMain/include",
			"Dependencies/include",
	}

	vpaths {
		["Headers"] = "**.h",
		["Sources"] = "**.cpp",
		["*"] = "premake5.lua"
	}

	files {
		"premake5.lua",
		"**.h",
		"**.cpp"
	}
