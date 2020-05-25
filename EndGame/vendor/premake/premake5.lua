workspace "EndGame"
  architecture "x64"

  location "../../"

  configurations {
    "Debug",
    "Release",
    "Dist"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "EndGame"
  location "EndGame"
  language "C++"
  kind "ConsoleApp"

  location "../../"

  targetdir ("../../bin/" .. outputdir .. "/EndGame" )
  objdir ("../../bin-int/" .. outputdir .. "/EndGame" )

  files {
    "../../EndGame/**.h",
    "../../EndGame/**.cpp",
    "../../EndGame/**.hpp",
    "../../Sandbox/**.hpp",
    "../../Sandbox/**.cpp"
  }

  sysincludedirs {
    "${SRCROOT}/EndGame/vendor/spdlog/include"
  }

  filter "system:macosx"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "macOS 10.15"
    removefiles {"../../EndGame/vendor/**"}

    defines {
      "EG_PLATFORM_OSX"
    }
