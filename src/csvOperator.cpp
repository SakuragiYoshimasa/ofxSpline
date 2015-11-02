//
//  csvOperator.cpp
//  ofSplineSample
//
//  Created by SakuragiYoshimasa on 2015/11/01.
//
//

#include "csvOperator.h"

void csvOperator::saveSplinePoints(string fileName, vector<ofVec3f> points){
    fileName += ".csv";
    string csv = "";
    for(int i = 0; i < points.size(); i++){
        csv += (ofToString(points[i].x) + ",");
        csv += (ofToString(points[i].y) + ",");
        csv += (ofToString(points[i].z) + "\n");
    }
    ofBuffer buffer = ofBuffer(csv);
    ofBufferToFile(fileName, buffer);
}

vector<ofVec3f> csvOperator::loadSplinePoints(string fileName){
    fileName += ".csv";
    vector<ofVec3f> points;
    ofFile file(fileName);
    ofBuffer buffer(file);
    while (!buffer.isLastLine()) {
        string line = buffer.getNextLine();
        vector<string> pointData = ofSplitString(line, ",");
        points.push_back(*new ofVec3f(ofToFloat(pointData[0]), ofToFloat(pointData[1]),ofToFloat(pointData[2])));
    }
    return points;
}

