project "V8"
	language "C++"
	--kind "SharedLib"
	kind "StaticLib"
	targetname "V8"
	--targetdir(buildpath("server/mods/deathmatch/V8"))
  
	vpaths {
    ["Headers/*"] = {"**.h", "../../../Shared/mods/deathmatch/**.h", "../../**.h"},
		["Sources/*"] = {"**.cpp", "../../../Shared/mods/deathmatch/**.cpp", "../../../Shared/**.cpp", "../../../vendor/**.cpp", "../../**.cpp"},
		["*"] = "premake5.lua"
	}

  defines { "BUILDING_V8_SHARED", "BUILDING_V8_PLATFORM_SHARED" }

	files {
		"premake5.lua",
		"Main.cpp",
		--"Main.cpp",
		"src/**.h",
		"include/**.h",
	}
  
	filter {}
		includedirs {
			".",
			"./src",
			"./include",
		}

    links {
      "lib/win32/v8.dll.lib",
      "lib/win32/v8_libbase.dll.lib",
      "lib/win32/v8_libplatform.dll.lib",

      --[[
      "lib/win32/icui18n.dll.lib",
      "lib/win32/libc++.dll.lib",
      "lib/win32/icuuc.dll.lib",
      "lib/win32/mksnapshot.lib",
      "lib/win32/torque.lib",
      "lib/win32/zlib.dll.lib",
      "lib/win32/bytecode_builtins_list_generator.lib",
      ]]
    }
