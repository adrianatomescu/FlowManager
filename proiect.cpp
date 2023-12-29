#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <ctime>

using namespace std;

// Clasa pentru gestionarea pasilor
class Step
{
public:
    virtual void displayStepInfo() const = 0;
    virtual void writeDetailsToFile(ofstream &file) const = 0;
    virtual string getStepName() const = 0;
    virtual ~Step() {}
};

// Clasa pentru gestionarea proceselor
class Process
{
private:
    string name;
    Step *steps[100]; // numarul maxim de pasi
    int stepCount;    // numarul actual de pasi

public:
    Process(const string &name) : name(name), stepCount(0)
    {
        for (int i = 0; i < 100; i++)
        {
            steps[i] = nullptr;
        }
    }

    // Metoda pentru adăugarea unui pas în proces
    void addStep(Step *newStep)
    {
        if (stepCount < 100)
        {
            steps[stepCount] = newStep;
            stepCount++;
        }
        else
        {
            cout << "Numarul maxim de pasi a fost atins." << endl;
        }
    }

    int getStepCount() const
    {
        return stepCount;
    }

    Step *getStep(int index) const
    {
        if (index >= 0 && index < stepCount)
        {
            return steps[index];
        }
        return nullptr;
    }

    ~Process() {}
};

// Clasa pentru TITLE Step
class TitleStep : public Step
{
private:
    string title, subtitle;

public:
    TitleStep(const string &title, const string &subtitle) : title(title), subtitle(subtitle) {}

    string getStepName() const override
    {
        return "TITLE";
    }

    void displayStepInfo() const override
    {
        cout << "Title: " << title << endl;
        cout << "Subtitle: " << subtitle << endl;
    }

    void writeDetailsToFile(ofstream &file) const
    {
        file << "TITLE Step" << endl;
        file << "Title: " << title << endl;
        file << "Subtitle: " << subtitle << endl;
    }
};

// Clasa pentru TEXT Step
class TextStep : public Step
{
private:
    string title, copy;

public:
    TextStep(const string &title, const string &copy) : title(title), copy(copy) {}

    string getStepName() const override
    {
        return "TEXT";
    }

    void displayStepInfo() const override
    {
        cout << "Title: " << title << endl;
        cout << "Copy: " << copy << endl;
    }

    void writeDetailsToFile(ofstream &file) const
    {
        file << "TEXT Step" << endl;
        file << "Title: " << title << endl;
        file << "Text: " << copy << endl;
    }
};

// Clasa pentru TEXT INPUT Step
class TextInputStep : public Step
{
private:
    string description, textInput;

public:
    TextInputStep(const string &description, const string &textInput) : description(description), textInput(textInput) {}

    string getStepName() const override
    {
        return "TEXT INPUT";
    }

    void displayStepInfo() const override
    {
        cout << "Description: " << description << endl;
        cout << "Text Input: " << textInput << endl;
    }

    void writeDetailsToFile(ofstream &file) const
    {
        file << "TEXT INPUT Step" << endl;
        file << "Descriere: " << description << endl;
        file << "Text: " << textInput << endl;
    }
};

// Clasa pentru NUMBER INPUT Step
class NumberInputStep : public Step
{
private:
    string description;
    float numberInput;

public:
    NumberInputStep(const string &description, float numberInput) : description(description), numberInput(numberInput) {}

    string getStepName() const override
    {
        return "NUMBER INPUT";
    }

    void displayStepInfo() const override
    {
        cout << "Description: " << description << endl;
        cout << "Number Input: " << numberInput << endl;
    }

    void writeDetailsToFile(ofstream &file) const
    {
        file << "NUMBER INPUT Step" << endl;
        file << "Descriere: " << description << endl;
        file << "Numar: " << numberInput << endl;
    }
};

// Clasa pentru CALCULUS Step
class CalculusStep : public Step
{
private:
    int steps;
    string operation;

public:
    CalculusStep(int steps, const string &operation) : steps(steps), operation(operation) {}

    string getStepName() const override
    {
        return "CALCULUS";
    }

    void displayStepInfo() const override
    {
        cout << "Steps: " << steps << endl;
        cout << "Operation: " << operation << endl;
    }

    void writeDetailsToFile(ofstream &file) const
    {
        file << "CALCULUS Step" << endl;
        file << "Numar: " << steps << endl;
        file << "Operatie: " << operation << endl;
    }
};

// Clasa pentru DISPLAY Steps
class DisplaySteps : public Step
{
private:
    int step;

public:
    DisplaySteps(int step) : step(step) {}

