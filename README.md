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

OR

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

├── ci/               # Jenkins server setup with Docker Compose

├── configs/      # YAML configuration files to configure tool behavior and validation rules

├── core/          # Shared engine-style core library (logging, assets, validation)

├── jenkins/      # Reserved for the Jenkinsfile that Jenkins uses

├── scripts/       # Scripts for building the app with CMake

├── tests/assets/  # Sample asset data used for validation and testing

└── CMakeLists.txt # Top-level CMake project configuration

### `app`

The **tool executable**, implemented as a command-line utility.
Can be extended with a GUI later on.

It supports **multiple modes** and acts as a tool that
can be invoked by developers, scripts, or CI systems.

Contains a Dockerfile for the app that developers and CI can use to set up a build environment.

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
- Is optional (except base.yaml)
- Overrides values from previous layers

---

### `ci`

Contains everything a developer needs to set up a local CI pipeline using Docker Compose.

---

### `core`

Represents **shared technology** similar to an internal engine or common
tools library.

- Built as a **static library**
- Contains reusable systems (logging, exit codes, asset parsing)
- Designed to be consumed by multiple tools or editors

This mirrors how studios structure shared tooling and engine-side code.

### `jenkins`

This directory is reserved for the Jenkinsfile that Jenkins uses.

---

### `scripts`

Contains **shell scripts** for building the project using **CMake**.
They are designed to make development more straightforward.

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

- **CMake** (target-based)
- Automatic package management with **vcpkg**
- **Docker** containerization
- Out-of-source builds
- Static library + executable architecture
- Designed to scale to multiple tools and shared codebases

AssetTools is designed to be built inside a Docker container, so developers don't need to worry about 
setting up their environment. Docker takes care that you have all the dependencies required to build
the project, and vcpkg takes care that the project has all the required libraries required for linking.

### Build instructions
Note: If on bash, use (pwd) instead of {PWD}

1. docker build -t asset-tools-env .\app\
2. docker run --rm -it -v ${PWD}:/workspace asset-tools-env
3. ./scripts/build.sh

If any issues:
- ./scripts/build_clean.sh

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
