# 🐻 🐰 FarmLife 🐷 🐮

**FarmLive** is a project written in **C++** that simulates a two-dimensional world of defined size, inhabited by diverse organisms divided into classes of plants and animals.

## Main goals of the project include:

- Implementing an ancestry history for each organism, stored as a list of birth and death turns, with full support for copy and move constructors as well as appropriate assignment operators that ensure proper updating of genealogical data.
- Extending the world with new types of organisms, along with a proper inheritance model and polymorphic methods for all classes.
- Refactoring the world's serialization and deserialization mechanism according to SOLID principles, so that each object is responsible for saving and loading its own state, enabling easier testing and expansion.
- Transforming the application from a console-based visualization of successive epochs into a version with a graphical user interface using the Qt framework, increasing the simulation’s attractiveness and interactivity.

### GUI Version Preview 🎮
<img width="500" src="https://github.com/user-attachments/assets/6ef1fa76-e1d8-45e2-bcf2-6ebd949d66a8" />

### Console Version Preview 🖥️  
<img width="800" src="https://github.com/user-attachments/assets/aafd0728-f150-477e-847f-72be3213600d" />



# 💻 Technologies Used

FarmLive is built using the following technologies:

📍 C++  
📍 Qt framework for graphical user interface  
📍 qmake build system  
 
 🛠️ Object-Oriented Programming (OOP) principles  
 🛠️ SOLID design principles  
 🛠️ Custom serialization and deserialization mechanisms  
 🛠️ Polymorphism and inheritance models  



# 🏁 Getting Started

To get started with the FarmLife, follow these steps:

1️⃣ Clone the Repository   

Download the repository to your local machine by running the following command in your terminal:  
```bash
git clone https://github.com/hsialitskaya/FarmLife.git FarmLife
```

2️⃣ Install Dependencies  

### System Requirements

- A C++17 compatible compiler (e.g., `g++` 7 or newer)  
- Qt framework (version 5.x or 6.x) installed  
- `qmake` build tool included with Qt  
- Make utility (`make`) installed on your system


3️⃣ Build and Run

- ### GUI Version (Qt-based)
1) From the root directory of the project, build the application using make:  
```bash
make
```

2) Run the built application:
```bash
./Projekt.app/Contents/MacOS/Projekt
```


- ### Console Version
1) Navigate to the core directory:
```bash
cd core
```

2) Compile the project using g++ with C++17 standard:
```bash
g++ -std=c++17 *.cpp -o world_app
```

3) Run the compiled application:
```bash
./world_app
```

## License
FarmLife is licensed under the MIT License. See [LICENSE](https://github.com/hsialitskaya/FarmLife/blob/main/LICENSE) for more information.    

Happy simulating and enjoy exploring the fascinating dynamics of your virtual ecosystem! 🎉
