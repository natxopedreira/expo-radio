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
    circuloClicks.circle(0, 0, diametro);
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
    
    
    // comprueba el volumen
    // los 8 puntos siguientes a 0
    //rectVolumen
    for (int i = 0; i < 8; i++) {
        ofRectangle r;
        r.set(clicks.at(i)-ofPoint(2,2), 5, 5);
        
        rectVolumen.push_back(r);
    }
    
    // los 8 ultimo
    for (int i = 0; i < 8; i++) {
        ofRectangle r;
        r.set(clicks.at((clicks.size()-1) -i)-ofPoint(2,2), 5, 5);
        
        rectVolumenUp.push_back(r);
    }
    
    
    
    
    
    
    // tipografia
    //fuente.loadFont("../../../sharedData/weblysleek_ui/weblysleekuil.ttf", 8, true, true, true);
    //font.loadFont("../../../sharedData/weblysleek_ui/weblysleekuil.ttf", 8);
    
    
    /////
    fontArea.loadFont("System San Francisco Display Ultralight.ttf", 23);
    fontArea.setAlignment(FTGL_ALIGN_RIGHT);
    fontArea.setLineLength(diametro/1.8);
    fontArea.setLineSpacing(.8);
    
    
    cout << fontArea.getTracking() << endl;
    
    //fuentePlayList.loadFont("../../../sharedData/weblysleek_ui/weblysleekuil.ttf", 8);
    //fuentePlaySelect.loadFont("../../../sharedData/weblysleek_ui/weblysleekuisl.ttf", 8);
    
    ////
    fontAreaBold.loadFont("System San Francisco Display Regular.ttf", 23);
    fontAreaBold.setAlignment(FTGL_ALIGN_RIGHT);
    fontAreaBold.setLineLength(diametro/1.2);
    
    fontAreaYear.loadFont("System San Francisco Display Regular.ttf", 14);
    fontAreaYear.setAlignment(FTGL_ALIGN_RIGHT);
    fontAreaYear.setLineLength(diametro/1.2);
    
    fontAreaSmall.loadFont("System San Francisco Display Ultralight.ttf", 14);
    fontAreaSmall.setAlignment(FTGL_ALIGN_RIGHT);
    fontAreaSmall.setLineLength(diametro/1.8);
    fontAreaSmall.setLineSpacing(.8);
    
    
    fontAreaId.loadFont("System San Francisco Display Ultralight.ttf", 45);
    fontAreaId.setAlignment(FTGL_ALIGN_RIGHT);
    fontAreaId.setLineLength(diametro/1.8);
    ///fontAreaId.setLineSpacing(0.0);
    
    
    
    // sonido
    sonidoRuido.loadSound("radioNoise.mp3");
    sonidoRuido.play();
    sonidoRuido.setLoop(true);
    sonidoRuido.setVolume(.5);
    
    
    /// dialAzul de la radio
    dialAzul.loadImage("dialAzul.png");
    dialVerde.loadImage("dialVerde.png");
    dialNaranja.loadImage("dialNaranja.png");
    dialGris.loadImage("dialGris.png");
    
    // snapshots
    fotosUsuarios.setup("/Users/natxo/Desktop/fotos/radioMp3_");
    
}

