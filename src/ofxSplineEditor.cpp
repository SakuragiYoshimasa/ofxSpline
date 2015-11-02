//
//  ofxSplineEditor.cpp
//  ofSplineSample
//
//  Created by SakuragiYoshimasa on 2015/10/31.
//
//

#include "ofxSplineEditor.h"

void ofxSplineEditor::setup(){
    spline.reset();
    gui.setup();
    gui.add(editPointLabel.setup("SplineEdit", ""));
    gui.add(savePoints.setup("Save", false));
    gui.add(loadPoints.setup("Load", false));
    gui.add(addCurve.setup("AddCurve", false));
    gui.add(editPointMode.setup("EditPointMode", false));
    gui.add(drawDirectionButton.setup("DrawDirection", true));
    gui.add(drawControlLine.setup("DrawControlLine", true));
    gui.add(editPointIndex.setup("EditPointIndex", 0, 0, spline.GetPointNum()));
    gui.add(pointSize.setup("PointSize", 5, 0, 100));
    gui.add(adjustScale.setup("AdjustScale", 10, 1, 200));
    gui.add(plusX.setup("+X", false));
    gui.add(minusX.setup("-X", false));
    gui.add(plusY.setup("+Y", false));
    gui.add(minusY.setup("-Y", false));
    gui.add(plusZ.setup("+Z", false));
    gui.add(minusZ.setup("-Z", false));
    gui.add(cameraLabel.setup("CameraPosition", ""));
    gui.add(plusCameraX.setup("+X", false));
    gui.add(minusCameraX.setup("-X", false));
    gui.add(plusCameraY.setup("+Y", false));
    gui.add(minusCameraY.setup("-Y", false));
    gui.add(plusCameraZ.setup("+Z", false));
    gui.add(minusCameraZ.setup("-Z", false));
    strokeWidth = 1.5;
    cameraPos = ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0);
}

void ofxSplineEditor::update(){
    updateSpline();
    updateSplineFileSystem();
    updateSplinePoint();
    updateCameraPosition();
    editPointIndex.setMax(spline.GetPointNum());
}

void ofxSplineEditor::updateSpline(){
    if(addCurve) {
        spline.addCurve();
        this->addCurve = false;
    }
}

void ofxSplineEditor::updateSplineFileSystem(){
    if(fileName == "") return;
    if(savePoints){
        spline.saveSpline(fileName);
        this->savePoints = false;
    }
    if(loadPoints){
        spline.loadSpline(fileName);
        this->loadPoints = false;
    }
}

void ofxSplineEditor::updateSplinePoint(){
    if(!editPointMode || spline.GetPoints().size() <= editPointIndex) return;
    ofVec3f newPoint = spline.GetPoints().at(editPointIndex);
    if(plusX) newPoint.x += adjustScale;
    if(plusY) newPoint.y += adjustScale;
    if(plusZ) newPoint.z += adjustScale;
    if(minusX) newPoint.x -= adjustScale;
    if(minusY) newPoint.y -= adjustScale;
    if(minusZ) newPoint.z -= adjustScale;
    spline.SetControlPoint(editPointIndex, newPoint);
}

void ofxSplineEditor::updateCameraPosition(){
    
    ofVec3f newCameraPos = editorCam.getPosition();
    if(plusCameraX) newCameraPos.x += adjustScale;
    if(plusCameraY) newCameraPos.y += adjustScale;
    if(plusCameraZ) newCameraPos.z += adjustScale;
    if(minusCameraX) newCameraPos.x -= adjustScale;
    if(minusCameraY) newCameraPos.y -= adjustScale;
    if(minusCameraZ) newCameraPos.z -= adjustScale;
    editorCam.setPosition(newCameraPos);
}

BezierSpline * ofxSplineEditor::getSpline(){
    return &spline;
}

void ofxSplineEditor::drawgui(){
    gui.draw();
}

void ofxSplineEditor::draw(){
    //drawMarkPoint();
    ofSetLineWidth(3);
    ofPath line = ofPath();
    line.setStrokeColor(ofColor(255,255,255));
    line.setFilled(false);
    line.setStrokeWidth(strokeWidth);
    float lineSteps = 10.0;
    ofVec3f lineStart = spline.GetPoint(0,1);
    line.moveTo(lineStart);
    for(int index = 1; index <= spline.GetCurveNum(); index++){
        for(int i = 0; i <= lineSteps; i++){
            ofVec3f lineEnd = spline.GetPoint(float(i)/lineSteps, index);
            line.lineTo(lineEnd);
            ofSetColor(0, 255, 0);
            if(drawDirectionButton) ofLine(lineEnd, lineEnd + spline.GetDirection(float(i)/lineSteps, index));
            lineStart = lineEnd;
        }
    }
    line.draw();
    ofSetColor(255, 0, 0);
     for(int i = 0; i < spline.GetPointNum(); i++){
         ofSetColor(spline.modeColors[(int)(spline.GetControlPointMode(i))]);
         if(i == editPointIndex){
             ofSetColor(255, 255, 0);
             ofDrawBox(spline.GetPoints().at(i), pointSize * 3);
         }
         ofDrawBox(spline.GetPoints().at(i), pointSize);
         ofSetColor(255, 200, 100);
         line.setStrokeWidth(1.0);
         if(!drawControlLine) continue;
         if(i % 3 == 1){
             ofLine(spline.GetPoints().at(i), spline.GetPoints().at(i - 1));
         }
         if(i % 3 == 2){
             ofLine(spline.GetPoints().at(i), spline.GetPoints().at(i + 1));
         }
    }
}

void ofxSplineEditor::setFileName(string fileName){
    this->fileName = fileName;
}

void ofxSplineEditor::setStrokeWidth(float width){
    strokeWidth = width;
}

void ofxSplineEditor::beginEditorCam(){
    editorCam.begin();
}

void ofxSplineEditor::endEditorCam(){
    editorCam.end();
}

void ofxSplineEditor::drawMarkPoint(){
    ofSetColor(255, 255, 255, 50);
    for(int x = 0; x < 1000; x += 100){
        for(int y = 0; y < 1000; y +=100){
            for(int z = -500; z < 500; z += 100){
                ofDrawSphere(x, y, z, 3);
            }
        }
    }
}
