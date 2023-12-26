#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ProcessStep
{
public:
    virtual void execute() const = 0;
    virtual void showDescription() const = 0;
    virtual ~ProcessStep() {}
};

class TitleStep : public ProcessStep
{
private:
    string title, subtitle;

public:
    TitleStep(const string& title, const string& subtitle) : title(title), subtitle(subtitle) {}

    void execute() const override
    {
        cout << "Title Step:\n";
        cout << "Title: " << title << endl;
        cout << "Subtitle: " << subtitle << endl;
    }

    void showDescription() const override
    {
        cout << "Title Step\n";
        cout << "Title: " << title << endl;
        cout << "Subtitle: " << subtitle << endl;
    }
};

class TextStep : public ProcessStep
{
private:
    string title, copy;

public:
    TextStep(const string& title, const string& copy) : title(title), copy(copy) {}

    void execute() const override
    {
        cout << "Text Step:\n";
        cout << "Title:" << title << endl;
        cout << "Copy: " << copy << endl;
    }

    void showDescription() const override
    {
        cout << "Text Step\n";
        cout << "Title: " << title << endl;
        cout << "Copy: " << copy << endl;
    }
};

class TextInputStep : public ProcessStep
{
private:
    string description, textInput;

public:
    TextInputStep(const string& description, const string& textInput) : description(description), textInput(textInput) {}

    void execute() const override
    {
        cout << "Text Input Step:\n";
        cout << "Description: " << description << endl;
        cout << "Text Input: " << textInput << endl;
    }

    void showDescription() const override
    {
        cout << "Text Input Step\n";
        cout << "Description: " << description << endl;
        cout << "Text Input: " << textInput << endl;
    }
};


class NumberInputStep : public ProcessStep
{
private:
    string description;
    float numberInput;

public:
    NumberInputStep(const string& description, float numberInput) : description(description), numberInput(numberInput) {}

    void execute() const override
    {
        cout << "Number Input Step\n";
        cout << "Description: " << description << endl;
        cout << "Number Input: " << numberInput << endl;
    }

    void showDescription() const override
    {
        cout << "Number Input Step\n";
        cout << "Description: " << description << endl;
        cout << "Number Input: " << numberInput << endl;
    }
};


class CalculusStep : public ProcessStep
{
private:
    int steps;
    string operation;

public:
    CalculusStep(int steps, const string& operation) : steps(steps), operation(operation) {}

    void execute() const override
    {
        cout << "Calculus Step\n";
        cout << "Steps: " << steps << endl;
        cout << "Operation: " << operation << endl;
    }

    void showDescription() const override
    {
        cout << "Calculus Step\n";
        cout << "Steps: " << steps << endl;
        cout << "Operation: " << operation << endl;
    }
};

class DisplayStep : public ProcessStep
{
private:
    int step;

public:
    DisplayStep(int step) : step(step) {}

    void execute() const override
    {
        cout << "Display Step\n";
        cout << "Information from Step " << step+ 1 << ":\n";
        steps[step]->showDescription();
    }

    void showDescription() const override {
        cout << "Display Step\n";
        cout << "Information from Step " << step + 1 << ":\n";
        steps[step]->showDescription();
    }

};

class TextFileStep : public ProcessStep
{
private:
    string description, fileName;

public:
    TextFileStep(const string& description, const string& fileName) : description(description), fileName(fileName) {}

    void execute() const override
    {
        cout << "Text File Input Step\n";
        cout << "Description: " << description << endl;
        cout << "File Name: " << fileName << endl;
    }

    void showDescription() const override
    {
        cout << "Text File Input Step\n";
        cout << "Description: " << description << endl;
        cout << "File Name: " << fileName << endl;
    }
};

class CSVFileStep : public ProcessStep
{
private:
    string description, fileName;

public:
    CSVFileStep(const string& description, const string& fileName) : description(description), fileName(fileName) {}

    void execute() const override
    {
        cout << "CSV File Input Step\n";
        cout << "Description: " << description << endl;
        cout << "File Name: " << fileName << endl;
    }

    void showDescription() const override
    {
        cout << "CSV File Input Step\n";
        cout << "Description: " << description << endl;
        cout << "File Name: " << fileName << endl;
    }
};

class OutputStep : public ProcessStep
{
private:
    int step;
    string fileName, title, description;

public:
    OutputStep(int step, const string& fileName, const string& title, const string& description) : step(step), fileName(fileName), title(title), description(description) {}

