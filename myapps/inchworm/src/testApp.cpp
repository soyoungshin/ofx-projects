#include "testApp.h"
#include <algorithm>

#define DEBUG 1

void testApp::d(char* msg) {
	if(DEBUG) puts(msg);
}

/**
 * Converts an HSV color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSV_color_space.
 * Assumes h, s, and v are contained in the set [0, 1] and
 * returns r, g, and b in the set [0, 255].
 *
 * @param   Number  h       The hue
 * @param   Number  s       The saturation
 * @param   Number  v       The value
 * @return  Array           The RGB representation
 
 from http://mjijackson.com/2008/02/rgb-to-hsl-and-rgb-to-hsv-color-model-conversion-algorithms-in-javascript
 */
void testApp::hsvToRgb(float h, int* rgb) {
	
	float s = 1;
	float v = 1;
    float r, g, b;
	
    int i = floor(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);
	
    switch(i % 6){
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }
	rgb[0] = (int)(r * 255);
	rgb[1] = (int)(g * 255);
	rgb[2] = (int)(b * 255);
}

//--------------------------------------------------------------
void testApp::setup(){
	ofSetWindowTitle("INCHWORM!!!!!");
	//ofBackground(255,255,255);
	ofBackground(0,0,0);
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
	
	// inchworm set up
	float hue = rand() % 100 / 100.0;
	numCenterSegments = 10;
	wormWidth = 40;
	wormHeight=55;
	/*
	int initVX = 1;
	int initVY = 0;
	 */
	float initAngle = 0;
	int initVS = 3;

	// front seg is a square, back seg is a triangle.
	// want front seg semicircle, bag seg triangle
	frontSeg.center.x = 200;
	frontSeg.center.y = 300;
	frontSeg.velo.angle = initAngle;
	/*
	frontSeg.velo.x = 1;
	frontSeg.velo.y = 0;
	 */
	frontSeg.velo.spd = initVS;
	hsvToRgb(hue, frontSeg.rgb);
	// initialize other pieces

	for(int i = 0; i < numCenterSegments; i++) {
		hue = fmod(hue + 0.08, 1);
		centerSegs[i].leftWidth = centerSegs[i].rightWidth = wormWidth;
		/*
		centerSegs[i].velo.x = initVX;
		centerSegs[i].velo.y = initVY;
		 */
		centerSegs[i].velo.angle = initAngle;
		centerSegs[i].velo.spd = 0;
		hsvToRgb(hue, centerSegs[i].rgb);
	}
	hue = fmod(hue + 0.08, 1);	
	/*
	rearSeg.velo.x = initVX;
	rearSeg.velo.y = initVY;
	 */
	rearSeg.velo.angle = initAngle;
	rearSeg.velo.spd = initVS;
	
	hsvToRgb(hue, rearSeg.rgb);
	
}

//--------------------------------------------------------------
void testApp::update(){


}

//--------------------------------------------------------------
void testApp::draw(){
	char buffer[50];
	float angleDiff = frontSeg.velo.angle - prevAngle;
	
	if(prevAngle == frontSeg.velo.angle) {


	float xAdd = cos(frontSeg.velo.angle * PI / 180) * frontSeg.velo.spd;
	

	float yAdd = sin(frontSeg.velo.angle * PI / 180) * frontSeg.velo.spd;
		
	frontSeg.center.x += xAdd;
	frontSeg.center.y += yAdd;	
	} else {
		
		prevAngle = frontSeg.velo.angle;
	}
	
	
	glPushMatrix();
		glTranslatef(frontSeg.center.x, frontSeg.center.y, 0);
	
		// rotate about x going in to the screen
		//float angle = atan2(frontSeg.velo.y, frontSeg.velo.x) * 180 / PI;
		float angle = frontSeg.velo.angle;
		glRotatef(angle - 90, 0, 0, 1);

		ofSetColor(frontSeg.rgb[0], frontSeg.rgb[1], frontSeg.rgb[2]);
		ofBeginShape();
		int halfWidth = wormWidth / 2;
		//ofVertex(halfWidth, 0);
		float circleRadius = sqrt(pow((float)wormWidth,2)/2);
	
		for(float i= -PI/4; i <= PI + PI/4; i+=.01) {
			ofVertex(cos(i) * circleRadius, sin(i) * circleRadius);
		}
		//ofVertex(-halfWidth, 0);
		
			
		ofEndShape();
		glPushMatrix();
			glTranslatef(sqrt(pow((float)wormWidth,2) / 4), -sqrt(pow((float)wormWidth,2) / 4), 0);
			glRotated(180, 0, 0, 1);
			glRotated(angleDiff, 0, 0, 1);
			//drawCenter(0, angleDiff, angleDiff == 0);
			//drawCenter(0, angleDiff, 0);
			drawCenter(0, angleDiff);
		glPopMatrix();
		
	glPopMatrix();
}

