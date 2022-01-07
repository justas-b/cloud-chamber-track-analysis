#include "Functions.h"

void to_greyscale(BMP Image, int height, int width, int**output){
    //converts BMP image to greyscale and stores it in an output array
    for(int x=0; x<width; x++){
        output[x]=new int[height];
        for(int y=0; y<height; y++){
            int Temp = 0.30*(Image(x, y)->Red) + 0.59*(Image(x, y)->Green) + 0.11*(Image(x, y)->Blue);
            if (Temp != 255){
                output[x][y] = 255-(Temp);
            }
            else{
                output[x][y] = 0;
            }
        }
    }
}

