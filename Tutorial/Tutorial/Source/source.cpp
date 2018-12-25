#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "LoadShaders.h"

#include <iostream>
#include <string>

GLFWwindow* window = nullptr;
int main()
{
	try
	{
		if (!glfwInit())
		{
			std::cout << "failed to initialize GLFW\n";
			throw int(1);
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(1024, 768, "Learning_OpenGL", nullptr, nullptr);
		if (nullptr == window)
		{
			std::cout << "failed to initialize window\n";
			throw int(1);
		}

		glfwMakeContextCurrent(window);

		glewExperimental = true;
		if (GLEW_OK != glewInit())
		{
			std::cout << "failed to initialize glew\n";
			throw int(1);
		}

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		glClearColor(0.0f, 0.4f, 0.4f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		//gen vertex array
		GLuint vertex_id;
		glGenVertexArrays(1, &vertex_id);
		glBindVertexArray(vertex_id);

		GLfloat vertices[6] = { -0.90f, -0.90f, 0.85f, -0.90f, -0.90f,  0.85f };
		GLuint buffer_id;
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		ShaderInfo  shaders[] =
		{
			{ GL_VERTEX_SHADER, "source/triangles.vert" },
			{ GL_FRAGMENT_SHADER, "source/triangles.frag" },
			{ GL_NONE, NULL }
		};

		GLuint program = LoadShaders(shaders);
		glUseProgram(program);

		glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);
		glEnableVertexAttribArray(0);

		do {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBindVertexArray(vertex_id);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window);
			glfwPollEvents();
		} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			0 == glfwWindowShouldClose(window));
	}
	catch (...)
	{

	}

	glfwTerminate();

	return 0;
}