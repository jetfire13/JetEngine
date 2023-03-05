workspace "JetEngine"
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
IncludeDir["GLFW"] = "JetEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "JetEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "JetEngine/vendor/imgui"

include "JetEngine/vendor/GLFW"
include "JetEngine/vendor/Glad"
include "JetEngine/vendor/imgui"

project "JetEngine"
	location "JetEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "JEpch.h"
	pchsource "JetEngine/src/JEpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	
	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"		
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"JE_PLATFORM_WINDOWS",
			"JE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
		}
		
	filter "configurations:Debug"
		defines "JE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "JE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "JE_DIST"
		buildoptions "/MD"
		optimize "On"	

project	"SandBox"
		location "SandBox"
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
		"JetEngine/vendor/spdlog/include",
		"JetEngine/src"
	}
	
	links
	{
		"JetEngine"
	}
	
	filter "system:windows"		
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"JE_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "JE_DEBUG"	
		buildoptions "/MDd"		
		symbols "On"
	
	filter "configurations:Release"
		defines "JE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "JE_DIST"
		buildoptions "/MD"
		optimize "On"	