    string getStepName() const override
    {
        return "DISPLAY";
    }

    void displayStepInfo() const override
    {
        cout << "Step: " << step << endl;
    }

    void writeDetailsToFile(ofstream &file) const
    {
        file << "DISPLAY Step" << endl;
        file << "Numar: " << step << endl;
    }
};

// Clasa pentru TEXT FILE Input Step
class TextFileInputStep : public Step
{
private:
    string description, fileName;

public:
    TextFileInputStep(const string &description, const string &fileName) : description(description), fileName(fileName) {}

    string getStepName() const override
    {
        return "TEXT FILE";
    }

    void displayStepInfo() const override
    {
        cout << "Description: " << description << endl;
        cout << "File Name: " << fileName << endl;
    }

    void writeDetailsToFile(ofstream &file) const
    {
        file << "TEXT FILE INPUT Step" << endl;
        file << "Descriere: " << description << endl;
        file << "Nume fisier: " << fileName << endl;
    }
};

// Clasa pentru CSV FILE Input Step
class CSVFileInputStep : public Step
{
private:
    string description, fileName;

public:
    CSVFileInputStep(const string &description, const string &fileName) : description(description), fileName(fileName) {}

    string getStepName() const override
    {
        return "CSV FILE";
    }

    void displayStepInfo() const override
    {
        cout << "Description: " << description << endl;
        cout << "File Name: " << fileName << endl;
    }

    void writeDetailsToFile(ofstream &file) const
    {
        file << "CSV FILE INPUT Step" << endl;
        file << "Descriere: " << description << endl;
        file << "Nume fisier: " << fileName << endl;
    }
};

// Clasa pentru OUTPUT Step
class OutputStep : public Step
{
private:
    int step;
    string fileName, title, description;

public:
    OutputStep(int step, const string &fileName, const string &title, const string &description) : step(step), fileName(fileName), title(title), description(description) {}

    string getStepName() const override
    {
        return "OUTPUT FILE";
    }

    void displayStepInfo() const override
    {

        cout << "Step: " << step << endl;
        cout << "File Name: " << fileName << endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
    }

    void writeDetailsToFile(ofstream &file) const
    {
        file << "OUTPUT Step" << endl;
        file << "Step: " << step << endl;
        file << "File Name: " << fileName << endl;
        file << "Title: " << title << endl;
        file << "Description: " << description << endl;
    }
};

// Clasa pentru END Step
class EndStep : public Step
{

    string getStepName() const override
    {
        return "END";
    }

    void displayStepInfo() const override
    {
        cout << "Sfarsitul procesului" << endl;
    }

    void writeDetailsToFile(ofstream &file) const
    {
        file << "END Step" << endl;
    }
};

// Afisare pasi disponibili
void displayAvailableSteps()
{
    cout << "Pasi disponibili:\n";
    cout << "1.TITLE step: title (string), subtitle (string)\n";
    cout << "2.TEXT step: title (string), copy (string)\n";
    cout << "3.TEXT INPUT step: description (string), text input (string)\n";
    cout << "4.NUMBER INPUT step: description (string), number input (float)\n";
    cout << "5.CALCULUS step: steps (integer), operation (string)\n";
    cout << "6.DISPLAY steps: step (integer)\n";
    cout << "7.TEXT FILE input step: description, file_name\n";
    cout << "8.CSV FILE input step: description, file_name\n";
    cout << "9.OUTPUT step: step (integer), name of file (string), title (text), description (text)\n";
    cout << "10.END step\n";
}

// Afisare creare proces(timestamp)
std::string generateTimestamp() {
    std::string timestamp;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    timestamp = std::to_string(ltm->tm_mday) + "/" +
                std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(1900 + ltm->tm_year) +
                std::to_string(ltm->tm_hour) + ":" +
                std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec);

    return timestamp;
}

