//
//  dial.h
//  circulo_radio
//
//  Created by mindSlot on 12/11/14.
//
//

#ifndef __circulo_radio__dial__
#define __circulo_radio__dial__

#include "ofMain.h"
#define GRAD_PI 180.000/PI

class infoMp3 {
public:
    string url="nada";
    string txt="nada";
};

class posicion{
public:
    float angulo;
    ofPoint vertice;
};


class dial {
    
public:
    dial();
    
    void setResolucion(int r);
    void setDiametro(int d);
    void setCentro(ofPoint p);
    
    void setup();

    void drawDebug();
    
    int posicionesSize();
    float anguloPosicion(int indes);
    ofPoint verticePosicion(int indes);
    
    vector<infoMp3> datos;
    
private:
    float getAngle(float _x, float _y,float _x0, float _y0);
    
    int resolucionCirculo;
    int diametroCirculo;

    ofPath trazadoCirculo;
    
    ofPoint centro;
    
    ofPolyline polylineTrazado;
    
    ofTrueTypeFont fuenteSmall;
    ofTrueTypeFont fuenteDestacado;
    
    vector<posicion> posiciones;
};

#endif /* defined(__circulo_radio__dial__) */
