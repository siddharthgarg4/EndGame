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
    "${SRCROOT}",
    "${SRCROOT}/EndGame/vendor/spdlog/include",
    "${SRCROOT}/EndGame/vendor/glfw/include",
    "${SRCROOT}/EndGame/vendor/glad/include",
    "${SRCROOT}/EndGame/vendor/imgui/include"
  }

  filter "system:macosx"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "macOS 10.15"
    removefiles {"../../EndGame/vendor/**"}

    buildoptions {"-fvisibility=hidden", "-fvisibility-inlines-hidden"}

    defines {
      "EG_PLATFORM_OSX"
    }

    filter "configurations:Debug"
      defines "EG_ENGINE_DEBUG"
      runtime "Debug"
      optimize "on"

    filter "configurations:Release"
      defines "EG_ENGINE_RELEASE"
      runtime "Release"
      optimize "on"

    filter "configurations:Dist"
      defines "EG_ENGINE_DIST"
      runtime "Release"
      optimize "on"

project "Sandbox"
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
    "${SRCROOT}",
    "${SRCROOT}/EndGame/vendor/spdlog/include",
    "${SRCROOT}/EndGame/vendor/glfw/include",
    "${SRCROOT}/EndGame/vendor/glad/include",
    "${SRCROOT}/EndGame/vendor/imgui/include"
  }

  libdirs {
    "${SRCROOT}/EndGame/vendor/glfw/lib/",
    "${SRCROOT}/EndGame/vendor/glad/lib/",
    "${SRCROOT}/EndGame/vendor/imgui/lib/"
  }

  links {
    "EndGame",
    "OpenGL.framework",
    "glfw.3.3",
    "glad",
    "imgui"
  }

  filter "system:macosx"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "macOS 10.15"
    removefiles {"../../EndGame/vendor/**"}

  defines {
    "EG_PLATFORM_OSX"
  }

  filter "configurations:Debug"
    defines "EG_DEBUG"
    runtime "Debug"
    optimize "on"

  filter "configurations:Release"
    defines "EG_RELEASE"
    runtime "Release"
    optimize "on"

  filter "configurations:Dist"
    defines "EG_DIST"
    runtime "Release"
    optimize "on"
