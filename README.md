# AssetTools — Internal Game Development Tools Prototype

AssetTools is a C++ prototype of an **internal game development tool**
designed to support **content creation workflows, asset pipelines, and
shared engine technology**.

The project is intentionally scoped as a **tools-side application**, not
a game runtime. Its focus is on:

- Developer productivity
- Robust, pipeline-friendly workflows
- Clear ownership between engine-style libraries and tools
- Maintainable, extensible C++ infrastructure

This mirrors the type of internal tools used by game studios to support
artists, designers, and engineers across multiple projects.

---

## 🎯 Project Goals

The primary goals of AssetTools are to:

- Provide a **shared core library** used by multiple tools
- Demonstrate a **target-based CMake project structure**
- Implement **production-style logging** suitable for automated pipelines
- Validate asset data using **rule-based, data-driven systems**
- Emphasize **stability, clarity, and maintainability** over cleverness

This project is learning-focused, but intentionally designed to be
**industry-realistic** and representative of professional tools code.

---

## 🧩 Project Structure

AssetTools/ 

├── core/        # Shared engine-style core library (logging, assets, validation)

├── app/         # Tool executable and mode-based command-line logic 

├── assets/      # Sample asset data used for validation and testing 

├── build/       # Out-of-source build artifacts (generated) 

└── CMakeLists.txt  # Top-level CMake project configuration 

### `core`

Represents **shared technology** similar to an internal engine or common
tools library.

- Built as a **static library**
- Contains reusable systems (logging, asset definitions, validation)
- Designed to be consumed by multiple tools or editors

This mirrors how studios structure shared tooling and engine-side code.

---

### `app`

The **tool executable**, implemented as a command-line utility.

It supports **multiple modes** and acts as a pipeline-facing tool that
can be invoked by developers, scripts, or CI systems.

---

### `assets`

Contains **small, text-based sample asset definitions** used to
demonstrate and test the validation pipeline.

These files are:
- Intentionally minimal
- Deterministic
- Included for demonstration and testing only

They do **not** represent real game content.

---

## 🛠 Tool Usage

### Validate Asset Data

AssetTools validate <asset_file>

Behavior:
- Parses asset definitions from the input file
- Applies rule-based validation
- Logs rule violations

### Inspect Assets

AssetTools inspect <asset_file>

Behavior:
- Retrieves asset metadata from the input file
- Logs asset metadata, including file extension, file size, and last-modified timestamp

---

## 🔧 Build System

- **CMake (target-based)**
- **Out-of-source builds**
- **Static library + executable architecture**
- Designed to scale to multiple tools and shared codebases

### Build Instructions (Windows, Visual Studio)

- CLI: use `build.bat` from a Developer Command Prompt for Visual Studio
- File Explorer: use `build_interactive.bat`

---

## 🧠 Design Philosophy

AssetTools prioritizes:

- Explicit ownership and lifetimes
- Clear contracts between systems
- Data-driven validation over hardcoded logic
- Predictable behavior in automated pipelines

The project is intentionally designed to resemble **real internal tools** 
used by studios.

---

## 🚧 Status

This project is under active development as a learning-focused tools
prototype. Future work includes:

- Configurable validation rules
- Directory-based asset discovery
- Platform-specific constraints
- Improved CLI ergonomics and diagnostics
