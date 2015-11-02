//
//  SplineWalker.cpp
//  ofSplineSample
//
//  Created by SakuragiYoshimasa on 2015/10/31.
//
//
#include "ofxSplineWalker.h"

void ofxSplineWalker::setup(BezierSpline *sp, float dur){
    spline = sp;
    duration = dur;
    index = 1;
    forward = true;
    forwardLook = true;
    mode = LOOP;
    playing = false;
}

void ofxSplineWalker::update(){
    if(!playing) return;
    if(forward){
        progress += 0.1 / duration;
    }else{
        progress -= 0.1 / duration;
    }
    updateProgress(index, progress, position, forward);
    
    if(forwardLook){
        progressLook = progress + 0.001;
    }else{
        progressLook = progress - 0.001;
    }
    updateProgress(indexLook, progressLook, loolAt, forwardLook);
}

void ofxSplineWalker::setMode(WalkMode mode){
    this->mode = mode;
}

void ofxSplineWalker::play(){
    playing = true;
}

void ofxSplineWalker::stop(){
    playing = false;
}

void ofxSplineWalker::updateProgress(int &i, float &p, ofVec3f &v, bool &f){
    if(f){
        if(p >= 1.0){
            if(spline->GetCurveNum() > i){
                p = 0.0;
                i++;
            }else{
                p = 1.0;
                if(mode == PINGPONG){
                    f = false;
                }else if (mode == LOOP){
                    i = 1;
                    p = 0.0;
                }
            }
        }
    }else{
        if(p <= 0.0){
            if(1 < i){
                p = 1.0;
                i--;
            }else{
                p = 0.0;
                f = true;
            }
        }
    }
    v = spline->GetPoint(p, i);
}

const ofVec3f ofxSplineWalker::getPosition(){
    return position;
}

const ofVec3f ofxSplineWalker::getLookAt(){
    return loolAt;
}