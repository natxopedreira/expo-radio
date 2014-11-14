#pragma once

#include "ofMain.h"

#include "click.h"

class infoMp3 {
public:
    string url="nada";
    string txt="nada";
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    click clicks;

    
    ofPoint posicionCentro;
    float time;
    vector<infoMp3> mptreses;
		
};