// Adaugare proces
void addStepsToProcess(ofstream &file)
{
    file.open("procese.txt", ios::app);

    if (!file.is_open())
    {
        cout << "Nu s-a putut deschide fisierul pentru adaugarea proceselor." << endl;
        return;
    }

    Process *newProcess = new Process("Nume proces");

    string processDescription;
    cout << "Introduceti titlul procesului: ";
    cin.ignore();
    getline(cin, processDescription);

    file << processDescription << endl;

    int option;
    do
    {
        displayAvailableSteps();
        cout << "Alegeti un pas din lista de pasi disponibili (1-10):";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            string title, subtitle;
            cout << "Introduceti titlul: ";
            cin.ignore();
            getline(cin, title);
            cout << "Introduceti subtitlul: ";
            getline(cin, subtitle);

            file << "TITLE step\n";
            file << "Titlu: " << title << "\n";
            file << "Subtitlu: " << subtitle << "\n";
            break;
        }
        case 2:
        {
            string title, copy;
            cout << "Introduceti titlul: ";
            cin.ignore();
            getline(cin, title);
            cout << "Introduceti textul: ";
            getline(cin, copy);
            newProcess->addStep(new TextStep(title, copy));
            break;
        }

        case 3:
        {
            string description, textInput;
            cout << "Introduceti descrierea: ";
            cin.ignore();
            getline(cin, description);
            cout << "Introduceti textul: ";
            getline(cin, textInput);
            newProcess->addStep(new TextInputStep(description, textInput));
            break;
        }

        case 4:
        {
            string description;
            float numberInput;
            cout << "Introduceti descrierea: ";
            cin.ignore();
            getline(cin, description);
            cout << "Introduceti un numar: ";
            cin >> numberInput;
            newProcess->addStep(new NumberInputStep(description, numberInput));
            break;
        }

        case 5:
        {
            int steps;
            string operation;
            cout << "Introduceti un numar: ";
            cin >> steps;
            cout << "Introduceti operatia: ";
            cin.ignore();
            getline(cin, operation);
            newProcess->addStep(new CalculusStep(steps, operation));
            break;
        }

        case 6:
        {
            int step;
            cout << "Introduceti un numar: ";
            cin >> step;
            newProcess->addStep(new DisplaySteps(step));
            break;
        }

        case 7:
        {
            string description, fileName;
            cout << "Introduceti descrierea: ";
            cin.ignore();
            getline(cin, description);
            cout << "Introduceti numele fisierului: ";
            cin.ignore();
            getline(cin, fileName);
            newProcess->addStep(new TextFileInputStep(description, fileName));
            break;
        }

        case 8:
        {
            string description, fileName;
            cout << "Introduceti descrierea: ";
            cin.ignore();
            getline(cin, description);
            cout << "Introduceti numele fisierului: ";
            cin.ignore();
            getline(cin, fileName);
            newProcess->addStep(new CSVFileInputStep(description, fileName));
            break;
        }

        case 9:
        {
            int step;
            string fileName, title, description;
            cout << "Introduceti un numar: ";
            cin >> step;
            cout << "Introduceti numele fisierului: ";
            cin.ignore();
            getline(cin, fileName);
            cout << "Introduceti titlul: ";
            cin.ignore();
            getline(cin, title);
            cout << "Introduceti descrierea: ";
            cin.ignore();
            getline(cin, description);
            newProcess->addStep(new OutputStep(step, fileName, title, description));
            break;
        }

        case 10: // Daca utilizatorul introduce 10, se opreste adaugarea
            break;

        default:
            cout << "Optiune invalida!" << endl;
            break;
        }
    } while (option != 10);

    delete newProcess;

    file << "END step\n\n";
    file.close();
}

// Afisare continut fisier
void displayFileContents(const string &fileName)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "Nu s-a putut deschide fisierul." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

// Sarirea unui anumit pas
void skipProcessStep(Process *currentProcess)
{
    string stepNameToSkip;
    cout << "Introduceti numele pasului pe care doriti sa il sariti: ";
    cin.ignore();
    getline(cin, stepNameToSkip);

    Step *stepToSkipPtr = nullptr;
    for (int i = 0; i < currentProcess->getStepCount(); ++i)
    {
        Step *currentStep = currentProcess->getStep(i);
        if (currentStep->getStepName() == stepNameToSkip)
        {
            stepToSkipPtr = currentStep;
            break;
        }
    }

    if (stepToSkipPtr == nullptr)
    {
        cout << "Pasul introdus nu exista in proces." << endl;
        return;
    }

    if (dynamic_cast<EndStep *>(stepToSkipPtr))
    {
        cout << "Nu puteti sa sariti peste pasul END." << endl;
        return;
    }

    cout << "Procesul ruleaza fara pasul: ";
    stepToSkipPtr->displayStepInfo();
    cout << "Proces rulat cu succes!" << endl;
}

