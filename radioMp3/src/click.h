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
#include "datos.h"
#include "ofxFTGL.h"
#include "snapshot.h"
#define GRAD_PI 180.000/PI

/*
 crea las posiciones por donde se puede mover el dial
 */

enum coleccionSintonizada{
    museoRadio,
    radioGalega,
    historicos,
    publicidad,
    
};



class emisora{
public:
    ofPoint posicion;
    float angulo;
    int numero;
    int pClick;
    infoMp3 mpTres;
};

class click {
public:
    
    void setup();
    void update();
    void draw();
    void drawCanales();
    void exit();
    
    void cambiaCanales(int _in);
    int dimeIndexMp3(string _mp3);
    
    void avanza();
    void retrocede();
    void cargaDatos(coleccionSintonizada _col);
    
    int getGradosGiro();
    
    ofPoint getClick();
    ofPoint getClickSinOffset();
    ofPoint posicionOffset;
    
    int numClicksDial;
    int numeroCanales;
    int diametro;
    int anchoCajaTexto;
    int gradosGiro;
    int cuadradoAudio;
    
    ofImage dialAzul, dialVerde, dialNaranja, dialGris;
    
    ofSoundPlayer sonidoRuido;
    ofSoundPlayer sonidoEmisora;
    
    
    coleccionSintonizada dimeCanal();
    
    
private:
    float getAngle(float _x, float _y,float _x0, float _y0);
    void rotaDial();
    void ajustaVolumen();
    void dibujaVolumen();
    
    
    ofVec2f getOffset( string s , bool bold );
    
    ofPoint clickActual;
    ofPoint clickActualSinOffet;
    
    vector<ofRectangle> rectVolumen;
    vector<ofRectangle> rectVolumenUp;
    
    ofxFTGLSimpleLayout fontArea, fontAreaBold, fontAreaSmall, fontAreaId, fontAreaYear;
    
    int lastAudio;
    int lastAguja;
    int indexClick;
    int posListaMp3;
    int direccion;
    int indesPlayList;
    
    float anguloActual;
    
    bool sintonizada;
    
    ofPath circuloClicks;
    
    ofPolyline lineaClicks;
    
    // lisda de emisoras visibles
    vector<emisora> canales;
    
    // lista con los clicks del dial
    vector<ofPoint> clicks;
    
    coleccionSintonizada cadenaSintonizada;
    
    datos data;
    
    snapshot fotosUsuarios;
};

#endif /* defined(__dialRota__click__) */