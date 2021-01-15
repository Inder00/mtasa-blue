project "MtaV8"
	language "C++"
	kind "SharedLib"
	--kind "StaticLib"
	targetname "MtaV8"
	targetdir(buildpath("server/mods/deathmatch/V8"))
  
	vpaths {
		["Headers/*"] = {"**.h", "../../../Shared/mods/deathmatch/**.h", "../../**.h"},
		["Sources/*"] = {"**.cpp", "../../../Shared/mods/deathmatch/**.cpp", "../../../Shared/**.cpp", "../../../vendor/**.cpp", "../../**.cpp"},
		["*"] = "premake5.lua"
	}
	
    defines { "BUILDING_V8_SHARED", "USING_V8_PLATFORM_SHARED" }
  --defines { "USING_V8_SHARED", "USING_V8_PLATFORM_SHARED" }

	files {
		"premake5.lua",
		"**.cpp",
		"**.h",
	}
  
	filter {}
		includedirs {
			".",
			"./src",
			"./include",
			"../../vendor/V8/",
			"../../vendor/V8/include/",
		}

    links {
		"V8",
		"../../vendor/V8/lib/win32/v8.dll.lib",
		"../../vendor/V8/lib/win32/v8_libbase.dll.lib",
		"../../vendor/V8/lib/win32/v8_libplatform.dll.lib",

		--[[
		"../../vendor/V8/lib/win32/icui18n.dll.lib",
		"../../vendor/V8/lib/win32/icuuc.dll.lib",
		"../../vendor/V8/lib/win32/bytecode_builtins_list_generator.lib",
		"../../vendor/V8/lib/win32/libc++.dll.lib",
		"../../vendor/V8/lib/win32/mksnapshot.lib",
		"../../vendor/V8/lib/win32/torque.lib",
		"../../vendor/V8/lib/win32/zlib.dll.lib",
		]]
    }
