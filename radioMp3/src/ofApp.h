#pragma once

#include "ofMain.h"

#include "click.h"

#include "ofxPowerMate.h"

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void onPowerMateData(powerData & d);
    
    click clicks;

    ofImage lineasGordas;
    ofImage mascara;
    ofImage fondoAzul, fondoVerde, fondoNaranja, fondoGris;
    ofImage botoneraOff, botoneraOn;
    
    ofxPowerMate powerMate;
    ofxFTGLSimpleLayout fuenteMenu;
    
    ofSoundPlayer sonidoBoton;
    
    ofPoint posicionCentro;
    float time;
};
