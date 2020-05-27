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
  kind "StaticLib"

  location "../../"

  targetdir ("../../bin/" .. outputdir .. "/EndGame" )
  objdir ("../../bin-int/" .. outputdir .. "/EndGame" )

  pchheader "EndGame/Src/EndGamePCH.hpp"
	pchsource "EndGame/Src/EndGamePCH.cpp"

  files {
    "../../EndGame/**.h",
    "../../EndGame/**.cpp",
    "../../EndGame/**.hpp",
    "../../EndGame/**.h"
  }

  sysincludedirs {
    "${SRCROOT}/EndGame/vendor/spdlog/include",
    "${SRCROOT}"
  }

  filter "system:macosx"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "macOS 10.15"
    removefiles {"../../EndGame/vendor/**"}

    defines {
      "EG_PLATFORM_OSX"
    }

    filter "configurations:Debug"
		  defines "EG_ENGINE_DEBUG"
		  optimize "On"

    filter "configurations:Release"
		  defines "EG_ENGINE_RELEASE"
		  optimize "On"

    filter "configurations:Dist"
		  defines "EG_ENGINE_DIST"
		  optimize "On"

project "Sandbox"
  location "EndGame"
  language "C++"
  kind "ConsoleApp"

  location "../../"

  targetdir ("../../bin/" .. outputdir .. "/EndGame" )
  objdir ("../../bin-int/" .. outputdir .. "/EndGame" )

  files {
    "../../Sandbox/**.hpp",
    "../../Sandbox/**.cpp"
  }

  sysincludedirs {
    "${SRCROOT}/EndGame/vendor/spdlog/include",
    "${SRCROOT}"
  }

  links {
    "EndGame"
  }

  filter "system:macosx"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "macOS 10.15"
    removefiles {"../../EndGame/vendor/**"}

  defines {
    "EG_PLATFORM_OSX"
  }

  filter "configurations:Debug"
    defines "EG_DEBUG"
    optimize "On"

  filter "configurations:Release"
    defines "EG_RELEASE"
    optimize "On"

  filter "configurations:Dist"
    defines "EG_DIST"
    optimize "On"
