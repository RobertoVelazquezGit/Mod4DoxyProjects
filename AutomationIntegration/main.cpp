/**
 * @file main.cpp
 * @brief Demonstrates the mock documentation workflow.
 */
#include "DocumentationSystem.h"

#include <iostream>

/**
 * @brief Exercises source analysis, documentation previews and simulated CI operations.
 * @details Prints results to standard output and demonstrates missing documentation
 * detection. Input files do not need to exist. No files are generated, no services
 * are contacted and Doxygen is not executed.
 * @return Zero on normal completion.
 */
int main()
{
    using namespace DocumentationSystem;

    std::cout << std::boolalpha;

    // Analyze mock source files. These files do not need to exist.
    CodeAnalyzer analyzer;

    const std::vector<std::filesystem::path> files = {
        R"(C:\Dev\MiProyecto\src\ExampleService.cpp)",
        "C:/Dev/MiProyecto/src/ExampleController.cpp",
        "src/AnotherClass.cpp"
    };

    auto classes = analyzer.analyzeSourceFiles(files);

    std::cout << "Classes analyzed: " << classes.size() << '\n';
    std::cout << "Documentation valid: "
        << analyzer.validateDocumentation(classes) << '\n';

    // C++17 structured binding: access the map key and value as name and score.
    for (const auto& [name, score] : analyzer.generateComplexityReport(classes)) {
        std::cout << "Complexity of " << name << ": " << score << '\n';
    }

    // Remove one comment to demonstrate missing documentation detection.
    if (!classes.empty()) {
        classes.front().documentation.clear();
    }

    for (const auto& name : analyzer.findUndocumentedElements(classes)) {
        std::cout << "Undocumented element: " << name << '\n';
    }

    // Restore the mock documentation before generation.
    if (!classes.empty()) {
        classes.front().documentation = "Example class documentation.";
    }

    // Configure and simulate documentation generation.
    DocumentationGenerator generator;

    DocumentationGenerator::GenerationConfig generationConfig{};
    generationConfig.format = DocumentationGenerator::OutputFormat::Markdown;
    generationConfig.outputDirectory = "docs";
    generationConfig.generateCrossReferences = true;

    std::cout << "\nGeneration succeeded: "
        << generator.generateDocumentation(classes, generationConfig)
        << '\n';

    for (const auto& classInfo : classes) {
        std::cout << generator.generateAPIReference(
            classInfo, generationConfig.format) << '\n';
    }

    std::cout << "Update succeeded: "
        << generator.updateExistingDocumentation("docs", classes) << '\n';

    std::cout << "Documentation consistent: "
        << generator.validateDocumentationConsistency("docs") << '\n';

    // Configure and simulate continuous integration.
    ContinuousDocumentation continuousDocumentation;

    ContinuousDocumentation::CIConfig ciConfig{};
    ciConfig.repositoryPath = ".";
    ciConfig.branchName = "main";
    ciConfig.watchedDirectories = { "src", "include" };
    ciConfig.autoPublish = true;

    const bool integrated = continuousDocumentation.integrateWithCI(ciConfig);
    std::cout << "\nCI integration succeeded: " << integrated << '\n';

    if (integrated &&
        continuousDocumentation.detectDocumentationChanges("mock-commit-123")) {
        continuousDocumentation.scheduleDocumentationUpdate(files);
        std::cout << "Documentation update scheduling simulated.\n";

        if (ciConfig.autoPublish) {
            std::cout << "Publication succeeded: "
                << continuousDocumentation.publishDocumentation(
                    "2.0", "https://example.com/docs")
                << '\n';
        }
    }

    std::cout << "\nChange log:\n";
    for (const auto& entry :
        continuousDocumentation.generateChangeLog("1.0", "2.0")) {
        std::cout << "- " << entry << '\n';
    }

    return 0;
}
