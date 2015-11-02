//
//  SplineWalker.h
//  ofSplineSample
//
//  Created by SakuragiYoshimasa on 2015/10/31.
//
//
#ifndef SplineWalker_h
#define SplineWalker_h
#include "BezierSpline.h"

enum WalkMode {
    LOOP,
    PINGPONG
};

class SplineWalker {
public:
    void setup(BezierSpline *sp, float dur);
    void update();
    void setMode(WalkMode mode);
    void play();
    void stop();
    const ofVec3f getPosition();
    const ofVec3f getLookAt();
    
private:
    void updateProgress(int &i, float &p, ofVec3f &v, bool &f);
    
    int index;
    int indexLook;
    bool forward;
    bool forwardLook;
    bool playing;
    float duration;
    float progress;
    float progressLook;
    WalkMode mode;
    ofVec3f position;
    ofVec3f loolAt;
    BezierSpline* spline;
};
#endif
