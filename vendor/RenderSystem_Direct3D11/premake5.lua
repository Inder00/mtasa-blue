project "RenderSystem_Direct3D11"
	targetname "RenderSystem_Direct3D11"
	language "C++"
	kind "StaticLib"

  links { "ogre", "d3d11" }
	defines { "OGRE_STATIC_LIB", "OGRE_NO_ZIP_ARCHIVE", "OGRE_NO_TBB_SCHEDULER" }

  includedirs { ".",
		"include",
		"include/Vao",
		"include/VendorExtensions",
		"include/Windowing",
		"include/Deprecated",

		"src",
		"src/Vao",
		"src/VendorExtensions",
		"src/Windowing",

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

	vpaths { 
		["Headers"] = "include/*.h",
		["Sources"] = "src/*.cpp",
		
		["Headers/Vao"] = "include/Vao/*.h",
		["Headers/VendorExtensions"] = "include/VendorExtensions/*.h",
		["Headers/Windowing"] = "include/Windowing/*.h",

		["Sources/Vao"] = "src/Vao/*.cpp",
		["Sources/VendorExtensions"] = "src/VendorExtensions/*.cpp",
		["Sources/Windowing"] = "src/Windowing/*.cpp",
		["*"] = "premake5.lua"
	}
	
	files {
		"premake5.lua",
		"src/**.cpp",
		"src/**.h",
		"include/**.h",
		"../ogre/include/Deprecated/*.h",
	}
	--removeincludes("C:/Program Files (x86)/Microsoft DirectX SDK (August 2009)/Include")
  -- remember to exclude directx9 from additional include directory ( C:\Program Files (x86)\Microsoft DirectX SDK (August 2009)\Include )