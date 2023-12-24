#include "flow.hpp"
#include <iostream>

using namespace std;

void TitleStep::execute() {
	cout << "Title step\n";
	cout << "Title: " << title << endl;
	cout << "Subtitle: " << subtitle << endl;

}

void TextStep::execute() {
	cout << "Text Step\n";
	cout << "Title: " << title << endl;
	cout << "Copy: " << copy << endl;
}

void TextInputStep::execute() {
	cout << "Text Input Step\n";
	cout << "Description: " << description << endl;
	cout << "Text Input: " << textInput << endl;
}

void NumberInputStep::execute() {
	cout << "Number Input Step\n";
	cout << "Description: " << description << endl;
	cout << "Number Input: " << numberInput << endl;
}

void CalculusStep::execute() {
	cout << "Calculus Step\n";
	cout << "Steps: " << steps << endl;
	cout << "Operation: " << operation << endl;
}

void DisplayStep::execute() {
	cout << "Display Step\n";
	cout << "Step: " << step << endl;
}

void TextFileStep::execute() {
	cout << "Text File Step\n";
	cout << "Description: " << description << endl;
	cout << "File Name: " << fileName << endl;
}

void CSVFileInputStep::execute() {
	cout << "CSV File Input Step\n";
	cout << "Description: " << description << endl;
	cout << "File Name: " << fileName << endl;
}

void OutputStep::execute() {
	cout << "Output Step\n";
	cout << "Step: " << step << endl;
	cout << "File Name: " << fileName << endl;
	cout << "Title: " << title << endl;
	cout << "Description: " << description << endl;
}

void EndStep::execute() {
	cout << "End Step\n";
	cout << "End of the flow reached.\n";
}

FlowManager::FlowManager() : totalFlows(0) {}

void FlowManager::createFlow(const string& flowName) {
	if (totalFlows < 100) {
		flows[totalFlows++] = new Flow(flowName);
	}
	else {
		cout << "Maximum limit reached.\n";
	}
}

void FlowManager::deleteFlow(const string& flowName) {
	for (int i = 0; i < totalFlows, i++) {
		if (flows[i]->getFlowName() == flowName) {
			delete flows[i];
			flows[i] = flows[--totalFlows];
			flows[totalFlows] == nullptr;
			cout << "Flow " << flowName << " deleted.\n";
			return;
		}
	}

	cout << "Flow " << flowName << "not found.\n";
}

void FlowManager::addStepToFlow(const string& flowName, Step* step) {
	for (int i = 0; i < totalFlows; i++) {
		if (flows[i]->getFlowName() == flowName) {
			flows[i]->addStep(step);
			return;
		}
	}
	cout << "Flow " << flowName << "not found.\n";
}

void FlowManager::runFlow(const string& flowName) {
	for (int i = 0; i < totalFlows; i++) {
		if (flows[i]->getFlowName() == flowName) {
			flows[i]->run();
			return;
		}
	}

	cout << "Flow " << flowName << "not found.\n";
}

void FlowManager::addPredefinedSteps(Flow* flow) {

	// Pasii prestabiliti ai fluxului
	Step* titleStep = new TitleStep("Default Title", "Default Subtitle");
	Step* textStep = new TextStep("Default Text Title", "Default Text Copy");
	Step* textInputStep = new TextInputStep("Default Text Input Description", "Default Text Input");
	Step* numberInputStep = new NumberInputStep("Default Number Input Description", 0.0f);
	Step* calculusStep = new CalculusStep(0, "+"); 
	Step* displayStep = new DisplayStep(0); 
	Step* textFileInputStep = new TextFileInputStep("Default Text File Description", "default.txt");
	Step* csvFileInputStep = new CSVFileInputStep("Default CSV File Description", "default.csv");
	Step* outputStep = new OutputStep(0, "output.txt", "Output Title", "Output Description");
	Step* endStep = new EndStep();

	flow->addStep(titleStep);
	flow->addStep(textStep);
	flow->addStep(textInputStep);
	flow->addStep(numberInputStep);
	flow->addStep(calculusStep);
	flow->addStep(displayStep);
	flow->addStep(textFileInputStep);
	flow->addStep(csvFileInputStep);
	flow->addStep(outputStep);
	flow->addStep(endStep);
}

void FlowManager::createFlowWithPredefinedSteps(const string& flowName) {
	if (totalFlows < 100) {
		Flow* newFlow = new Flow(flowName);
		addPredefinedSteps(newFlow); // adaugam pasii prestabiliti la fluxul nou
		flows[totalFlows++] = newFlow;
	}
	else {
		cout << "Maximul limit reached.\n";
	}
}
