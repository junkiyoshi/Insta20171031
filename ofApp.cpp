#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofSetCircleResolution(32);

	this->box2d.init();
	this->box2d.setGravity(0, 20);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update() {
	for (int i = this->circles.size() - 1; i > -1; i--) {
		if (this->circles_life[i] < 0) {
			this->circles[i].get()->destroy();
			this->circles.erase(this->circles.begin() + i);
			this->circles_life.erase(this->circles_life.begin() + i);
			this->circles_color.erase(this->circles_color.begin() + i);
		}
	}

	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (int i = 0; i < this->circles.size(); i++) {
		ofSetColor(this->circles_color[i], this->circles_life[i]);
		ofDrawCircle(this->circles[i].get()->getPosition().x, this->circles[i].get()->getPosition().y, 8);

		this->circles_life[i] -= 1;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	float radius = 10;
	for (int i = 0; i < 5; i++) {
		float color_value = ofRandom(256);
		for (int deg = 0; deg < 360; deg += 10) {
			float tmp_x = radius * cos(deg * DEG_TO_RAD);
			float tmp_y = radius * sin(deg * DEG_TO_RAD);

			this->circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
			this->circles.back().get()->setPhysics(3.0, 0.5, 0.1);
			this->circles.back().get()->setup(this->box2d.getWorld(), x + tmp_x, y + tmp_y, 8);
			this->circles.back().get()->addForce(ofVec2f(tmp_x, tmp_y), 16.0);

			this->circles_life.push_back(255);

			ofColor circle_color;
			circle_color.setHsb(color_value, 255, 255);
			this->circles_color.push_back(circle_color);
		}

		radius += 10;
	}
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(1920, 1080, OF_WINDOW);
	ofRunApp(new ofApp());
}