#pragma once

#include "glad.h"
#include "GLFW/glfw3.h"
#include "Utils.h"

#include <string>
#include <vector>

class Gl {
public:
	Gl() = delete;

	static void checkGLErrors();

	class VBO {
		inline static const GLuint invalidId = 0;

		static void generate(GLsizei n, GLuint* arrays);
		static void bind(GLenum target, GLuint buffer);
		static void unbind(GLenum target);
		static bool isBind();
		static void buffData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);

	private:
		inline static GLuint id = invalidId;
		friend class Gl;
	};

	class VAO {
		inline static const GLuint invalidId = 0;

		static void generate(GLsizei n, GLuint* arrays);
		static void bind(GLuint array);
		static void unbind();
		static bool isBind();
		static void enableVertexAttribArray(GLuint index);
		static void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
			GLsizei stride, const void* pointer);
		static void disableVertexAttribArray(GLuint index);

	private:
		inline static GLuint id = invalidId;
		friend class Gl;
	};


	class Shader {
	public:
		inline static const GLuint invalidId = 0;

		enum class Type {
			VERTEX = GL_VERTEX_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER,
			GEOMETRY = GL_GEOMETRY_SHADER
		};

		[[nodiscard]] static GLuint createAndLoadFromFile(const std::filesystem::path& path, const Type type);
		[[nodiscard]] static GLuint create(const Type type);
		[[nodiscard]] static GLint getShaderiv(GLuint shader, GLenum pname);
		static void deleteShader(GLuint shader);
		static void compile(GLuint shader);
		static void loadSource(GLuint shader, const char* shaderSource);
	private:
		inline static GLuint id = invalidId;
		friend class Gl;
	};

	class Program {//TODO: Continue implementation
	public:
		inline static const GLuint invalidId = 0;

		[[nodiscard]] static GLuint create();
		static void attachShader(GLuint shaderProgram, GLuint shader);
		static void link(GLuint shaderProgram);
		static bool isAttached();
		static void deleteProgram(GLuint shaderProgram);
	private:
		inline static GLuint id = invalidId;
	};
private:
};

//class OpenGlApp {
//public:
//	OpenGlApp();
//	~OpenGlApp();
//
//	void draw();
//private:
//	bool init();
//	bool shadersSetup();
//	bool setupVertexShader(GLuint& vertexShader);
//	bool setupFragmentShader(GLuint& fragmentShader);
//	bool setupShaderProgram(GLuint& vertexShader, GLuint& fragmentShader);
//	void initVertexBuffer();
//	void removeShaders(GLuint& vertexShader, GLuint& fragmentShader);
//	void setupGLFWVersion();
//
//	void initializeShaderSources();
//	std::string checkShaderFailureStatus(GLuint shader, GLenum pname);
//	std::string checkProgramFailureStatus(GLuint program, GLenum pname);
//	bool createWindow();
//private:
//	const char* vertexShaderSource = nullptr;
//	const char* fragmentShaderSource = nullptr;
//	//std::string vertexShaderSource{};
//	//std::string fragmentShaderSource{};
//	GLFWwindow* window = nullptr;
//	GLuint shaderProgram = 0;
//	GLuint VBO = 0;
//	GLuint VAO = 0;
//
//};