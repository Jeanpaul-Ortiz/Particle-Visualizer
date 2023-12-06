#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
	timer=0;
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;
	currentColor=Red;
	counter=1;
	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 

	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the fourth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setColor(currentColor);
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}	

}

//--------------------------------------------------------------
void ofApp::update(){
	timer++;
	if(replaying) {
		keysAllowed=false;
		recording=false;

		if(timer%30 == 0){
				if(vIterator > recordedkeys.size() || vIterator < recordedkeys.empty()){
					replaying=false;
					vIterator=0;
					keysAllowed=true;
					recordedkeys.clear();
				}
				else{
				 	keyPressed(recordedkeys[vIterator]);
					vIterator++;
				}
			}
		}
	

		for(unsigned int i = 0; i < p.size(); i++){
			p[i].setMode(currentMode);
			p[i].setColor(currentColor);

	
			if (!paused){
				p[i].update();
				}
		
		}
	


	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}	
}	

//--------------------------------------------------------------
void ofApp::draw(){
	if(backgroundCounter == 1){
    	ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10), OF_GRADIENT_CIRCULAR);
	}
	else if(backgroundCounter == 2){
		ofBackgroundGradient(ofColor(0,100,100), ofColor(135,206,235), OF_GRADIENT_LINEAR);
	}
	else if(backgroundCounter == 3 || backgroundCounter == 0){
		ofBackgroundGradient(ofColor(255, 0, 255), ofColor(0,128,128), OF_GRADIENT_BAR);
		backgroundCounter = 0;}

	for(unsigned int i = 0; i < p.size(); i++){
		static float ogScale = p[i].scale;
		if(fullRect.inside(p[i].pos) == true && recExist == true){
			p[i].scale = ogScale * 3;
		}
		if(fullRect.inside(p[i].pos) == false || recExist == false){
			p[i].scale = ogScale;
		}
		p[i].draw();
	}
	
	ofSetColor(230);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}
//230
	ofSetColor(230);	
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
	ofDrawBitmapString("Press y to change background color", 10, 110);


	if(recExist){
		ofNoFill();
		fullRect = ofRectangle(rectPoint1,rectPoint2); //Settting the Rectangle points before it is drawn
		ofDrawRectangle(ofRectangle(fullRect));
		ofFill();
	}
	if(recording){
		ofSetColor(230);
		ofDrawBitmapString("RECORDING...", 10,90 );
	}
	if(replaying){
		ofSetColor(230);
		ofDrawBitmapString("REPLAYING...", 10,90 );

		ofSetColor(230);
		ofDrawBitmapString("Press 'C' to cancel replaying",10, 35);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

 if(keysAllowed){
 	newCompare=key;
 }
 else{
	newCompare=recordedkeys[vIterator];
 }
 
	if( newCompare == '1'){

		 if(recording){
		 		recordedkeys.push_back(newCompare);
		 	}

			currentMode = PARTICLE_MODE_ATTRACT;
			currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
				
	}

	if( newCompare == '2'){
		 if(recording){
		 		recordedkeys.push_back(newCompare);
		 	}
	
			currentMode = PARTICLE_MODE_REPEL;
			currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 
					
	}

	if( newCompare == '3'){
		 if(recording){
		 		recordedkeys.push_back(newCompare);
		 	}
		
			currentMode = PARTICLE_MODE_NEAREST_POINTS;
			currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:"; 	
							
	}

	if( newCompare == '4'){
		 if(recording){
	 		recordedkeys.push_back(newCompare);
		}
		
			currentMode = PARTICLE_MODE_NOISE;
			currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
			resetParticles();
		
	}	

	if(newCompare == ' '){
		if(recording){
			recordedkeys.push_back(newCompare);
			}
		
			resetParticles();
		
	}

	if( newCompare == 't' ){
		if(recording){
			recordedkeys.push_back(newCompare);
			}

		
			counter+=1;
				if(counter==1){
					currentColor= Red;
				}
				else if(counter==2){
					currentColor= Green;
				}
				else if(counter==3){
				currentColor = Blue;
				counter=0;
				}
		
	}

	if(newCompare == 's'){
		if(recording){
				recordedkeys.push_back(newCompare);
			}
		
			paused = !paused;
		
		
	}

	if( newCompare == 'd'){
		if(recording){
				recordedkeys.push_back(newCompare);
			}
		
			for(unsigned int i = 0; i < p.size(); i++ ){
				p[i].vel *= 2;
			}
		
	}

	if( newCompare == 'a'){
		if(recording){
				recordedkeys.push_back(newCompare);
			}
		
			for( unsigned int i = 0; i < p.size(); i++){
				p[i].vel /= 2;
			}
		
	}

	if( newCompare == 'y'){
		if(recording){
				recordedkeys.push_back(newCompare);
			}
		backgroundCounter += 1;
		if(backgroundCounter == 1){
			ofSetBackgroundColor(255,255,255);
		}
	}



	if(newCompare=='r'){
		recording = !recording;
	}

	if(newCompare=='p'){
		replaying= true;
		
	}
	
	if(key == 'c'){
		replaying=false;
		keysAllowed=true;
		recordedkeys.clear();
	}

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if(button == 0){
	    rectPoint2.set(ofGetMouseX(), ofGetMouseY());
}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if( button == 0){
		rectPoint1.set(ofGetMouseX(), ofGetMouseY());
		recExist = true;
	}
	if(button == 2){
		delRectangle.set(ofGetMouseX(),ofGetMouseY());
		if(fullRect.inside(delRectangle) == true){
			fullRect.~ofRectangle();
			recExist = false;
		}
	}
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