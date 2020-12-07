#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// initializing presetable value named "int" with an integer reference(test_)
	auto intarg = preset_.add("int", test_);
	// set each preset with a name
	for(int i = 0; i < 10; ++i) {
		intarg->set(ofToString(i), i*2);
	}
	// you can add presetable value without owning a variable
	auto vec2arg = preset_.add<glm::vec2>("vec2", 0, 0);
	// or this way
//	auto vec2arg = preset_.add("vec2", glm::vec2{0, 0});
	for(int i = 0; i < 10; ++i) {
		vec2arg->set(ofToString(i), {i*5,i*10});
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString("press [0-9] to select preset", 10, 10);
	// you can get the value via a reference(test_) you passed when initializing
	ofDrawBitmapString("intarg:  " + ofToString(test_), 10, 20);
	// or you can grab whole instance so that you can get the value with get()
	auto vec2arg = preset_.get<glm::vec2>("vec2");
	ofDrawBitmapString("vec2arg: " + ofToString(vec2arg->get()), 10, 30);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// update preset values with certain key
	preset_.update(ofToString(key-'0'));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
