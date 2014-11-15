#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofEnableAntiAliasing();
    ofSetVerticalSync(true);
    
    // cada dos grados hay un click
    clicks.numClicksDial = 180;
    clicks.numeroCanales = 10;
    clicks.diametro = 500;
    clicks.anchoCajaTexto = 150;
  
    // le decimos el offset para que nos de posiciones relativas a el
    posicionCentro = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
    clicks.posicionOffset = posicionCentro;
    clicks.setup();
    

    time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(ofGetElapsedTimef()>time+.2){
        
        time = ofGetElapsedTimef();
    }
    
    clicks.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
        ofTranslate(1300, ofGetHeight()/2);
        ofScale(0.5, 0.5);
        clicks.draw();
    ofPopMatrix();
    
    ofPushMatrix();
        //dial de la radio
        ofTranslate(400, ofGetHeight()/2);
        clicks.drawCanales();
    ofPopMatrix();
    
    ofSetColor(255,190);
    ofRect(0, 0, 400, ofGetHeight());
    
    
    
    
    
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
