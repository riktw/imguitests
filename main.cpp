#include <iostream>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_internal.h"
#include "serial.h"
#include <string.h>


serial::Serial my_serial("/dev/ttyUSB0", 115200, serial::Timeout::simpleTimeout(1000));

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
	int r, g, b,rold,gold,bold;
	char rgbstring[12] = { 0 };

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		ImGui_ImplGlfw_NewFrame();

		{
			static float f = 0.0f;
			ImGui::Text("Hello World");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			rold = r;
			gold = g;
			bold = b;
			ImGui::ColorPicker3("clear color", (float*)&clear_color, ImGuiColorEditFlags_NoSliders);
			r = (clear_color.x*100);
			g = (clear_color.y*100);
			b = (clear_color.z*100);
			if(r >= 100)
				r = 99;
			if(g >= 100)
				g = 99;
			if(b >= 100)
				b = 99;
			sprintf(rgbstring, "RGB:%02i%02i%02i\n",r, g, b);
			if((r != rold) || (b != bold) || (g != gold))
			{
				my_serial.write(rgbstring);
			}
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

