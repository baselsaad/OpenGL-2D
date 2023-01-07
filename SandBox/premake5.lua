project "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin/Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"res/shaders/*",
		"res/textures/*"
	}

	includedirs
	{
		"src/",
		"../OpenGL/src/",
		"../OpenGL/vendor",
		"../OpenGL/vendor/spdlog/include",
		"../OpenGL/%{IncludeDir.glm}",
		"../OpenGL/%{IncludeDir.GLEW}",
		"../OpenGL/%{IncludeDir.GLFW}"
	}

	links
	{
		"OpenGL"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		disablewarnings { "4244" }
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		disablewarnings { "4244" }
		defines "RELEASE"
		runtime "Release"
        optimize "on"