    void execute() const override
    {
        cout << "Output Step\n";
        cout << "Step: " << step << endl;
        cout << "File Name: " << fileName << endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
    }

    void showDescription() const override
    {
        cout << "Output Step\n";
        cout << "Step: " << step << endl;
        cout << "File Name: " << fileName << endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
    }
};

class EndStep : public ProcessStep
{
public:
    void execute() const override
    {
        cout << "End of the process\n";
    }

    void showDescription() const override
    {
        cout << "End Step\n";
        cout << "This is the end step\n";
    }
};


class Process {
private:
    vector<ProcessStep*> steps;
    vector<int> numberInputStepsIndex;
    vector<int> textOrCSVInputStepsIndex;
    int currentStepIndex;

public:

    Process() : currentStepIndex(0) {}

    void addStep(ProcessStep* step) {
        steps.push_back(step);
    }

    void executeProcess() const {
        for (const auto& step : steps) {
            step->execute();
        }
    }

    void clearProcess() {
        for (auto step : steps) {
            delete step;
        }
        steps.clear(); // Golește vectorul de pași
    }
    void createNewFlow() {
        clearProcess();

        TitleStep* titleStep = new TitleStep("New Introduction", "New Subtitle");
        addStep(titleStep);

        TextStep* textStep = new TextStep("New Text Step", "Sample text for new step");
        addStep(textStep);

        NumberInputStep* numberInputStep = new NumberInputStep("Enter a new number:", 20.8);
        addStep(numberInputStep);

        executeProcess();
    }

    void showAvailableSteps() const {
        cout << "Available Steps and Descriptions:\n";
        for (int i = 0; i < steps.size(); i++) {
            cout << "Step " << i + 1 << ":\n";
            steps[i]->showDescription();
            cout << endl;
        }
    }

    ~Process() {
        for (auto step : steps) {
            delete step;
        }
    }

    void skipStep() {
        if (currentStepIndex < steps.size() - 1) {
            currentStepIndex++;
            cout << "Skipped to next step.\n";
            steps[currentStepIndex]->execute();
        }
        else {
            cout << "Already at the last step.\n";
        }
    }

    void addTitleStep(const string& title, const string& subtitle) {
        TitleStep* titleStep = new TitleStep(title, subtitle);
        addStep(titleStep);
    }

    void addTextStep(const string& title, const string& copy) {
        TextStep* textStep = new TextStep(title, copy);
        addStep(textStep);
    }

    void addTextInputStep(const string& description, const string& textInput) {
        TextInputStep* textInputStep = new TextInputStep(description, textInput);
        addStep(textInputStep);
    }

    void addNumberInputStep(const string& description, float numberInput) {
        NumberInputStep* numberInputStep = new NumberInputStep(description, numberInput);
        steps.push_back(numberInputStep);
        numberInputStepsIndex.push_back(steps.size() - 1); // Indexul pașului de tip NumberInput
    }

    void addCalculusStep(int step1Index, int step2Index, const string& operation) {
        if (step1Index < 0 || step2Index < 0 || step1Index >= numberInputStepsIndex.size() || step2Index >= numberInputStepsIndex.size()) {
            cerr << "Invalid step index.\n";
            return;
        }

        int realStep1Index = numberInputStepsIndex[step1Index];
        int realStep2Index = numberInputStepsIndex[step2Index];

        if (realStep1Index == realStep2Index) {
            cerr << "Cannot perform operation on the same step.\n";
            return;
        }

        ProcessStep* step1 = steps[realStep1Index];
        ProcessStep* step2 = steps[realStep2Index];

        if (!(step1->showDescription().find("Number Input") != string::npos && step2->showDescription().find("Number Input") != string::npos)) {
            cerr << "Invalid steps for calculus operation. Please use NUMBER INPUT steps.\n";
            return;
        }

        float input1 = static_cast<NumberInputStep*>(step1)->getNumberInput();
        float input2 = static_cast<NumberInputStep*>(step2)->getNumberInput();

        float result;
        if (operation == "+") {
            result = input1 + input2;
        }
        else if (operation == "-") {
            result = input1 - input2;
        }
        else if (operation == "*") {
            result = input1 * input2;
        }
        else if (operation == "/") {
            if (input2 == 0) {
                cerr << "Cannot divide by zero.\n";
                return;
            }
            result = input1 / input2;
        }
        else if (operation == "min") {
            result = min(input1, input2);
        }
        else if (operation == "max") {
            result = max(input1, input2);
        }
        else {
            cerr << "Invalid operation.\n";
            return;
        }

        cout << "Calculus Step Result:\n";
        cout << "Operation: Step " << realStep1Index + 1 << " " << operation << " Step " << realStep2Index + 1 << endl;
        cout << "Result: " << result << endl;
    }

