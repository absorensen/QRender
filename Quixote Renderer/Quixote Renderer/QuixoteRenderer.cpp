#include "QuixoteRenderer.h"

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
const float ASPECT_RATIO = ((float)SCR_WIDTH) / SCR_HEIGHT;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
double deltaTime = 0.0f;
double lastFrame = 0.0f;

// lights
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


float cubeVertices[] = {
	// positions         
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
};

float planeVertices[] = {
	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

	5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
	5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
	glm::vec3(1.7f,  0.2f,  0.6f),
	glm::vec3(1.3f, -1.3f, -2.0f),
	glm::vec3(-2.0f,  1.0f, -1.0f),
	glm::vec3(-0.8f,  1.5f, 0.8f)
};

glm::vec3 pointLightColors[] = {
	glm::vec3(1.0f,  0.2f,  0.1f),
	glm::vec3(0.3f, 1.0f, 0.2f),
	glm::vec3(0.9f,  0.9f, 0.9f),
	glm::vec3(0.2f,  0.3f, 1.0f)
};

float transparentVertices[] = {
	// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};

float points[] = {
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
	0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
};

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

std::vector<glm::vec3> windows
{
	glm::vec3(-1.5f, 0.0f, -0.48f),
	glm::vec3(1.5f, 0.0f, 0.51f),
	glm::vec3(0.0f, 0.0f, 0.7f),
	glm::vec3(-0.3f, 0.0f, -2.3f),
	glm::vec3(0.5f, 0.0f, -0.6f)
};

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
						 // positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};

std::vector<std::string> faces
{
	"Resources/CubeMaps/skybox/right.jpg",
	"Resources/CubeMaps/skybox/left.jpg",
	"Resources/CubeMaps/skybox/top.jpg",
	"Resources/CubeMaps/skybox/bottom.jpg",
	"Resources/CubeMaps/skybox/front.jpg",
	"Resources/CubeMaps/skybox/back.jpg"
};


int main()
{
	// init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // try to create a window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Quixote Renderer", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// get system info
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// depth testing
	glEnable(GL_DEPTH_TEST);

	//Shader lampShader("Lamp.vert", "Lamp.frag");
	/*Shader shader("StencilTesting.vert", "StencilTesting.frag");
	Shader shaderSingleColor("StencilTesting.vert", "shaderSingleColor.frag");*/
	//Shader shader("Cubemaps.vert", "Cubemaps.frag");
	//Shader skyboxShader("Skybox.vert", "Skybox.frag");
	//Shader shaderRed("UniformBufferObject.vert", "Red.frag");
	//Shader shaderGreen("UniformBufferObject.vert", "Green.frag");
	//Shader shaderBlue("UniformBufferObject.vert", "Blue.frag");
	//Shader shaderYellow("UniformBufferObject.vert", "Yellow.frag");

	Shader shader("VisualizeNormalsModel.vert", "VisualizeNormalsModel.frag");
	Shader normalShader("VisualizeNormals.vert", "VisualizeNormals.frag", "VisualizeNormals.geom");

	Model nanosuit("Resources/Models/nanosuit/nanosuit.obj");

	// generate a VAO and VBO, points
	//unsigned int VBO, VAO;
	//glGenBuffers(1, &VBO);
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);
	////// bind the new vertex buffer object to the gl_array_buffer
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	////// copy data to buffer
	//glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	////// position attribute
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));
	//glBindVertexArray(0);

	//// generate a Vertex Array Object
	//unsigned int cubeVAO, cubeVBO;
	//glGenVertexArrays(1, &cubeVAO);
	//glGenBuffers(1, &cubeVBO);
	//glBindVertexArray(cubeVAO);
	////// bind the new vertex buffer object to the gl_array_buffer
	//glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	////// copy data to buffer
	//glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);

	////// position attribute
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	//unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed.ID, "Matrices");
	//unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen.ID, "Matrices");
	//unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue.ID, "Matrices");
	//unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(shaderYellow.ID, "Matrices");

	//glUniformBlockBinding(shaderRed.ID, uniformBlockIndexRed, 0);
	//glUniformBlockBinding(shaderGreen.ID, uniformBlockIndexGreen, 0);
	//glUniformBlockBinding(shaderBlue.ID, uniformBlockIndexBlue, 0);
	//glUniformBlockBinding(shaderYellow.ID, uniformBlockIndexYellow, 0);

	//unsigned int uboMatrices;
	//glGenBuffers(1, &uboMatrices);
	//glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	//glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

	//glm::mat4 projection = glm::perspective(45.0f, ASPECT_RATIO, 0.1f, 100.0f);
	//glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	//glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);


	//unsigned int cubeTexture = loadTexture("Resources/Textures/container.jpg");
	//unsigned int cubemapTexture = loadCubemap(faces);

