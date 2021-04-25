#include "Text.h"

Text::Text(Context *context, float width, float height, GLuint texture, std::string text) {
    mContext = context;
    mProgram = mContext->getUIShader()->getProgram();
    mTexture = texture;

    mPosX = -1.0f;
    mPosY = 1.0f;

    mWidth = width;
    mHeight = height;

    mText = text;

    mCharacterSize = 100;
    mCharacterSpacing = -40;

    mImages = std::vector<Image>();

    for(char& c : mText){
        addLetter(c);
    }
}

void Text::render() {
    for(int i =0;i<mImages.size();i++){
        mImages[i].render();
    }
}

Image Text::getLetter(int row, int col) {
    Image img(mContext, (float)mCharacterSize, (float)mCharacterSize, mContext->getFontTexture());
    img.setTextureCoord(new float []{
            col * 64.f / 1920.f, row * 64.f / 1080.f,
            (col + 1) * 64.f / 1920.f, row * 64.f / 1080.f,
            (col + 1) * 64.f / 1920.f, (row + 1) * 64.f / 1080.f,
            col * 64.f / 1920.f, (row + 1) * 64.f / 1080.f
    });
    return img;
}

void Text::addLetter(char letter) {
    float startPosX = mPosX;
    float startPosY = mPosY;
    if(mImages.size() > 0){
        float offsetX = 0.0f;

        float width = ((float)mImages.size() * (float)mCharacterSize) + ((float)mImages.size() * (float)mCharacterSpacing);

        float pos1X = -1.0f;
        float pos2X = (2 * width / (float)mContext->getWidth()) - 1;

        offsetX = abs(pos1X - pos2X);
        startPosX = startPosX + offsetX;
    }

    switch(letter){
        case 'A':
            mImages.push_back(getLetter(0, 0));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'B':
            mImages.push_back(getLetter(0, 1));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'C':
            mImages.push_back(getLetter(0, 2));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'D':
            mImages.push_back(getLetter(0, 3));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'E':
            mImages.push_back(getLetter(0, 4));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'F':
            mImages.push_back(getLetter(0, 5));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'G':
            mImages.push_back(getLetter(0, 6));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'H':
            mImages.push_back(getLetter(0, 7));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'I':
            mImages.push_back(getLetter(0, 8));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'J':
            mImages.push_back(getLetter(0, 9));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'K':
            mImages.push_back(getLetter(0, 10));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'L':
            mImages.push_back(getLetter(0, 11));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'M':
            mImages.push_back(getLetter(0, 12));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'N':
            mImages.push_back(getLetter(0, 13));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'O':
            mImages.push_back(getLetter(0, 14));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'P':
            mImages.push_back(getLetter(0, 15));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'Q':
            mImages.push_back(getLetter(0, 16));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'R':
            mImages.push_back(getLetter(0, 17));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'S':
            mImages.push_back(getLetter(0, 18));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'T':
            mImages.push_back(getLetter(0, 19));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'U':
            mImages.push_back(getLetter(0, 20));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'V':
            mImages.push_back(getLetter(0, 21));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'W':
            mImages.push_back(getLetter(0, 22));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'X':
            mImages.push_back(getLetter(0, 23));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'Y':
            mImages.push_back(getLetter(0, 24));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case 'Z':
            mImages.push_back(getLetter(0, 25));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case ' ':
            mImages.push_back(getLetter(0, 26));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case '0':
            mImages.push_back(getLetter(3, 0));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case '1':
            mImages.push_back(getLetter(3, 1));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case '2':
            mImages.push_back(getLetter(3, 2));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case '3':
            mImages.push_back(getLetter(3, 3));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case '4':
            mImages.push_back(getLetter(3, 4));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case '5':
            mImages.push_back(getLetter(3, 5));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case '6':
            mImages.push_back(getLetter(3, 6));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case '7':
            mImages.push_back(getLetter(3, 7));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case '8':
            mImages.push_back(getLetter(3, 8));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
        case '9':
            mImages.push_back(getLetter(3, 9));

            mImages[mImages.size() - 1].setPosition(startPosX, startPosY);

            break;
    }
}

void Text::setText(std::string text) {
    mText = text;

    mImages = std::vector<Image>();

    for(char& c : mText){
        addLetter(c);
    }
}

void Text::setCharacterSize(int size) {
    mCharacterSize = size;
    mCharacterSpacing = (float)mCharacterSize * (-0.4);

    mImages = std::vector<Image>();

    for(char& c : mText){
        addLetter(c);
    }
}

int Text::getCharacterSize() {
    return mCharacterSize;
}

void Text::setPosition(float x, float y) {
    mPosX = (2 * x / (float)mContext->getWidth()) - 1;
    mPosY = 1 - (2 * y / (float)mContext->getHeight());

    float startPosX = mPosX;
    float startPosY = mPosY;

    for(int i =0;i<mImages.size();i++){
        float offsetX = 0.0f;
        if(i > 0){
            float pos1X = -1.0f;
            float pos2X = (2 * ((float)mCharacterSize + (float)mCharacterSpacing)) / (float)mContext->getWidth() - 1;

            offsetX = abs(pos1X - pos2X);
        }

        startPosX = startPosX + offsetX;
        mImages[i].setPosition(startPosX, startPosY);
    }
}

float Text::getWidthBounds() {
    return ((float)mImages.size() * (float)mCharacterSize) + ((float)(mImages.size() - 1) * (float)mCharacterSpacing);
}

float Text::getHeightBounds() {
    return (float)mCharacterSize;
}

float Text::getPosX() {
    return (mPosX + 1) * (float)mContext->getWidth() / 2.0f;
}

float Text::getPosY() {
    return (-mPosY + 1) * (float)mContext->getHeight() / 2.0f;
}
