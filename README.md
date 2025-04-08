# 📚 LibraryManager-C

LibraryManager-C is a lightweight and efficient library management system written in C 📚💻. 
It provides essential features to manage a simple library setup, making it an excellent project for learning core C programming concepts like:

- 🧑‍💻 User registration and login
- 🛠️ Role-based access control (e.g., admin functionality)
- 📘 Book borrowing and returning system
- 💾 Data persistence using text files, with certain operations performed in binary mode

This console-based application is great for practicing file handling, working with structures, and building menu-driven programs in C 🚀🛠️

---

## 🛠️ Features

### 👨‍🎓 Student Side:
- 📥 Register new student account
- 🔐 Login
- 📖 View available books
- 📚 Borrow book
- 🔄 Return book
- 🚪 Logout

### 👨‍💼 Admin Side:
- 🔐 Login (default password: `adminPass` id: 12345)
- ➕ Add books
- ❌ Remove books
- 📑 View all books
- 📋 View all registered students
- 📦 View borrowed book logs
- 🚪 Logout

---

## 🗂️ File Structure

```
LibraryManager-C/
│
├── src/                          # 📌 Modular source files
│   ├── main.c                    # 🔧 Main program logic
│   ├── admin.c                   # 👨‍💼 Admin-related functions
│   ├── books.c                   # 📚 Book-related functions
│   └── student.c                 # 🎓 Student-related functions
│
├── include/                      # 📘 Header files
│   └── lib.h                     # 📄 Shared declarations
│
├── data/                         # 🗃️ Main program data
│   ├── bookNumber.txt            # 🔢 Book number tracker
│   ├── booksData.txt             # 📖 Book information
│   ├── studentNumber.txt         # 🔢 Student number tracker
│   └── studentsData.txt          # 🎓 Student information
│
├── single_file_version/          # 🧍‍♂️ Easy 1-file version for users
│   ├── Library Management System.c  # 💾 All code in one file
│
└── README.md                     # 📄 Project documentation you are here

```

---

### 📁 Single File Version

The `single_file_version/` folder contains a version of the project where all the code is written in a **single `.c` file**. 
This is useful if you want a simplified version without dealing with multiple source files.

---

### 🔧 Requirements

To compile and run this project, you’ll need a **C compiler** like `gcc`.  
You can run the code either from the **terminal** or through an **IDE** like **VS Code**, **Code::Blocks**, or **CLion**.

---

### 🚀 How to Run

#### ✅ Option 1: Run the Full Project (Multi-file version)

1. **Compile the `main.c` file** located inside the `src/` folder.  
2. After compilation, **move to the main project directory** .  
3. Run the generated executable.

Using `gcc`:

```bash
cd src
gcc main.c ../lib/*.c -o ../library
cd ..
./library
```
---

#### ✅ Option 2: Run the Single File Version

1. Go into the `single_file_version/` folder.
2. Compile and run the single `.c` file:

```bash
cd single_file_version
gcc library_single.c -o library
./library
```

---


## 📝 To-Do / Future Improvements

- 🔄 Change admin password feature
- 📊 Track due dates and overdue fines
- 🧹 Clean CLI interface with colors (using ANSI escape codes)
- 🌐 Export reports to `.csv` files
- 🧪 Add unit testing support

---

## 🤝 Contributing

Pull requests are welcome! 🙌 For major changes, please open an issue first to discuss what you would like to change.

---

## 🪪 License

This project is open-source and available under the [MIT License](LICENSE). 📝

---

## 🙌 Acknowledgements

Built with ❤️ in C by **Parth Garg**  
