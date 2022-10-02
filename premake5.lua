workspace "TGEP"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "TGEP/submodules/GLFW/include"
IncludeDir["Glad"] = "TGEP/submodules/Glad/include"
IncludeDir["ImGui"] = "TGEP/submodules/imgui"
IncludeDir["glm"] = "TGEP/submodules/glm"
IncludeDir["stb_image"] = "TGEP/submodules/stb_image"
IncludeDir["asio"] = "TGEP/submodules/asio/include"

group "Dependencies"
	include "TGEP/submodules/GLFW"
	include "TGEP/submodules/Glad"
	include "TGEP/submodules/imgui"

group ""

project "TGEP"
	location "TGEP"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/submodules/stb_image/**.h",
		"%{prj.name}/submodules/stb_image/**.cpp",
		"%{prj.name}/submodules/glm/glm/**.hpp",
		"%{prj.name}/submodules/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.asio}"
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
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "TGEP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TGEP_RELEASE"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
		"TGEP/src",
		"TGEPNetworking/src",
		"TGEP/submodules",
		"%{IncludeDir.glm}",
		"%{IncludeDir.asio}"
	}

	links
	{
		"TGEP"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "TGEP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TGEP_RELEASE"
		runtime "Release"
		optimize "on"