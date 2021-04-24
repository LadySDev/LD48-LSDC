#ifndef LSDC_SHADER_H
#define LSDC_SHADER_H

#include <GLES3/gl3.h>

#include <cstdlib>
#include <android/asset_manager.h>

class Shader {
public:
    Shader(AAssetManager* assetManager, const char *vertexSourcePath, const char *fragmentSourcePath);

    GLuint* getProgram();
private:
    const char* mVertexSource;
    int mVertexLength;
    const char * mFragmentSource;
    int mFragmentLength;
    GLuint mProgram;

    bool createProgram();
    GLuint loadShader(GLenum shaderType, const GLchar* shaderSource, const int length);
};


#endif //LSDC_SHADER_H
