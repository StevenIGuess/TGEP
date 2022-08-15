workspace "TGEP"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "TGEP"
	location "TGEP"
	kind "StaticLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"TGEP/src"
	}

	filter{"system:windows"}
		cppdialect "C++latest"
		staticruntime "On"
		systemversion "latest"
		buildoptions "/MT"

		defines
		{
			_ENGINE_LOG_MACROS_
		}

	filter "configurations:Debug"
		defines "TGEP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TGEP_RELEASE"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"TGEP/src"
	}

	links
	{
		"TGEP"
	}

	filter{"system:windows"}
		cppdialect "C++latest"
		staticruntime "On"
		systemversion "latest"
		buildoptions "/MT"

		defines
		{

		}

	filter "configurations:Debug"
		defines "TGEP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TGEP_RELEASE"
		optimize "On"