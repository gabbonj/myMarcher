#include <window.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <string>


void framebuffer_size_callback(GLFWwindow* window, int _width, int height){
    glViewport(0, 0, _width, height);
}

Window::Window(unsigned int _height, unsigned int _width, std::string _name, Renderer& _renderer) :
    height(_height), width(_width), name(_name), renderer(_renderer) {}

void Window::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        renderer.camera.camera_position += renderer.camera.camera_forward * 0.1f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        renderer.camera.camera_position -= renderer.camera.camera_forward * 0.1f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        renderer.camera.camera_position -= glm::cross(renderer.camera.camera_forward, glm::vec3(0.0, 1.0, 0.0)) * 0.1f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        renderer.camera.camera_position += glm::cross(renderer.camera.camera_forward, glm::vec3(0.0, 1.0, 0.0)) * 0.1f;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        renderer.camera.camera_position += glm::vec3(0.0, 1.0, 0.0) * 0.1f;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
            renderer.camera.camera_position -= glm::vec3(0.0, 1.0, 0.0) * 0.1f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        renderer.camera.rotateCamera(renderer.camera.pitch, renderer.camera.yaw - 0.01f);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        renderer.camera.rotateCamera(renderer.camera.pitch, renderer.camera.yaw + 0.01f);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        renderer.camera.rotateCamera(renderer.camera.pitch + 0.01f, renderer.camera.yaw);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        renderer.camera.rotateCamera(renderer.camera.pitch - 0.01f, renderer.camera.yaw);
}

void Window::guiInit() {
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsClassic();
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void Window::guiPreUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::guiUpdate() {
    ImGui::Begin("myMarcher");
    ImGui::SetWindowSize(ImVec2(0, 0));
        if (ImGui::CollapsingHeader("Window")) {
            ImGui::Text("Width :");
            ImGui::SameLine();
            ImGui::Text(std::to_string(width).c_str());
            ImGui::Text("Height :");
            ImGui::SameLine();
            ImGui::Text(std::to_string(height).c_str());
            ImGui::Separator();
            ImGui::Text("Time :");
            ImGui::SameLine();
            ImGui::Text(std::to_string(time).c_str());
            ImGui::Text("FPS :");
            ImGui::SameLine();
            ImGui::Text(std::to_string(1.0 / delta_time).c_str());
        }
        if (ImGui::CollapsingHeader("Rederer")) {
            ImGui::DragFloat3("Camera position", &renderer.camera.camera_position[0], 0.1f);
            ImGui::Separator();
            ImGui::InputInt("Max steps", &renderer.max_steps);
            ImGui::InputFloat("Epsilon", &renderer.epsilon, renderer.epsilon*0.01f, 0.0f, "%g");
            ImGui::InputFloat("Far distance", &renderer.far_distance);
            ImGui::Separator();
            ImGui::InputFloat3("Attenuation constants", &renderer.attenuation[0], "%g");
            ImGui::SliderFloat("Shadow intensity", &renderer.shadow_intensity, 0.0f, 1.0f);
            ImGui::InputFloat("Shadow bias", &renderer.shadow_bias, renderer.shadow_bias*0.01f, 0.0f, "%g");
            ImGui::DragFloat("Shadow softness", &renderer.shadow_k, 0.1f);
            ImGui::DragFloat("Gamma", &renderer.gamma, 0.05f);
            ImGui::ColorEdit3("Background color", &renderer.background_color[0]);;
        }
    ImGui::End();

    ImGui::Begin("Scene");
        if (ImGui::CollapsingHeader("Lights")){
            if (ImGui::Button("Add"))
                renderer.scene.addLight(Light(glm::vec3(0.0), glm::vec3(1.0), 0.5f));
            ImGui::Separator();
            for (unsigned int i = 0; i < renderer.scene.scene_lights.size(); ++i) {
                ImGui::Text("Light");
                ImGui::SameLine();
                ImGui::Text(std::to_string(i).c_str());
                ImGui::PushID(i);
                ImGui::DragFloat3("Position", &renderer.scene.scene_lights.at(i).position[0], 0.1f);
                ImGui::SliderFloat3("Color", &renderer.scene.scene_lights.at(i).color[0], 0.0f, 1.0f);
                ImGui::SliderFloat("Brightness", &renderer.scene.scene_lights.at(i).brightness, 0.0f, 3.0f);
                if (ImGui::Button("Remove")) 
                    renderer.scene.removeLight(i);
                ImGui::SameLine();
                if (ImGui::Button("Duplicate")) 
                    renderer.scene.addLight(renderer.scene.scene_lights.at(i));
                ImGui::Separator();
            }
        }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::guiCleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Window::windowInit() {
    // glfw init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(height, width, name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // loading glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    renderer.initRender();
    resolution_loc = glGetUniformLocation(renderer.marcher.id, "resolution");
    renderer.inv_view_loc= glGetUniformLocation(renderer.marcher.id, "view_invers");
    renderer.inv_proj_loc = glGetUniformLocation(renderer.marcher.id, "camera_invers");
    renderer.camera.invers_proj = glm::inverse(glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f));
    guiInit();
}

bool Window::windowUpdate() {
    current_time = glfwGetTime();
    if (glfwWindowShouldClose(window)) return false;
    processInput();

    // updating the screenspace
    glfwGetWindowSize(window, &width, &height);
    glUniform2f(resolution_loc, float(width), float(height));
    renderer.camera.setCameraPosition(renderer.camera.camera_position);
    glUniformMatrix4fv(renderer.inv_view_loc, 1, GL_FALSE, &renderer.camera.invers_view[0][0]);
    glUniformMatrix4fv(renderer.inv_proj_loc, 1, GL_FALSE, &renderer.camera.invers_proj[0][0]);

    // rendering
    guiPreUpdate();
    renderer.preRender();
    renderer.render();
    guiUpdate();

    // preparing for the next frame
    glfwSwapBuffers(window);
    glfwPollEvents();
    delta_time = glfwGetTime() - current_time;
    time += delta_time;
    return true;   
}

void Window::windowCleanup() {
    glfwTerminate();
    renderer.cleanupRender();
    guiCleanup();
}
