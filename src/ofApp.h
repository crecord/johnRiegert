#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxCameraSaveLoad.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void loadFromFile(string fileName);
    
        void transitionCam (int millis);
        bool camTransitioning;
        int startTimeCamTrans;
        ofVec3f endTarget;
        ofVec3f endPosition;
    
        vector<ofMesh> allScribbles;
        vector<ofMesh> allScribblesScaled;
        vector< vector<ofFloatColor> > normColors;
        vector< vector<ofFloatColor> > highlightColors;
    
        ofEasyCam cam;
        int lastNearestIndex;
        int nearestIndex;
    
        bool playingLine;
        int lineToPlay;
        int index;
    
        ofVec3f defaultCamPos;
		
};
