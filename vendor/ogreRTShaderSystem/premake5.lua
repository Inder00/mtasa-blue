project "OgreRTShaderSystem"
	targetname "OgreRTShaderSystem"
	language "C++"
	kind "StaticLib"

  links { "ogre" }
	defines { "OGRE_STATIC_LIB", "OGRE_NO_ZIP_ARCHIVE", "OGRE_NO_TBB_SCHEDULER" }

  includedirs { ".",
		"include",

		"src",

		"../ogre/include",
		"../ogre/include/Animation",
		"../ogre/include/CommandBuffer",
		"../ogre/include/Compositor",
		"../ogre/include/Compute",
		"../ogre/include/Emscripten",
		"../ogre/include/GLX",
		"../ogre/include/gtk",
		"../ogre/include/Hash",
		"../ogre/include/Math/Array",
		"../ogre/include/Math/Array/C",
		"../ogre/include/Math/Array/NEON/Single",
		"../ogre/include/Math/Array/SSE2/Single",
		"../ogre/include/Math/Simple",
		"../ogre/include/Math/Simple/C",
		"../ogre/include/NaCI",
		"../ogre/include/Threading",
		"../ogre/include/Vao",
		"../ogre/include/WIN32",
		"../ogre/include/Android",
		"../ogre/include/Deprecated",
	}

	removeincludedirs {
		path.join(dxdir, "Include")
	}

	vpaths { 
		["Headers"] = "include/*.h",
		["Sources"] = "src/*.cpp",
		
		["*"] = "premake5.lua"
	}
	
	files {
		"premake5.lua",
		"src/**.cpp",
		"src/*.cpp.inc",
		"include/*.inl",
		"include/**.h",
		"../ogre/include/Deprecated/*.h",
	}