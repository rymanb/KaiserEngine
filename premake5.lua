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
IncludeDir["stb_image"] = "Kaiser/vendor/stb_image"
IncludeDir["assimp"] = "Kaiser/vendor/assimp/include"

include "Kaiser/vendor/glfw"
include "Kaiser/vendor/glad"
include "Kaiser/vendor/imgui"


project "Kaiser"
	location "Kaiser"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	buildoptions "/MP"




	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "stdafx.h"
	pchsource "Kaiser/src/stdafx.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",

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
		"%{IncludeDir.entt}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}"
		
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

		
		links
		{
			"Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mtd.lib"
		}

		postbuildcommands 
		{
			'{COPY} "../Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mtd.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Release"
		defines "KS_RELEASE"
		--buildoptions "/MD"
		runtime "Release"
		optimize "On"

		links
		{
			"Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mt.lib"
		}

		postbuildcommands 
		{
			'{COPY} "../Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mtd.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Dist"
		defines "KS_DIST"
		--buildoptions "/MD"
		runtime "Release"
		optimize "On"

		links
		{
			"Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mt.lib"
		}

		postbuildcommands 
		{
			'{COPY} "../Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mtd.dll" "%{cfg.targetdir}"'
		}

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
		"%{IncludeDir.entt}",
		"%{IncludeDir.assimp}"
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

		links
		{
			"Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mtd.lib"
		}

		postbuildcommands 
		{
			'{COPY} "../Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mtd.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Release"
		runtime "Release"
		--buildoptions "/MD"
		defines "KS_RELEASE"
		optimize "On"
		
		links
		{
			"Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mt.lib"
		}

		postbuildcommands 
		{
			'{COPY} "../Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mtd.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Dist"
		runtime "Release"
		--buildoptions "/MD"
		defines "KS_DIST"
		optimize "On"
		
		links
		{
			"Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mt.lib"
		}

		postbuildcommands 
		{
			'{COPY} "../Kaiser/vendor/assimp/bin/Debug/assimp-vc143-mtd.dll" "%{cfg.targetdir}"'
		}
		