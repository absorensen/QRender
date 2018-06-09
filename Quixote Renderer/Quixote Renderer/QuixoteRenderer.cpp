// TODO: Do the last exercises in HelloTriangle


#include "QuixoteRenderer.h"

const char *vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos; \n"
"\n"
"void main()\n"
"{ \n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	// init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// try to create a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Quixote Renderer", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// get system info
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// set callback function for window resize
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// declare intent to bind vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// attach shader source code to shader object and compile
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// was compilation of vertex shader successful?
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// declare intent to create fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// bind and compile fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// was compilation of fragment shader successful?
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// create shader object
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// attach the shaders to the shader object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// clean up, these shaders have been used
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	float vertices[] = {
		0.5f,  0.5f, 0.0f,  
		0.5f, -0.5f, 0.0f,  
		-0.5f, -0.5f, 0.0f, 
		-0.5f,  0.5f, 0.0f   
	};
	unsigned int indices[] = {  
		0, 1, 3,   
		1, 2, 3    
	};

	// generate a Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// init vertex buffer objects
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//generate Element Buffer Object
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// bind Vertex Array Object
	glBindVertexArray(VAO);

	// bind the new vertex buffer object to the gl_array_buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// copy data to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// bind the new element buffer object to the gl_element_array_buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// copy indices to buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// tell OpenGL how to interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// for wireframe, comment in
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// while the window has not been closed
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// de-allocate resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// deallocate
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// set window to specified dimensions
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	// if escape was pressed, suggest closing the window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}