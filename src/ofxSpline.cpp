//
//  BezierSpline.cpp
//  ofSplineSample
//
//  Created by SakuragiYoshimasa on 2015/10/31.
//
//

#include "ofxSpline.h"

void ofxSpline::reset(){
    points.clear();
    points.push_back(*new ofVec3f(-200,-100,0));
    points.push_back(*new ofVec3f(-100,100,0));
    points.push_back(*new ofVec3f(100,-100,0));
    points.push_back(*new ofVec3f(200,100,0));
    curveNum = 1;
    modes.clear();
    modes.push_back(MIRRORED);
    modes.push_back(MIRRORED);
    modeColors[0] = ofColor(255,255,255,255);
    modeColors[1] = ofColor(255,255,0,255);
    modeColors[2] = ofColor(0,255,255,255);
}

void ofxSpline::drawSpline(float strokeWidth, float lineStep, bool drawDirection, ofColor splineColor){
    ofSetLineWidth(3);
    ofPath line = ofPath();
    line.setStrokeColor(splineColor);
    line.setFilled(false);
    line.setStrokeWidth(strokeWidth);
    float lineSteps = 10.0;
    ofVec3f lineStart = this->GetPoint(0,1);
    line.moveTo(lineStart);
    for(int index = 1; index <= this->GetCurveNum(); index++){
        for(int i = 0; i <= lineSteps; i++){
            ofVec3f lineEnd = this->GetPoint(float(i)/lineSteps, index);
            line.lineTo(lineEnd);
            ofSetColor(0, 255, 0);
            if(drawDirection) ofLine(lineEnd, lineEnd + this->GetDirection(float(i)/lineSteps, index));
            lineStart = lineEnd;
        }
    }
    line.draw();
};

void ofxSpline::saveSpline(string fileName){
    csvOperator::saveSplinePoints(fileName, points);
}

void ofxSpline::loadSpline(string fileName){
    points.clear();
    modes.clear();
    modes.push_back(MIRRORED);
    points = csvOperator::loadSplinePoints(fileName);
    curveNum = (points.size() - 1)/3;
    for(int i = 0; i < GetCurveNum(); i++){
        modes.push_back(MIRRORED);
        EnforceMode(i * 3);
        EnforceMode(i * 3 + 1);
        EnforceMode(i * 3 + 2);
    }
}

void ofxSpline::addCurve(){
    ofVec3f point = points[points.size() - 1];
    for(int i = 0; i < 3; i++){
        point.x += ofRandom(50);
        point.y += ofRandom(-50,50);
        point.z += ofRandom(-50,50);
        points.push_back(point);
    }
    curveNum++;
    modes.push_back(modes[modes.size() - 1]);
    EnforceMode(points.size() - 4);
}

void ofxSpline::removeCurve(){
    if(points.size() < 4) return;
    for(int i = 0; i < 3; i++){
        points.erase(points.end());
    }
    modes.erase(modes.end());
    curveNum--;
}

void ofxSpline::SetControlPoint(int index, ofVec3f point){
    //move controllPoints too
    if(index % 3 == 0){
        ofVec3f delta = point - points[index];
        if(index > 0){
            points[index - 1] += delta;
        }
        if(index + 1 < points.size()){
            points[index + 1] += delta;
        }
    }
    points[index] = point;
    EnforceMode(index);
}

void ofxSpline::SetControlPointMode(int index, ControlMode mode){
    modes[(index + 1)/3] = mode;
    EnforceMode(index);
}

const int ofxSpline::GetCurveNum(){
    return curveNum;
}

const int ofxSpline::GetPointNum(){
    return points.size();
}

const vector<ofVec3f> ofxSpline::GetPoints(){
    return points;
}

ofVec3f ofxSpline::GetControlPoint(int index){
    return points[index];
}

ControlMode ofxSpline::GetControlPointMode(int index){
    return modes[(index + 1) / 3];
}

ofVec3f ofxSpline::GetPoint(float t){
    if(t >= 1) t = 1;
    if(t < 0) t = 0;
    int i;
    t = t * float(curveNum);
    i = int(t);
    t -= i;
    i *= 3;
    return GetPoint(t , i);
}

ofVec3f ofxSpline::GetPoint(float t, int curveIndex){
    return Bezier::GetPoint(points[(curveIndex - 1) * 3], points[(curveIndex - 1) * 3 + 1], points[(curveIndex - 1) * 3 + 2], points[curveIndex * 3], t);
}

ofVec3f ofxSpline::GetVelocity(float t, int curveIndex){
    return  Bezier::GetFirstDerivative(points[(curveIndex - 1) * 3], points[(curveIndex - 1) * 3 + 1], points[(curveIndex - 1) * 3 + 2], points[curveIndex * 3], t);
}

ofVec3f ofxSpline::GetDirection(float t ,int curveIndex){
    return (GetVelocity(t, curveIndex)).normalize() * 100;
}

void ofxSpline::EnforceMode(int index){
    int modeIndex = (index + 1) / 3;
    ControlMode mode = modes[modeIndex];
    if(mode == FREE || modeIndex == 0 || modeIndex == modes.size() - 1){
        return;
    }
    //Mirrored か alignedならもう一方を強制移動
    int middleIndex = modeIndex * 3;
    int fixedIndex, enforedIndex;
    if(index <= middleIndex){
        fixedIndex = middleIndex - 1;
        enforedIndex = middleIndex + 1;
    }else{
        fixedIndex = middleIndex + 1;
        enforedIndex = middleIndex - 1;
    }
    
    ofVec3f middle = points[middleIndex];
    ofVec3f enforcedTangent = middle - points[fixedIndex];
    if(mode == ALIGNED){
        enforcedTangent = enforcedTangent.normalized() * middle.distance(points[enforedIndex]);
    }
    points[enforedIndex] = middle + enforcedTangent;
}