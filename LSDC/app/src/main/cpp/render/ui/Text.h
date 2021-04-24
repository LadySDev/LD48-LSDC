#ifndef LSDC_TEXT_H
#define LSDC_TEXT_H

#include "../../Context.h"
#include "Image.h"
#include <string>
#include <vector>

class Text {
public:
    Text(Context* context, float width, float height, GLuint texture, std::string text);

    void render();

    void setText(std::string text);
    void setPosition(float x, float y);
    float getWidthBounds();
private:
    Context* mContext;
    GLuint* mProgram;
    GLuint mTexture;

    float mWidth;
    float mHeight;

    float mPosX;
    float mPosY;

    std::string mText;
    int mCharacterSize;
    int mCharacterSpacing;

    std::vector<Image> mImages;

    Image getLetter(int row, int col);
    void addLetter(char letter);
};


#endif //LSDC_TEXT_H
