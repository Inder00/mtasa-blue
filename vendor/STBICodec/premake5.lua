project "STBICodec"
	targetname "STBICodec"
	language "C++"
	kind "StaticLib"
	
	defines { "WIN32", "_WINDOWS", "_MT", "_USRDLL", 'CMAKE_INTDIR="Debug"', "OGREMAIN_STATIC_DEFINE", "CODEC_STBI_STATIC_DEFINE", "OGRE_STATIC_LIB",
		"OGRE_NO_ZIP_ARCHIVE" -- Seems like it uses a bit different zlib version
	}

	vpaths {
		["Headers"] = {"include/**.h"},
		["Sources"] = {"src/**.cpp"},
		["*"] = "premake5.lua"
	}

	filter {}
		includedirs {
			"include",
			"src",
			"../ogre/OgreMain/include",
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
