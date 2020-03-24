project "Ogre test"
	language "C++"
	kind "ConsoleApp"
	targetname "client"
	targetdir(buildpath("mods/deathmatch"))

	defines { "LUA_USE_APICHECK", "SDK_WITH_BCRYPT" }
	links {
		"Lua_Client", "pcre", "json-c", "ws2_32", "portaudio", "zlib",
		"RenderSystem_Direct3D11", "ogre",
		"dxgi.lib",
		"dxguid.lib",
	}

	vpaths {
		["Headers/*"] = {"**.h"},
		["Sources/*"] = {"**.cpp"},
		["*"] = "premake5.lua"
	}

	filter {}
		includedirs {
			".",
			"../../vendor/assimp/include",
			"../../vendor/ogre/include",
			"../../vendor/RenderSystem_Direct3D11/include",
	}

	files {
		"premake5.lua",
		"**.h",
		"**.cpp",
	}