// for sanity, we always assume the upper left corner is the rear left corner of the previous piece
//void testApp::drawCenter(int idx, float prevAngleDiff, int drawStraight) {
void testApp::drawCenter(int idx, float prevAngleDiff) {
	int drawStraight = 0;
	glPushMatrix();
	if(drawStraight) {
		if(idx < numCenterSegments) {
			//logic to draw one center segment
			// take half the direction diff of the segment in front each time
			ofSetColor(centerSegs[idx].rgb[0], centerSegs[idx].rgb[1], centerSegs[idx].rgb[2]);
			float decayedAngle = prevAngleDiff * ANGLE_DECAY;
			glTranslatef(wormWidth / 2, 0, 0);
			glRotated(prevAngleDiff, 0, 0, 1);
			ofBeginShape();
				ofVertex(-wormWidth / 2,0);
				ofVertex(-wormWidth / 2,wormHeight);
				ofVertex(wormWidth / 2, wormHeight);
				ofVertex(wormWidth / 2,0);
			ofEndShape();
			glTranslatef(-wormWidth / 2, 0, 0);
			
			glTranslatef(0,wormHeight,0);
			//drawCenter(idx+1, decayedAngle, drawStraight);
			drawCenter(idx+1, decayedAngle);
		} else if (idx == numCenterSegments) {
			// draw the butt
			ofSetColor(rearSeg.rgb[0], rearSeg.rgb[1], rearSeg.rgb[2]);
			ofBeginShape();
				ofVertex(0,0);
				ofVertex(wormWidth, 0);
				ofVertex(wormWidth/2, wormHeight * 1.5);
			ofEndShape();
			
		}
	} else {
		if(idx < numCenterSegments) {
			//logic to draw one center segment
			// take half the direction diff of the segment in front each time
			ofSetColor(centerSegs[idx].rgb[0], centerSegs[idx].rgb[1], centerSegs[idx].rgb[2]);
			float decayedAngle = prevAngleDiff * ANGLE_DECAY;
			glTranslatef(wormWidth / 2, 0, 0);
			glRotated(prevAngleDiff, 0, 0, 1);
			ofBeginShape();
			ofVertex(-wormWidth / 2,0);
			ofVertex(-wormWidth / 2,wormHeight);
			ofVertex(wormWidth / 2, wormHeight);
			ofVertex(wormWidth / 2,0);
			ofEndShape();
			glTranslatef(-wormWidth / 2, 0, 0);
			
			glTranslatef(0,wormHeight,0);
			//drawCenter(idx+1, decayedAngle, drawStraight);
			drawCenter(idx+1, decayedAngle);
		} else if (idx == numCenterSegments) {
			// draw the butt
			ofSetColor(rearSeg.rgb[0], rearSeg.rgb[1], rearSeg.rgb[2]);
			ofBeginShape();
			ofVertex(0,0);
			ofVertex(wormWidth, 0);
			ofVertex(wormWidth/2, wormHeight * 1.5);
			ofEndShape();
			
		}
	}
	glPopMatrix();
	// otherwise do nothing
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if (key == 'f'){
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	char buffer[50];	
	
	// figure out whether the mouse click spot is to the left or right of current direction
	
	
	// set some flag to head towards here
	//seekGoal = 1;
	goal.x = x;
	goal.y = y;
	//goal.clockwise = button == 0;
	
	
	
	
	float angleFromHead = atan2(goal.y - frontSeg.center.y, goal.x - frontSeg.center.x) * 180 / PI;
	
	// this might be backwards
	float diff = frontSeg.velo.angle - angleFromHead;
	
	while(diff > 180) {
		diff = diff - 360;
	}
	while(diff < -180) {
		diff += 360;
	}
	
	
	if (diff < -1) {
		goal.clockwise = -1;
		frontSeg.velo.angle += MAX_ANGLE_CHANGE;
	} else if (diff > 1) {
		goal.clockwise = 1;
		frontSeg.velo.angle -= MAX_ANGLE_CHANGE;
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	//seekGoal = 0;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
