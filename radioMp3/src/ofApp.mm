#include "ofApp.h"


/*
coleccionSintonizada
 
 museoRadio
 radioGalega
 historicos
 publicidad
 
 */


//#define USE_POWERMATE

//--------------------------------------------------------------
void ofApp::setup(){
  
    
    CGCaptureAllDisplays();
    NSWindow * window = (NSWindow *)ofGetWindowPtr()->getCocoaWindow();
    [window setLevel:CGShieldingWindowLevel()];
    
    
    
  

    
    
    

    ofSetDataPathRoot("../Resources/data/");
    
    
    ofHideCursor();
    
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
    mascara.loadImage("mascara_2_blur.png");
    fondoAzul.loadImage("azul.jpg");
    fondoVerde.loadImage("verde.jpg");
    fondoNaranja.loadImage("naranja.jpg");
    fondoGris.loadImage("gris.jpg");
    lineasGordas.loadImage("lineas-gordas.png");
    
    // csv con las cuñas
    //clicks.cargaDatos(museoRadio);
    
    //powerMate
    powerMate.conecta();
    ofAddListener(powerMate.tengoInfo, this, &ofApp::onPowerMateData);
    
    
    //iniciamos en museoRadio
    clicks.cargaDatos(museoRadio);
    
    
    botoneraOff.loadImage("botones-cadenas.png");
    botoneraOn.loadImage("botones-cadenas-ON.png");
    
    
    fuenteMenu.loadFont("System San Francisco Display Ultralight.ttf", 15);
    fuenteMenu.setLineLength(300);
   
    
    sonidoBoton.loadSound("mac-sound-pack-funk.mp3");
    //sonidoBoton.setLoop(OF_LOOP_NONE);
    //sonidoBoton.setMultiPlay(false);
    sonidoBoton.setVolume(255);
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
    
    
    switch (clicks.dimeCanal()) {
        case museoRadio:
            fondoAzul.draw(-250,-50);
            break;
            
        case radioGalega:
            fondoVerde.draw(-250,-50);
            break;
            
        case historicos:
            fondoNaranja.draw(-250,-50);
            break;
            
        case publicidad:
            fondoGris.draw(-250,-50);
            break;
    }
    
    
    
    ofPushMatrix();
    
    
        ofTranslate(960, ofGetHeight()-40);
    
    
        ofRotate(clicks.getGradosGiro());
    
    switch (clicks.dimeCanal()) {
        case museoRadio:
                clicks.dialAzul.draw((clicks.dialAzul.getWidth()/2 * -1) , clicks.dialAzul.getHeight()/2 * -1);
            break;
            
        case radioGalega:
                clicks.dialVerde.draw((clicks.dialAzul.getWidth()/2 * -1) , clicks.dialAzul.getHeight()/2 * -1);
            break;
            
        case historicos:
                clicks.dialNaranja.draw((clicks.dialAzul.getWidth()/2 * -1) , clicks.dialAzul.getHeight()/2 * -1);
            break;
            
        case publicidad:
                clicks.dialGris.draw((clicks.dialAzul.getWidth()/2 * -1) , clicks.dialAzul.getHeight()/2 * -1);
            break;
    }
    
    //clicks.dialAzul.draw((clicks.dialAzul.getWidth()/2 * -1) , clicks.dialAzul.getHeight()/2 * -1);
    
    
    ofPopMatrix();
    
    ofPushMatrix();
        ofTranslate(960, ofGetHeight()-40);
        ofRotate(270);
        clicks.drawCanales();
    ofPopMatrix();
    
    
    // dial rojo
    ofPushStyle();
    
    ofPolyline pl;
    pl.addVertex(ofPoint(960, ofGetHeight()-40));
    pl.addVertex(ofPoint(ofGetWidth()/2,0));
    
    ofSetColor(200,0,0);
    ofLine(pl.getPointAtLength(374), (ofPoint(ofGetWidth()/2,160)));
    ofPopStyle();
    
    // lineas decoracion
    lineasGordas.draw(0,120);
    
    
    // mascara
    mascara.draw(0, 0);
    
    
    // botonera cadenas
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(1580, 375);
    ofRotate(270);
    
    ofSetColor(255);
    botoneraOff.draw(0, 0, botoneraOff.getWidth()+80, botoneraOff.getHeight()-7);
    
    // textos
    
    
    int posY = 0;
    int cual = 0;
    
    switch (clicks.dimeCanal()) {
        case museoRadio:
            posY = 0;
            cual = 0;
            break;
            
        case radioGalega:
            posY = 55;
            cual = 1;
            break;
            
        case historicos:
            posY = 55*2;
            cual = 2;
            break;
            
        case publicidad:
            posY = 55*3;
            cual = 3;
            break;
    }
    
    
    
    
    botoneraOn.draw(0, posY, botoneraOn.getWidth()+80, botoneraOn.getHeight()-7);
    
    
    if(cual == 0){
        ofSetColor(255);
    }else{
        ofSetColor(20);
    }
    fuenteMenu.drawString("Museo de la radio", 20, 35);
    
    
    if(cual == 1){
        ofSetColor(255);
    }else{
        ofSetColor(20);
    }
    
    fuenteMenu.drawString("Radio Galega", 20, 91);
    
    if(cual == 2){
        ofSetColor(255);
    }else{
        ofSetColor(20);
    }
    
    fuenteMenu.drawString("Históricas", 20, 145);
    
    
    if(cual == 3){
        ofSetColor(255);
    }else{
        ofSetColor(20);
    }
    
    fuenteMenu.drawString("Publicidad", 20, 201);
    
    ofPopMatrix();
    ofPopStyle();
    
    
}
//--------------------------------------------------------------
void ofApp::onPowerMateData(powerData & d){
    //cout << "onPowerMateData "  << d.direccion << endl;
    
    if(d.direccion==1) clicks.avanza();
    if(d.direccion==255) clicks.retrocede();
    
    // el volumen max de la emisora esta en 0.5
    int v = clicks.sonidoEmisora.getVolume()*100;
    
    powerMate.setBrillo(v);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // 358 alante
    // 356 atras
    
    if(key == 358) clicks.avanza();
    
    
    if(key == 356) clicks.retrocede();
    
    /*
     coleccionSintonizada
     
     museoRadio
     radioGalega
     historicos
     publicidad
     
     */
    if(key == 'w') clicks.cargaDatos(museoRadio); //w
    if(key == 'a') clicks.cargaDatos(radioGalega); //a
    if(key == 'd') clicks.cargaDatos(historicos); //s
    if(key == 's') clicks.cargaDatos(publicidad); //d
    if(key == 'c') ofShowCursor();
    if(key == 'f'){
        // cierras y sales
        exit();
        //system("sudo halt");
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    sonidoBoton.play();
    //cout << "key" << endl;
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

//--------------------------------------------------------------
void ofApp::exit(){
    clicks.exit();
    system("osascript -e 'tell app \"System Events\" to shut down'");
    ofExit();
}