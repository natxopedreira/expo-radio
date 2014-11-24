#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    powerMate.conecta();
    ofAddListener(powerMate.tengoInfo, this, &ofApp::onPowerMateData);
    
    intensidad = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::onPowerMateData(powerData & d){
    cout << "onPowerMateData "  << d.direccion << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key == 'p'){
        powerMate.apaga();
    }
    if(key == 'e'){
        powerMate.enciende();
    }
    
    if(key == 'i'){
        powerMate.setBrillo(255);
    }
    if(key == 'o'){
        powerMate.setBrillo(10);
    }
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
