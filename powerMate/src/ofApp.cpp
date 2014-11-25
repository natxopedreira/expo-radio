#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    powerMate.conecta();
    
    
    intensidad = 0;
    
    
    gui.setup();
    gui.add(brillo.setup("brillo", 0, 0, 255));
    
    ofAddListener(powerMate.tengoInfo, this, &ofApp::onPowerMateData);
   
}

//--------------------------------------------------------------
void ofApp::update(){
    powerMate.setBrillo(brillo);
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::onPowerMateData(powerData & d){
    cout << "onPowerMateData direccion "  << d.direccion << endl;
    cout << "onPowerMateData presionado "  << d.presionado << endl;
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
