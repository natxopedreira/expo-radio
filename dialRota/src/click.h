//
//  click.h
//  dialRota
//
//  Created by Natxo Pedreira gonzalez on 13/11/14.
//
//

#ifndef __dialRota__click__
#define __dialRota__click__

#include "ofMain.h"
#define GRAD_PI 180.000/PI

/*
 crea las posiciones por donde se puede mover el dial
 */

class emisora{
public:
    ofPoint posicion;
    float angulo;
    int numero;
    int pClick;
};

class click {
public:
    
    void setup();
    void update();
    void draw();
    void drawCanales();
    
    ofPoint getClick();
    ofPoint getClickSinOffset();
    
    ofPoint posicionOffset;
    int numClicksDial;
    
private:
    float getAngle(float _x, float _y,float _x0, float _y0);
    
    ofPoint clickActual;
    ofPoint clickActualSinOffet;
    
    ofTrueTypeFont fuente;
    
    float anguloActual;
    int indexClick;
    
    ofPath circuloClicks;
    ofPolyline lineaClicks;
    
    // lisda de emisoras visibles
    vector<emisora> canales;
    
    // lista con los clicks del dial
    vector<ofPoint> clicks;
    
    
};

#endif /* defined(__dialRota__click__) */
