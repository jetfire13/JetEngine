workspace "JetEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "JetEngine"
	location "JetEngine"
	kind "SharedLib"
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
		"JetEngine/vendor/spdlog/include"
	}
	
	filter "system:windows"		
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"JE_PLATFORM_WINDOWS",
			"JE_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
		}
		
	filter "configurations:Debug"
		defines "JE_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "JE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JE_DIST"
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
		symbols "On"
	
	filter "configurations:Release"
		defines "JE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JE_DIST"
		optimize "On"	