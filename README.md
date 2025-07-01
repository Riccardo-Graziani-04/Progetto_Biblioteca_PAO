# 📚 Progetto Biblioteca PAO

A **library management system** developed in **C++ with Qt**, allowing management of **books, music, and movies** with JSON-based persistent storage. Developed as a project for the **Object Oriented Programming** course at University of Padova.

---

## 🚀 Features

✅ Add, edit, and delete items (books, music, movies)  
✅ JSON file import/export for persistent data storage  
✅ Qt GUI for intuitive interaction  
✅ Search and filter functionality  
✅ MVC-like structure for clean separation of concerns  
✅ Resource icons and images for UI polish

---

## 🛠️ Technologies Used

- **C++** (Object-Oriented Design)
- **Qt Framework** (GUI, event handling)
- **JSON** (data persistence)
- **QMake** (build system)

---

## 🗂️ Project Structure

    Progetto_Biblioteca_PAO/
    │
    ├── Feedback progetto.txt       # Project feedback notes
    ├── LICENSE                     # MIT/Other license
    ├── Pao_Project.pdf             # Project documentation/report
    ├── README.md                   # This file
    │
    └── Progetto_Biblioteca-main/
        ├── main.cpp                        # Entry point
        ├── Progetto_Biblioteca.pro         # Qt project file
        ├── Makefile, .qmake.stash          # Build files
        ├── test_file.json                  # Sample data
        │
        ├── Model/
        │   ├── Items/          # Book, Movie, Music models (inherit from AbstractItem)
        │   ├── JSON/           # JSON file handling, repositories, visitors
        │   ├── Memory/         # In-memory repository management
        │   └── Utility/        # Enums, visitor patterns, utilities
        │
        ├── Resources/
        │   ├── *.png           # Icons for GUI
        │   └── Images/         # Sample cover images
        │
        └── View/
            ├── MainWindow/                 # Main GUI window
            ├── DetailWidgets/              # Detailed item views
            ├── EditWidgets/                # Item creation/editing interfaces
            └── ListWidgets/                # Search, item list, and card views

---

## 🖥️ How to Build

### Requirements:
- Qt 5/6 with Qt Creator
- C++ compiler (GCC/Clang/MSVC)

### Build Steps:

1. Open `Progetto_Biblioteca.pro` in Qt Creator.
2. Click **Configure Project**.
3. Click **Build and Run**.

Or via terminal:

    qmake
    make
    ./Progetto_Biblioteca

---

## 📂 Sample Data

Use `test_file.json` for initial testing, or load your own JSON library file from the GUI.

---

## 📝 License

The project is distributed under the **MIT License** and it's evaluation is contained inside the `Feedback progetto.txt` file.

---

## 📄 Project Report and Evaluation

Detailed functional and design documentation is provided in `Pao_Project.pdf` (written in italian).

---

## 🤝 Contributing

This repository is a university project and is not actively maintained, but contributions are welcome for learning and experimentation. If you are a UniPD student, do not copy this project outright, but use it as a learning tool to build something unique. You can still gain insight on how to structure your project and how to include polymorphism and inheritance.

---
