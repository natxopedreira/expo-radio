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
    // los llenamos
    for (int i = 0; i < numeroCanales; i++) {
        int iClick = i*numClicksDial/numeroCanales;
        
        emisora m;
        m.posicion = clicks.at(iClick);
        m.angulo = getAngle(clicks[iClick].x, clicks[iClick].y, 0, 0);
        m.numero = i;
        m.pClick = iClick;
        
        canales.push_back(m);
    }
    
    // tipografia
    fuente.loadFont("../../../sharedData/weblysleek_ui/weblysleekuil.ttf", 8, true, true, true);
    font.loadFont("../../../sharedData/weblysleek_ui/weblysleekuil.ttf", 8);
    
    
    /// metemos los datos de mp3 dentro de lel vector de emisoras
    /// movemos el dial una vuelta entera
    
    for (int m = 0; m < data.mptreses.size(); m++) {
        if(m<canales.size()) canales.at(m).mpTres = data.mptreses.at(m);

    }
    
    
    /// cuando arranca pillamos el index del que esta en 180º
    posListaMp3 =  9;
    
    
}

//--------------------------------------------------------------
void click::update(){
    
    
    
    
    
    
    
    
    
    
    //cada vez que se suma uno
    
    
    // calculamos el angulo actual
    anguloActual = getAngle(clicks[indexClick].x, clicks[indexClick].y, 0, 0);
    
    // calculamos el punto actual donde esta la bola
    clickActual = clicks[indexClick] + posicionOffset;
    
    // posicion de la bola sin offset
    clickActualSinOffet = clicks[indexClick];
    
    // mueve el dial
    rotaDial();
    
    

}
//--------------------------------------------------------------
void click::avanza(){
    indexClick++;
    // alante
    if(indexClick>=clicks.size()-1) indexClick = 0;
}
//--------------------------------------------------------------
void click::retrocede(){
    indexClick--;
    //atras
    if(indexClick<0) indexClick = clicks.size()+indexClick;
}
//--------------------------------------------------------------
void click::rotaDial(){
    // posicionamos la lista de canales contando con el indexClick que es lo que va aumentando o disminuendo con el rotary
    for (int i = 0; i < canales.size(); i++) {
        int in = indexClick + numClicksDial/numeroCanales*i;
        
        if(in>clicks.size()-1) in = indexClick + numClicksDial/numeroCanales*i - numClicksDial;
        
        canales.at(i).posicion = clicks[in];
        canales.at(i).angulo = getAngle(clicks[in].x, clicks[in].y, 0, 0);
        
        // si hay un canal dentro del rango de sintonizar way aviso
        if((int)canales.at(i).angulo == 0){
            //cout << "deeeeentro" << endl;
            //cambiaCanales(i);
        }
    }
    
   
}

//--------------------------------------------------------------
void click::cambiaCanales(int _in){
    // la sintonizada esta en 0º
    // la de arriba en 260º
    // la de abajo en 100º
    
    // la de arriba toma la referencia de la de 280º
    // la de abajo toma la referencia de la de 80º
    
    int indexCanalArribaCambiar = 0;
    int indexCanalAbajoCambiar = 0;

    string urlArriba = "";
    string urlAbajo = "";
    
    for (int i = 0; i < canales.size(); i++) {
        
        if((int)canales.at(i).angulo > 258 && (int)canales.at(i).angulo < 262){
            // 260º
            indexCanalArribaCambiar = i;
        
        }else if ((int)canales.at(i).angulo > 98 && (int)canales.at(i).angulo < 102){
            // 100º
            indexCanalAbajoCambiar = i;
        
        }else if ((int)canales.at(i).angulo > 278 && (int)canales.at(i).angulo < 282){
            //280º
            urlArriba = canales.at(i).mpTres.url;
            
        }else if ((int)canales.at(i).angulo > 78 && (int)canales.at(i).angulo < 82){
            // 80º
            urlAbajo = canales.at(i).mpTres.url;
        }
    }
    
    /////////////
    
    int anteriorArribaData = 0; // valor previo al que tiene
    int siguienteAbajoData = 0; // valor siguiente al que tiene
    
    for (int d = 0; d < data.mptreses.size(); d++) {
        
        if (data.mptreses.at(d).url == urlArriba){
            anteriorArribaData = d-1;
        }else if (data.mptreses.at(d).url == urlAbajo){
            siguienteAbajoData = d+1;
        }
        
    }
    
    if (anteriorArribaData<0){
        cout << "excepcion !!!!" << endl;
        
        
        cout << "anteriorArribaData antes " << anteriorArribaData << endl;
        
        anteriorArribaData = data.mptreses.size()+anteriorArribaData;
        
        cout << "anteriorArribaData despues " << anteriorArribaData << endl;
        cout << "canales.at(indexCanalArribaCambiar).mpTres " << canales.at(indexCanalArribaCambiar).mpTres.url << endl;
    }
    
    
    cout << "anteriorArribaData " << anteriorArribaData << endl;
    
    if (siguienteAbajoData<0 || siguienteAbajoData>data.mptreses.size()) siguienteAbajoData = 0;
    
    //cout << "urlArriba " << urlArriba << " donde " << canales.at(indexCanalArribaCambiar).mpTres.url << " ahora " << data.mptreses.at(anteriorArribaData).url<< endl;
    
    canales.at(indexCanalArribaCambiar).mpTres = data.mptreses.at(anteriorArribaData);
    canales.at(indexCanalAbajoCambiar).mpTres = data.mptreses.at(siguienteAbajoData);
    
    
    
    
}

//--------------------------------------------------------------
int click::dimeIndexMp3(string _mp3){
    for (int i = 0;  i < canales.size(); i++) {
        if(canales.at(i).mpTres.url == _mp3) return i;
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
            if((int)canales.at(i).angulo ==260 || (int)canales.at(i).angulo ==100) ofSetColor(255,0,50);
        
            ofTranslate(canales.at(i).posicion);
            ofRotate((int)canales.at(i).angulo);
        
            font.drawString(canales.at(i).mpTres.txt + " :: " + ofToString(canales.at(i).mpTres.url) + " :: " + ofToString((int)canales.at(i).angulo), 0, 0);
            //font.drawString("Emisora " + ofToString(i), 0, 0);
            //fuente.drawStringAsShapes("EMISORA " + ofToString(i), 0, 0);
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