-- Chess
workspace "OpenGL"
	architecture "x64"
	startproject "SandBox"

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
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["GLEW"] = "vendor/GLEW/include"
IncludeDir["glm"] =  "vendor/glm"
IncludeDir["stb_image"] = "vendor/stb_image"
IncludeDir["imgui"] = "vendor/imgui"
IncludeDir["spdlog"] = "vendor/spdlog/include"

-- Projects
group "Dependencies"
	include "OpenGL/vendor/GLFW"
	include "OpenGL/vendor/GLEW"
    include "OpenGL/vendor/imgui"
group ""

include "OpenGL"
include "SandBox"

newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("./bin")
		os.rmdir("./OpenGL/vendor/bin")
        print("Removing intermediate binaries")
        os.rmdir("./bin-int")
		os.rmdir("./OpenGL/vendor/bin-int")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}
