#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofxLoadCamera(cam, "ofEasyCamSettings");
    defaultCamPos = cam.getPosition();
    loadFromFile("hand.json");
    lastNearestIndex = -1;
    nearestIndex = 0;
    playingLine = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    

    
    
    if(!playingLine & !camTransitioning){
        
        ofVec3f curCamPos = cam.getPosition();
        cam.setPosition((mouseX - curCamPos.x) * .05, (-mouseY + 200 - curCamPos.y) * .05, curCamPos.z);
        cam.setTarget(ofVec3f(0,0,0));
        
        float nearestDistance = 0;
        ofVec2f nearestVertex;
        ofVec2f mouse(mouseX, mouseY);
        
        for(int i=0; i < allScribbles.size(); i++){
            for(int y = 0; y < allScribbles.at(i).getNumVertices(); y++) {
                ofVec3f cur = cam.worldToScreen(allScribbles.at(i).getVertex(y));
                float distance = cur.distance(mouse);
                bool isFirst = i == 0 & y == 0;
                
                if( isFirst || distance < nearestDistance) {
                    nearestDistance = distance;
                    nearestVertex = cur;
                    nearestIndex = i;
                }
            }
        }
        
        if(lastNearestIndex != nearestIndex){
            if (lastNearestIndex > -1){
                allScribbles.at(lastNearestIndex).clearColors();
                allScribbles.at(nearestIndex).addColors(normColors.at(nearestIndex));
            }
            allScribbles.at(nearestIndex).clearColors();
            allScribbles.at(nearestIndex).addColors(highlightColors.at(nearestIndex));
        }
        lastNearestIndex = nearestIndex; 
    }
    else if (playingLine & !camTransitioning){
        if(index < allScribbles.at(lineToPlay).getNumVertices()){
            cam.setPosition(allScribblesScaled.at(lineToPlay).getVertex(index));
            cam.setTarget(allScribbles.at(lineToPlay).getVertex(index));
            allScribbles.at(lineToPlay).setColor(index, ofFloatColor(1,1,1));
            index ++;
        }
        else{
            
            endTarget = allScribbles.at(lineToPlay).getVertex(index-1);
            endPosition = allScribblesScaled.at(lineToPlay).getVertex(index-1);
            ofVec3f endPosition;
            playingLine = false;
            index = 0;
            startTimeCamTrans = ofGetElapsedTimeMillis();
            camTransitioning = true;
            //
        }
    }
    else{
        transitionCam(5000);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    for(int i=0; i< allScribbles.size(); i++){
        allScribbles.at(i).draw();
        //allScribblesScaled.at(i).draw();
    }
    ofDrawEllipse(0, 0, 20, 20);
    cam.end();
}


void ofApp::loadFromFile(string fileName){
    ofxJSONElement resultScribble;
    resultScribble.clear();
    bool parsingSuccessful2 = resultScribble.open(fileName);
    if (!parsingSuccessful2)
    {
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << endl;
    }
    else{
        
        
        
        ofLog() << "size: " << resultScribble["scribbles"].size();
        
        for (int i=0; i < resultScribble["scribbles"].size(); i++){
            if(resultScribble["scribbles"][i]["line"].size() > 50){
            int count = 0;
            ofMesh Temp;
            Temp.clear();
            Temp.setMode(OF_PRIMITIVE_POINTS);
            vector<ofFloatColor> normColorTemp;
            vector<ofFloatColor> highColorTemp;
            ofMesh TempScaled;
            TempScaled.clear();
            TempScaled.setMode(OF_PRIMITIVE_POINTS);
            for (int y = 0; y < resultScribble["scribbles"][i]["line"].size(); y+=3){
                ofVec3f pos = ofVec3f(resultScribble["scribbles"][i]["line"][y].asFloat(),resultScribble["scribbles"][i]["line"][y+1].asFloat(), resultScribble["scribbles"][i]["line"][y+2].asFloat());
                Temp.addVertex(pos);
                Temp.addIndex(count);
                Temp.addColor(ofFloatColor(1,1,1));
                TempScaled.addVertex(pos *1.5 );
                TempScaled.addIndex(count);
                TempScaled.addColor(ofFloatColor(0,0,1));
                normColorTemp.push_back(ofFloatColor(1,1,1));
                highColorTemp.push_back(ofFloatColor(1,0,0));
                count ++;
            }
            allScribblesScaled.push_back(TempScaled);
            allScribbles.push_back(Temp);
            normColors.push_back(normColorTemp);
            highlightColors.push_back(highColorTemp);
            }
        }
        
        ofLog() << "size: " << allScribbles.size();
        
    }
}

void ofApp::exit(){
    ofxSaveCamera(cam, "ofEasyCamSettings");
    
}


void ofApp::transitionCam (int millis){
    // map the current time between
    float transPercent;
    transPercent = ofMap(ofGetElapsedTimeMillis() , startTimeCamTrans, startTimeCamTrans + millis , 0, 1);
    
    if (transPercent < 1){
        // transition the camera
        ofVec3f inBetweenPos = ofVec3f(ofMap(transPercent, 0, 1, endPosition.x, defaultCamPos.x),ofMap(transPercent, 0, 1, endPosition.y, defaultCamPos.y),ofMap(transPercent, 0, 1, endPosition.z, defaultCamPos.z));
    }
    else{
        // this transition is over!
        camTransitioning = false;
        cam.setPosition(defaultCamPos);
        cam.setTarget(ofVec3f(0,0,0));
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    playingLine = true;
    lineToPlay = nearestIndex;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
