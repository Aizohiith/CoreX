#pragma once

#include "../config.hpp"

#if INCLUDE_GLEW

#include <GL\glew.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <fstream>

class Shader
{
public:
	Shader();
	void Load_From_File(const char* VertexShader, const char* FragmentShader);// Load shaders
	void Compile(const char* VertexShader, const char* FragmentShader);//Compile Shader
	void Start();
	static void Stop();

	void Set_Attribute(GLuint ID, float Value) const;
	void Set_Attribute(GLuint ID, const glm::vec2& Value) const;
	void Set_Attribute(GLuint ID, const glm::vec3& Value) const;
	void Set_Attribute(GLuint ID, const glm::vec4& Value) const;
	void Set_Attribute(GLuint ID, const glm::mat4& Value) const;
	void Set_Attribute(GLuint ID, const GLuint TextreUnit) const;

	~Shader();

	GLuint Attribute_ID(const char* AttributeName) const;
	GLuint Program_ID() const;

private:
	GLuint gi_ID;

	std::string Load_File(const char* FileName);
	void Add(GLuint ProgramID, const char* ShaderCode, GLenum ShaderType);//Add Shader
};

#endif