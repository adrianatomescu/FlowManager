## OOP 2023 Project: Process Builder

### Vision:
Our vision is to create an intuitive application empowering users to design custom process flows tailored to their work needs, enabling seamless automation and optimization.

### Background:
As digitalization becomes imperative for businesses, there arises a need for transitioning processes into efficient apps capable of automation and optimization. Stakeholders require the ability to effortlessly create, adapt, and analyze flows pertinent to their operations.

### Goal:
Our aim is to develop a process builder tool facilitating users in crafting personalized flows with ease.

### Types of Steps:
- **TITLE Step**: Title (string), Subtitle (string)
- **TEXT Step**: Title (string), Copy (string)
- **TEXT INPUT Step**: Description (string), Text Input (string)
- **NUMBER INPUT Step**: Description (string), Number Input (float)
- **CALCULUS Step**: Steps (integer), Operation (string)
- **DISPLAY Step**: Step (integer)
- **TEXT FILE Input Step**: Description, File Name 
- **CSV FILE Input Step**: Description, File Name
- **OUTPUT Step**: Step (integer), File Name (string), Title (text), Description (text)
- **END Step**

### User Stories:
#### As a User, I Can:
- Build flows using predefined steps.
- Access descriptions of available steps.
- Create new flows effortlessly.
- Navigate linear flows seamlessly.
- Skip any step within a flow.
- Add numerous steps to a flow.
- Incorporate any step type into the flow.
- Customize TITLE, TEXT, TEXT INPUT, NUMBER INPUT, CALCULUS, DISPLAY, TEXT FILE Input, CSV FILE Input, OUTPUT, and END steps.
- Utilize arithmetic operations in CALCULUS steps.
- View results of CALCULUS steps.
- Display file content in DISPLAY steps.
- Import .txt and .csv files.
- Generate text files as output.
- Provide names, titles, and descriptions for output files.
- Include information from previous steps in output files.
- Signal the end of a flow.
- Handle errors during step input.
- Assign names to each created flow.
- Track creation timestamps for flows.
- Execute created flows.
- Progress through each step during flow execution.
- View analytics for each flow, including start/completion counts, screen skip counts, and error statistics.
- Delete flows.

### Requirements:
- Codebase
- Demo (maximum 90 seconds) demonstrating flow creation, execution, and analytics.
- Testing matrix with a minimum of 20 tests covering key functionalities.
- Coverage of OOP concepts:
  - Classes and Objects
  - Constructors and Destructors
  - Encapsulation
  - Inheritance
  - Polymorphism
  - Abstractization
  - Templates
  - Exceptions

### Repository Structure:
- **Codebase**: Contains the project's source code.
- **Demo Video**: Illustrates flow creation, execution, and analytics within 90 seconds.
- **Testing Matrix**: Lists and verifies at least 20 tests covering critical functionalities.
