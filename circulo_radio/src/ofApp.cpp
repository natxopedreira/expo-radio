#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(255);
    
    infoMp3 f1;
    f1.txt = "uno";
    f1.url = "uno.mp3";
    
    infoMp3 f2;
    f2.txt = "dos";
    f2.url = "dos.mp3";
    
    infoMp3 f3;
    f3.txt = "tres";
    f3.url = "tres.mp3";
    
    infoMp3 f4;
    f4.txt = "cuatro";
    f4.url = "cuatro.mp3";
    
    infoMp3 f5;
    f5.txt = "cinco";
    f5.url = "cinco.mp3";
    
    infoMp3 f6;
    f6.txt = "seis";
    f6.url = "seis.mp3";
    
    infoMp3 f7;
    f7.txt = "siete";
    f7.url = "siete.mp3";
    
    infoMp3 f8;
    f8.txt = "ocho";
    f8.url = "ocho.mp3";
    
    infoMp3 f9;
    f9.txt = "nueve";
    f9.url = "nueve.mp3";
    
    infoMp3 f10;
    f10.txt = "diez";
    f10.url = "diez.mp3";
    
    infoMp3 f11;
    f11.txt = "once";
    f11.url = "once.mp3";
    
    infoMp3 f12;
    f12.txt = "doce";
    f12.url = "doce.mp3";
    
    infoMp3 f13;
    f13.txt = "trece";
    f13.url = "trece.mp3";
    
    infoMp3 f14;
    f14.txt = "catorce";
    f14.url = "catorce.mp3";
    
    infoMp3 f15;
    f15.txt = "quince";
    f15.url = "quince.mp3";
    
    infoMp3 f16;
    f16.txt = "dieciseis";
    f16.url = "dieciseis.mp3";
    
    infoMp3 f17;
    f17.txt = "diecisiete";
    f17.url = "diecisiete.mp3";
    
    infoMp3 f18;
    f18.txt = "dieciocho";
    f18.url = "dieciocho.mp3";
    
    infoMp3 f19;
    f19.txt = "diecinueve";
    f19.url = "diecinueve.mp3";
    
    infoMp3 f20;
    f20.txt = "veinte";
    f20.url = "veinte.mp3";
    
    mptreses.push_back(f1);
    mptreses.push_back(f2);
    mptreses.push_back(f3);
    mptreses.push_back(f4);
    mptreses.push_back(f5);
    mptreses.push_back(f6);
    mptreses.push_back(f7);
    mptreses.push_back(f8);
    mptreses.push_back(f9);
    mptreses.push_back(f10);
    mptreses.push_back(f11);
    mptreses.push_back(f12);
    mptreses.push_back(f13);
    mptreses.push_back(f14);
    mptreses.push_back(f15);
    mptreses.push_back(f16);
    mptreses.push_back(f17);
    mptreses.push_back(f18);
    mptreses.push_back(f19);
    mptreses.push_back(f20);
    
    
    indiceDial = 0;
    
    
    dialRadio.setDiametro(300);
    dialRadio.setResolucion(14);
    dialRadio.setCentro(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
    
    dialRadio.setup();
    
    mueveDial();
    //pondatosDialUp();
    

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    dialRadio.drawDebug();
}

//--------------------------------------------------------------
void ofApp::mueveDial(){
    int posicion = indiceDial;

    // indiceDial tiene que estar dentro del vector de mpteses
    
    cout << "------------------------------------------->" << endl;
    // recoremos todos los vertices del circulo menos el 0 que es el centro
    for (int i = 1; i < dialRadio.posicionesSize()-1; i++) {
            cout << "mueveDial() posicion" << posicion << endl;
        
            dialRadio.datos.at(i) = mptreses[posicion];
        
            posicion++;
            if(posicion>=mptreses.size()) posicion = 0;
            
        
    }
    cout << "<-------------------------------------------" << endl;
}


//--------------------------------------------------------------
void ofApp::bajaDial(){
    int posicion = indiceDial;
    
    // indiceDial tiene que estar dentro del vector de mpteses
    
    cout << "------------------------------------------->" << endl;
    // recoremos todos los vertices del circulo menos el 0 que es el centro
    for (int i = 1; i < dialRadio.posicionesSize()-1; i++) {
        cout << "bajaDial() posicion" << posicion << endl;
        if(posicion <= 0 || posicion>=mptreses.size()) posicion = 0;
        
        
        dialRadio.datos.at(i) = mptreses[posicion];
        
        posicion++;
        
    }
    cout << "<-------------------------------------------" << endl;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == 356){
        indiceDial ++;
        
        // si esta al final del vector vuelve al 0
        if(indiceDial>= mptreses.size()) indiceDial = 0;
        
        mueveDial();
        
        /*if(indiceDial >= mptreses.size()-1){
            indiceDial = 0;
        }else{
            indiceDial ++;
        }
     
        pondatosDialUp();
        */
    }
    
    if(key == 358){
        indiceDial --;
        
        // si esta al inicio pasa a ser el ultimo del vector para ir patras
        if(indiceDial < 0) indiceDial = mptreses.size()-1;
        
        bajaDial();
        
        /*
        if(indiceDial<=0){
            indiceDial = 0;
        }else{
            indiceDial --;
        }
        
        pondatosDialDown();
        */
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