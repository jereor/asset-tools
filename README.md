# AssetTools — Internal Game Development Tools Prototype



AssetTools is a C++ prototype of an **internal game development tool** designed to support **content creation workflows, asset pipelines, and shared engine technology**.



The project is intentionally scoped as a **tools-side application**, not a game runtime. Its focus is on:

- Developer productivity

- Robust pipelines

- Clear ownership between engine modules and tools

- Maintainable, extensible C++ infrastructure



This mirrors the type of internal tools used by game studios to support artists, designers, and engineers across multiple projects.



---



## 🎯 Project Goals



The primary goals of AssetTools are:



- Provide a **shared core library** used by multiple tools

- Demonstrate **target-based CMake project structure**

- Implement **production-style logging** suitable for automated pipelines

- Lay the foundation for editor and asset workflow tools

- Emphasize **stability, clarity, and maintainability** over cleverness



This project is built as a learning-focused but **industry-realistic** prototype.



---



## 🧩 Project Structure



AssetTools/

├── core/ # Shared engine-style core library

│ ├── include/

│ │ └── core/

│ │ ├── Version.h

│ │ └── Logger.h

│ └── src/

│ ├── Version.cpp

│ └── Logger.cpp

│

├── app/ # Tool executable

│ └── src/

│ └── main.cpp

│

├── build/ # Out-of-source build directory (generated)

├── CMakeLists.txt # Top-level build orchestration

└── README.md





### `core`

Represents **shared technology** similar to an internal engine or common tools library.  

It is built as a **static library** and is intended to be reused by multiple tools.



### `app`

The actual **tool executable**, representing a command-line or editor-side utility that would be used in production workflows.



---



## 🔧 Build System



- **CMake (target-based)**

- **Out-of-source builds**

- **Static library + executable architecture**

- Designed to scale to multiple tools and codebases



### Build Instructions (Windows, Visual Studio)



CLI - Use the build.bat through Developer Command Prompt for VS

File Explorer - Use the build_interactive.bat