//	unsigned int transparentTexture = loadTexture("Resources/Textures/blending_transparent_window.png");
	////unsigned int emissionMap = loadTexture("Resources/Textures/matrix.jpg");


	//lightingShader.use();
	//lightingShader.setInt("material.diffuse", 0);
	//lightingShader.setInt("material.specular", 1);
	////lightingShader.setInt("material.emission", 2);

	//shader.use();
	//shader.setInt("skybox", 0);


	//skyboxShader.use();
	//skyboxShader.setInt("skybox", 0);

	//glm::mat4 model = glm::mat4(); 
	//glm::mat4 view = glm::mat4();
	//glm::mat4 projection = glm::mat4();
	// while the window has not been closed
	while (!glfwWindowShouldClose(window)) {
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// input
		processInput(window);

		// rendering commands here
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), ASPECT_RATIO, 1.0f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model;

		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		shader.setMat4("model", model);

		shader.setFloat("time", glfwGetTime());

		nanosuit.Draw(shader);

		normalShader.use();
		normalShader.setMat4("projection", projection);
		normalShader.setMat4("view", view);
		normalShader.setMat4("model", model);

		nanosuit.Draw(normalShader);

		//shader.use();
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_POINTS, 0, 4);

		//glm::mat4 view = camera.GetViewMatrix();
		//glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		//glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
		//glBindBuffer(GL_UNIFORM_BUFFER, 0);

		//// RED
		//glBindVertexArray(cubeVAO);
		//shaderRed.use();
		//glm::mat4 model;
		//model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f));
		//shaderRed.setMat4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//// GREEN
		//glBindVertexArray(cubeVAO);
		//shaderGreen.use();
		//model = glm::mat4();
		//model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f));
		//shaderGreen.setMat4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//// YELLOW
		//glBindVertexArray(cubeVAO);
		//shaderYellow.use();
		//model = glm::mat4();
		//model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f));
		//shaderYellow.setMat4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//// BLUE
		//glBindVertexArray(cubeVAO);
		//shaderBlue.use();
		//model = glm::mat4();
		//model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f));
		//shaderBlue.setMat4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//shader.use();
		//model = glm::mat4();
		//view = camera.GetViewMatrix();
		//projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		//shader.setMat4("model", model);
		//shader.setMat4("view", view);
		//shader.setMat4("projection", projection);
		
		// cubes
		//glBindVertexArray(cubeVAO);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);

		//// draw skybox as last
		//glDepthFunc(GL_LEQUAL);
		//skyboxShader.use();
		//view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		//skyboxShader.setMat4("view", view);
		//skyboxShader.setMat4("projection", projection);

		////skybox cube
		//glBindVertexArray(skyboxVAO);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);
		//glDepthFunc(GL_LESS);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// de-allocate resources
	//glDeleteVertexArrays(1, &cubeVAO);
	////glDeleteVertexArrays(1, &skyboxVAO);
	//glDeleteBuffers(1, &cubeVBO);
	//glDeleteBuffers(1, &skyboxVBO);
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);

	// deallocate
	glfwTerminate();
	return 0;
}


void initQuixote(GLFWwindow* window, int& error) {
	
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		error = -1;
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// get system info
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		error = -1;
		return;
	}

	// depth testing
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	// blending
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// face culling
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

	// stencil
	//glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void setBox(Shader &shader, const glm::vec3 cubePositions[], const unsigned int diffuseMap, const unsigned int specularMap, unsigned int &cubeVAO) {
	shader.setFloat("material.shininess", 32.0f);

	// bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	// bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	glBindVertexArray(cubeVAO);

	for (unsigned int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		glm::mat3 invModel = (transpose(inverse(model)));
		shader.setMat4("model", model);
		shader.setMat3("invModel", invModel);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void setLamps(Shader &shader, glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection, unsigned int &lightVAO) {
	// also draw the lamp object(s)
	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	// we now draw as many light bulbs as we have point lights.
	glBindVertexArray(lightVAO);
	for (unsigned int i = 0; i < 4; i++)
	{
		model = glm::mat4();
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		shader.setMat4("model", model);
		shader.setVec3("color", pointLightColors[i]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	return;
}

void setTransforms(Shader &shader, glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection) {
	projection = glm::perspective(glm::radians(camera.Zoom), ASPECT_RATIO, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	//shader.setMat4("model", model);
	//shader.setVec3("viewPos", camera.Position);
	//glm::mat3 invModel = (transpose(inverse(model)));
	//shader.setMat3("invModel", invModel);
}


void setFlashLight(Shader &shader) {
	shader.setVec3("spotLight.position", camera.Position);
	shader.setVec3("spotLight.direction", camera.Front);
	shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
	shader.setFloat("spotLight.constant", 1.0f);
	shader.setFloat("spotLight.linear", 0.09f);
	shader.setFloat("spotLight.quadratic", 0.032f);
}

void setDirectionLight(Shader &shader) {
	shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
}

void setPointLights(Shader &shader, const glm::vec3 positions[], const glm::vec3 colors[] ) {
	for (GLuint i = 0; i < 4; ++i) {
		std::string number = std::to_string(i);
		shader.setVec3("pointLights[" + number + "].position", positions[i]);
		shader.setVec3("pointLights[" + number + "].ambient", colors[i].x * 0.1f, colors[i].y * 0.1f, colors[i].z * 0.1f);
		shader.setVec3("pointLights[" + number + "].diffuse", colors[i].x, colors[i].y, colors[i].z);
		shader.setVec3("pointLights[" + number + "].specular", 1.0f, 1.0f, 1.0f);
		shader.setFloat("pointLights[" + number + "].constant", 1.0f);
		shader.setFloat("pointLights[" + number + "].linear", 0.09f);
		shader.setFloat("pointLights[" + number + "].quadratic", 0.032f);
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	// set window to specified dimensions
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	// if escape was pressed, suggest closing the window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);

}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	
	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	} 
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
	
	return textureID;
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); ++i)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else 
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}