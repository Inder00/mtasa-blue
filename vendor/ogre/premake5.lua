project "ogre"
	targetname "ogre"
	language "C++"
	kind "StaticLib"

	defines { "OGRE_STATIC_LIB", "OGRE_NO_ZIP_ARCHIVE", "OGRE_NO_TBB_SCHEDULER" }
  --WIN32;_WINDOWS;OGRE_NONCLIENT_BUILD;FREEIMAGE_LIB;_MT;_USRDLL;CMAKE_INTDIR="Debug";OgreMain_EXPORTS;%(PreprocessorDefinitions)
	includedirs { ".",
		"include",
		"include/Animation",
		"include/CommandBuffer",
		"include/Compositor",
		"include/Compute",
		"include/Emscripten",
		"include/GLX",
		"include/gtk",
		"include/Hash",
		"include/Math/Array",
		"include/Math/Array/C",
		"include/Math/Array/NEON/Single",
		"include/Math/Array/SSE2/Single",
		"include/Math/Simple",
		"include/Math/Simple/C",
		"include/NaCI",
		"include/Threading",
		"include/Vao",
		"include/WIN32",
		"include/Android",
		"include/Deprecated",
  
		"src",
		"src/Animation",
		"src/CommandBuffer",
		"src/Compositor",
		"src/Compute",
		"src/Emscripten",
		"src/GLX",
		"src/gtk",
		"src/Hash",
		"src/Math/Array",
		"src/Math/Array/C",
		"src/Math/Array/NEON/Single",
		"src/Math/Array/SSE2/Single",
		"src/Math/Simple",
		"src/Math/Simple/C",
		"src/Threading",
		"src/Vao",
		"src/WIN32",
		"src/Android",
		"src/Android/JNI",
		"src/Deprecated",
	}
	
	warnings "Off";

	vpaths { 
		["Headers"] = "include/*.h",
		["Sources"] = "src/*.cpp",
		
		["Headers/Animation"] = "include/Animation/*.h",
		["Headers/CommandBuffer"] = "include/CommandBuffer/*.h",
		["Headers/Compositor"] = "include/Compositor/*.h",
		["Headers/Compute"] = "include/Compute/*.h",
		["Headers/Emscripten"] = "include/Emscripten/*.h",
		["Headers/GLX"] = "include/GLX/*.h",
		["Headers/gtk"] = "include/gtk/*.h",
		["Headers/Hash"] = "include/Hash/*.h",
		["Headers/Math/Array"] = "include/Math/Array/*.h",
		["Headers/Math/Array/C"] = "include/Math/Array/C/*.h",
		["Headers/Math/Array/NEON/Single"] = "include/Math/Array/NEON/Single/*.h",
		["Headers/Math/Array/SSE2/Single"] = "include/Math/Array/SSE2/Single/*.h",
		["Headers/Math/Simple"] = "include /Math/Simple/*.h",
		["Headers/Math/Simple/C"] = "include/Math/Simple/C/*.h",
		["Headers/NaCI"] = "include/NaCI/*.h",
		["Headers/Threading"] = "include/Threading/*.h",
		["Headers/Vao"] = "include/Vao/*.h",
		["Headers/WIN32"] = "include/WIN32/*.h",
		["Headers/Android"] = "include/Android/*.h",
		["Headers/Android/JNI"] = "include/Android/JNI/*.h",
		["Headers/Deprecated"] = "include/Deprecated*.h",

		["Sources/Animation"] = "src/Animation/*.cpp",
		["Sources/CommandBuffer"] = "src/CommandBuffer/*.cpp",
		["Sources/Compositor"] = "src/Compositor/*.cpp",
		["Sources/Compute"] = "src/Compute/*.cpp",
		["Sources/GLX"] = "src/GLX/*.cpp",
		["Sources/Hash"] = "src/Hash/*.cpp",
		["Sources/Math/Array"] = "src/Math/Array/*.cpp",
		["Sources/Math/Array/C"] = "src/Math/Array/C/*.cpp",
		["Sources/Math/Array/NEON/Single"] = "src/Math/Array/NEON/Single/*.cpp",
		["Sources/Math/Array/SSE2/Single"] = "src/Math/Array/SSE2/Single/*.cpp",
		["Sources/Math/Simple"] = "src/Math/Simple/*.cpp",
		["Sources/Math/Simple/C"] = "src/Math/Simple/C/*.cpp",
		["Sources/Threading"] = "src/Threading/*.cpp",
		["Sources/Vao"] = "src/Vao/*.cpp",
		["Sources/WIN32"] = "src/WIN32/*.cpp",
		["Sources/Android"] = "src/Android/*.cpp",
		["Sources/Deprecated"] = "src/Deprecated/*.cpp",
		["*"] = "premake5.lua"
	}
	
	files {
		"premake5.lua",
		"src/**.cpp",
		"src/**.h",
		"src/Threading/**.cpp",
		"include/**.h",
		"include/Threading/**.h",
	}

	pchheader "OgreStableHeaders.h"
	pchsource "src/stdafx.cpp"