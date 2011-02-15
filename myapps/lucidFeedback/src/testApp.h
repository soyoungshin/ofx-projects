#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include <iostream>
#include <vector>
#include <algorithm>

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
		ofVideoGrabber vidGrab;
		vector<ofPoint> points;
		//unsigned char * videoBuf;
		ofTexture videoTexture;
		unsigned char * oldFrame;
		int camWidth;
		int camHeight;
		int grabVideo;
		int vectorIdx;
		

};

#endif
