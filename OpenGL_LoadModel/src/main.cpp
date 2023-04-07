#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const float screen_Width = 800.0f;
const float screen_Height = 600.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screen_Width, screen_Height, "Load_Model", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Window Created Failed" << std::endl;

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Init GLAD Failed" << std::endl;

		return -1;
	}

	glViewport(0, 0, screen_Width, screen_Height);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}