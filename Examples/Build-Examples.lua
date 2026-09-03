-- Every example is a standalone executable, built from its own directory plus the shared
-- code in Common, which is always included. To add an example, create a directory next to
-- Common and list its name here.
local examples =
{
   "HelloTriangle"
}

group "Examples"

for _, example_name in ipairs(examples) do

project (example_name)
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++23"
   staticruntime "off"

   files
   {
      example_name .. "/**.h",
      example_name .. "/**.cpp",
      example_name .. "/**.slang",

      -- Shared by every example
      "Common/**.h",
      "Common/**.cpp",
      "Shaders/**.slang"
   }

   includedirs
   {
      example_name,
      "Common",

	  -- Include Ping
	  "../Ping/Source",
       "../Vendor/Sources/glfw-3.4.bin.WIN64/include",
       vulkan_sdk_path .. "/Include",
       "../" .. imgui_dir,
       "../" .. glm_dir,
       "../" .. glm_dir .. "/glm"
   }

   libdirs {vulkan_sdk_path .. "/Lib"}
   libdirs {"../" .. glfw_dir .. "/lib-vc2022"}

   links
   {
      "Ping",
      "vulkan",
      "glfw3",
      "imgui"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"

   filter {}

end

group ""
