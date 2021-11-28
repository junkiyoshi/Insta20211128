#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofNoFill();
	ofSetCircleResolution(72);

	for (int radius = 50; radius <= 250; radius += 100) {

		vector<glm::vec2> base_location_group;
		for (float deg = 0; deg < 360; deg += 5) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			base_location_group.push_back(location);
		}

		this->base_location_group_list.push_back(base_location_group);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->log_list.clear();

	for (auto& base_location_group : this->base_location_group_list) {
	
		for (auto& base_location : base_location_group) {

			vector<glm::vec2> log;
			log.push_back(glm::vec2(base_location));
			this->log_list.push_back(log);
		}
	}


	int step = 1;
	for (int i = 0; i < this->log_list.size(); i++) {

		int k = 0;
		int group = i / 72;
		int radius = 50 + 100 * group;
		while (true) {

			auto deg = ofMap(ofNoise(glm::vec4(radius, this->log_list[i].back() * 0.0035, ofGetFrameNum() * ofMap(group, 0, 5, 0.003, 0.008) + k * 0.0005)), 0, 1, -360, 360);
			auto next = this->log_list[i].back() + glm::vec2(step * cos(deg * DEG_TO_RAD), step * sin(deg * DEG_TO_RAD));
			auto length = glm::length(next);

			if (length > radius - 40 && length < radius + 40) {

				this->log_list[i].push_back(next);
			}
			else {

				break;
			}

			k++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	
	ofColor color;
	for (int i = 0; i < this->log_list.size(); i++) {
		
		ofSetLineWidth(1.2);

		int group = i / 72;
		color.setHsb(ofMap(group, 0, 3, 0, 255), 255, 255);
		ofSetColor(color);
		
		if (this->log_list[i].size() > 1) {

			ofNoFill();
			ofBeginShape();
			ofVertices(this->log_list[i]);
			ofEndShape();
		}

		int radius = 50 + 100 * group;
		ofDrawCircle(glm::vec2(), radius);

		ofSetLineWidth(3);
		ofDrawCircle(glm::vec2(), radius - 40);
		ofDrawCircle(glm::vec2(), radius + 40);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}