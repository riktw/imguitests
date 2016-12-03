#include <iostream>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_internal.h"
#include "serial.h"


serial::Serial my_serial("/dev/ttyACM0", 115200, serial::Timeout::simpleTimeout(1000));

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %d, %s\n",error, description);
}

int main()
{
	using namespace std;
	
	glfwSetErrorCallback(error_callback);
	if(!glfwInit())
		return 1;
	GLFWwindow* window = glfwCreateWindow(768, 480, "ImGui example", NULL, NULL);
	glfwMakeContextCurrent(window);
	ImGui_ImplGlfw_Init(window, true);

	ImVec4 clear_color = ImColor(114, 144, 154);

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		ImGui_ImplGlfw_NewFrame();

		{
			static float f = 0.0f;
			ImGui::Text("Hello World");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
		}


		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(window);
	}

	ImGui_ImplGlfw_Shutdown();
	glfwTerminate();

	return 0;
}

