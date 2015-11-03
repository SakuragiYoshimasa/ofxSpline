//
//  ofxSplineEditor.hpp
//  ofSplineSample
//
//  Created by SakuragiYoshimasa on 2015/10/31.
//
//

#ifndef ofxSplineEditor_h
#define ofxSplineEditor_h

#include "ofMain.h"
#include "BezierSpline.h"
#include "ofxGui.h"
#include "csvOperator.h"

class ofxSplineEditor {
public:
    ofxSplineEditor(){};
    void setup();
    void update();
    void draw();
    void drawgui();
    void setFileName(string fileName);
    void setStrokeWidth(float width);
    void setSplineColor(const ofColor c);
    void beginEditorCam();
    void endEditorCam();
    BezierSpline * getSpline();
private:
    
    void updateSpline();
    void updateSplineFileSystem();
    void updateSplinePoint();
    void updateCameraPosition();
    void drawMarkPoint();
    //------------------------------------
    //GUI
    //------------------------------------
    ofxPanel gui;
    ofxIntSlider editPointIndex;
    ofxToggle drawDirectionButton;
    ofxToggle drawControlLine;
    ofxToggle addCurve;
    ofxToggle removeCurve;
    ofxToggle editPointMode;
    ofxToggle savePoints;
    ofxToggle loadPoints;
    ofxLabel editPointLabel;
    ofxFloatSlider pointSize;
    ofxFloatSlider adjustScale;
    ofxButton plusX;
    ofxButton minusX;
    ofxButton plusY;
    ofxButton minusY;
    ofxButton plusZ;
    ofxButton minusZ;
    ofxLabel cameraLabel;
    ofxButton plusCameraX;
    ofxButton minusCameraX;
    ofxButton plusCameraY;
    ofxButton minusCameraY;
    ofxButton plusCameraZ;
    ofxButton minusCameraZ;
    
    //-------------------------------------
    //
    //-------------------------------------
    BezierSpline spline;
    ofEasyCam editorCam;
    ofVec3f cameraPos;
    ofColor splineColor;
    float strokeWidth;
    string fileName = "";
};
#endif
