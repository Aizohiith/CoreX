#pragma once

#include "../config.hpp"

#if INCLUDE_GLEW

#include <GL\glew.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <fstream>

namespace CoreX
{
	namespace GLEW
	{
		class Shader
		{
			public:
				Shader();
				void Load_From_File(const char* VertexShader, const char* FragmentShader);// Load shaders
				void Compile(const char* VertexShader, const char* FragmentShader);//Compile Shader
				void Start();
				static void Stop();


				template<typename T>
				void Set(const char* Name, const T& Value) { Set(Attribute_ID(Name), Value); };
				template<typename T>
				void Set(GLuint ID, const T& value) const;

				~Shader();

				GLuint Attribute_ID(const char* AttributeName) const;
				GLuint Program_ID() const;

			private:
				GLuint gi_ID;

				std::string Load_File(const char* FileName);
				void Add(GLuint ProgramID, const char* ShaderCode, GLenum ShaderType);//Add Shader
		};

		static const char* Basic_Vertex = R"(
		#version 330 core
		layout(location = 0) in vec3 aPos;

		out vec3 ourColor;

		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;

		void main()
		{
			gl_Position = projection * view * model * vec4(aPos, 1.0);
			ourColor = (aPos + 1.0) * 0.5;
		}

		)";

		static const char* Basic_Fragment = R"(
		#version 330 core
		in vec3 ourColor;
		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(ourColor, 1.0f);
		}

		)";

		static const char* Basic_Skydome_Vertex = R"(
		#version 330 core
		layout(location = 0) in vec3 aPos;

		out vec3 ourColor;

		uniform vec3 horizon_color = vec3(0.3, 0.4, 0.5);
		uniform vec3 peak_color = vec3(0.0, 0.2, 0.5);
		uniform mat4 view;
		uniform mat4 projection;

		void main()
		{
			gl_Position = projection * view * vec4(aPos, 1.0);
			float normalized_y = clamp(aPos.y + 0.5, 0.0, 1.0);
			ourColor =  horizon_color * (1.0 - normalized_y) + peak_color * normalized_y;
		}

		)";

		static const char* Basic_Skydome_Fragment = R"(
		#version 330 core
		in vec3 ourColor;
		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(ourColor, 1.0f);
		}

		)";
	}
}

#endif