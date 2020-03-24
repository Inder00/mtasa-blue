project "Ogre test"
	language "C++"
	kind "ConsoleApp"
	targetname "OgreTest"
	targetdir(buildpath("ogretest"))

	defines { "OGRE_TEST" }
	links { "RenderSystem_Direct3D11", "ogre", "dxgi.lib", "dxguid.lib" }

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
			"../../Client/mods/deathmatch/logic/ogre"
	}

	files {
		"premake5.lua",
		"**.h",
		"**.cpp",
		"../../Client/mods/deathmatch/logic/ogre/**.h",
		"../../Client/mods/deathmatch/logic/ogre/**.cpp",
	}

	removeincludedirs {
		path.join(dxdir, "Include")
	}