    void addDisplayStep(int previousStepIndex) {
        if (previousStepIndex < 0 || previousStepIndex >= steps.size()) {
            cerr << "Invalid previous step index.\n";
            return;
        }

        if (!(steps[previousStepIndex]->showDescription().find("Text Input") != string::npos || steps[previousStepIndex]->showDescription().find("CSV File") != string::npos)) {
            cerr << "Previous step must be TEXT INPUT or CSV INPUT.\n";
            return;
        }

        DisplayStep* displayStep = new DisplayStep(previousStepIndex);
        steps.push_back(displayStep);
    }

    void addTextInputStep(const string& description, const string& textInput) {
        TextInputStep* textInputStep = new TextInputStep(description, textInput);
        steps.push_back(textInputStep);
        textOrCSVInputStepsIndex.push_back(steps.size() - 1); // Indexul pasului de tip TEXT INPUT
    }

    void addCSVFileStep(const string& description, const string& fileName) {
        CSVFileStep* csvFileStep = new CSVFileStep(description, fileName);
        steps.push_back(csvFileStep);
        textOrCSVInputStepsIndex.push_back(steps.size() - 1); // Indexul pasului de tip CSV INPUT
    }
};

int main() {
    Process myProcess;
    bool stepsAlreadyShown = false;

    try {
        /*
        // Proces pentru pasul de titlu
        TitleStep* titleStepProcess = new TitleStep("Introduction", "Subtitle");
        myProcess.addTitleStep("Introduction", "Subtitle");


        // Proces pentru pasul de text
        TextStep* textStepProcess = new TextStep("Text Step", "Sample text for step");
        myProcess.addTextStep("Text Step", "Sample text for step");

        // Proces pentru pasul de text input
        TextInputStep* textInputStepProcess = new TextInputStep("Description for text input:", "Sample text input");
        mmyProcess.addTextInputStep("Description for text input:", "Sample text input");

        // Proces pentru pasul de input numerice
        NumberInputStep* numberInputStepProcess = new NumberInputStep("Description for number input:", 10.5);
        myProcess.addNumberInputStep("Description for number input:", 10.5);

        // Proces pentru pasul de calcul
        CalculusStep* calculusStepProcess = new CalculusStep(5, "Addition");
        myProcess.addStep(calculusStepProcess);

        // Proces pentru pasul de afișare
        DisplayStep* displayStepProcess = new DisplayStep(3);
        myProcess.addStep(displayStepProcess);

        // Proces pentru pasul de fișier text
        TextFileStep* textFileStepProcess = new TextFileStep("Description for text file input", "example.txt");
        myProcess.addStep(textFileStepProcess);

        // Proces pentru pasul de fișier CSV
        CSVFileStep* csvFileStepProcess = new CSVFileStep("Description for CSV file input", "data.csv");
        myProcess.addStep(csvFileStepProcess);

        // Proces pentru pasul de output
        OutputStep* outputStepProcess = new OutputStep(4, "output.txt", "Output File", "Description for output file");
        myProcess.addStep(outputStepProcess);

        // Proces pentru pasul de finalizare
        EndStep* endStepProcess = new EndStep();
        myProcess.addStep(endStepProcess);
        */

        myProcess.addTitleStep("Introduction", "Subtitle");
        myProcess.addTextStep("Text Step", "Sample text for step");

        myProcess.addNumberInputStep("Description for number input:", 10.5);
        myProcess.addNumberInputStep("Another description for number input:", 20.8);

        myProcess.showAvailableSteps();

        myProcess.addCalculusStep(0, 1, "+");
        myProcess.addCalculusStep(0, 1, "*");

        // Afisarea pasilori disponibi + descrieri
        myProcess.showAvailableSteps();

        // Executarea fluxului creat
        myProcess.executeProcess();

        // Crearea unui nou flux
        myProcess.createNewFlow();

        myProcess.addTextInputStep("Description for text input:", "Sample text input");
        myProcess.addCSVFileStep("Description for CSV file input", "data.csv");

        myProcess.addDisplayStep(0); 
        myProcess.addDisplayStep(1); 

    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    // Skip a step
    char choice;
    cout << "Do you want to skip the current step? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        myProcess.skipStep();
    }

    return 0;
}
