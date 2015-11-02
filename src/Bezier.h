//
//  Bezier.hpp
//  ofSplineSample
//
//  Created by SakuragiYoshimasa on 2015/10/31.
//
//
#ifndef Bezier_h
#define Bezier_h

#include "ofMain.h"

enum ControlMode{
    FREE,
    ALIGNED,
    MIRRORED
};

class Bezier {
public:
    static ofVec3f GetPoint(ofVec3f p0, ofVec3f p1, ofVec3f p2, ofVec3f p3, float t);
    static ofVec3f GetFirstDerivative(ofVec3f p0, ofVec3f p1, ofVec3f p2, ofVec3f p3, float t);
    static ofVec3f Lerp(ofVec3f p0, ofVec3f p1, float t);
};
#endif
