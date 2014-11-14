//
//  dial.cpp
//  circulo_radio
//
//  Created by mindSlot on 12/11/14.
//
//

#include "dial.h"

dial::dial(){
    resolucionCirculo = 14;
    diametroCirculo = 400;
    
    centro.set(ofGetWidth()/2, ofGetHeight()/2);
    
}

void dial::setup(){
    
    trazadoCirculo.circle(centro, diametroCirculo);
    trazadoCirculo.setCircleResolution(resolucionCirculo);
    
    polylineTrazado = trazadoCirculo.getOutline().at(0);
    
    
    /// fuenteSmall
    fuenteSmall.loadFont("../../../sharedData/weblysleek_ui/weblysleekuil.ttf", 18, true, true, true);
    fuenteSmall.setLetterSpacing(1);
    fuenteSmall.setSpaceSize(.5);
    
    // fuenteDestacado
    fuenteDestacado.loadFont("../../../sharedData/weblysleek_ui/weblysleek_ui/weblysleekuisb.ttf", 20, true, true, true);
    fuenteDestacado.setLetterSpacing(1);
    fuenteDestacado.setSpaceSize(.5);
    
    
    // todos los vertices del circulo
    for (int i = 0; i < polylineTrazado.getVertices().size(); i++) {
        
        // vertice circulo
        ofPoint verticeTrazado = polylineTrazado.getVertices().at(i);
        
        // vertice centro
        ofPoint centroTrazado = polylineTrazado.getCentroid2D();
        
        // angulo
        float angle = getAngle(verticeTrazado.x, verticeTrazado.y, centroTrazado.x, centroTrazado.y);
        
        // posicion
        posicion p;
        p.vertice = verticeTrazado;
        p.angulo = angle;
        
        posiciones.push_back(p);
        
    }
    
    // si hay mas vertices que posiciones, cambias el tamaño
    datos.resize(posiciones.size());
    /*if(posiciones.size() > datos.size()){
        datos.resize(posiciones.size());
    }*/
    
    ofSetCircleResolution(48);
    


    cout << "dial::setup posiciones.size()" << posiciones.size() << endl;

}




//--------------------------------------------------------------
void dial::setResolucion(int r){
    resolucionCirculo = r;
}

//--------------------------------------------------------------
void dial::setDiametro(int d){
    diametroCirculo = d;
}


//--------------------------------------------------------------
void dial::drawDebug(){
    ofSetColor(255, 250, 237);
    ofCircle(centro, diametroCirculo + 20);

    
    
    //ofPushMatrix();
    //ofTranslate(centro);
    //ofSetRectMode(OF_RECTMODE_CENTER);
    //ofRotate(30);
    
    // quesitos
    
    /// ponemos la info de los mp3les
    for (int i = 1; i < posiciones.size()-1; i++) {

        ofPoint p = posiciones.at(i).vertice;
        float a = posiciones.at(i).angulo;
        int indiceMp3 = i;
        
        ofRectangle rectSmall = fuenteSmall.getStringBoundingBox(ofToString(i), 0, 0);
        
        
        //ponle unas lineas
        ofSetColor(204, 194, 167);
        //ofLine(p, centro);
        
        
        // textos
        ofSetColor(0, 0, 0);
        
        ofPushMatrix();
            ofTranslate(p);
            ofScale(-1,-1);
            ofRotate(a);
        
        if(i == 8) ofSetColor(255, 0, 0);
        
            //fuenteSmall.drawStringAsShapes(ofToString(i), 0, 0);
            fuenteSmall.drawStringAsShapes(ofToString(datos[indiceMp3].url), 0, 0);
        
        ofPopMatrix();
        
    }
    
    //ofPopMatrix();
    
    
    ofSetColor(255, 255, 255, 180);
    ofRect(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
    
    
    
    
}
//--------------------------------------------------------------
void dial::setCentro(ofPoint p){
    centro = p;
}

//--------------------------------------------------------------
int dial::posicionesSize(){
    return posiciones.size();
}

//--------------------------------------------------------------
float dial::anguloPosicion(int indes){
    return posiciones.at(indes).angulo;
}


//--------------------------------------------------------------
ofPoint dial::verticePosicion(int indes){
    return  posiciones.at(indes).vertice;
}

//--------------------------------------------------------------
float dial::getAngle(float _x, float _y,float _x0, float _y0) {
    if (_x-_x0 == 0.0) {
        if(_y-_y0 < 0.0)
            return 270;
        else
            return 90;
    } else if (_y-_y0 == 0) {
        if(_x-_x0 < 0)
            return 180;
        else
            return 0;
    }
    
    if ( _y-_y0 > 0.0)
        if (_x-_x0 > 0.0)
            return atan((_y-_y0)/(_x-_x0)) * GRAD_PI;
        else
            return 180.0 - (atan((_y-_y0)/-(_x-_x0)) * GRAD_PI);
        else
            if (_x-_x0 > 0.0)
                return 360.0 - (atan(-(_y-_y0)/(_x-_x0)) * GRAD_PI);
            else
                return 180.0 + (atan(-(_y-_y0)/-(_x-_x0)) * GRAD_PI);
}