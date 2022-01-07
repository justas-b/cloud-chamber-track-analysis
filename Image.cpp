#include "Image.h"
#include "EasyBMP.h"
#include "Functions.h"

Image::Image() {
    _Background.ReadFromFile("D:\\UNI\\Year 4\\C++ and Object Oriented Programming\\Projects\\Final_Project\\Run2\\background.bmp");
    _Raw.ReadFromFile("D:\\UNI\\Year 4\\C++ and Object Oriented Programming\\Projects\\Final_Project\\Run2\\Alpha\\scene00451.bmp");
    _width = _Background.TellWidth();
    _height = _Background.TellHeight();
    _background = new int*[_width];
    _raw = new int*[_width];
    _output = new int*[_width];
    to_greyscale(_Background, _height, _width, _background);
    to_greyscale(_Raw, _height, _width, _raw);
}

void Image::getCleaned() {
    //subtracts the pixel values of the background image from the raw image and stores result in a new 2D array
    for(int x=0; x<_width;x++){
        _output[x] = new int[_height];
        for(int y=0; y<_height; y++){
            _output[x][y]=_background[x][y]-_raw[x][y];
        }
    }
}

void Image::blurImage() {
    //class method that implements blurring between all nearest neighbours of a pixel
    int **temp= new int*[_width];
    for(int x=0; x<_width;x++){
        temp[x] = new int[_height];
        for(int y=0; y<_height; y++){
            temp[x][y]=_output[x][y];
        }
    }

    for(int i=0; i<_width; i++){
        for(int j=0; j<_height; j++){
            int count = 1;
            int brightness = temp[i][j];
            if(i-1!=-1){
                brightness += temp[i-1][j];
                count++;
                if(j-1!=-1){
                    brightness += temp[i-1][j-1];
                    brightness += temp[i][j-1];
                    count+=2;
                }
                if(j+1!=_height){
                    brightness += temp[i-1][j+1];
                    brightness += temp[i][j+1];
                    count+=2;
                }
            }
            if(i+1!=_width){
                brightness += temp[i+1][j];
                count++;
                if(j-1!=-1){
                    brightness += temp[i+1][j-1];
                    count++;
                }
                if(j+1!=_height){
                    brightness +=temp[i+1][j+1];
                    count++;
                }
            }
        _output[i][j]=brightness/count;
        }
    }

    for(int i=0; i<_width; i++) {
        delete[] temp[i];
    }
    delete[] temp;
}

void Image::saveImage() {
    // class method that saves output as a BMP image
    double min = 9e9;
    double max = -9e9;
    for( int i=0 ; i < _width ;i++ )
    {
        for( int j=0; j <_height ; j++ )
        {
            if( _output[i][j] < min )
            { min = _output[i][j]; }
            if( _output[i][j] > max )
            { max = _output[i][j]; }
        }
    }

    BMP Output;
    Output.SetSize(_width,_height);
    Output.SetBitDepth(32);

    //plot the pixels of the cleaned image and saves the result as a new bmp file
    for(int i=0 ; i < _width ; i++ )
    {
        for(int j=0; j < _height ; j++ )
        {
            double scaled_value = 1 - ( _output[i][j] - min )/( max-min + 1e-16 );
            ebmpBYTE pixel_value = (ebmpBYTE) ( scaled_value * 255.0 );
            Output(i,j)->Red = pixel_value;
            Output(i,j)->Green = pixel_value;
            Output(i,j)->Blue = pixel_value;
        }
    }
    Output.WriteToFile( "cleaned_image.bmp" );

    //clearing memory from the heap
    for(int i=0; i<_width; i++){
        delete[] _background[i];
        delete[] _raw[i];
        delete[] _output[i];
    }
    delete[] _background;
    delete[] _raw;
    delete[] _output;
}