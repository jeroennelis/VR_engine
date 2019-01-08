#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GL.h"
#include "glm\mat4x4.hpp"
#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
	std::string GeomitrySource;
};

class Shader
{
private:
	std::string m_Filepath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniforms

	void LoadUniform1i(const std::string& name, int i);
	void LoadUniform1f(const std::string& name, float f);
	void LoadUniform2f(const std::string& name, float v0, float v1);
	void LoadUniform3f(const std::string& name, float v0, float v1, float v2);
	void LoadUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void LoadUniformMatrix(const std::string& name, const glm::mat4 &matrix);
	void LoadBool(const std::string& name, bool value);
	void LoadUniformMatrixArray(const std::string& name, int size, const std::vector<glm::mat4> & matrices);
	//TODO for every uniform type

private:
	
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentshader, const std::string& GeometryShader);
	int GetUniformLocation(const std::string& name);
};

