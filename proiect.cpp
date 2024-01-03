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
    string name, processName;
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

    std::string getName() const
    {
        return processName;
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

    float getNumber() const
    {
        return numberInput;
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
    float result; // Rezultatul operației

public:
    CalculusStep(int steps, const string &operation) : steps(steps), operation(operation), result(0) {}

    string getStepName() const override
    {
        return "CALCULUS";
    }

    void displayStepInfo() const override
    {
        cout << "Steps: " << steps << endl;
        cout << "Operation: " << operation << endl;
        cout << "Result: " << result << endl;
    }

    void writeDetailsToFile(ofstream &file) const override
    {
        file << "CALCULUS Step" << endl;
        file << "Numar: " << steps << endl;
        file << "Operatie: " << operation << endl;
        file << "Rezultat: " << result << endl;
    }

    void performOperation(float inputNumber)
    {
        if (operation == "+")
        {
            result = inputNumber + steps;
        }
        else if (operation == "-")
        {
            result = inputNumber - steps;
        }
        else if (operation == "*")
        {
            result = inputNumber * steps;
        }
        else if (operation == "/")
        {
            if (steps != 0)
            {
                result = inputNumber / steps;
            }
            else
            {
                cout << "Nu se poate împărți la zero." << endl;
            }
        }
        else if (operation == "min")
        {
            result = min(inputNumber, static_cast<float>(steps));
        }
        else if (operation == "max")
        {
            result = max(inputNumber, static_cast<float>(steps));
        }
        else
        {
            cout << "Operație necunoscută." << endl;
        }
    }

    float getResult() const
    {
        return result;
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

    // Metoda pentru a scrie parametrii într-un fișier separat
    void writeParametersToFile() const
    {
        ofstream paramsFile(fileName + "_params.txt");
        if (paramsFile.is_open())
        {
            paramsFile << "Descriere: " << description << endl;
            paramsFile << "Nume fisier: " << fileName << endl;
            paramsFile.close();
            cout << "Parametrii pasului TEXT FILE input au fost scrisi in fisierul " << fileName << "_params.txt" << endl;
        }
        else
        {
            cout << "Nu s-a putut crea fisierul pentru parametrii pasului TEXT FILE input." << endl;
        }
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

    // Metoda pentru a scrie parametrii într-un fișier separat
    void writeParametersToFile() const
    {
        ofstream paramsFile(fileName + "_params.csv");
        if (paramsFile.is_open())
        {
            paramsFile << "Descriere: " << description << endl;
            paramsFile << "Nume fisier: " << fileName << endl;
            paramsFile.close();
            cout << "Parametrii pasului CSV FILE input au fost scrisi in fisierul " << fileName << "_params.csv" << endl;
        }
        else
        {
            cout << "Nu s-a putut crea fisierul pentru parametrii pasului CSV FILE input." << endl;
        }
    }
};

// Clasa pentru DISPLAY Steps
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

    void writeDetailsToFile(ofstream &file) const override
    {
        file << "DISPLAY Step" << endl;
        file << "Numar: " << step << endl;
    }

    void displayFileContent() const
    {
        string fileExtension = (step == 1) ? "_params.txt" : "_params.csv";
        string fileName = (step == 1) ? "nume_fisier_text" : "nume_fisier_csv";

        ifstream fileToDisplay(fileName + fileExtension);
        if (fileToDisplay.is_open()) {
            string line;
            while (getline(fileToDisplay, line)) {
                cout << line << endl;
            }
            fileToDisplay.close();
        } else {
            cout << "Nu s-a putut citi fisierul asociat pasului TextFileInputStep sau CSVFileInputStep." << endl;
        }
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

    void createOutputFile() const
    {
        std::ofstream outputFile(fileName + "_output.txt");

        if (!outputFile.is_open())
        {
            std::cout << "Nu s-a putut crea fisierul de output." << std::endl;
            return;
        }

        outputFile << "Step: " << step << std::endl;
        outputFile << "File Name: " << fileName << std::endl;
        outputFile << "Title: " << title << std::endl;
        outputFile << "Description: " << description << std::endl;

        outputFile.close();
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

// Gestionare erori
class MyException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Exceptie";
    }
};

class FileOperationException : public std::exception
{
public:
    explicit FileOperationException(const std::string &message) : errorMessage(message) {}

    const char *what() const noexcept override
    {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class ProcessNotFoundException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Procesul nu a fost găsit.";
    }
};

class StepNotFoundException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Pasul nu a fost găsit în proces.";
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
std::string generateTimestamp()
{
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
    string fileName;
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
            newProcess->addStep(new TitleStep(title, subtitle));
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
            file << "TEXT step\n";
            file << "Titlu: " << title << "\n";
            file << "Text: " << copy << "\n";
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
            file << "TEXT INPUT step\n";
            file << "Descriere: " << description << "\n";
            file << "Text: " << textInput << "\n";
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
            file << "NUMBER INPUT step\n";
            file << "Descriere: " << description << "\n";
            file << "Numar: " << numberInput << "\n";
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
            file << "CALCULUS step\n";
            file << "Numar: " << steps << "\n";
            file << "Operatie: " << operation << "\n";

            // Verificați existența unui pas anterior de tip NumberInputStep
            bool numberInputFound = false;
            for (int i = 0; i < newProcess->getStepCount(); ++i)
            {
                Step *step = newProcess->getStep(i);
                if (dynamic_cast<NumberInputStep *>(step))
                {
                    numberInputFound = true;
                    float inputNumber = dynamic_cast<NumberInputStep *>(step)->getNumber();
                    CalculusStep *calculusStep = new CalculusStep(steps, operation);

                    // Efectuați operația specificată între parametrii NumberInput și Calculus
                    calculusStep->performOperation(inputNumber);

                    // Adăugați pasul CalculusStep în proces
                    newProcess->addStep(calculusStep);

                    // Afisati rezultatul
                    cout << "Rezultat: " << calculusStep->getResult() << endl;

                    break;
                }
            }

            // Dacă nu a fost găsit un pas de tip NumberInputStep, afișați un mesaj
            if (!numberInputFound)
            {
                cout << "Trebuie să adăugați mai întâi un pas de tip NumberInputStep pentru a efectua o operație Calculus." << endl;
            }
            break;
        }

case 6:
{
    int step;
    cout << "Introduceti un numar (1-txt, 2-csv): ";
    cin >> step;
    file << "DISPLAY INPUT step\n";
    file << "Numar: " << step << "\n";

    if (step == 1 || step == 2) {
        DisplaySteps *displayStep = new DisplaySteps(step);
        newProcess->addStep(displayStep);

        // Afisam continutul fisierului asociat pasului TextFileInputStep sau CSVFileInputStep
        displayStep->displayFileContent();
    } else {
        cout << "Selectie invalida pentru afisare. Va rugam selectati 1 sau 2 pentru afisarea continutului fisierului." << endl;
    }

    break;
}




        case 7:
        {
            string description, fileName;
            cout << "Introduceti descrierea: ";
            cin.ignore();
            getline(cin, description);
            cout << "Introduceti numele fisierului: ";
            getline(cin, fileName);
            file << "TEXT FILE input step\n";
            file << "Descriere: " << description << "\n";
            file << "Nume fisier: " << fileName << "\n";
            TextFileInputStep *textFileStep = new TextFileInputStep(description, fileName);
            textFileStep->writeDetailsToFile(file);
            newProcess->addStep(textFileStep);
            textFileStep->writeParametersToFile();
            break;
        }

        case 8:
        {
            string description, fileName;
            cout << "Introduceti descrierea: ";
            cin.ignore();
            getline(cin, description);
            cout << "Introduceti numele fisierului: ";
            getline(cin, fileName);
            file << "CSV FILE input step\n";
            file << "Descriere: " << description << "\n";
            file << "Nume fisier: " << fileName << "\n";
            CSVFileInputStep *csvFileStep = new CSVFileInputStep(description, fileName);
            csvFileStep->writeDetailsToFile(file);
            newProcess->addStep(csvFileStep);
            csvFileStep->writeParametersToFile();
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
            getline(cin, title);
            cout << "Introduceti descrierea: ";
            getline(cin, description);
            file << "OUTPUT step\n";
            file << "Numar: " << step << "\n";
            file << "Nume fisier: " << fileName << "\n";
            file << "Titlu: " << title << "\n";
            file << "Descriere: " << description << "\n";
            newProcess->addStep(new OutputStep(step, fileName, title, description));

            // Creare fișier de output
            OutputStep output(step, fileName, title, description);
            output.createOutputFile();
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

// Analiza procesului
void analyzeProcess(const string &processName)
{
    ifstream file("procese.txt");

    if (!file.is_open())
    {
        cout << "Nu s-a putut deschide fisierul de procese." << endl;
        return;
    }

    string line;
    int initiatedCount = 0;
    int completedCount = 0;
    int skippedStepCount = 0;
    int errorScreenCount = 0;
    int totalErrors = 0;
    int completedProcessCount = 0;

    bool found = false; // Inițializăm found cu false pentru fiecare rulare
    while (getline(file, line))
    {
        if (line == processName)
        {
            found = true;
            ++initiatedCount; // Incrementăm inițierea procesului găsit

            while (getline(file, line))
            {
                if (line == "END step")
                {
                    ++completedProcessCount;
                    break;
                }
                else if (line == "Procesul ruleaza fara pasul:")
                {
                    getline(file, line); // Trecem peste linia următoare
                    getline(file, line); // Obținem informația despre pas

                    if (line.substr(0, 7) == "Eroare:")
                    {
                        ++errorScreenCount;
                        ++totalErrors;
                    }
                }
                else if (line == "Nu puteti sa sariti peste pasul END.")
                {
                    ++skippedStepCount;
                }
            }
        }
    }

    file.close();

    if (!found)
    {
        cout << "Procesul " << processName << " nu a fost gasit." << endl;
        return;
    }

    cout << "Analiza procesului '" << processName << "':" << endl;
    cout << "De cate ori a fost initiat procesul: " << initiatedCount << endl;
    cout << "De cate ori a fost finalizat fluxul: " << completedProcessCount << endl;
    cout << "De cate ori a fost sarit un pas: " << skippedStepCount << endl;
    cout << "Numarul de ecrane de eroare afisate pentru fiecare pas: " << errorScreenCount << endl;

    if (completedProcessCount > 0)
    {
        double averageErrors = static_cast<double>(totalErrors) / completedProcessCount;
        cout << "Numarul mediu de erori pentru fiecare proces finalizat: " << averageErrors << endl;
    }
    else
    {
        cout << "Nu exista procese finalizate pentru calculul numarului mediu de erori." << endl;
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
            cout << "4. Analiza unui proces\n";
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

            case 4:
            {
                string processToAnalyze;
                cout << "Introduceti numele procesului pe care doriti sa il analizati: ";
                cin >> processToAnalyze;
                analyzeProcess(processToAnalyze);
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
    catch (const FileOperationException &fileEx)
    {
        cerr << "Eroare la operațiile cu fișiere: " << fileEx.what() << endl;
    }
    catch (const ProcessNotFoundException &procEx)
    {
        cerr << "Eroare: " << procEx.what() << endl;
    }
    catch (const StepNotFoundException &stepEx)
    {
        cerr << "Eroare: " << stepEx.what() << endl;
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