// Rulare proces
void runProcess(const string &processName)
{
    ifstream file("procese.txt");

    if (!file.is_open())
    {
        cout << "Nu s-a putut deschide fisierul de procese." << endl;
        return;
    }

    bool processFound = false;
    string line;
    while (getline(file, line))
    {
        if (line == processName)
        {
            processFound = true;
            break;
        }
    }

    file.close();

    if (!processFound)
    {
        cout << "Procesul " << processName << " nu a fost gasit." << endl;
        return;
    }

    ifstream processFile("procese.txt");
    if (!processFile.is_open())
    {
        cout << "Nu s-a putut deschide fisierul de procese." << endl;
        return;
    }

    cout << "Continutul fisierului de procese:\n";
    while (getline(processFile, line))
    {
        cout << line << endl;
    }
    processFile.close();

    Process *currentProcess = new Process(processName);
    ifstream processFile2("procese.txt");
    if (!processFile2.is_open())
    {
        cout << "Nu s-a putut deschide fisierul de procese." << endl;
        return;
    }

    while (getline(processFile2, line))
    {
        if (line == processName)
        {
            while (getline(processFile2, line))
            {
                if (line == "END step")
                {
                    break;
                }

                if (line == "TITLE step")
                {
                    string title, subtitle;
                    getline(processFile2, title);
                    getline(processFile2, subtitle);
                    currentProcess->addStep(new TitleStep(title.substr(7), subtitle.substr(11)));
                }
                else if (line == "TEXT step")
                {
                    string title, copy;
                    getline(processFile2, title);
                    getline(processFile2, copy);
                    currentProcess->addStep(new TextStep(title.substr(7), copy.substr(6)));
                }
                else if (line == "TEXT INPUT step")
                {
                    string description, textInput;
                    getline(processFile2, description);
                    getline(processFile2, textInput);
                    currentProcess->addStep(new TextInputStep(description.substr(12), textInput.substr(10)));
                }
                else if (line == "NUMBER INPUT step")
                {
                    string description;
                    float numberInput;
                    getline(processFile2, description);
                    processFile2 >> numberInput;
                    processFile2.ignore();
                    currentProcess->addStep(new NumberInputStep(description.substr(12), numberInput));
                }
                else if (line == "CALCULUS step")
                {
                    int steps;
                    string operation;
                    processFile2 >> steps;
                    processFile2.ignore();
                    getline(processFile2, operation);
                    currentProcess->addStep(new CalculusStep(steps, operation.substr(11)));
                }
                else if (line == "DISPLAY steps")
                {
                    int step;
                    processFile2 >> step;
                    processFile2.ignore();
                    currentProcess->addStep(new DisplaySteps(step));
                }
                else if (line == "TEXT FILE input step")
                {
                    string description, fileName;
                    getline(processFile2, description);
                    getline(processFile2, fileName);
                    currentProcess->addStep(new TextFileInputStep(description.substr(0, description.size() - 1), fileName.substr(12)));
                }
                else if (line == "CSV FILE input step")
                {
                    string description, fileName;
                    getline(processFile2, description);
                    getline(processFile2, fileName);
                    currentProcess->addStep(new CSVFileInputStep(description.substr(0, description.size() - 1), fileName.substr(11)));
                }
                else if (line == "OUTPUT step")
                {
                    int step;
                    string fileName, title, description;
                    processFile2 >> step;
                    processFile2.ignore();
                    getline(processFile2, fileName);
                    getline(processFile2, title);
                    getline(processFile2, description);
                    currentProcess->addStep(new OutputStep(step, fileName.substr(12), title.substr(7), description.substr(13)));
                }
            }
            break;
        }
    }

    processFile2.close();

    string userChoice;
    cout << "\nDoriti sa rulati procesul? (da/nu): ";
    cin >> userChoice;

    if (userChoice == "da")
    {
        string skipStepChoice;
        cout << "Doriti sa sariti peste un pas? (da/nu): ";
        cin >> skipStepChoice;

        if (skipStepChoice == "da")
        {
            skipProcessStep(currentProcess);
        }
        else
        {
            cout << "Procesul ruleaza" << endl;
            for (int i = 0; i < currentProcess->getStepCount(); ++i)
            {
                Step *currentStep = currentProcess->getStep(i);
                cout << "Detalii pas " << i + 1 << ":" << endl;
                currentStep->displayStepInfo();
            }

            cout << "Procesul a fost rulat cu succes." << endl;
        }
    }
    else
    {
        cout << "Procesul nu a fost rulat." << endl;
    }

    delete currentProcess;
}

