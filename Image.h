#ifndef FINAL_PROJECT_IMAGE_H
#define FINAL_PROJECT_IMAGE_H
#include "EasyBMP.h"

class Image {
    public:
        Image();
        void getCleaned();
        void blurImage();
        void saveImage();

    private:
        BMP _Background;
        BMP _Raw;
        int _height;
        int _width;
        int **_background;
        int **_raw;
        int **_output;
};

#endif //FINAL_PROJECT_IMAGE_H
