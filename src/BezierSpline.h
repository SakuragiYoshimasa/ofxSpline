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
#include "csvOperator.h"

class BezierSpline{
public:
    BezierSpline(){
        reset();
    };
    
    void reset();
    void saveSpline(string fileName);
    void loadSpline(string fileName);
    void addCurve();
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
