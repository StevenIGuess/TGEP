workspace "TGEP"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "TGEP/submodules/glfw/include"
IncludeDir["glad"] = "TGEP/submodules/glad/include"
IncludeDir["ImGui"] = "TGEP/submodules/imgui/"
IncludeDir["glm"] = "TGEP/submodules/glm/"
IncludeDir["asio"] = "TGEP/submodules/asio/include/"
IncludeDir["stb_image"] = "TGEP/submodules/stb_image/"


include "TGEP/submodules/glfw"
include "TGEP/submodules/glad"
include "TGEP/submodules/imgui"

project "TGEP"
	location "TGEP"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/submodules/stb_image/**.cpp",
		"%{prj.name}/submodules/stb_image/**.h"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.asio}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"glfw3",
		"glad",
		"ImGui",
		"opengl32.lib"
	}
	

	filter{"system:windows"}
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"_ENGINE_LOG_MACROS_",
			"_WIN32_WINNT=0x0A00"
		}

	filter "configurations:Debug"
		defines "TGEP_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "TGEP_RELEASE"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"TGEP/src",
		"%{IncludeDir.asio}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"TGEP"
	}

	filter{"system:windows"}
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"_WIN32_WINNT=0x0A00"
		}

	filter "configurations:Debug"
		defines "TGEP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TGEP_RELEASE"
		optimize "On"