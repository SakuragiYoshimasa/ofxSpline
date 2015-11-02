#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    editor = *new ofxSplineEditor();
    editor.setup();
    editor.setFileName("testPoint");
    walker.setup(editor.getSpline(), 5);
    walker.setMode(PINGPONG);
    walker.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    editor.update();
    walker.update();
    if(walkerMode){
        walkerCamera.setPosition(walker.getPosition());
        walkerCamera.lookAt(walker.getLookAt());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    editor.drawgui();
    if(walkerMode){
        walkerCamera.begin();
    }else{
        editor.beginEditorCam();
    }
    editor.draw();
    ofSetColor(255, 0, 0);
    if(walkerMode) ofSetColor(200, 0, 0,100);
    ofDrawBox(walker.getPosition(), 10);
    if(walkerMode){
        walkerCamera.end();
    }else{
        editor.endEditorCam();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') walkerMode = !walkerMode;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mouseX = x;
    mouseY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
