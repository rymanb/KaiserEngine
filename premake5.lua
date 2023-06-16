workspace "Kaiser"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Kaiser/vendor/glfw/include"
IncludeDir["Glad"] = "Kaiser/vendor/glad/include"
IncludeDir["ImGui"] = "Kaiser/vendor/imgui"
IncludeDir["glm"] = "Kaiser/vendor/glm"
IncludeDir["entt"] = "Kaiser/vendor/entt"

include "Kaiser/vendor/glfw"
include "Kaiser/vendor/glad"
include "Kaiser/vendor/imgui"


project "Kaiser"
	location "Kaiser"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"



	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "stdafx.h"
	pchsource "Kaiser/src/stdafx.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"

	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
		
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"

		systemversion "latest"

		defines
		{
			"KS_PLATFORM_WINDOWS",
			"KS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "KS_DEBUG"
		--buildoptions "/MDd"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "KS_RELEASE"
		--buildoptions "/MD"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "KS_DIST"
		--buildoptions "/MD"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Kaiser/vendor/spdlog/include",
		"Kaiser/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Kaiser"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"KS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		--buildoptions "/MDd"
		defines "KS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		--buildoptions "/MD"
		defines "KS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		--buildoptions "/MD"
		defines "KS_DIST"
		optimize "On"
		