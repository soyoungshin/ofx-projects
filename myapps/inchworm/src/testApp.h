#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#define MAX_CENTER_SEGMENTS 30
#define MIN_CENTER_SEGMENTS 0
// highest turn per frame.
#define MAX_ANGLE_CHANGE 10
#define ANGLE_DECAY 0.5

// rebuilding the wheel, I know

typedef struct {
	// x,y compontents and speed in pixels/frame
	float angle;
	float spd;
}	wormVelocity;

typedef struct {
	float x;
	float y;
}	wormPoint;
	
typedef struct {
	int x;
	int y;
	int clockwise;
}	mouseGoal;

typedef struct {
	// center of the rear of the semicircle
	wormPoint center;
	wormVelocity velo;
	//float hue;
	int rgb[3];
}	frontSegment;

// the center parts of the inchworm
typedef struct {
	float leftWidth;
	float rightWidth;
	//float hue;
	int rgb[3];
	// particle systems bitches!
	wormVelocity velo;
	
}	segment;

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
		int numCenterSegments;
		segment centerSegs[MAX_CENTER_SEGMENTS];
		frontSegment frontSeg;
		frontSegment rearSeg;
	private:
		void d(char* msg);
		void drawCenter(int idx, float prevAngle);
		void hsvToRgb(float h, int* rgb);
		// can calculate volume of each piece this way
		int wormWidth;
		int wormHeight;
		mouseGoal goal;
		int seekGoal;
		float prevAngle;
	
		
};

#endif
	
