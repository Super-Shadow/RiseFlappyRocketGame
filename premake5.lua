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
IncludeDir["Glad"] = "Rise/vendor/Glad/include"
IncludeDir["ImGui"] = "Rise/vendor/imgui"
IncludeDir["glm"] = "Rise/vendor/glm"

group "Dependencies"
	include "Rise/vendor/GLFW"
	include "Rise/vendor/Glad"
	include "Rise/vendor/imgui"

group ""

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"RS_PLATFORM_WINDOWS",
			"RS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "RS_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RS_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "RS_DIST"
		runtime "Release"
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
		"Rise/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Rise"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"RS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RS_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RS_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "RS_DIST"
		runtime "Release"
		optimize "On"
