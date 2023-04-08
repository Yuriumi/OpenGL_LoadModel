#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "../ref/load/Model.h"

#include "../ref/camera/Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

const float screen_Width = 800.0f;
const float screen_Height = 600.0f;

Camera mainCamera(glm::vec3(0.0f, 0.0f, 3.0f));
bool cameraMove = false;
bool firstMouse = true;
float lastX = screen_Width / 2.0f;
float lastY = screen_Height / 2.0f;

float currentTime = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Init GLAD Failed" << std::endl;

		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, screen_Width, screen_Height);

	Shader modelShader("./shader/vModel.shader", "./shader/fModel.shader");
	Model humanModel("D:/LearnOpenGL/Model/nanosuit/nanosuit.obj");

	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	while (!glfwWindowShouldClose(window))
	{
		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		process_input(window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		modelShader.use();
		// view/projection矩阵
		projection = glm::perspective(glm::radians(mainCamera.fov), screen_Width / screen_Height, 0.1f, 100.0f);
		view = mainCamera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		// 渲染加载的3d模型
		glm::mat4 model = glm::mat4(1.0f);
		//使其位于场景的中心
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		//缩小它
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		humanModel.Draw(modelShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5f * deltaTime;
	if (cameraMove)
	{
		// Mouse Setting
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			mainCamera.processKeyBoard(Camera_Movement::FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			mainCamera.processKeyBoard(Camera_Movement::BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			mainCamera.processKeyBoard(Camera_Movement::LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			mainCamera.processKeyBoard(Camera_Movement::RIGHT, deltaTime);
	}
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (cameraMove)
		mainCamera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mainCamera.processMouseScroll(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
			cameraMove = true;
		else if (action == GLFW_RELEASE)
			cameraMove = false;
	}
}