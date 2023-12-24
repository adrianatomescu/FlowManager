#include "flow.hpp"
#include <iostream>

using namespace std;

TitleStep::TitleStep(const string& t, const string& st) : title(t), subtitle(st) {
	if (title.empty() || subtitle.empty()) {
		throw invalid_argument("Title and subtitle must not be empty.");
	}
}
void TitleStep::execute() {
	cout << "Title step\n";
	cout << "Title: " << title << endl;
	cout << "Subtitle: " << subtitle << endl;

}

TextStep::TextStep(const string& t, const string& c) : title(t), copy(c) {
	if (title.empty() || copy.empty()) {
		throw invalid_argument("Title and copy must not be empty.");
	}
}

void TextStep::execute() {
	cout << "Text Step\n";
	cout << "Title: " << title << endl;
	cout << "Copy: " << copy << endl;
}

TextInputStep::TextInputStep(const string& d, const string& input) : description(d), textInput(input) {
	if (description.empty()) {
		throw invalid_argument("Description must not be empty for Text Input Step.");
	}
}

void TextInputStep::execute() {
	cout << "Text Input Step\n";
	cout << "Description: " << description << endl;
	cout << "Text Input: " << textInput << endl;
}

NumberInputStep::NumberInputStep(const string& d, float n) : description(d), numberInput(n) {
	if (description.empty()) {
		throw invalid_argument("Description must not be empty for Number Input Step.");
	}
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
		cout << "Maximum limit reached.\n";
	}
}

// Implementarea metodelor pentru a afisa descrierile pasilor disponibili
void FlowManager::showAvailableSteps() {
	cout << "Available Steps:\n";
	cout << "1. Title Step: Create a title and a subtitle.\n";
	cout << "2. Text Step: Add a title and a text description.\n";
	cout << "3. Text Input Step: Specify the expected input.\n";
	cout << "4. Number Input Step: Describe the expected number input.\n";
	cout << "5. Calculus Step: Perform mathematical operations on previous inputs.\n";
	cout << "6. Display Step: Show content from a previous step.\n";
	cout << "7. Text File Input Step: Add a .txt file.\n";
	cout << "8. CSV File Input Step: Add a .csv file.\n";
	cout << "9. Output Step: Generate a text file as output.\n";
	cout << "10. End Step: Signal the end of the flow.\n";
}

void FlowManager::showStepDescriptions() {
	cout << "Step Descriptions:\n";
	cout << "Title Step: Create a title and a subtitle.\n";
	cout << "Text Step: Add a title and a text description.\n";
	cout << "Text Input Step: Specify the expected input.\n";
	cout << "Number Input Step: Describe the expected number input.\n";
	cout << "Calculus Step: Perform mathematical operations on previous inputs.\n";
	cout << "Display Step: Show content from a previous step.\n";
	cout << "Text File Input Step: Add a .txt file.\n";
	cout << "CSV File Input Step: Add a .csv file.\n";
	cout << "Output Step: Generate a text file as output.\n";
	cout << "End Step: Signal the end of the flow.\n";
}

void Flow::run() {
	for (int i = 0; i < totalSteps; i++) {
		if (!skippedSteps[i]) {
			currentStepIndex = i; // actualizam indexul pasului curent
			steps[currentStepIndex]->execute();
		}
	}
}

void Flow::nextStep() {
	if (currentStepIndex < totalSteps) {
		currentStepIndex++;
	}
}

void Flow::skipToStep(int index) {
	if (index >= 0 && index < totalSteps) {
		skippedSteps[index] == true;
		if (currentStepIndex == index) {
			nextStep(); // avanseaza la pasul urmator
		}
	}
}