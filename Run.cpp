#include "Run.h"
#include "Track.h"
#include "Image.h"

Run::Run(){
    Image image;
    image.getCleaned();
    image.blurImage();
    image.saveImage();
    Track track;
    track.NearestNeighbour_8Way();
    std::cout<<"The length of the track is "<<track.GetLength()<<std::endl;
    std::cout<<"Total brightness of the track is "<<track.GetBrightness()<<std::endl;
    std::cout<<"The average brightness per pixel of the track is "<<track.BrightnessPerPixel()<<std::endl;
    std::cout<<"The brightness per length is "<<track.BrightnessPerLength()<<std::endl;

    if(track.TouchesEdge()){
        std::cout<<"The track touches the edge!"<<std::endl;
    }
    else{
        std::cout<<"The track does not touch the edge!"<<std::endl;
    }
}

Run::Run(bool blur){
    Image image;
    image.getCleaned();

    std::cout<<"Background subtraction successful!"<<std::endl;

    if(blur){
        image.blurImage();
        std::cout<<"Image blurred successfully!"<<std::endl;
    }

    image.saveImage();
}

void Run::Run_Track(int algo){
    Track _track;

    if(algo==4){
        _track.NearestNeighbour_4Way();
        std::cout<<"4-way nearest neighbour algorithm implemented."<<std::endl;
    }
    else if(algo==8){
        _track.NearestNeighbour_8Way();
        std::cout<<"8-way nearest neighbour algorithm implemented."<<std::endl;
    }

    if(_track.TouchesEdge()){
        std::cout<<"The track touches the edge of the chamber!"<<std::endl;
    }
    else{
        std::cout<<"The track does not touch the edge of the chamber!"<<std::endl;
    }

    std::cout<<"The total brightness of the track is "<<_track.GetBrightness()<<std::endl;
    std::cout<<"The average brightness per pixel is "<<_track.BrightnessPerPixel()<<std::endl;
    std::cout<<"The length of the track is "<<_track.GetLength()<<" pixels."<<std::endl;
    std::cout<<"The brightness per unit length is "<<_track.BrightnessPerLength()<<std::endl;
}
