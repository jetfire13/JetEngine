workspace "JetEngine"
	architecture "x64"
	startproject "SandBox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "JetEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "JetEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "JetEngine/vendor/imgui"
IncludeDir["glm"] = "JetEngine/vendor/glm/"

include "JetEngine/vendor/GLFW"
include "JetEngine/vendor/Glad"
include "JetEngine/vendor/imgui"



project "JetEngine"
	location "JetEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"IMGUI_API=__declspec(dllexport)"
	}
	
	pchheader "JEpch.h"
	pchsource "JetEngine/src/JEpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
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
		systemversion "latest"
		
		defines
		{
			"JE_PLATFORM_WINDOWS",
			"JE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines "JE_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "JE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JE_DIST"
		runtime "Release"
		optimize "on"	

project	"SandBox"
		location "SandBox"
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
		"JetEngine/vendor/spdlog/include",
		"JetEngine/src",
		"JetEngine/vendor",
		"JetEngine/vendor/glm/glm"
		
	}
	
	links
	{
		"JetEngine"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"JE_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "JE_DEBUG"	
		runtime "Debug"	
		symbols "on"
	
	filter "configurations:Release"
		defines "JE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JE_DIST"
		runtime "Release"
		optimize "on"	