//--------------------------------------------------------------
void click::cargaDatos(coleccionSintonizada _col){
    
    string _urlCsv ="";
    
    switch (_col) {
        case museoRadio:
            _urlCsv = "naranja.csv";
            cadenaSintonizada = museoRadio;
            break;
            
        case radioGalega:
            _urlCsv = "azul.csv";
            cadenaSintonizada = radioGalega;
            break;
            
        case historicos:
            _urlCsv = "verde.csv";
            cadenaSintonizada = historicos;
            break;
            
        case publicidad:
            _urlCsv = "rojo.csv";
            cadenaSintonizada = publicidad;
            break;
            
        default:
            break;
    }
    
    
    
    // comprobamos si hay canales
    //if(canales.size()>0) canales.erase(canales.begin(), canales.end());
    if(canales.size()>0) canales.clear();
    
    // los canales representan la lisda de emisoras visibles
    // los llenamos
    
    if(_urlCsv !=""){
        
        // si no hay un resultado valido para _urlCsv no pones los canales
        
        for (int i = 0; i < numeroCanales; i++) {
            int iClick = i*numClicksDial/numeroCanales;
            
            emisora m;
            m.posicion = clicks.at(iClick);
            m.angulo = getAngle(clicks[iClick].x, clicks[iClick].y, 0, 0);
            m.numero = i;
            m.pClick = iClick;
            
            canales.push_back(m);
        }
        
    }
    
    
    
    //miramos si hay alguna cuña cargada
    if(sonidoEmisora.getIsPlaying()) sonidoEmisora.stop();
    
    // cargamos los datos
    data.carga(_urlCsv);
    
    
    /// metemos los datos de mp3 dentro de lel vector de emisoras
    /// movemos el dial una vuelta entera
    
    for (int m = 0; m < data.mptreses.size(); m++) {
        if(m<canales.size()) canales.at(m).mpTres = data.mptreses.at(m);
    }
    
    //cout << "primer elemento " << data.mptreses.at(0).txt << endl;
    
    /// cuando arranca pillamos el index del que esta en 180º
    posListaMp3 =  9;
    
    /// hacia donde se mueve 1 avanza // 0 retrocede
    direccion = 0;
    
    // si esta puesta una frecuencia
    sintonizada = false;
    
    
    // hack para que no aparezca el 0 sintonizado
    indexClick = 60;
    gradosGiro = 60;
    
    
    // el id del ultimo audio que sono
    lastAudio = -1;
    lastAguja = -1;
    indesPlayList = -1;
    cuadradoAudio = -1;
    
    
}
coleccionSintonizada click::dimeCanal(){

    return cadenaSintonizada;
}
//--------------------------------------------------------------
void click::update(){
    
    // calculamos el angulo actual
    anguloActual = getAngle(clicks[indexClick].x, clicks[indexClick].y, 0, 0);
    
    // calculamos el punto actual donde esta la bola
    clickActual = clicks[indexClick] + posicionOffset;
    
    // posicion de la bola sin offset
    clickActualSinOffet = clicks[indexClick];
    
    // mueve el dial
    rotaDial();
    
    // ajusta el volumen
    ajustaVolumen();
    
    // snap shot
    fotosUsuarios.update();
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
    
    //ofLine(canales.at(0).posicion, ofPoint(0,0)); // lineas para debug
    
    for (int i = 0; i < canales.size(); i++) {
        //ofSetColor(150);
        if((int)canales.at(i).angulo==0) ofSetColor(0);
        if((int)canales.at(i).angulo<=30 && (int)canales.at(i).angulo>0) ofSetColor(50);
        if((int)canales.at(i).angulo>30 && (int)canales.at(i).angulo<50) ofSetColor(100);
        if((int)canales.at(i).angulo>=50 && (int)canales.at(i).angulo<70) ofSetColor(150);
        if((int)canales.at(i).angulo>=70 && (int)canales.at(i).angulo<90) ofSetColor(200);
        
        // 285 360
        if((int)canales.at(i).angulo>340 && (int)canales.at(i).angulo<360) ofSetColor(100);
        if((int)canales.at(i).angulo>320 && (int)canales.at(i).angulo<=340) ofSetColor(150);
        if((int)canales.at(i).angulo>275 && (int)canales.at(i).angulo<=320) ofSetColor(200);
        
        
        
        ofPolyline pl;
        pl.addVertex(ofPoint(0,0));
        pl.addVertex(canales.at(i).posicion);
        
        
        ofLine(canales.at(i).posicion, pl.getPointAtLength(375)); // lineas para debug
        
        
        ofPushMatrix();
        if((int)canales.at(i).angulo ==0) ofSetColor(0,0,50);
        if((int)canales.at(i).angulo ==260 || (int)canales.at(i).angulo ==100) ofSetColor(255,0,50);
        
        /*
         debug
         
         string mensaje = "id " + ofToString(i) + " :: "
         + canales.at(i).mpTres.txt + " :: "
         + ofToString(canales.at(i).mpTres.url) + "  ";
         */
        
        string mensaje = canales.at(i).mpTres.txt;
        string strId = canales.at(i).mpTres.url;
        
        
        ofStringReplace(strId, ".mp3", "");
        
        int largoId = strId.size();
        if(largoId==1) strId = "0"+strId;
        /*
         string mensaje = ofToString(canales.at(i).angulo) + "º id :: " + ofToString(i) + " :: "
         + canales.at(i).mpTres.txt + " :: "
         + ofToString(canales.at(i).mpTres.url) + "  ";
         */
        
        ofVec2f offset;
        
        ofTranslate(canales.at(i).posicion);
        ofRotate(canales.at(i).angulo);
        
        ofSetColor(0);
        
        
        if((int)canales.at(i).angulo == 0){
            //offset = getOffset(mensaje, true);
            fontAreaBold.drawString(mensaje, -diametro/1.2, -14);
            fontAreaSmall.drawString(canales.at(i).mpTres.desc, -diametro/1.8, 39);
            
            int alto = fontAreaSmall.getStringBoundingBox(canales.at(i).mpTres.desc, -diametro/1.8, 39).getHeight();
            
            if(canales.at(i).mpTres.desc.size()>40) alto *=2.3;
            
            fontAreaYear.drawString(canales.at(i).mpTres.year, -diametro/1.199, 52+alto);
        }else{
            //ofSetColor(150);
            if((int)canales.at(i).angulo==0) ofSetColor(0);
            if((int)canales.at(i).angulo<=30 && (int)canales.at(i).angulo>0) ofSetColor(50);
            if((int)canales.at(i).angulo>30 && (int)canales.at(i).angulo<50) ofSetColor(100);
            if((int)canales.at(i).angulo>=50 && (int)canales.at(i).angulo<70) ofSetColor(150);
            if((int)canales.at(i).angulo>=70 && (int)canales.at(i).angulo<90) ofSetColor(200);
            
            
            
            if((int)canales.at(i).angulo>340 && (int)canales.at(i).angulo<360) ofSetColor(100);
            if((int)canales.at(i).angulo>320 && (int)canales.at(i).angulo<=340) ofSetColor(150);
            if((int)canales.at(i).angulo>275 && (int)canales.at(i).angulo<=320) ofSetColor(200);
            
            
            //offset = getOffset(mensaje, false);
            fontArea.drawString(mensaje, -diametro/1.8, -14);
        }
        
        
        if(strId.size()>2) strId.erase(strId.begin(), strId.begin()+1);
        fontAreaId.drawString(strId, -1020 , 36);
        
        
        
        ofPopMatrix();
    }
    
    
    
    //// VOLUMENS SONIDO NOISE ///////////////////////////////
    dibujaVolumen();
    
    
    ofPopStyle();
}

