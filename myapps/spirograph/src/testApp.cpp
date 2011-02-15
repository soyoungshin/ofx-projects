#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	// 640x480 max
	camWidth = 480;
	camHeight = 320;
	numFrames = 15;
	queueIdx = 0;
	prevFrames = new unsigned char[numFrames * camWidth * camHeight * 3];
	nextFrame = new unsigned char[camWidth * camHeight * 3];
	memset(prevFrames, 0, numFrames * camWidth * camHeight * 3);
	videoTexture.allocate(camWidth, camHeight, GL_RGB);
	
	vidGrab.setVerbose(true);
	vidGrab.initGrabber(camWidth,camHeight);
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0, 0, 0);
	vidGrab.grabFrame();
	if(vidGrab.isFrameNew()) {
		// add new frame to the end of my circular array, and change texture
		// place the frame at that index, and increment index
		unsigned char * currentFrame = vidGrab.getPixels();
		int numBytes = camHeight * camWidth * 3;
		memcpy(&prevFrames[numBytes * queueIdx], currentFrame, numBytes);
		
		queueIdx++;
		while(queueIdx >= numFrames) {
			queueIdx -= numFrames;
		}
		
		// this could use some work.
		// for each pixel, find the max pixel, and use it for the texture
		int totalPixels = camWidth * camHeight * 3;
		for (int i = 0; i < totalPixels; i++) {
			int max = prevFrames[i];
			
			for (int frameIdx = 1; frameIdx < numFrames; frameIdx++) {
				int currPixel = prevFrames[frameIdx * totalPixels + i];
				max = max > currPixel ? max : currPixel;
			}
			 
			nextFrame[i] = max;
			 
		}
		
		videoTexture.loadData(nextFrame, camWidth, camHeight, GL_RGB);
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xffffff);
	vidGrab.draw(20,20);
	videoTexture.draw(20+camWidth,20,camWidth,camHeight);	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == OF_KEY_BACKSPACE) {
		queueIdx = 0;
		memset(prevFrames, 0, numFrames * camWidth * camHeight * 3);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

