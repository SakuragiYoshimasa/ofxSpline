//
//  Bezier.cpp
//  ofSplineSample
//
//  Created by SakuragiYoshimasa on 2015/10/31.
//
//
#include "Bezier.h"

ofVec3f Bezier::GetPoint(ofVec3f p0, ofVec3f p1, ofVec3f p2, ofVec3f p3, float t){
    if(t > 1.0) t = 1.0;
    if(t < 0) t = 0;
    float oneMinusT = 1.0 - t;
    return oneMinusT * oneMinusT * oneMinusT * p0 + 3.0 * oneMinusT * oneMinusT * t * p1 + 3.0 * oneMinusT * t * t * p2 + t * t * t * p3;
    //return Lerp(Lerp(p0, p1, t), Lerp(p1, p2, t), t);
    //Not use Lerp p0,p1,p2
    //return (1.0 - t) * (1.0 - t) * p0 + 2.0 * (1.0 - t) * t * p1 + t * t * p2;
};

ofVec3f Bezier::GetFirstDerivative(ofVec3f p0, ofVec3f p1, ofVec3f p2, ofVec3f p3, float t){
    if(t > 1.0) t = 1.0;
    if(t < 0) t = 0;
    float oneMinusT = 1.0 - t;
    return 3.0 * oneMinusT * oneMinusT * (p1 - p0) + 6.0 * oneMinusT * t * (p2 - p1) + 3.0 * t * t * (p3 - p2);
    //return 2.0 * (1.0 - t) * (p1 - p0) + 2.0 * t * (p2 - p1);
};

ofVec3f Bezier::Lerp(ofVec3f p0, ofVec3f p1, float t){
    if(t > 1.0) t = 1.0;
    if(t < 0) t = 0;
    return p0 + t * (p1 - p0);
};