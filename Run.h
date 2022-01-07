#ifndef FINAL_PROJECT_RUN_H
#define FINAL_PROJECT_RUN_H

#include "Track.h"

class Run {
    public:
        Run();
        Run(bool blur);
        void Run_Track(int algo);
    private:
        Track _track;
};


#endif //FINAL_PROJECT_RUN_H
