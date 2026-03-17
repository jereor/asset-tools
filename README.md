# AssetTools — Internal Game Development Tools Prototype

AssetTools is a C++ prototype of an **internal game development tool**
designed to support **content creation workflows and asset pipelines**.
AssetTools can scale to hold multiple different asset tools, like asset validation, 
asset inspection, asset scanning, etc.
However, this prototype focuses mainly on asset validation.

This prototype showcases pre-engine asset validation similar to what game companies 
like Supercell would use. 
The idea is that assets are validated close to asset creation to catch problems 
before the assets are imported to the game engine. 
First by artists and designers, and later re-validated by build pipelines.

This mirrors the type of internal tools used by game studios to support
artists, designers, and engineers across multiple projects.

---

## 🎯 Project Goals

The primary goals of AssetTools are to:

- Provide a **shared core library** used by multiple asset tools
- Demonstrate a **target-based CMake project structure**
- Implement **production-style logging** suitable for automated pipelines
- Validate asset data using **rule-based, data-driven systems**
- Provide an easy-to-use **configuration** layer
- Be **easy to understand and use** by artists, designers, engineers and CI

This project is learning-focused, but intentionally designed to be
**industry-realistic** and representative of professional tools code.

---

## 🛠 Tool Usage

### Validate Assets

AssetTools validate <asset_file>
AssetTools validate <asset_directory>

Behavior:
- Parses asset/assets into data structs
- Applies rule-based validation
- Logs rule violations

### Inspect Assets

AssetTools inspect <asset_file>

Behavior:
- Retrieves asset metadata from the asset file
- Logs asset metadata, including file extension, file size, and last-modified timestamp

---

## 🚧 Project Status

This project is under active development as a learning-focused tools
prototype. Future work includes:

- Graphical UI
- Automated tests
- Validation Summary (success/failure counts)
- '--verbose' flag wired to logging
- More texture validation rules (image dimensions, power-of-two, color model, etc.)

---

## 🧩 Project Structure

AssetTools/ 

├── app/           # Tool executable and mode-based command-line logic

├── build/         # Out-of-source build artifacts (generated)

├── configs/       # YAML configuration files to configure tool behavior and validation rules

├── core/          # Shared engine-style core library (logging, assets, validation)

├── jenkins/       # Jenkins and Docker configuration files for running Jenkins

├── scripts/       # Scripts for building the app with CMake

├── tests/assets/  # Sample asset data used for validation and testing

└── CMakeLists.txt # Top-level CMake project configuration

### `app`

The **tool executable**, implemented as a command-line utility.
Can be extended with a GUI later on.

It supports **multiple modes** and acts as a tool that
can be invoked by developers, scripts, or CI systems.

---

### `build`

Generated with CMake / build scripts. 
Navigate to app/Release or app/Debug to find the executable.

---

### `configs`

Contains **YAML configuration files** to configure tool behavior and validation rules.
Passed into the tool as CLI arguments.

Config layers (in order of precedence)
1. Built-in defaults (code)
2. Base project config (base.yaml) - Defines project-wide rules that apply to everything
3. Category config (textures.yaml, audio.yaml, …) - Override or extend base rules per asset category
4. [Planned] Asset-level metadata (.meta files) - Override rules for specific assets

Each layer:
- Is optional except base.yaml
- Overrides values from previous layers

---

### `core`

Represents **shared technology** similar to an internal engine or common
tools library.

- Built as a **static library**
- Contains reusable systems (logging, exit codes, asset parsing)
- Designed to be consumed by multiple tools or editors

This mirrors how studios structure shared tooling and engine-side code.

### `jenkins`

This directory is reserved for installing and configuring **Jenkins**.
It contains:
- Jenkinsfile: Defines the Jenkins pipeline as code. Used by the **Jenkins server**.
- Dockerfile: Defines the CMake environment needed to build asset-tools. Used by **Jenkins Docker agents**.

The /jenkins-install directory contains instructions how to install Jenkins on your machine using Docker.
---

### `scripts`

Contains **shell scripts** for building the project using **CMake**.
They are designed to make development more straightforward and
to be used on all platforms.

---

### `tests/assets`

Contains **sample assets** used to
demonstrate and test the validation pipeline.

These files are included for demonstration and testing only.

---

### `CMakeLists.txt`

Used by CMake to define the project's source files, build targets, and configuration options. 
It contains rules for the build process, allowing CMake to generate the necessary files for building the executable.

Designed to work on all platforms, without requiring all the dependencies to be installed before-hand.
Only CMake, a C++ compiler, and Git are required. CMake installs the rest automatically through Git.

---

## 🔧 Build System

- **CMake (target-based)**
- **Out-of-source builds**
- **Static library + executable architecture**
- Designed to scale to multiple tools and shared codebases

### Pre-Requirements:
- CMake (3.16 or newer)
- C++23 compiler (LLVM 18.0+ or MSVC 18.0+)
- git (2.0 or newer)

### Build Instructions (Linux/Windows)
Use the scripts in /scripts (eg. `build.sh`)

### Build Instructions (MacOS)
Navigate to the 'asset-tools' folder and run the following commands:
- cmake -S . -B build -DCMAKE_CXX_COMPILER=/path/to/your/c++/compiler
- cmake --build build --config Release --parallel

---

## 🧠 Design Philosophy

AssetTools is designed to be:
- Engine-agnostic (not Unity / Unreal specific)
- Pre-engine (runs before assets enter an editor)
- CI-friendly (clear exit codes, deterministic behavior)
- Developer-first (clear diagnostics, predictable configuration)

The project is intentionally designed to resemble **real internal tools** 
used by studios across many projects with different game engines and practices.

YAML files

   ↓

ConfigLoader

   ↓

Typed C++ config structs

   ↓

Tool modes (validate / inspect)

   ↓

Diagnostics

   ↓

App decides exit code & output
