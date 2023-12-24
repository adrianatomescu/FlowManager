#ifndef FLOW_HPP
#define FLOW_HPP

#include <iostream>
#include <string>

using namespace std;

class Step {
public:
	virtual void execute() = 0;
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

class FlowManager {
private:
	Flow* flows[100]; // maxim 100 fluxturi
	int totalFlows;
	void addPredefinedSteps(Flow* flow);

public:
	FlowManager();
	void createFlow(const string& flowName);
	void deleteFlow(const string& flowName);
	void addStepToFlow(const string& flowName, Step* step);
	void createFlowWithPredefinedSteps(const string& flowName);
	
};

#endif //FLOW_HPP
