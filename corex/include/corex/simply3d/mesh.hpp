#pragma once

#include "../config.hpp"

#if INCLUDE_GLEW == 1
#include <GL/glew.h>
#include <vector>

namespace CoreX
{
	namespace Simply3D
	{
		class Mesh
		{
			public:
				Mesh() : gi_VAO(0), gi_VBO(0), gi_EBO(0) {};
				~Mesh();
				void Set_Data(const std::vector<float>& Vertices, const std::vector<unsigned int>& Indices);
				void Render() const;

			private:
				GLuint gi_VAO;
				GLuint gi_VBO;
				GLuint gi_EBO;
				std::vector<float> garr_Vertices;
				std::vector<unsigned int> garr_Indices;
		};

		Mesh::~Mesh()
		{
			// Clean up OpenGL resources
			if (gi_EBO)
				glDeleteBuffers(1, &gi_EBO);
			if (gi_VBO)
				glDeleteBuffers(1, &gi_VBO);
			if (gi_VAO)
				glDeleteVertexArrays(1, &gi_VAO);
		}

		void Mesh::Set_Data(const std::vector<float>& Vertices, const std::vector<unsigned int>& Indices)
		{
			if (not gi_VAO)
				glGenVertexArrays(1, &gi_VAO);
			garr_Vertices = Vertices;
			garr_Indices = Indices;

			glBindVertexArray(gi_VAO);

			// Generate and bind the VBO
			glGenBuffers(1, &gi_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, gi_VBO);
			glBufferData(GL_ARRAY_BUFFER, garr_Vertices.size() * sizeof(float), &garr_Vertices[0], GL_STATIC_DRAW);

			// Generate and bind the EBO
			glGenBuffers(1, &gi_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gi_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, garr_Indices.size() * sizeof(unsigned int), &garr_Indices[0], GL_STATIC_DRAW);

			// Assume the vertex data layout is: position (3 floats) and color (3 floats)
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			//glEnableVertexAttribArray(1);

			// Unbind the VAO
			glBindVertexArray(0);
		}

		void Mesh::Render() const
		{
			glBindVertexArray(gi_VAO);
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(garr_Indices.size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
}

#endif