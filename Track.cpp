#include "Track.h"
#include "EasyBMP.h"
#include <vector>
#include <algorithm>
#include <cmath>

Track::Track() {
    _cleaned.ReadFromFile("D:\\UNI\\Year 4\\C++ and Object Oriented Programming\\Projects\\Final_Project\\cmake-build-debug\\cleaned_image.bmp");
    _width = _cleaned.TellWidth();
    _height = _cleaned.TellHeight();
    cleaned = new double*[_width];
    tracks = new int*[_width];
    added = new int*[_width];


    for ( int xPixel = 0; xPixel < _width; ++xPixel){
        cleaned[xPixel] = new double[_height];
        for (int yPixel = 0; yPixel < _height; ++yPixel){
            // convert each pixel to greyscale
            double Temp = 0.30*(_cleaned(xPixel, yPixel)->Red) + 0.59*(_cleaned(xPixel, yPixel)->Green) + 0.11*(_cleaned(xPixel, yPixel)->Blue);
            if (Temp != 255){
                cleaned[xPixel][yPixel] = 255-(Temp);
            }
            else{
                cleaned[xPixel][yPixel] = 0;
            }
        }
    }

    for(int p=0; p<_width;p++){
        //initialises all pixels to have 0
        //initialises an added array to all 0s
        tracks[p] = new int[_height];
        added[p] = new int[_height];
        for(int q=0; q<_height; q++){
            tracks[p][q]=0;
            added[p][q]=0;
        }
    }
}

void Track::NearestNeighbour_4Way() {
    //determines a particle track using an 4-way nearest neighbour algorithm
    int max = 0;
    int x=0;
    int y=0;

    for(int i=0; i<_width; i++){
        for(int j=0; j<_height; j++){
            if(cleaned[i][j]>max){
                max=cleaned[i][j];
                x=i;
                y=j;
            }
        }
    }

    tracks[x][y]=cleaned[x][y];
    _track_xpos.push_back(x);
    _track_ypos.push_back(y);
    _track_brightness.push_back(cleaned[x][y]);
    added[x][y]=1;
    std::vector<int> x_pos {x-1,x+1,x, x};
    std::vector<int> y_pos {y, y, y-1, y+1};
    std::vector<int> x_pos_temp;
    std::vector<int> y_pos_temp;

    while(x_pos.empty()==false) {
        for(int i = 0; i < x_pos.size(); i++) {
            if(x_pos[i]!=-1 && x_pos[i]!=_width+1 && y_pos[i]!=-1 && y_pos[i]!=_height+1 && cleaned[x_pos[i]][y_pos[i]] > 50 && added[x_pos[i]][y_pos[i]]!=1) {
                tracks[x_pos[i]][y_pos[i]] = cleaned[x_pos[i]][y_pos[i]];
                added[x_pos[i]][y_pos[i]] = 1;
                _track_xpos.push_back(x_pos[i]);
                _track_ypos.push_back(y_pos[i]);
                _track_brightness.push_back(cleaned[x_pos[i]][y_pos[i]]);
                x_pos_temp.push_back(x_pos[i]);
                x_pos_temp.push_back(x_pos[i]);
                for(int j = -1; j < 2; j+=2) {
                    y_pos_temp.push_back(y_pos[i]+j);
                }
                y_pos_temp.push_back(y_pos[i]);
                y_pos_temp.push_back(y_pos[i]);
                for(int j=-1; j<2; j+=2) {
                    x_pos_temp.push_back(x_pos[i]+j);
                }
            }
        }
        x_pos.clear();
        y_pos.clear();

        for (int i = 0; i < x_pos_temp.size(); i++) {
            x_pos.push_back(x_pos_temp[i]);
            y_pos.push_back(y_pos_temp[i]);
        }
        x_pos_temp.clear();
        y_pos_temp.clear();
    }

    BMP Output;
    Output.SetSize(_width,_height);
    Output.SetBitDepth(32);

    // plot the pixels
    for(int i=0 ; i < _width ; i++ )
    {
        for(int j=0; j < _height ; j++ )
        {
            double scaled_value = 1-( tracks[i][j] - 0 )/( max + 1e-16 );
            ebmpBYTE pixel_value = (ebmpBYTE) ( scaled_value * 255.0 );
            Output(i,j)->Red = pixel_value;
            Output(i,j)->Green = pixel_value;
            Output(i,j)->Blue = pixel_value;
        }
    }

    Output.WriteToFile( "tracks_4way.bmp" );
}

