//
//  datos.h
//  dialRota
//
//  Created by Natxo Pedreira gonzalez on 14/11/14.
//
//

#ifndef dialRota_datos_h
#define dialRota_datos_h

#include "ofMain.h"

class infoMp3 {
public:
    string url="nada";
    string txt="nada";
};

class datos {
public:
    datos(){
        
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
        
   
    
    
    }
    vector<infoMp3> mptreses;
    
};


#endif
