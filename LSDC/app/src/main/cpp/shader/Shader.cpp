#include "Shader.h"

Shader::Shader(AAssetManager* assetManager, const char *vertexSourcePath, const char *fragmentSourcePath) {

    AAsset* vertexTxt = AAssetManager_open(assetManager, vertexSourcePath, AASSET_MODE_STREAMING);
    AAsset* fragmentTxt = AAssetManager_open(assetManager, fragmentSourcePath, AASSET_MODE_STREAMING);


    mVertexSource = (const GLchar *)AAsset_getBuffer(vertexTxt);
    mVertexLength = AAsset_getLength(vertexTxt);
    mFragmentSource = (const GLchar *)AAsset_getBuffer(fragmentTxt);
    mFragmentLength = AAsset_getLength(fragmentTxt);

    createProgram();

    AAsset_close(vertexTxt);
    AAsset_close(fragmentTxt);
}

bool Shader::createProgram() {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, mVertexSource, mVertexLength);
    if (!vertexShader)
    {
        return false;
    }
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, mFragmentSource, mFragmentLength);
    if (!fragmentShader)
    {
        return false;
    }
    mProgram = glCreateProgram();
    if (mProgram)
    {
        glAttachShader(mProgram , vertexShader);
        glAttachShader(mProgram, fragmentShader);
        glLinkProgram(mProgram);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(mProgram , GL_LINK_STATUS, &linkStatus);
        if( linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength)
            {
                char* buf = (char*) malloc(bufLength);
                if (buf)
                {
                    glGetProgramInfoLog(mProgram, bufLength, NULL, buf);
                    free(buf);
                }
            }
            glDeleteProgram(mProgram);
            mProgram = 0;
        }
    }

    return true;
}

GLuint Shader::loadShader(GLenum shaderType, const GLchar *shaderSource, const int length) {
    GLuint shader = glCreateShader(shaderType);
    if (shader)
    {
        glShaderSource(shader, 1, (const GLchar **)&shaderSource, &length);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char * buf = (char*) malloc(infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint *Shader::getProgram() {
    return &mProgram;
}