void Track::NearestNeighbour_8Way(){
    //determines a particle track using an 8-way nearest neighbour algorithm
    int max = 0;
    int x=0;
    int y=0;

    for(int i=0; i<_width; i++){
        for(int j=0; j<_height; j++){
            if(cleaned[i][j]>max){
                max=cleaned[i][j];
                x=i;
                y=j;
            }
        }
    }

    tracks[x][y]=cleaned[x][y];
    _track_xpos.push_back(x);
    _track_ypos.push_back(y);
    _track_brightness.push_back(cleaned[x][y]);
    added[x][y]=1;
    std::vector<int> x_pos {x, x, x-1, x-1, x-1, x+1, x+1, x+1};
    std::vector<int> y_pos {y+1, y-1, y, y+1, y-1, y, y+1, y-1};
    std::vector<int> x_pos_temp;
    std::vector<int> y_pos_temp;

    while(x_pos.empty()==false) {
        for(int i = 0; i < x_pos.size(); i++) {
            if(x_pos[i]!=-1 && x_pos[i]!=_width+1 && y_pos[i]!=-1 && y_pos[i]!=_height+1 && cleaned[x_pos[i]][y_pos[i]] > 50 && added[x_pos[i]][y_pos[i]]!=1) {
                tracks[x_pos[i]][y_pos[i]] = cleaned[x_pos[i]][y_pos[i]];
                added[x_pos[i]][y_pos[i]] = 1;
                _track_xpos.push_back(x_pos[i]);
                _track_ypos.push_back(y_pos[i]);
                _track_brightness.push_back(cleaned[x_pos[i]][y_pos[i]]);
                x_pos_temp.push_back(x_pos[i]);
                x_pos_temp.push_back(x_pos[i]);
                for(int j=-1; j<2; j+=2) {
                    y_pos_temp.push_back(y_pos[i]+j);
                }
                x_pos_temp.push_back(x_pos[i]-1);
                x_pos_temp.push_back(x_pos[i]-1);
                x_pos_temp.push_back(x_pos[i]-1);
                for(int j=-1; j<2; j++){
                    y_pos_temp.push_back(y_pos[i]+j);
                }
                x_pos_temp.push_back(x_pos[i]+1);
                x_pos_temp.push_back(x_pos[i]+1);
                x_pos_temp.push_back(x_pos[i]+1);
                for(int j=-1; j<2; j++){
                    y_pos_temp.push_back(y_pos[i]+j);
                }
            }
        }
        x_pos.clear();
        y_pos.clear();

        for (int i = 0; i < x_pos_temp.size(); i++) {
            x_pos.push_back(x_pos_temp[i]);
            y_pos.push_back(y_pos_temp[i]);
        }
        x_pos_temp.clear();
        y_pos_temp.clear();
    }

    BMP Output;
    Output.SetSize(_width,_height);
    Output.SetBitDepth(32);

    // plot the pixels
    for(int i=0 ; i < _width ; i++ )
    {
        for(int j=0; j < _height ; j++ )
        {
            double scaled_value = 1-( tracks[i][j] - 0 )/( max + 1e-16 );
            ebmpBYTE pixel_value = (ebmpBYTE) ( scaled_value * 255.0 );
            Output(i,j)->Red = pixel_value;
            Output(i,j)->Green = pixel_value;
            Output(i,j)->Blue = pixel_value;
        }
    }

    Output.WriteToFile( "tracks_8way.bmp" );
}

bool Track::TouchesEdge(){
    //returns true if track touches the edge of the chamber and false if it does not
    bool touches = false;

    for(int i=0; i<_track_xpos.size(); i++){
        if(_track_xpos[i]==0 || _track_xpos[i]==_width-1 || _track_ypos[i]==0 || _track_ypos[i]==_height-1){
            touches = true;
            break; //breaks out of loop if any pixel touches the edge
        }
    }
    return touches;
}

int Track::GetBrightness(){
    //calculates the total brightness of a track
    unsigned int brightness = 0;

    for(int i=0; i<_track_brightness.size(); i++){ //loop through all track brightness vector elements
        brightness += _track_brightness[i]; //sums all track brightness elements
    }
    return brightness;
}

double Track::BrightnessPerPixel(){
    //calculates the average brightness per pixel
    return GetBrightness()/_track_brightness.size();
}

double Track::GetLength(){
    //calculates the Euclidean distance between a set of pixel coordinates to determine length
    int x_min = *std::min_element(_track_xpos.begin(), _track_xpos.end());
    int x_max = *std::max_element(_track_xpos.begin(), _track_xpos.end());
    int y_min = *std::min_element(_track_ypos.begin(), _track_ypos.end());
    int y_max = *std::max_element(_track_ypos.begin(), _track_ypos.end());

    return sqrt(pow(x_max-x_min,2)+ pow(y_max-y_min,2));
}

double Track::BrightnessPerLength(){
    //calculates the brightness per unit length of the track
    return GetBrightness()/GetLength();
}