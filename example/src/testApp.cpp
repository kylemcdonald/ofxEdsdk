#include "testApp.h"

#define FOREACH_CAMERA for (int iCam=0; iCam<2; ++iCam)

void testApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	//ofxEdsdk::Camera::listDevices();
	
	intialised[0]=false;
	intialised[1]=false;
}

void testApp::update() {
	FOREACH_CAMERA {
		camera[iCam].update();
		if(camera[iCam].isFrameNew()) {
			// process the live view with camera.getLivePixels()
		}
		if(camera[iCam].isPhotoNew()) {
			// process the photo with camera.getPhotoPixels()
			// or just save the photo to disk (jpg only):
			camera[iCam].savePhoto(ofToString(ofGetFrameNum()) + ".jpg");
		}
	}
}

void testApp::draw() {
	FOREACH_CAMERA {
		camera[iCam].draw(iCam * camera[0].getWidth()/2, 0, camera[iCam].getWidth() / 2, camera[iCam].getHeight() / 2);
		// camera.drawPhoto(0, 0, 432, 288);
		
		if(camera[iCam].isLiveReady()) {
			stringstream status;
				status << camera[iCam].getWidth() << "x" << camera[iCam].getHeight() << " @ " <<
				(int) ofGetFrameRate() << " app-fps " << " / " <<
				(int) camera[iCam].getFrameRate() << " cam-fps";
			ofDrawBitmapString(status.str(), 10 + camera[0].getWidth()/2 * iCam, 20);
		}
	}
}

void testApp::keyPressed(int key) {
	if(key == ' ') {
		FOREACH_CAMERA
			camera[iCam].takePhoto();
	}
	
	if(key == '1' || key == '0')
	{
		if (!intialised[key-'0'])
		{
			camera[key - '0'].setup();
			intialised[key-'0'] = true;
		}
	}
}