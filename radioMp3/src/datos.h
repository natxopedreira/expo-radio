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
#include "ofxCsv.h"
using namespace wng;

class infoMp3 {
public:
    string url="nada";
    string txt="nada";
    string desc="nada";
    string year="nada";
    int idele = 0;
};

class datos {
public:
    
    void carga(string _url){
        
        if(mptreses.size()>0){
            mptreses.clear();
            //cout << "mptreses.clear()" << endl;
            
        }
        csv.clear();
        csv.loadFile(ofToDataPath(_url),";");
        
        for(int i=0; i<csv.numRows; i++) {
            //cout << csv.data[i][0] << endl;
            //cout << csv.data[i][1] << endl;
            
            string s = csv.data[i][1];
            //s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
            
            string sDesc = csv.data[i][2];
            //sDesc.erase(std::remove(sDesc.begin(), sDesc.end(), '\n'), sDesc.end());
            
            
            infoMp3 mp3;
            
            mp3.desc = sDesc;
            mp3.txt = s;
            mp3.url = csv.data[i][0]+".mp3";
            mp3.year = csv.data[i][3];
            mp3.idele = i;
            //cout << s << " :: " << sDesc << endl;
            
            mptreses.push_back(mp3);
        }
        
        //cout << "mptreses cuantos " << mptreses.size() << endl;
    }
    ofxCsv csv;
    
    vector<infoMp3> mptreses;
    
};


#endif
