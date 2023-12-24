#ifndef FLOW_HPP
#define FLOW_HPP

#include <iostream>
#include <string>

using namespace std;

class Step {
public:
	virtual void execute() = 0;
	virtual string getDescription() const = 0;
};

class TitleStep : public Step {
private:
	string title, subtitle;

public:
	TitleStep(const string& t, const string& st) : title(t), subtitle(st) {}

	void execute() override;
};

class TextStep : public Step {
private:
	string title, copy;

public:
	TextStep(const string& t, const string& c) : title(t), copy(c) {}

	void execute() override;
};

class TextInputStep : public Step {
private:
	string description, textInput;

public:
	TextInputStep(const string& d, const string& input) : description(d), textInput(input) {}

	void execute() override;
};

class NumberInputStep : public Step {
private:
	string description;
	float numberInput;

public:
	NumberInputStep(const string& d, float n) : description(d), numberInput(n) {}

	void execute() override;
};

class CalculusStep : public Step {
private:
	int steps;
	string operation;

public:
	CalculusStep(int s, const string& op) : steps(s), operation(op) {}

	void execute() override;
};

class DisplayStep : public Step {
private:
	int step;

public:
	DisplayStep(int s) : step(s) {}

	void execute() override;
};

class TextFileInputStep : public Step {
private:
	string description, fileName;

public:
	TextFileInputStep(const string& d, const string& f) : description(d), fileName(f) {}

	void execute() override;
};

class CSVFileInputStep : public Step {
private:
	string description, fileName;

public:
	CSVFileInputStep(const string& d, const string& f) : description(d), fileName(f) {}

	void execute() override;
};

class OutputStep : public Step {
private:
	int step;
	string fileName, title, description;

public:
	OutputStep(int s, const string& f, const string& t, const string& d) : step(s), fileName(f), title(t), description(d) {}

	void execute() override;
};

class EndStep : public Step {
public:
	void execute() override;
};

class Flow {
private:
	string flowName;
	Step** steps; // maxim 100 de pasi intr un flux
	int totalSteps, currentStepIndex;
	bool* skippedSteps 

public:
	Flow(const string& name) : flowName(name), totalSteps(0), currentStepIndex(0);
		/*
		* for (int i = 0; i < 100; i++) {
			skippedSteps[i] = false;
		}
		*/
	

	~Flow();
	void addStep(Step* step);
	void run();
	void nextStep();
	void skipToStep(int index);

	string getFlowName() const {
		return flowName;
	}
};

class FlowManager {
private:
	Flow* flows[100]; // maxim 100 fluxturi
	int totalFlows;
	void addPredefinedSteps(Flow* flow);

	FlowManager() : totalFlows(0);
	void createFlow(const string& flowName);
	void deleteFlow(const string& flowName);
	void addStepToFlow(const string& flowName, Step* step);
	void createFlowWithPredefinedSteps(const string& flowName);
	void showAvailableSteps();
	void showStepDescriptions();
	
};

#endif //FLOW_HPP