//--------------------------------------------------------------
void click::dibujaVolumen(){
    /// indica el volumen de la interferencia
    /// con los 8 ultimos puntos y los 8 primeros
    
    bool dentroSliderAudio = false;
    
    for (int i = 0; i < rectVolumen.size(); i++) {
        ofSetColor(160 - 8*i, 50);
        
        for (int j = 0; j < canales.size(); j++) {
            if(rectVolumen.at(i).inside(canales.at(j).posicion)){
                ofSetColor(50);
            }
        }
        ofRect(rectVolumen.at(i));
    }
    
    
    
    
    /// los 8 ultimos
    for (int i = 0; i < rectVolumenUp.size(); i++) {
        ofSetColor(160 - 8*i, 50);
        
        for (int j = 0; j < canales.size(); j++) {
            if(rectVolumenUp.at(i).inside(canales.at(j).posicion)){
                //cout << "deeeeentro " << ofToString(i) << endl;
                ofSetColor(50);
            }
        }
        ofRect(rectVolumenUp.at(i));
    }
}

//--------------------------------------------------------------
void click::avanza(){
    indexClick++;
    // alante
    if(indexClick>=clicks.size()-1) indexClick = 0;
    
    direccion = 1;
    sintonizada = false;
    
    gradosGiro += 2;
    if (gradosGiro>360) gradosGiro = 0;
}
//--------------------------------------------------------------
void click::retrocede(){
    indexClick--;
    //atras
    if(indexClick<0) indexClick = clicks.size()+indexClick;
    
    direccion = 0;
    sintonizada = false;
    
    gradosGiro-=2;
    if (gradosGiro<0) gradosGiro = 360-gradosGiro;
}


