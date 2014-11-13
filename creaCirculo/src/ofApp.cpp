#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    ofBackground(0,0,0);
    
    
    //circuloClicks
    // creamos un circulo con coordenada 0,0
    
    
    circuloClicks.circle(0, 0, 350);
    circuloClicks.setCircleResolution(90);
    
    
    ofPolyline temp = circuloClicks.getOutline()[0];
    // 90 clicks
    lineaClicks = circuloClicks.getOutline()[0];
    

    
    // borramos el que es el centro
    for (int i = 0; i < lineaClicks.getVertices().size(); i++) {
        if(lineaClicks.getVertices().at(i) == ofPoint(0,0)) lineaClicks.getVertices().erase(lineaClicks.getVertices().begin()+i);
    }
    

    
    for (int i = 0; i < lineaClicks.getVertices().size(); i++) {
        //cout << lineaClicks.getVertices().at(0).x << endl;
        //cout << lineaClicks.getVertices().at(0).y << endl;
        
        clicks.push_back(lineaClicks.getVertices().at(i));
    }
    
    
    // ponemos el primero en el 0
    clickBola = clicks[0];
    indexClick = 0;
    
    
    clickBolaReverse = clicks.at(clicks.size()-1);
    indexCLickReverse = clicks.size()-1;
}

//--------------------------------------------------------------
void ofApp::update(){
    if(indexClick>=clicks.size()-1) indexClick = 0;
    indexClick++;
    
    
    if(indexCLickReverse<=0) indexCLickReverse = clicks.size()-1;
    indexCLickReverse--;
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    //movemos al medio
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    ofSetColor(255, 255, 255);
    // looop para los clicks
    for (int i = 0; i < clicks.size()-1; i++) {
        ofCircle(clicks.at(i), 2);
        ofDrawBitmapString(ofToString(i), clicks.at(i));
        
        ofLine(0, 0, lineaClicks.getVertices().at(i).x, lineaClicks.getVertices().at(i).y);
        
    }
    
    ofSetColor(255, 0, 0);
    ofCircle(clicks[indexClick], 10);
    
    ofSetColor(0, 255, 0);
    ofCircle(clicks[indexCLickReverse], 10);
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
