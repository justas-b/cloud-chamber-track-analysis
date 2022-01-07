#ifndef FINAL_PROJECT_TRACK_H
#define FINAL_PROJECT_TRACK_H

#include "EasyBMP.h"
#include <vector>

class Track {
    public:
        Track();
        void NearestNeighbour_4Way();
        void NearestNeighbour_8Way();
        bool TouchesEdge();
        int GetBrightness();
        double BrightnessPerPixel();
        double GetLength();
        double BrightnessPerLength();

    private:
        BMP _cleaned;
        double **cleaned;
        int **tracks;
        int **added;
        int _height;
        int _width;
        std::vector<int> _track_xpos; //stores x coordinate of pixel of track
        std::vector<int> _track_ypos; //stores y coordinate of pixel of track
        std::vector<int> _track_brightness; //stores brightness of pixel of track
};

#endif //FINAL_PROJECT_TRACK_H
