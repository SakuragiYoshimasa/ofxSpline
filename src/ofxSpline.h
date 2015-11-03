//
//  BezierSpline.h
//  ofSplineSample
//
//  Created by SakuragiYoshimasa on 2015/10/31.
//
#ifndef BezierSpline_h
#define BezierSpline_h
#include "ofMain.h"
#include "Bezier.h"
class ofxSpline;

#include "csvOperator.h"
#include "ofxSplineEditor.h"
#include "ofxSplineWalker.h"

class ofxSpline {
public:
    ofxSpline(){
        reset();
    };
    
    void reset();
    void drawSpline(float strokeWidth = 1.5 , float lineStep = 10.0, bool drawDirection = true, ofColor splineColor = ofColor(255,255,255));
    void saveSpline(string fileName);
    void loadSpline(string fileName);
    void addCurve();
    void removeCurve();
    void SetControlPoint(int index, ofVec3f point);
    void SetControlPointMode(int index, ControlMode mode);
    const int GetPointNum();
    const int GetCurveNum();
    const vector<ofVec3f> GetPoints();
    ofVec3f GetControlPoint(int index);
    ofVec3f GetPoint(float t);
    ofVec3f GetPoint(float t, int curveIndex);
    ofVec3f GetVelocity(float t, int curveIndex);
    ofVec3f GetDirection(float t ,int curveIndex);
    ControlMode GetControlPointMode(int index);
    
    ofColor modeColors[3];
private:
    void EnforceMode(int index);
    int curveNum;
    vector<ofVec3f> points;
    vector<ControlMode> modes;
};

#endif
