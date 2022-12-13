project "OpenGL"
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
		"Dependencies/stb_image/**.h",
		"Dependencies/stb_image/**.cpp",
		"Dependencies/glm/**.hpp",
		"Dependencies/glm/**.inl",
		"Dependencies/imgui/*.h",
		"Dependencies/imgui/imgui_impl_glfw_gl3.cpp",
		"Dependencies/imgui/imgui_demo.cpp",
		"Dependencies/imgui/imgui_draw.cpp",
		"Dependencies/imgui/imgui.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
		"Dependencies/",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"GLEW",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLEW_STATIC"
		}

	filter "configurations:Debug"
	 -- defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
	 -- defines "RELEASE"
		runtime "Release"
		optimize "on"