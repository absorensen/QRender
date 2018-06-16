#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"
#include "Model.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void setLamps(Shader &shader, glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection, unsigned int &lightVAO);
void setBox(Shader &shader, const glm::vec3 cubePositions[], const unsigned int diffuseMap, const unsigned int specularMap, unsigned int &cubeVAO);
void setTransforms(Shader &shader, glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);
void setFlashLight(Shader &shader);
void setDirectionLight(Shader &shader);
void setPointLights(Shader &shader, const glm::vec3 pointLightPositions[], const glm::vec3 pointLightColors[]);
void initQuixote(GLFWwindow* window, int& error);
unsigned int loadTexture(char const * path);