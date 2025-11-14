# Smart Study

[![Build Status](https://img.shields.io/github/actions/workflow/status/Milkeles/smart-study/ci.yml)](https://github.com/Milkeles/smart-study/actions)
[![License: MIT](https://img.shields.io/github/license/Milkeles/smart-study)](LICENSE)
[![Issues](https://img.shields.io/github/issues/Milkeles/smart-study)](https://github.com/Milkeles/smart-study/issues)
[![Pull Requests](https://img.shields.io/github/issues-pr/Milkeles/smart-study)](https://github.com/Milkeles/smart-study/pulls)

Smart Study is an open-source, cross-platform desktop application designed to help students and pupils organize their learning process more efficiently. It integrates proven techniques such as flashcards and the Pomodoro method into a unified workflow. Future versions will include AI-powered functionality such as automatic flashcard generation and note summarization.

---

## Contents

- Overview
- Features
- Architecture Overview
- Technology Stack
- Installation and Setup
- Roadmap
- Goals and Success Metrics
- Development Workflow
- Contributing
- License

---

## Overview

Many learners spend excessive time preparing rather than studying. Writing flashcards manually, scheduling reminders, and configuring Pomodoro timers across several apps can slow progress instead of supporting it.

Smart Study addresses this by providing:

- A consolidated environment for studying and review
- Faster creation of learning materials
- Consistency through structured workflows
- Planned AI-driven automation of repetitive tasks

Supported platforms in the initial release: **Windows and Linux**.

---

## Features

### Available in Version 1

- Cross-platform desktop application
- Pomodoro timer with configurable study/break intervals
- Flashcard creation and learning interface
- Reminder system for routine study habits
- Local persistent storage (SQLite)
- Basic user profile and usage history

### Planned for Future Releases

- AI-assisted flashcard generation from user content
- AI-powered summarization and extraction of key concepts
- Improved usage analytics and feedback loops
- Optional secure cloud sync or portable offline export
- UI/UX refinements and guided onboarding experience

> Details beyond version 1 may change based on feedback and feasibility.

---

## Architecture Overview

Smart Study uses a layered architecture:

<details>
<summary>View Layer Description</summary>

1. Presentation Layer  
   Built with Qt 6.x. Responsible for rendering the interface and handling user interaction.

2. Application and Business Logic Layer  
   Implements core behavior such as Pomodoro timing rules, flashcard logic, validation, and note handling. Exposed via service classes acting as a facade.

3. Data Layer  
   Implements the Repository pattern to perform CRUD operations on user data persisted in SQLite.

</details>

This structure supports maintainability, testing, and future extensibility (for example, alternate storage engines or synchronization capabilities).

---

## Technology Stack

| Component | Technology |
|----------|------------|
| Language | C++17 |
| GUI Framework | Qt 6.x |
| Build System | CMake 3.20+ |
| Database | SQLite3 |
| DB Wrapper | SQLiteCPP |
| Dependency Manager | vcpkg |
| Version Control | Git + GitHub |
| CI/CD | GitHub Actions |

---

## Installation and Setup

> These commands assume familiarity with CMake and Qt development. Platform-specific setup instructions may be added later.

### 1. Install Requirements

Required:

- C++17 compatible compiler  
- CMake 3.20+  
- Qt 6.x development libraries  
- Git  

Recommended:

- vcpkg for dependencies

### 2. Clone Repository

git clone https://github.com/Milkeles/smart-study.git  
cd smart-study

### 3. Optional: Install Dependencies (via vcpkg)

vcpkg install sqlitecpp

### 4. Configure and Build

Example:

cmake -B build -S . -DCMAKE_BUILD_TYPE=Release  
cmake --build build --config Release

Windows users may open the resulting solution file located in `build/`.

### 5. Run

Linux:

./build/smart-study

Windows:

build\Release\smart-study.exe

Executable names may vary depending on your build configuration.

---

## Roadmap

| Feature Category | Version 1 | Future Versions |
|-----------------|-----------|----------------|
| Platform Support | Windows, Linux | Additional platform exploration |
| Pomodoro Timer | Manual configuration | Automatic recommendations |
| Flashcards | User-created | AI-assisted generation |
| Reminders | Basic | Expanded configuration options |
| Notes | Basic creation | AI summarization and structure extraction |
| Storage | Local SQLite | Optional cloud or portable sync |
| AI | Not included | Local model integration (planned LLaMA-based model) |

---

## Goals and Success Metrics

Smart Study is built to:

- Reduce study-preparation time by approximately 50–100%
- Encourage consistency and time-on-task behavior
- Improve perceived and measurable learning outcomes

Potential success indicators include:

- Average user session duration (target: >10 minutes/day)
- Weekly and monthly retention
- Flashcard creation and review frequency
- Self-assessed productivity improvements

---

## Development Workflow

Smart Study uses **Trunk-Based Development**.

- Only long-lived branch: `main`
- All work is done in short-lived branches

Branch naming conventions:

feature/<description>  
bugfix/<description>

Pull Requests:

- Must pass automated builds and checks
- Require review before merging

---

## Contributing

Contributions are welcome.

Before contributing:

1. Review open issues or start a discussion  
2. Fork the repository  
3. Create a feature branch  
4. Follow existing patterns and architecture  
5. Submit a Pull Request targeting `main`

Documentation contributions (fixes, improvements, clarifications) are also encouraged.

---

## License

Distributed under the MIT License.  
See `LICENSE` for details.