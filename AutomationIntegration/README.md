# AutomationIntegration

Example C++17 project demonstrating a mock documentation workflow and
source-code documentation with Doxygen.

## Overview

The project provides three mock classes for source analysis, documentation
generation and continuous integration. Their simple implementations make it
possible to explore Doxygen comments, API documentation and call graphs.

All operations are simulated: source files are not parsed, documentation files
are not written by the application, and Git and external services are not accessed.
Doxygen generates this documentation separately from the example application.

## Main classes

- DocumentationSystem::CodeAnalyzer creates synthetic class information,
  checks for missing documentation and collects supplied complexity scores.
- DocumentationSystem::DocumentationGenerator produces plain-text API previews
  and simulates documentation generation and validation. All requested output
  formats produce the same plain-text preview.
- DocumentationSystem::ContinuousDocumentation simulates CI integration,
  change detection, update scheduling, publication and change logs.

## Example program

The main.cpp program demonstrates the public methods of all three classes and
prints the results to standard output. It also removes and restores a class
documentation string to demonstrate missing documentation detection.

Input paths can be absolute or relative. The referenced files do not need to exist.

## Requirements

- C++17 or later.
- Visual Studio with the MSVC compiler.
- Doxygen to generate the HTML documentation.
- Graphviz (`dot`) to generate documentation diagrams.

## Build and run

Open `Mod4DoxyProjects.sln` in Visual Studio, select `AutomationIntegration` as
the startup project and use the Debug x64 configuration, which enables C++17.
Build and run the project to display the mock workflow results.

## Generate documentation

Save a Doxygen configuration named `Doxyfile` in this project directory.
Include the header, source files and this README in its inputs, and configure:

```ini
INPUT = DocumentationSystem.h DocumentationSystem.cpp main.cpp README.md
OUTPUT_DIRECTORY = docs
GENERATE_HTML = YES
HTML_OUTPUT = html
GENERATE_LATEX = NO
MARKDOWN_SUPPORT = YES
USE_MDFILE_AS_MAINPAGE = README.md
HAVE_DOT = YES
```

From this project directory, run:

```powershell
doxygen Doxyfile
Start-Process ".\docs\html\index.html"
```

Doxygen creates `docs/html/index.html` with this README as the main page and
the documented C++ entities as navigable API pages. Regenerate the documentation
after changing the source comments or this README.
