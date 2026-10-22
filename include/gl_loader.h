#pragma once

#include <GLFW/glfw3.h>

// Simple OpenGL function loader using glfwGetProcAddress
// This replaces glad with a minimal native approach

namespace gl {

// Function pointer types
using PFNGLCLEARPROC = void(*)(GLbitfield);
using PFNGLCLEARCOLORPROC = void(*)(GLfloat, GLfloat, GLfloat, GLfloat);
using PFNGLENABLEPROC = void(*)(GLenum);
using PFNGLDISABLEPROC = void(*)(GLenum);
using PFNGLVIEWPORTPROC = void(*)(GLint, GLint, GLsizei, GLsizei);
using PFNGLGENVERTEXARRAYSPROC = void(*)(GLsizei, GLuint*);
using PFNGLBINDVERTEXARRAYPROC = void(*)(GLuint);
using PFNGLDELETEVERTEXARRAYSPROC = void(*)(GLsizei, const GLuint*);
using PFNGLGENBUFFERSPROC = void(*)(GLsizei, GLuint*);
using PFNGLBINDBUFFERPROC = void(*)(GLenum, GLuint);
using PFNGLBUFFERDATAPROC = void(*)(GLenum, GLsizeiptr, const void*, GLenum);
using PFNGLDELETEBUFFERSPROC = void(*)(GLsizei, const GLuint*);
using PFNGLVERTEXATTRIBPOINTERPROC = void(*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
using PFNGLENABLEVERTEXATTRIBARRAYPROC = void(*)(GLuint);
using PFNGLDRAWARRAYSPROC = void(*)(GLenum, GLint, GLsizei);
using PFNGLDRAWELEMENTSPROC = void(*)(GLenum, GLsizei, GLenum, const void*);
using PFNGLCULLFACEPROC = void(*)(GLenum);
using PFNGLFRONTFACEPROC = void(*)(GLenum);
using PFNGLCREATESHADERPROC = GLuint(*)(GLenum);
using PFNGLSHADERSOURCEPROC = void(*)(GLuint, GLsizei, const GLchar**, const GLint*);
using PFNGLCOMPILESHADERPROC = void(*)(GLuint);
using PFNGLCREATEPROGRAMPROC = GLuint(*)(void);
using PFNGLATTACHSHADERPROC = void(*)(GLuint, GLuint);
using PFNGLLINKPROGRAMPROC = void(*)(GLuint);
using PFNGLUSEPROGRAMPROC = void(*)(GLuint);
using PFNGLDELETESHADERPROC = void(*)(GLuint);
using PFNGLDELETEPROGRAMPROC = void(*)(GLuint);
using PFNGLGETSHADERIVPROC = void(*)(GLuint, GLenum, GLint*);
using PFNGLGETSHADERINFOLOGPROC = void(*)(GLuint, GLsizei, GLsizei*, GLchar*);
using PFNGLGETPROGRAMIVPROC = void(*)(GLuint, GLenum, GLint*);
using PFNGLGETPROGRAMINFOLOGPROC = void(*)(GLuint, GLsizei, GLsizei*, GLchar*);
using PFNGLGETUNIFORMLOCATIONPROC = GLint(*)(GLuint, const GLchar*);
using PFNGLUNIFORM1IPROC = void(*)(GLint, GLint);
using PFNGLUNIFORM1FPROC = void(*)(GLint, GLfloat);
using PFNGLUNIFORM3FPROC = void(*)(GLint, GLfloat, GLfloat, GLfloat);
using PFNGLUNIFORM1FVPROC = void(*)(GLint, GLsizei, const GLfloat*);
using PFNGLUNIFORM3FVPROC = void(*)(GLint, GLsizei, const GLfloat*);
using PFNGLUNIFORMMATRIX4FVPROC = void(*)(GLint, GLsizei, GLboolean, const GLfloat*);
using PFNGLACTIVETEXTUREPROC = void(*)(GLenum);
using PFNGLBINDTEXTUREPROC = void(*)(GLenum, GLuint);
using PFNGLGENTEXTURESPROC = void(*)(GLsizei, GLuint*);
using PFNGLTEXIMAGE2DPROC = void(*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
using PFNGLTEXPARAMETERIPROC = void(*)(GLenum, GLenum, GLint);

// Function pointers
inline PFNGLCLEARPROC glClear = nullptr;
inline PFNGLCLEARCOLORPROC glClearColor = nullptr;
inline PFNGLENABLEPROC glEnable = nullptr;
inline PFNGLDISABLEPROC glDisable = nullptr;
inline PFNGLVIEWPORTPROC glViewport = nullptr;
inline PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
inline PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
inline PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;
inline PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
inline PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
inline PFNGLBUFFERDATAPROC glBufferData = nullptr;
inline PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
inline PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
inline PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
inline PFNGLDRAWARRAYSPROC glDrawArrays = nullptr;
inline PFNGLDRAWELEMENTSPROC glDrawElements = nullptr;
inline PFNGLCULLFACEPROC glCullFace = nullptr;
inline PFNGLFRONTFACEPROC glFrontFace = nullptr;
inline PFNGLCREATESHADERPROC glCreateShader = nullptr;
inline PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
inline PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
inline PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
inline PFNGLATTACHSHADERPROC glAttachShader = nullptr;
inline PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
inline PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
inline PFNGLDELETESHADERPROC glDeleteShader = nullptr;
inline PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
inline PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
inline PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
inline PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
inline PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
inline PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
inline PFNGLUNIFORM1IPROC glUniform1i = nullptr;
inline PFNGLUNIFORM1FPROC glUniform1f = nullptr;
inline PFNGLUNIFORM3FPROC glUniform3f = nullptr;
inline PFNGLUNIFORM1FVPROC glUniform1fv = nullptr;
inline PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;
inline PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
inline PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
inline PFNGLBINDTEXTUREPROC glBindTexture = nullptr;
inline PFNGLGENTEXTURESPROC glGenTextures = nullptr;
inline PFNGLTEXIMAGE2DPROC glTexImage2D = nullptr;
inline PFNGLTEXPARAMETERIPROC glTexParameteri = nullptr;

inline void load() {
    glClear = reinterpret_cast<PFNGLCLEARPROC>(glfwGetProcAddress("glClear"));
    glClearColor = reinterpret_cast<PFNGLCLEARCOLORPROC>(glfwGetProcAddress("glClearColor"));
    glEnable = reinterpret_cast<PFNGLENABLEPROC>(glfwGetProcAddress("glEnable"));
    glDisable = reinterpret_cast<PFNGLDISABLEPROC>(glfwGetProcAddress("glDisable"));
    glViewport = reinterpret_cast<PFNGLVIEWPORTPROC>(glfwGetProcAddress("glViewport"));
    glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(glfwGetProcAddress("glGenVertexArrays"));
    glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(glfwGetProcAddress("glBindVertexArray"));
    glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(glfwGetProcAddress("glDeleteVertexArrays"));
    glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(glfwGetProcAddress("glGenBuffers"));
    glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(glfwGetProcAddress("glBindBuffer"));
    glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(glfwGetProcAddress("glBufferData"));
    glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(glfwGetProcAddress("glDeleteBuffers"));
    glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(glfwGetProcAddress("glVertexAttribPointer"));
    glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(glfwGetProcAddress("glEnableVertexAttribArray"));
    glDrawArrays = reinterpret_cast<PFNGLDRAWARRAYSPROC>(glfwGetProcAddress("glDrawArrays"));
    glDrawElements = reinterpret_cast<PFNGLDRAWELEMENTSPROC>(glfwGetProcAddress("glDrawElements"));
    glCullFace = reinterpret_cast<PFNGLCULLFACEPROC>(glfwGetProcAddress("glCullFace"));
    glFrontFace = reinterpret_cast<PFNGLFRONTFACEPROC>(glfwGetProcAddress("glFrontFace"));
    glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(glfwGetProcAddress("glCreateShader"));
    glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(glfwGetProcAddress("glShaderSource"));
    glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(glfwGetProcAddress("glCompileShader"));
    glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(glfwGetProcAddress("glCreateProgram"));
    glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(glfwGetProcAddress("glAttachShader"));
    glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(glfwGetProcAddress("glLinkProgram"));
    glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(glfwGetProcAddress("glUseProgram"));
    glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(glfwGetProcAddress("glDeleteShader"));
    glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(glfwGetProcAddress("glDeleteProgram"));
    glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(glfwGetProcAddress("glGetShaderiv"));
    glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(glfwGetProcAddress("glGetShaderInfoLog"));
    glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(glfwGetProcAddress("glGetProgramiv"));
    glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(glfwGetProcAddress("glGetProgramInfoLog"));
    glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(glfwGetProcAddress("glGetUniformLocation"));
    glUniform1i = reinterpret_cast<PFNGLUNIFORM1IPROC>(glfwGetProcAddress("glUniform1i"));
    glUniform1f = reinterpret_cast<PFNGLUNIFORM1FPROC>(glfwGetProcAddress("glUniform1f"));
    glUniform3f = reinterpret_cast<PFNGLUNIFORM3FPROC>(glfwGetProcAddress("glUniform3f"));
    glUniform1fv = reinterpret_cast<PFNGLUNIFORM1FVPROC>(glfwGetProcAddress("glUniform1fv"));
    glUniform3fv = reinterpret_cast<PFNGLUNIFORM3FVPROC>(glfwGetProcAddress("glUniform3fv"));
    glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(glfwGetProcAddress("glUniformMatrix4fv"));
    glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>(glfwGetProcAddress("glActiveTexture"));
    glBindTexture = reinterpret_cast<PFNGLBINDTEXTUREPROC>(glfwGetProcAddress("glBindTexture"));
    glGenTextures = reinterpret_cast<PFNGLGENTEXTURESPROC>(glfwGetProcAddress("glGenTextures"));
    glTexImage2D = reinterpret_cast<PFNGLTEXIMAGE2DPROC>(glfwGetProcAddress("glTexImage2D"));
    glTexParameteri = reinterpret_cast<PFNGLTEXPARAMETERIPROC>(glfwGetProcAddress("glTexParameteri"));

}

} // namespace gl