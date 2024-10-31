#include "corex/config.hpp"

#if INCLUDE_GLEW
#include "corex/glew/shader.h"

namespace CoreX
{
	namespace GLEW
	{

		Shader::Shader()
		{
			gi_ID = 0;
		}

		void Shader::Load_From_File(const char* ps_VertexShader, const char* ps_FragmentShader)
		{
			std::string ls_VertexString = Load_File(ps_VertexShader);//Load Vertex Shader
			std::string ls_FragmentString = Load_File(ps_FragmentShader);//Load Fragment Shader

			Compile(ls_VertexString.c_str(), ls_FragmentString.c_str());//Compile Shader
		}

		void Shader::Start()
		{
			glUseProgram(gi_ID);//Use Shader Program
		}

		void Shader::Stop()
		{
			glUseProgram(0);
		}

		Shader::~Shader()
		{
			if (gi_ID != 0)
				glDeleteProgram(gi_ID);
		}

		GLuint Shader::Attribute_ID(const char* ps_AttributeName) const
		{
			return glGetUniformLocation(gi_ID, ps_AttributeName);
		}

		GLuint Shader::Program_ID() const
		{
			return gi_ID;
		}

		std::string Shader::Load_File(const char* ps_FileLocation)
		{
			std::string ls_Result;
			std::ifstream pp_FileStream(ps_FileLocation, std::ios::in);

			if (!pp_FileStream.is_open()) {
				std::cerr << "LoadFile FAILED: " << ps_FileLocation << " Does Not Exist" << std::endl;
				return "";
			}

			std::string ls_Line = "";
			while (!pp_FileStream.eof())
			{
				std::getline(pp_FileStream, ls_Line);
				ls_Result.append(ls_Line + "\n");
			}

			pp_FileStream.close();
			return ls_Result;
		}

		void Shader::Compile(const char* ps_VertexShader, const char* ps_FragmentShader)
		{
			//Create Shader Program
			gi_ID = glCreateProgram();

			if (!gi_ID)
			{
				std::cerr << "Failed to create shader" << std::endl;
				return;
			}
			//
			//Add Shader
			Add(gi_ID, ps_VertexShader, GL_VERTEX_SHADER);
			Add(gi_ID, ps_FragmentShader, GL_FRAGMENT_SHADER);
			//
			//Link Shader Program
			GLint result = 0;
			GLchar eLog[1024] = { 0 };

			glLinkProgram(gi_ID);
			glGetProgramiv(gi_ID, GL_LINK_STATUS, &result);

			if (!result)
			{
				glGetProgramInfoLog(gi_ID, sizeof(eLog), NULL, eLog);
				std::cerr << "Error linking program: " << eLog << std::endl;
				return;
			}
			//
			//Validate Shader Program
			glValidateProgram(gi_ID);
			glGetProgramiv(gi_ID, GL_VALIDATE_STATUS, &result);
			if (!result)
			{
				glGetProgramInfoLog(gi_ID, sizeof(eLog), NULL, eLog);
				std::cerr << "Error validating program: " << eLog << std::endl;
				return;
			}
			//
		}

		void Shader::Add(GLuint pi_ProgramID, const char* ps_ShaderCode, GLenum pp_ShaderType)
		{
			GLuint gi_ID = glCreateShader(pp_ShaderType);//Create Shader
			//Set Shader Code
			const GLchar* ls_ShaderCode[1] = { ps_ShaderCode };
			GLint li_CodeLength[1] = { static_cast<GLint>(strlen(ps_ShaderCode)) };
			glShaderSource(gi_ID, 1, ls_ShaderCode, li_CodeLength);
			//
			//Compile Shader
			glCompileShader(gi_ID);

			GLint result = 0;
			GLchar eLog[1024] = { 0 };

			glGetShaderiv(gi_ID, GL_COMPILE_STATUS, &result);
			if (!result)
			{
				glGetShaderInfoLog(gi_ID, 1024, NULL, eLog);
				std::cerr << "Error compiling the shader of type: " << pp_ShaderType << " With message: " << eLog << std::endl;
				return;
			}
			//

			glAttachShader(pi_ProgramID, gi_ID);//Attach Shader
		}

		// Specialization for float
		template<>
		void Shader::Set<float>(GLuint pi_ID, const float& pf_Value) const {
			glUniform1f(pi_ID, pf_Value);
		}

		// Specialization for glm::vec2
		template<>
		void Shader::Set<glm::vec2>(GLuint pi_ID, const glm::vec2& pv_Value) const {
			glUniform2f(pi_ID, pv_Value.x, pv_Value.y);
		}

		// Specialization for glm::vec3
		template<>
		void Shader::Set<glm::vec3>(GLuint pi_ID, const glm::vec3& pv_Value) const {
			glUniform3f(pi_ID, pv_Value.x, pv_Value.y, pv_Value.z);
		}

		// Specialization for glm::vec4
		template<>
		void Shader::Set<glm::vec4>(GLuint pi_ID, const glm::vec4& pv_Value) const {
			glUniform4f(pi_ID, pv_Value.x, pv_Value.y, pv_Value.z, pv_Value.w);
		}

		// Specialization for glm::mat4
		template<>
		void Shader::Set<glm::mat4>(GLuint pi_ID, const glm::mat4& pm_Value) const {
			glUniformMatrix4fv(pi_ID, 1, GL_FALSE, glm::value_ptr(pm_Value));
		}

		// Specialization for GLuint (texture unit)
		template<>
		void Shader::Set<GLuint>(GLuint pi_ID, const GLuint& pi_TextureUnit) const {
			glUniform1i(pi_ID, pi_TextureUnit);
		}

	}
}

#endif