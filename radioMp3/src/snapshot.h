//
//  snapshot.h
//  radioMp3
//
//  Created by Natxo Pedreira gonzalez on 2/12/14.
//
//

#ifndef radioMp3_snapshot_h
#define radioMp3_snapshot_h

#include "ofMain.h"
#include "ofxImageSequenceRecorder.h"

class snapshot {
public:
    
    void setup(string _url){
        grabber.initGrabber(640, 480);
        
        grabaFrames.setPrefix(_url);
        grabaFrames.setFormat("jpg");
        
        grabaFrames.startThread(false, false);
    }
    
    void update(){
        grabber.update();
    }
    
    void takePhoto(){
        grabaFrames.addFrame(grabber);
        
    }
    
    void exit(){
        grabaFrames.waitForThread();
    }
   
    ofxImageSequenceRecorder grabaFrames;
    
private:
    
    ofVideoGrabber grabber;
};

#endif