int click::getGradosGiro(){
    return gradosGiro;
    
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
        if((int)canales.at(i).angulo == 0 && data.mptreses.size()>0){
            //cout << "deeeeentro" << endl;
            if(!sintonizada)cambiaCanales(i);
            
           
        }
    }
    
    
}

//--------------------------------------------------------------
void click::cambiaCanales(int _in){
    // sanpshot
    fotosUsuarios.takePhoto();
    
    sintonizada = true;
    
    // index del vector canales que tengo que cambiar
    int cualCambiar =0;
    int cualCambiarAbajo =0;
    
    // index del valor de referencia
    int canalReferencia = 0;
    int canalReferenciAbajo = 0;
    
    string stringReferencia = "";
    string stringReferenciAbajo = "";
    
    // index de cual suena
    int indexSuena = 0;
    int dataDestino = 0;
    int dataDestinoAbajo = 0;
    
    ////108
    
    for (int i = 0; i < canales.size(); i++) {
        if((int)canales.at(i).angulo > 248 && (int)canales.at(i).angulo < 255){
            cualCambiar = i;
        }else if ((int)canales.at(i).angulo > 282 && (int)canales.at(i).angulo < 292){
            stringReferencia = canales.at(i).mpTres.url;
            
        }else if ((int)canales.at(i).angulo > 103 && (int)canales.at(i).angulo < 112){
            cualCambiarAbajo = i;
            
        }else if ((int)canales.at(i).angulo > 67 && (int)canales.at(i).angulo < 80){
            stringReferenciAbajo = canales.at(i).mpTres.url;
            
        }else if ((int)canales.at(i).angulo == 0){
            indexSuena = i;
        }
    }
    
    
    if(direccion == 1){
        // la rueda avanza hay que cambiar el de arriba 252º
        for (int d = 0; d < data.mptreses.size(); d++) {
            if (data.mptreses.at(d).url == stringReferencia) canalReferencia = d;
            
        }
        
        dataDestino = canalReferencia - 1;
        if (dataDestino<0) dataDestino = data.mptreses.size()-1;
        
        //canales.at(cualCambiar).mpTres.url = "ostiiii";
        //cout << "stringReferencia " << stringReferencia << endl;
        //cout << "canalReferencia " << canalReferencia << endl;
        //cout << "quiero cambiar el que pone " << canales.at(cualCambiar).mpTres.url <<endl;
        //cout << "quiero cambiar el id " << cualCambiar <<endl;
        //cout << "ponerle el data id " << dataDestino <<endl;
        //cout << "tiene que poner " << data.mptreses.at(dataDestino).url <<endl;
        //cout << "me baso en el valor de " << data.mptreses.at(canalReferencia).url << "con id " << canalReferencia << endl;
        
        canales.at(cualCambiar).mpTres.url = data.mptreses.at(dataDestino).url;
        canales.at(cualCambiar).mpTres.txt = data.mptreses.at(dataDestino).txt;
        canales.at(cualCambiar).mpTres.desc = data.mptreses.at(dataDestino).desc;
        canales.at(cualCambiar).mpTres.year = data.mptreses.at(dataDestino).year;
        
    }else if (direccion == 0){
        // la rueda avanza hay que cambiar el de arriba 252º
        for (int d = 0; d < data.mptreses.size(); d++) {
            if (data.mptreses.at(d).url == stringReferenciAbajo) canalReferenciAbajo = d;
        }
        
        dataDestinoAbajo = canalReferenciAbajo + 1;
        if (dataDestinoAbajo>=data.mptreses.size()) dataDestinoAbajo = 0;
        
        //cout << "stringReferenciAbajo " << stringReferenciAbajo << endl;
        //cout << "canalReferenciAbajo " << canalReferenciAbajo << endl;
        //cout << "quiero cambiar el que pone " << canales.at(cualCambiarAbajo).mpTres.url <<endl;
        //cout << "quiero cambiar el id " << cualCambiarAbajo <<endl;
        //cout << "ponerle el data id " << dataDestinoAbajo <<endl;
        //cout << "tiene que poner " << data.mptreses.at(dataDestinoAbajo).url <<endl;
        //cout << "me baso en el valor de " << data.mptreses.at(canalReferenciAbajo).url << "con id " << canalReferenciAbajo << endl;
        
        canales.at(cualCambiarAbajo).mpTres.url = data.mptreses.at(dataDestinoAbajo).url;
        canales.at(cualCambiarAbajo).mpTres.txt = data.mptreses.at(dataDestinoAbajo).txt;
        canales.at(cualCambiarAbajo).mpTres.desc = data.mptreses.at(dataDestinoAbajo).desc;
        canales.at(cualCambiarAbajo).mpTres.year = data.mptreses.at(dataDestinoAbajo).year;
    }
    
    
    // miramos si hay una emisora cargada
    if (sonidoEmisora.isLoaded() && _in != lastAudio) {
        sonidoEmisora.unloadSound();
    }
    
    if(_in != lastAudio){
        /// haces play con el audio de la frecuencia seleccionada
        
        sonidoEmisora.loadSound("Audios mp3/" + canales.at(_in).mpTres.url);
        sonidoEmisora.setVolume(.5);
        sonidoEmisora.play();
    }
    
    lastAudio = _in;
    
    // en que canal esta lo que seleccionas
    lastAguja = _in;
}

