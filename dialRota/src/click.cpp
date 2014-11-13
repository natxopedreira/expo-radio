//
//  click.cpp
//  dialRota
//
//  Created by Natxo Pedreira gonzalez on 13/11/14.
//
//

#include "click.h"


void click::setup(){

    // hacemos un circulo con ofPath y luego le marcamos la resolucion
    circuloClicks.circle(0, 0, 250);
    circuloClicks.setCircleResolution(numClicksDial);
    
    // copiamos el exterior a una polylinea
    lineaClicks = circuloClicks.getOutline()[0];
    
    // borramos el vertice que es el centro
    for (int i = 0; i < lineaClicks.getVertices().size(); i++) {
        if(lineaClicks.getVertices().at(i) == ofPoint(0,0)){
         lineaClicks.getVertices().erase(lineaClicks.getVertices().begin()+i);
        }
    }
    
    // lenamos el vector con los clicks por donde se van a mover el dial
    for (int i = 0; i < lineaClicks.getVertices().size(); i++) {
        clicks.push_back(lineaClicks.getVertices().at(i));
    }
    
    // los canales representan la lisda de emisoras visibles
    // los llenamos solo con la posicion
    for (int i = 0; i < 18; i++) {
        int iClick = i*numClicksDial/18;
        
        emisora m;
        m.posicion = clicks.at(iClick);
        m.angulo = getAngle(clicks[iClick].x, clicks[iClick].y, 0, 0);
        m.numero = i;
        m.pClick = iClick;
        
        canales.push_back(m);
    }
    
    // tipografia
    fuente.loadFont("weblysleek_ui/weblysleekuil.ttf", 8, true, true, true);
    
}

//--------------------------------------------------------------
void click::update(){
    if(indexClick>=clicks.size()-1) indexClick = 0;
    
    indexClick++;
    //cada vez que se suma uno
    
    
    // calculamos el angulo actual
    anguloActual = getAngle(clicks[indexClick].x, clicks[indexClick].y, 0, 0);
    
    // calculamos el punto actual donde esta la bola
    clickActual = clicks[indexClick] + posicionOffset;
    
    // posicion de la bola sin offset
    clickActualSinOffet = clicks[indexClick];
    
    
    // posicionamos la lista de canales contando con el indexClick que es lo que va aumentando o disminuendo con el rotary
    for (int i = 0; i < canales.size(); i++) {
        int in = indexClick + 10*i;
        
        if(in>clicks.size()-1) in = indexClick + 10*i - numClicksDial;
        
        canales.at(i).posicion = clicks[in];
        canales.at(i).angulo = getAngle(clicks[in].x, clicks[in].y, 0, 0);
        
        // si hay un canal dentro del rango de sintonizar way aviso
        if((int)canales.at(i).angulo == 0){
            cout << "deeeeentro" << endl;
        }
    }
    

}

//--------------------------------------------------------------
void click::draw(){

    // looop por todos los clicks
    ofPushStyle();
    
    for (int i = 0; i < clicks.size()-1; i++) {
        ofSetColor(255, 0, 0);
        ofCircle(clicks.at(i), 2);
        ofSetColor(150);
        ofLine(0, 0, lineaClicks.getVertices().at(i).x, lineaClicks.getVertices().at(i).y);
        ofSetColor(50);
        ofDrawBitmapString(ofToString(i), clicks.at(i));
    }

    // 
    ofSetColor(255, 0, 0);
    ofCircle(clicks[indexClick], 20);
    
    // angulo del dial
    ofSetColor(0);
    ofLine(clicks[indexClick].x, clicks[indexClick].y, 0, 0);
    
    // numero de clicks disponibles
    ofDrawBitmapString("num de clicks " + ofToString(numClicksDial), ofPoint(0,0));
    
    // angulo actual del dial
    ofDrawBitmapString("angulo " + ofToString((int)anguloActual), ofPoint(0,20));
    
    // posicion x e y del dial
    ofDrawBitmapString("posicion x:" + ofToString((int)clickActualSinOffet.x) + " y:" + ofToString((int)clickActualSinOffet.y), ofPoint(0,40));
    
    ofPopStyle();
}

//--------------------------------------------------------------
void click::drawCanales(){
    
    // looop para los canales
    ofPushStyle();
    
    for (int i = 0; i < canales.size(); i++) {
        ofSetColor(0);
        ofLine(canales.at(i).posicion, ofPoint(0,0));
        
        ofPushMatrix();
            if((int)canales.at(i).angulo ==0) ofSetColor(0,255,50);
        
            ofTranslate(canales.at(i).posicion);
            ofRotate(canales.at(i).angulo);
            fuente.drawStringAsShapes("EMISORA " + ofToString(i), 0, 0);
        ofPopMatrix();
    }
    
    ofPopStyle();
}


//--------------------------------------------------------------
ofPoint click::getClick(){
    return clickActual;
}

//--------------------------------------------------------------
ofPoint click::getClickSinOffset(){
    return  clickActualSinOffet;
}

//--------------------------------------------------------------
float click::getAngle(float _x, float _y,float _x0, float _y0) {
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