#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetWindowShape(1024, 340);
    
    ofxEdsdk::Camera::listDevices();
    
    for(int i=0; i<NUM_CAMS; i++) {
        camera[i].setup(i);
    }
   
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(int i=0; i<NUM_CAMS; i++) {
        camera[i].update();

        
        
        if(camera[i].isPhotoNew()) {
            stringstream name;
            name << beginAt << "_" << i << ".jpg";
            camera[i].savePhoto(name.str());
        }
        
        if(camera[i].isMovieNew()) {
            stringstream name;
            name << beginAt << "_" << i << ".mov";
            camera[i].savePhoto(name.str());
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    int x = 10;
    int y = 10;
    
    for(int i=0; i<NUM_CAMS; i++) {
        camera[i].draw(x, y, 480, 320);
        
        stringstream status;
        status << camera[i].getWidth() << "x" << camera[i].getHeight() << " @ " <<
            (int) ofGetFrameRate() << " app-fps / " <<
            (int) camera[i].getFrameRate() << " cam-fps / " <<
            (camera[i].getBandwidth() / (1<<20)) << " MiB/s";
        ofDrawBitmapString(status.str(), x, y);
        
        x += 490;
    }
    
}

//--------------------------------------------------------------
void ofApp::exit() {
    for(int i=0; i<NUM_CAMS; i++) {
        camera[i].close();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == ' ') {
        for(int i=0; i<NUM_CAMS; i++)
            camera[i].takePhoto();
    }
    
    if(key == 'v') {
        
        if(bIsRecordingMovie) {
            ofLogNotice() << "End Recording";
            for(int i=0; i<NUM_CAMS; i++) camera[i].endMovieRecording();
            bIsRecordingMovie = false;
        }
        else {
            ofLogNotice() << "Begin Recording";
            beginAt = ofGetFrameNum();
            for(int i=0; i<NUM_CAMS; i++) camera[i].beginMovieRecording();
            bIsRecordingMovie = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
