#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// Clasa pentru gestionarea pasilor
class Step
{
public:
    virtual void displayStepInfo() const = 0;
    virtual ~Step() {}
};

// Clasa pentru gestionarea proceselor
class Process
{
private:
    string name;
    Step *steps[100]; // numarul maxim de pasi

public:
    Process(const string &name) : name(name)
    {
        for (int i = 0; i < 100; i++)
        {
            steps[i] = nullptr;
        }
    }
};

// Clasa pentru TITLE Step
class TitleStep : public Step
{
private:
    string title, subtitle;

public:
    TitleStep(const string &title, const string &subtitle) : title(title), subtitle(subtitle) {}
};

// Clasa pentru TEXT Step
class TextStep : public Step
{
private:
    string title, copy;

public:
    TextStep(const string &title, const string &copy) : title(title), copy(copy) {}
};

// Clasa pentru TEXT INPUT Step
class TextInputStep : public Step
{
private:
    string description, textInput;

public:
    TextInputStep(const string &description, const string &textInput) : description(description), textInput(textInput) {}
};

// Clasa pentru NUMBER INPUT Step
class NumberInputStep : public Step
{
private:
    string description;
    float numberInput;

public:
    NumberInputStep(const string &description, float numberInput) : description(description), numberInput(numberInput) {}
};

// Clasa pentru CALCULUS Step
class CalculusStep : public Step
{
private:
    int steps;
    string operation;

public:
    CalculusStep(int steps, const string &operation) : steps(steps), operation(operation) {}
};

// Clasa pentru DISPLAY Steps
class DisplaySteps : public Step
{
private:
    int step;

public:
    DisplaySteps(int step) : step(step) {}
};

// Clasa pentru TEXT FILE Input Step
class TextFileInputStep : public Step
{
private:
    string description, fileName;

public:
    TextFileInputStep(const string &description, const string &fileName) : description(description), fileName(fileName) {}
};

// Clasa pentru CSV FILE Input Step
class CSVFileInputStep : public Step
{
private:
    string description, fileName;

public:
    CSVFileInputStep(const string &description, const string &fileName) : description(description), fileName(fileName) {}
};

// Clasa pentru OUTPUT Step
class OutputStep : public Step
{
private:
    int step;
    string fileName, title, description;

public:
    OutputStep(int step, const string &fileName, const string &title, const string &description) : step(step), fileName(fileName), title(title), description(description) {}
};

// Clasa pentru END Step
class EndStep : public Step
{
};

// Citirea proceselor existente din fisier
void readProcessesFromFile(const string& procese) {
    ifstream file(procese);

    if (!file.is_open()) {
        cerr << "Nu am putut deschide fisierul." << endl;
        return;
    }

    string line;
    string title, text, input, display, output;
    while (getline(file, line)) {
        if (!line.empty()) {
            if (line.find("Procesul") != string::npos) {
                continue; 
            }

            size_t pos = line.find("step:");
            if (pos != string::npos) {
                string stepType = line.substr(0, pos); // tipul da pas

                // Detaliile fiecarui pas
                string details = line.substr(pos + 5); // +5 pentru a sari peste "step:"
                if (stepType.find("TITLE") != string::npos) {
                    title = details;
                } else if (stepType.find("TEXT") != string::npos) {
                    text = details;
                } else if (stepType.find("INPUT") != string::npos || stepType.find("NUMBER") != string::npos) {
                    input += details + "\n";
                } else if (stepType.find("DISPLAY") != string::npos) {
                    display = details;
                } else if (stepType.find("OUTPUT") != string::npos) {
                    output = details;
                }
            }
        }

        if (line.find("END step:") != string::npos) {

            title.clear();
            text.clear();
            input.clear();
            display.clear();
            output.clear();
        }
    }

    file.close();
}


// Afisarea proceselor existente
void displayExistingProcesses(const string& procese) {
    ifstream file(procese);

    if (!file.is_open()) {
        cerr << "Nu am putut deschide fisierul." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}


int main() {
    try {
        readProcessesFromFile("procese.txt");

        int choice;
        do {
            cout << "Selecteaza o optiune (1/2):" << endl;
            cout << "1. Alege un proces existent" << endl;
            cout << "2. Adauga un proces nou" << endl;
            cout << "Introduceti optiunea: ";
            cin >> choice;

            if (choice == 1) {
                displayExistingProcesses("procese.txt");
                cout << "\n";
                char modifyOrUse;
                cout << "Doresti sa modifici sau sa folosesti un proces? (M,F): ";
                cin >> modifyOrUse;

                if(modifyOrUse == 'M' || modifyOrUse == 'm') {
                    // logica modificare
                } 
                else if(modifyOrUse == 'F' || modifyOrUse == 'f') {
                    int index;

                    cout << "Selecteaza procesul pe care doresti sa il folosesti (numarul corespunzator): ";
                    cin >> index;
                    --index;
                    // logica alegere
                }

            }
            else if (choice == 2) {
                // logica pentru adaugarea unui proces nou
                break; // optiune valida
            }
            else {
                cout << "Optiune invalida. Te rugam sa introduci din nou." << endl;
            }
        } while (true); //solicita optiunea pana cand este introdus 1/2
    } catch (const exception& ex) {
        cerr << "A aparut o exceptie: " << ex.what() << endl;
    } catch (...) {
        cerr << "A aparut o exceptie necunoscuta." << endl;
    }

    return 0;
}
