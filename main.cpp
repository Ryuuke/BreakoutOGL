#include "Game.h"
#include <GLFW/glfw3.h>


constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode);

Game breakoutOgl(SCREEN_WIDTH, SCREEN_HEIGHT);

int main()
{
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	auto window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BreakoutOGL", nullptr, nullptr);
	
	if (window == nullptr)
		return -1;
	
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallback);

	glewExperimental = true;
	glewInit();
	glGetError();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	breakoutOgl.Init();
	breakoutOgl.m_state = Game::GAME_ACTIVE;

	float deltaTime = 0.f;
	float previousDelta = 0.f;

	while (!glfwWindowShouldClose(window))
	{
		deltaTime = (float)glfwGetTime() - previousDelta;
		previousDelta = glfwGetTime();

		glfwPollEvents();

		breakoutOgl.ProcessInput(deltaTime);
		breakoutOgl.Update(deltaTime);

		glClearColor(.2f, .3f, .4, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		breakoutOgl.Render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

void keyCallback(GLFWwindow * window, int key, int scanCode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
			breakoutOgl.m_keys[key] = true;
		else if (action == GLFW_RELEASE)
			breakoutOgl.m_keys[key] = false;
	}
}
