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
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

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

  removefiles {"../../EndGame/vendor/**"}

  sysincludedirs {
    "${SRCROOT}",
    "${SRCROOT}/EndGame/vendor/",
    "${SRCROOT}/EndGame/vendor/glm",
    "${SRCROOT}/EndGame/vendor/spdlog/include",
    "${SRCROOT}/EndGame/vendor/glfw/include",
    "${SRCROOT}/EndGame/vendor/glad/include",
    "${SRCROOT}/EndGame/vendor/imgui/include"
  }

  filter "system:macosx"
    systemversion "macOS 10.15"

    buildoptions {"-fvisibility=hidden", "-fvisibility-inlines-hidden"}

    defines {
      "EG_PLATFORM_OSX",
      "GL_SILENCE_DEPRECATION",
      "GLFW_INCLUDE_NONE"
    }

    filter "configurations:Debug"
      defines "EG_ENGINE_DEBUG"
      runtime "Debug"
      symbols "on"

    filter "configurations:Release"
      defines "EG_ENGINE_RELEASE"
      runtime "Release"
      optimize "on"

    filter "configurations:Dist"
      defines "EG_ENGINE_DIST"
      runtime "Release"
      optimize "on"

project "Sandbox"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

  location "../../"

  targetdir ("../../bin/" .. outputdir .. "/EndGame" )
  objdir ("../../bin-int/" .. outputdir .. "/EndGame" )

  files {
    "../../Sandbox/**.hpp",
    "../../Sandbox/**.cpp"
  }

  sysincludedirs {
    "${SRCROOT}",
    "${SRCROOT}/EndGame/vendor/",
    "${SRCROOT}/EndGame/vendor/glm",
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
    "glfw3",
    "glad",
    "imgui",
    "OpenGL.framework",
    "Cocoa.framework",
    "IOKit.framework"
  }

  filter "system:macosx"
    systemversion "macOS 10.15"

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