// Stergere proces
void deleteProcess(const string &processName)
{
    ifstream file("procese.txt");

    if (!file.is_open())
    {
        cout << "Nu s-a putut deschide fisierul de procese." << endl;
        return;
    }

    string processNameToDelete;
    cout << "Introduceti numele procesului pe care doriti sa-l stergeti: ";
    cin >> processNameToDelete;

    file.close();

    ifstream inputFile("procese.txt");
    ofstream tempFile("temp.txt");

    if (!inputFile.is_open() || !tempFile.is_open())
    {
        cout << "Eroare la deschiderea fisierelor." << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(inputFile, line))
    {
        if (line == processNameToDelete)
        {
            found = true;
            while (getline(inputFile, line))
            {
                if (line == "END step")
                {
                    tempFile << line << "\n\n";
                    break;
                }
            }
        }
        else
        {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (!found)
    {
        cout << "Procesul cu numele " << processNameToDelete << " nu a fost gasit." << endl;
        remove("temp.txt");
    }
    else
    {
        remove("procese.txt");
        rename("temp.txt", "procese.txt");
        cout << "Procesul cu numele " << processNameToDelete << " a fost sters cu succes." << endl;
    }
}

// Stergere pas
void deleteStep(const string &processName, const string &stepName)
{
    ifstream file("procese.txt");

    if (!file.is_open())
    {
        cout << "Nu s-a putut deschide fisierul de procese." << endl;
        return;
    }

    file.close();

    ifstream inputFile("procese.txt");
    ofstream tempFile("temp.txt");

    if (!inputFile.is_open() || !tempFile.is_open())
    {
        cout << "Eroare la deschiderea fisierelor." << endl;
        return;
    }

    bool processFound = false;
    bool stepFound = false;
    string line;
    while (getline(inputFile, line))
    {
        if (line == processName)
        {
            processFound = true;
            tempFile << line << endl;

            while (getline(inputFile, line))
            {
                if (line == stepName)
                {
                    stepFound = true;
                    while (getline(inputFile, line))
                    {
                        if (line == "END step")
                        {
                            tempFile << line << "\n\n";
                            break;
                        }
                    }
                }
                else
                {
                    tempFile << line << endl;
                }
            }
        }
        else
        {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (!processFound)
    {
        cout << "Procesul cu numele " << processName << " nu a fost gasit." << endl;
        remove("temp.txt");
    }
    else if (!stepFound)
    {
        cout << "Pasul cu numele " << stepName << " din procesul " << processName << " nu a fost gasit." << endl;
        remove("temp.txt");
    }
    else
    {
        remove("procese.txt");
        rename("temp.txt", "procese.txt");
        cout << "Pasul cu numele " << stepName << " din procesul " << processName << " a fost sters cu succes." << endl;
    }
}

int main()
{
    ofstream file;

    try
    {
        int choice;
        std::string timestamp;

        do
        {
            cout << "Alegeti o optiune:\n";
            cout << "1. Creare proces nou\n";
            cout << "2. Rulare proces\n";
            cout << "3. Stergere proces\n";
            cout << "0. Iesire\n";
            cout << "Optiune: ";
            cin >> choice;
            string processName;

            switch (choice)
            {
            case 1:
                addStepsToProcess(file);
                timestamp = generateTimestamp(); 
                cout << "Proces creat la data: " << timestamp << endl; 
                break;

            case 2:
                cout << "Introduceti numele procesului: ";
                cin >> processName;
                runProcess(processName);
                break;

            case 3:
            {
                string var, stepName;
                cout << "Doriti sa stergeti un proces sau un anumit pas?\n";
                cout << "Tastati optiunea (pas/proces): ";
                cin >> var;
                if (var == "proces" || var == "PROCES")
                {
                    deleteProcess(processName);
                }
                else if (var == "pas" || var == "PAS")
                {
                    string pName, sName;
                    cout << "Introduceti numele procesului din care doriti sa stergeti pasul: ";
                    cin >> pName;
                    cout << "Introduceti numele pasului: ";
                    cin >> sName;
                    deleteStep(pName, sName);
                }
                else
                {
                    cout << "Optiune invalida!" << endl;
                }
                break;
            }

            case 0:
                cout << "Iesire din program." << endl;
                break;

            default:
                cout << "Optiune invalida!" << endl;
                break;
            }
        } while (choice != 0);
    }
    catch (const exception &ex)
    {
        cerr << "A aparut o exceptie: " << ex.what() << endl;
    }
    catch (...)
    {
        cerr << "A aparut o exceptie necunoscuta." << endl;
    }

    return 0;
}