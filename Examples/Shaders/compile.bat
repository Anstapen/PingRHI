C:/VulkanSDK/1.4.341.1/Bin/slangc.exe shader.slang -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name -entry vertMain -entry fragMain -o slang.spv
slangc.exe shader.slang -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name -entry vertMain -entry fragMain -source-embed-style u32 -source-embed-name g_shaderMain -o shader_embed.h
C:/VulkanSDK/1.4.341.1/Bin/slangc.exe imgui.slang -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name -entry vertMain -entry fragMain -o imgui.spv
C:/VulkanSDK/1.4.341.1/Bin/slangc.exe line.slang -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name -entry vertMain -entry fragMain -o line.spv
pause