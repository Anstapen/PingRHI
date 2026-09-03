glfw_dir = "Vendor/Sources/glfw-3.4.bin.WIN64"
imgui_commit = "6029ee3789a2b7898f6423ec0c88cc4e5425f5a9" -- imgui docking branch, pinned for docking support
imgui_dir = "Vendor/Sources/imgui-" .. imgui_commit
glm_version = "1.0.1"
glm_dir = "Vendor/Sources/glm-" .. glm_version

function check_glfw()
    print("Checking for glfw...")
    os.chdir("Vendor")
    if(os.isdir("Sources") == false) then
        os.mkdir("Sources")
    end
    os.chdir("Sources")
    if(os.isdir("glfw-3.4.bin.WIN64") == false) then
        if(not os.isfile("glfw.zip")) then
            print("glfw not found, downloading from https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip")
            local result_str, response_code = http.download("https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip", "glfw.zip", {
                headers = { "From: Premake", "Referer: Premake" }
            })
        end
        print("Unzipping to " ..  os.getcwd())
        zip.extract("glfw.zip", os.getcwd())
        os.remove("glfw.zip")
    end
    os.chdir("../../")
end

function check_imgui()
    print("Checking for imgui...")
    os.chdir("Vendor")
    if(os.isdir("Sources") == false) then
        os.mkdir("Sources")
    end
    os.chdir("Sources")
    if(os.isdir("imgui-" .. imgui_commit) == false) then
        if(not os.isfile("imgui.zip")) then
            print("imgui not found, downloading from https://github.com/ocornut/imgui/archive/" .. imgui_commit .. ".zip")
            local result_str, response_code = http.download("https://github.com/ocornut/imgui/archive/" .. imgui_commit .. ".zip", "imgui.zip", {
                headers = { "From: Premake", "Referer: Premake" }
            })
        end
        print("Unzipping to " ..  os.getcwd())
        zip.extract("imgui.zip", os.getcwd())
        os.remove("imgui.zip")
    end
    os.chdir("../../")
end

function check_glm()
    print("Checking for glm...")
    local glm_url = "https://github.com/g-truc/glm/releases/download/" .. glm_version .. "/glm-" .. glm_version .. "-light.zip"
    local target_dir = "glm-" .. glm_version
    os.chdir("Vendor")
    if(os.isdir("Sources") == false) then
        os.mkdir("Sources")
    end
    os.chdir("Sources")
    if(os.isdir(target_dir) == false) then
        if(not os.isfile("glm.zip")) then
            print("glm not found, downloading from " .. glm_url)
            local result_str, response_code = http.download(glm_url, "glm.zip", {
                headers = { "From: Premake", "Referer: Premake" }
            })
        end
        -- the light archive holds an unversioned glm/ folder, so it is extracted into a
        -- versioned directory to keep glm_dir in step with glm_version
        os.mkdir(target_dir)
        print("Unzipping to " ..  os.getcwd() .. "/" .. target_dir)
        zip.extract("glm.zip", os.getcwd() .. "/" .. target_dir)
        os.remove("glm.zip")
    end
    os.chdir("../../")
end

function build_externals()
     print("Checking external dependencies...")
     check_imgui()
     check_glm()
     filter "system:windows"
        check_glfw()
end

build_externals()
