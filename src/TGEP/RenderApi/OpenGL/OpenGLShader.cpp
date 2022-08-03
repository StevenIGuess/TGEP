#include "OpenGLShader.h"

#include "pch.h"
#include <glad/glad.h>
#include "helper.h"


namespace TGEP 
{

    OpenGLShader::OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar *source = (const GLchar *)vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            printf("%s", "VERTEX SHADER COMPILATION FAILED");
            printf("%s", infoLog.data());
            
            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.
            
            // In this simple program, we'll just leave
            return;
        }

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = (const GLchar *)fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            printf("%s", "FRAGMENT COMPILATION FAILED");
            printf("%s", infoLog.data());
            
            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.
            
            // In this simple program, we'll just leave
            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_ShaderID = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_ShaderID, vertexShader);
        glAttachShader(m_ShaderID, fragmentShader);

        // Link our program
        glLinkProgram(m_ShaderID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_ShaderID, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_ShaderID, maxLength, &maxLength, &infoLog[0]);
            
            // We don't need the program anymore.
            glDeleteProgram(m_ShaderID);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            printf("%s", "SHADER PROGRAM COMPILATION FAILED");
            printf("%s", infoLog.data());

            // Use the infoLog as you see fit.
            
            // In this simple program, we'll just leave
            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_ShaderID, vertexShader);
        glDetachShader(m_ShaderID, fragmentShader);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ShaderID);
    }

    void OpenGLShader::UnBind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniform(const std::string &name, const glm::mat4 &value)
    {
        GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    void OpenGLShader::UploadUniform(const std::string &name, const glm::vec4 &value)
    {
        GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }
}