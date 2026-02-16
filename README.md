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
- Provide an easy-to-use **configuration** layer
- Be **easy to understand and use** by artists, designers, engineers and CI

This project is learning-focused, but intentionally designed to be
**industry-realistic** and representative of professional tools code.

---

## 🧩 Project Structure

AssetTools/ 

├── app/         # Tool executable and mode-based command-line logic

├── assets/      # Sample asset data used for validation and testing

├── build/       # Out-of-source build artifacts (generated)

├── configs/     # YAML configuration files to configure tool behavior and validation rules

├── core/        # Shared engine-style core library (logging, assets, validation)

└── CMakeLists.txt  # Top-level CMake project configuration

### `app`

The **tool executable**, implemented as a command-line utility.
Can be extended with a GUI later on.

It supports **multiple modes** and acts as a pipeline-facing tool that
can be invoked by developers, scripts, or CI systems.

---

### `assets`

Contains **sample assets** used to
demonstrate and test the validation pipeline.

These files are included for demonstration and testing only.

---

### `build`

Generated with CMake / build scripts. 
Navigate to app/Release or app/Debug to find the executable.

---

### `configs`

Contains **YAML configuration files** to configure tool behavior and validation rules.
Passed into the tool as CLI arguments. (eg. --config path/to/config)

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

---

### `CMakeLists.txt`

Used by CMake to define the project's source files, build targets, and configuration options. 
It contains rules for the build process, allowing CMake to generate the necessary files for building the executable.

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

### Pre-Requirements:
- CMake (3.16 or newer)
- C++23 compiler (LLVM 18.0+ or MSVC 18.0+)

### Build Instructions (Windows)

- CLI: use `build.bat`
- File Explorer: use `build_interactive.bat`

### Build Instructions (MacOS)
Navigate to the 'asset-tools' folder and run the following commands (use your compiler path):
- cmake -S . -B build -DCMAKE_CXX_COMPILER=/usr/local/opt/llvm-18/bin/clang++
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

   ↓  (schema validation only)

Typed C++ config structs

   ↓

Tool modes (inspect / validate)

   ↓

Diagnostics

   ↓

App decides exit code & output

---

## 🚧 Status

This project is under active development as a learning-focused tools
prototype. Future work includes:

- Configurable validation rules
- Directory-based asset discovery
- Platform-specific constraints
- Improved CLI ergonomics and diagnostics
