# DocQuality

A small C++ project for practicing source-code documentation with Doxygen.
All quality assessments use simulated data. No documentation files are read
and the benchmark scores do not represent actual industry standards.

## Overview

The example creates a quality report, compares version labels, lists fictional
stale documents, and retrieves a fictional quality benchmark.

## Main Types

- DocumentationQuality::QualityMetrics provides the assessment operations.
- DocumentationQuality::QualityMetrics::DocumentationScore holds quality scores.
- DocumentationQuality::QualityMetrics::QualityReport contains scores, issues,
  recommendations, and counts by category.

## Example Program

The `main.cpp` example calls all four public methods and prints their results.
It uses `docs` as a sample path, compares version labels `1.0` and `2.0`, and
uses the default stale-document threshold of 90 days.

The simulated overall score is 0.795 and the fictional benchmark is 0.885.
The stale-document examples are `api_reference.md` (120 days) and
`legacy_guide.md` (200 days).

## Requirements

- C++17 or later.
- Visual Studio and MSVC for the existing solution and project files.
- Doxygen and Graphviz, with `doxygen` and `dot` available on `PATH`.

## Generate Documentation

From the DocQuality project directory, run:

```powershell
doxygen Doxyfile
```

Open `docs/html/index.html` to browse the documentation. The configuration
includes private members, source browsing, class relationships, include graphs,
call graphs, and caller graphs. Diagnostics are written to
`docs/doxygen-warnings.log`.

Edit the source comments or this README, then run the same command to regenerate
the documentation. HTML is the configured output format.
