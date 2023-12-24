#include "Flow.hpp"
#include <iostream>

using namespace std;

void TitleStep::execute() {
	cout << "Title step" << endl;
}

void TextInputStep::execute() {
	cout << "Text Input Step" << endl;
}


Flow::Flow(const string& flowName) : name(flowName), currentStep(0), totalSteps(0) {}

void Flow::addStep(Step* step) {
	if (totalSteps < 10) {
		steps[totalSteps++] = step;
	}
	else {
		cout << "Flow reached maximum stepts!\n";
	}
}

void Flow::run() {
	while (currentStep < totalSteps) {
		steps(currentStep)->execute();
		// navigating through steps
		currentStep++;
	}
}