workspace "Rise"
	architecture "x64"
	startproject "Sandbox" 

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Rise/vendor/GLFW/include"

include "Rise/vendor/GLFW"

project "Rise"
	location "Rise"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "rspch.h"
	pchsource "Rise/src/rspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"RS_PLATFORM_WINDOWS",
			"RS_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "RS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RS_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Rise/vendor/spdlog/include",
		"Rise/src"
	}

	links
	{
		"Rise"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RS_DIST"
		optimize "On"
