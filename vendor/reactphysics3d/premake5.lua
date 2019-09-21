project "reactphysics3d"
	language "C++"
	kind "StaticLib"
	targetname "reactPhysics3D"

	defines { "_LIB" }

	vpaths {
		["*"] = "premake5.lua",
		["Sources"] = "**.cpp",
		["Headers"] = "**.h",
	}

	includedirs {
		"vendor/reactphysics3d",
	}

	files {
		"**.cpp",
		"**.h",
	}

