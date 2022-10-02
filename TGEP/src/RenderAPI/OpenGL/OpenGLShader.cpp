#include "pch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>


namespace TGEP
{
    static GLenum ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
        {
            return GL_VERTEX_SHADER;
        }
        if (type == "fragment")
        {
            return GL_FRAGMENT_SHADER;
        }
        ASSERT_CORE(false, "UNKNOWN_SHADER_TYPE");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& path)
    {
        std::string src = ReadFile(path);
        auto shaderSources = OpenGLShader::PreProcess(src);
        Compile(shaderSources);

        size_t lastSlash = path.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        size_t lastDot = path.rfind('.');
        lastDot = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
        m_Name = path.substr(lastSlash, lastDot);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
        m_Name = name;
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    std::string OpenGLShader::ReadFile(const std::string& path)
    {
        std::string result;
        std::ifstream in(path.c_str(), std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            LOG_ERROR("%s%s%s\n", "ERROR::COULD_NOT_LOAD_FILE@'", path.c_str(), "' THROWN@FN_OPENGLSHADER::READFILE");
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& src)
    {
        std::unordered_map<GLenum, std::string> shaderSources;
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = src.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            size_t eol = src.find_first_of("\r\n", pos);
            ASSERT_CORE(eol != std::string::npos, "SYNTAX_ERROR@FN_PREPROCCES");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = src.substr(begin, eol - begin);
            ASSERT_CORE(ShaderTypeFromString(type), "INVALID_SHADER_TYPE@FN_PREPROCCES");

            size_t nextLinePos = src.find_first_not_of("\r\n", eol);
            pos = src.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = src.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? src.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        GLuint program = glCreateProgram();
        ASSERT_CORE(shaderSources.size() <= 2, "TOO MANY SHADERS IN ONE FILE!");
        std::array<GLenum, 2> glShaderIDs;
        int glShaderIDIndex = 0;
        for (auto& kv : shaderSources)
        {
            GLenum type = kv.first;
            const std::string& srcString = kv.second;

            GLuint shader = glCreateShader(type);

            const GLchar* source = (const GLchar*)srcString.c_str();
            glShaderSource(shader, 1, &source, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
                LOG_ERROR("%s\n", "SHADER_COMPILATION_FAILED");
                LOG_ERROR("%s", infoLog.data());
                glDeleteShader(shader);
                break;
            }
            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);

            for (auto id : glShaderIDs)
                glDeleteShader(id);

            printf("%s", "SHADER PROGRAM COMPILATION FAILED");
            printf("%s", infoLog.data());
            return;
        }

        for (auto id : glShaderIDs)
            glDetachShader(program, id);

        m_RendererID = program;
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::UnBind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::mat4& value)
    {
        UploadUniform(name, value);
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::vec4& value)
    {
        UploadUniform(name, value);
    }

    void OpenGLShader::SetUniform(const std::string& name, const int& value)
    {
        UploadUniform(name, value);
    }

    void OpenGLShader::UploadUniform(const std::string& name, const glm::mat4& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    void OpenGLShader::UploadUniform(const std::string& name, const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }
    void OpenGLShader::UploadUniform(const std::string& name, const int& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }
}