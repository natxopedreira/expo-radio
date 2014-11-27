#include "ofApp.h"

//#define USE_POWERMATE

//--------------------------------------------------------------
void ofApp::setup(){
    //ofEnableAntiAliasing();
    ofBackground(255);
    ofSetVerticalSync(true);
    
    // cada dos grados hay un click
    clicks.numClicksDial = 180;
    clicks.numeroCanales = 10;
    clicks.diametro = 875;
    clicks.anchoCajaTexto = 150;
  
    // le decimos el offset para que nos de posiciones relativas a el
    posicionCentro = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
    clicks.posicionOffset = posicionCentro;
    clicks.setup();
    
    // time
    time = ofGetElapsedTimef();
    
    // dialog
    mascara.loadImage("../../../sharedData/mascara.png");
    
    //powerMate
    //powerMate.conecta();
    //ofAddListener(powerMate.tengoInfo, this, &ofApp::onPowerMateData);
   
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(ofGetElapsedTimef()>time+.2){ 
        time = ofGetElapsedTimef();
    }
    
    ///
    clicks.update();
//
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
        ofTranslate(960, ofGetHeight());
        ofRotate(clicks.getGradosGiro());
        clicks.dialAzul.draw((clicks.dialAzul.getWidth()/2 * -1) , clicks.dialAzul.getHeight()/2 * -1);
    ofPopMatrix();
    
    ofPushMatrix();
        ofTranslate(960, ofGetHeight());
        ofRotate(270);
        clicks.drawCanales();
    ofPopMatrix();
    
    mascara.draw(0, -150);
    
    
}
//--------------------------------------------------------------
void ofApp::onPowerMateData(powerData & d){
    //cout << "onPowerMateData "  << d.direccion << endl;
    
    if(d.direccion==1) clicks.avanza();
    if(d.direccion==255) clicks.retrocede();
    
    // el volumen max de la emisora esta en 0.5
    int v = clicks.sonidoEmisora.getVolume()*100;
    
    //powerMate.setBrillo(v);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // 358 alante
    // 356 atras
    
    if(key == 358) clicks.avanza();
    
    
    if(key == 356) clicks.retrocede();
    
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
