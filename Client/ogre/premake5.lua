project "MtaOgre"
	language "C++"
	kind "ConsoleApp"
	targetname "MtaOgre"
	targetdir(buildpath("mta"))

	defines { "OGRE_TEST", "DEBUG"}
	links { "RenderSystem_Direct3D11", "ogre", "OgreHlmsUnlit","OgreHlmsPbs", "dxgi.lib", "dxguid.lib" }

	vpaths {
		["Headers/*"] = {"**.h"},
		["Sources/*"] = {"**.cpp"},
		["*"] = "premake5.lua"
	}

	filter {}
		includedirs {
			".",
			"../../vendor/ogre/include",
			"../../vendor/OgreHlmsUnlit/include",
			"../../vendor/OgreHlmsPbs/include",
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
