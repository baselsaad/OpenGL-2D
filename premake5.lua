-- Chess
workspace "OpenGL"
	architecture "x64"
	startproject "OpenGL"

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

-- Include directories relative to OpenGL-Core
IncludeDir = {}
IncludeDir["GLFW"] = "Dependencies/GLFW/include"
IncludeDir["GLEW"] = "Dependencies/GLEW/include"
IncludeDir["glm"] =  "Dependencies/glm"
IncludeDir["stb_image"] = "Dependencies/stb_image"
IncludeDir["imgui"] = "Dependencies/imgui"

-- Projects
group "Dependencies"
	include "OpenGL/Dependencies/GLFW"
	include "OpenGL/Dependencies/GLEW"
group ""

include "OpenGL"
