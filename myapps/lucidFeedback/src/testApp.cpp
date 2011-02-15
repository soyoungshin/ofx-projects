#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;
	grabVideo = 1;
	vectorIdx = 0;
	
	vidGrab.setVerbose(true);
	vidGrab.initGrabber(camWidth,camHeight);
	
	oldFrame = new unsigned char[camWidth * camHeight * 3];
	videoTexture.allocate(camWidth, camHeight, GL_RGB);
	
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);
	
	vidGrab.grabFrame();
	if(grabVideo && vidGrab.isFrameNew()) {
		int totalPixels = camWidth * camHeight * 3;
		unsigned char * pixels = vidGrab.getPixels();
		for(int i = 0; i < totalPixels; i++) {
			oldFrame[i] = min((int) (oldFrame[i] * 0.9 + 0.1 * pixels[i]), 255);
		}
		videoTexture.loadData(oldFrame, camWidth, camHeight, GL_RGB);
	}
	/*
	if (grabVideo && vidGrab.isFrameNew()){
		// figure out where the center of white is
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrab.getPixels();
		int rowAcc = 0, colAcc = 0, count = 0;
		for(int row = 0; row < camHeight; row++) {
			for(int col = 0; col < camWidth; col++) {
				int i = row * camWidth + col * 3;

				if(pixels[i] > 250) {
					rowAcc += row;
					colAcc += col;
					count++;
				}
			}
		}
		if(count != 0) {
			ofPoint p = ofPoint((int) colAcc / count, (int) rowAcc / count);
			points.push_back(p);
		}
	}*/
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xffffff);
	if(grabVideo) {
		vidGrab.draw(20,20);
	}
	videoTexture.draw(20+camWidth,20,camWidth,camHeight);
	/*
	if(grabVideo) {	
		vidGrab.draw(20,20);
	} else {
		printf("printing points\n");
		int s = points.size();
		for(int i = 0; i < s; i++) {
			printf("%f, %f\n", points[i].x, points[i].y);
			ofCircle(points[i].x, points[i].y, 1);
		}
		printf("done printing points \n\n");
	}*/
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' ') {
		// pause live video
		grabVideo = grabVideo == 0 ? 1 : 0;
	} else if(key == OF_KEY_BACKSPACE) {
		// clear the vector
		points.clear();
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