//--------------------------------------------------------------
void click::ajustaVolumen(){
    
    bool dentroSliderAudio = false;
    
    for (int i = 0; i < rectVolumen.size(); i++) {
        for (int j = 0; j < canales.size(); j++) {
            if(rectVolumen.at(i).inside(canales.at(j).posicion)){
                
                if(j == lastAguja){
                    dentroSliderAudio = true;
                    cuadradoAudio = i;
                }
                
                float sonido = ofMap(i*.10, 0.0, 0.7, 0.0, 0.5);
                float sonidoReverse = ofMap(sonido,0.0, 0.5, 0.5, 0.0);
                
                sonidoRuido.setVolume(sonido);
                if(dentroSliderAudio) sonidoEmisora.setVolume(sonidoReverse);
                
            }
        }
    }
    ////////////////////////////////////////
    /// los 8 ultimos
    for (int i = 0; i < rectVolumenUp.size(); i++) {
        for (int j = 0; j < canales.size(); j++) {
            if(rectVolumenUp.at(i).inside(canales.at(j).posicion)){
                
                if(j == lastAguja){
                    dentroSliderAudio = true;
                    cuadradoAudio = i;
                }
                
                float sonido = ofMap(i*.10, 0.0, 0.7, 0.0, 0.5);
                
                float sonidoReverse = ofMap(sonido, 0.0, 0.5, 0.5, 0.0);
                
                sonidoRuido.setVolume(sonido);
                if(dentroSliderAudio) sonidoEmisora.setVolume(sonidoReverse);
            }
        }
        ofRect(rectVolumenUp.at(i));
    }
}

//--------------------------------------------------------------
int click::dimeIndexMp3(string _mp3){
    for (int i = 0;  i < canales.size(); i++) {
        if(canales.at(i).mpTres.url == _mp3) return i;
    }
}

//--------------------------------------------------------------
ofVec2f click::getOffset( string s, bool bold ){
    ofRectangle r;
    
    if(bold){
        r = fontAreaBold.getStringBoundingBox(s, 0, 0);
    }else{
        r = fontArea.getStringBoundingBox(s, 0, 0);
    }
    
    return ofVec2f( floor(-r.x - r.width), floor(-r.y - r.height*0.5) );
}

//--------------------------------------------------------------
ofPoint click::getClick(){
    return clickActual;
}

//--------------------------------------------------------------
ofPoint click::getClickSinOffset(){
    return  clickActualSinOffet;
}


void click::exit(){
    fotosUsuarios.exit();
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