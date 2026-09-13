#include "DocumentationSystem.h"

#include <sstream>

namespace DocumentationSystem {

    // Mock implementations: no source parsing, file writes or external services.
    std::vector<CodeAnalyzer::ClassInfo> CodeAnalyzer::analyzeSourceFiles(
        const std::vector<std::filesystem::path>& files) {
        std::vector<ClassInfo> classes;
        for (const auto& file : files) {
            if (file.empty()) {
                continue;
            }

            FunctionInfo method{};
            method.name = "exampleMethod";
            method.returnType = "void";
            method.parameters = { { "int", "value" } };
            method.documentation = "Mock method for documentation examples.";
            method.complexityScore = 1;

            ClassInfo classInfo{};
            classInfo.name = file.stem().string();
			classInfo.methods = { method };  // Add a single mock method, similar to classInfo.methods.push_back(method);    
            classInfo.members = { "int exampleValue" };
            classInfo.documentation = "Mock class for " + file.filename().string();
            classes.push_back(classInfo);
        }
        return classes;
    }

    bool CodeAnalyzer::validateDocumentation(const std::vector<ClassInfo>& classes) {
        return findUndocumentedElements(classes).empty();
    }

    std::map<std::string, int> CodeAnalyzer::generateComplexityReport(
        const std::vector<ClassInfo>& classes) {
        std::map<std::string, int> report;
        for (const auto& classInfo : classes) {
            for (const auto& method : classInfo.methods) {
                report[classInfo.name + "::" + method.name] = method.complexityScore;
            }
        }
        return report;
    }

    std::vector<std::string> CodeAnalyzer::findUndocumentedElements(
        const std::vector<ClassInfo>& classes) {
        std::vector<std::string> elements;
        for (const auto& classInfo : classes) {
            if (classInfo.documentation.empty()) {
                elements.push_back(classInfo.name);
            }
            for (const auto& method : classInfo.methods) {
                if (method.documentation.empty()) {
                    elements.push_back(classInfo.name + "::" + method.name);
                }
            }
        }
        return elements;
    }

    bool DocumentationGenerator::generateDocumentation(
        const std::vector<CodeAnalyzer::ClassInfo>& classes,
        const GenerationConfig& config) {
        if (classes.empty() || config.outputDirectory.empty()) {
            return false;
        }

        std::string content;
        for (const auto& classInfo : classes) {
            content += generateAPIReference(classInfo, config.format);
        }
        if (config.generateCrossReferences) {
            content += generateCrossReferences(classes);
        }
        // Other generation options are intentionally ignored by this mock.
        return applyTemplate(config.templateDirectory, content, config.outputDirectory);
    }

    bool DocumentationGenerator::updateExistingDocumentation(
        const std::filesystem::path& docPath,
        const std::vector<CodeAnalyzer::ClassInfo>& newClasses) {
        return !docPath.empty() && !newClasses.empty();
    }

    std::string DocumentationGenerator::generateAPIReference(
        const CodeAnalyzer::ClassInfo& classInfo, OutputFormat format) {
        // All formats return a plain-text preview, including PDF.
        std::ostringstream output;
        output << "[Mock API reference] " << classInfo.name << '\n';
        output << classInfo.documentation << '\n';
        if (!classInfo.baseClass.empty()) {
            output << "Base class: " << classInfo.baseClass << '\n';
        }
        for (const auto& member : classInfo.members) {
            output << member << '\n';
        }
        for (const auto& method : classInfo.methods) {
            output << formatFunction(method, format) << '\n';
        }
        return output.str();
    }

    bool DocumentationGenerator::validateDocumentationConsistency(
        const std::filesystem::path& docDirectory) {
        // Simulates validation without checking the filesystem.
        return !docDirectory.empty();
    }

    std::string DocumentationGenerator::formatFunction(
        const CodeAnalyzer::FunctionInfo& func, OutputFormat /*format*/) {
        // The unused format parameter is unnamed to avoid compiler warnings.
        std::ostringstream output;
        output << func.returnType << ' ' << func.name << '(';
        for (std::size_t i = 0; i < func.parameters.size(); ++i) {
            if (i != 0) {
                output << ", ";
            }
            output << func.parameters[i].first << ' ' << func.parameters[i].second;
        }
        output << ") - " << func.documentation;
        return output.str();
    }

    std::string DocumentationGenerator::generateCrossReferences(
        const std::vector<CodeAnalyzer::ClassInfo>& classes) {
        std::string references = "Mock cross references:\n";
        for (const auto& classInfo : classes) {
            references += classInfo.name + '\n';
        }
        return references;
    }

    bool DocumentationGenerator::applyTemplate(
        const std::string& /*templatePath*/, const std::string& content,
        const std::string& outputPath) {
        // An empty template path represents the default mock template.
        return !content.empty() && !outputPath.empty();
    }

    bool ContinuousDocumentation::integrateWithCI(const CIConfig& config) {
        return !config.repositoryPath.empty() && !config.branchName.empty();
    }

    bool ContinuousDocumentation::detectDocumentationChanges(const std::string& commitHash) {
        // Any nonempty identifier represents a commit with documentation changes.
        return !commitHash.empty();
    }

    void ContinuousDocumentation::scheduleDocumentationUpdate(
        const std::vector<std::filesystem::path>& /*changedFiles*/) {
        // No-op: the mock does not create background tasks or retain state.
    }

    bool ContinuousDocumentation::publishDocumentation(
        const std::string& version, const std::string& publishUrl) {
        return !version.empty() && !publishUrl.empty();
    }

    std::vector<std::string> ContinuousDocumentation::generateChangeLog(
        const std::string& fromVersion, const std::string& toVersion) {
        if (fromVersion.empty() || toVersion.empty() || fromVersion == toVersion) {
            return {};
        }
        return {
            // Return a vector containing two strings: the version change and a mock update description.
            // The comma separates the two string elements in the returned vector.
            "Mock documentation changes: " + fromVersion + " -> " + toVersion,
            "Updated example API reference."
        };
    }

}
