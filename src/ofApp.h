#pragma once

#include "ofMain.h"
#include "Particle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		particleMode currentMode;
		int counter;// helps toggle infinitely through color options
		string currentModeStr; 
		particleColor currentColor;
		int backgroundCounter; //Used in a new feature to change color of the background

		
		bool paused = false;//stops update of every dot
		bool recording= false;//puts the key pressed in the recordedkeys vector
		bool replaying= false;//changes keypressed values to that of recordedkeys vector
		bool cancelReplay=false;

		int timer;//timer for the vector intervals
	
		bool keysAllowed=true;//allows keypressed to take new values of ones pressed or recorded
		int newCompare;//used to take the decisions in keypressed
		
		
		vector <Particle> p;
		vector <glm::vec3> attractPoints;
		vector <glm::vec3> attractPointsWithMovement;

		vector <int> recordedkeys;//vector for the recorded keys
		int vIterator=0; //itterates through vector and is increased with help of the timer

		ofPoint rectPoint1; //top left corner of rectangle
		ofPoint rectPoint2; // bottom right corner of rectangle

		ofRectangle fullRect; // completed rectangle
		ofPoint delRectangle; //x and y coordinates of right click
		bool recExist; //boolean to draw or delete rectangle
		

};
