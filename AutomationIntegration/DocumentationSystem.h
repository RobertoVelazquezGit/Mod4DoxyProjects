#pragma once
#include <string>
#include <vector>
#include <map>
#include <filesystem>

namespace DocumentationSystem {

    class CodeAnalyzer {
    public:
        struct FunctionInfo {
            std::string name;
            std::string returnType;
            std::vector<std::pair<std::string, std::string>> parameters;
            std::vector<std::string> exceptions;
            std::string documentation;
            int complexityScore;
        };

        struct ClassInfo {
            std::string name;
            std::string baseClass;
            std::vector<FunctionInfo> methods;
            std::vector<std::string> members;
            std::string documentation;
        };

        std::vector<ClassInfo> analyzeSourceFiles(const std::vector<std::filesystem::path>& files);

        bool validateDocumentation(const std::vector<ClassInfo>& classes);

        std::map<std::string, int> generateComplexityReport(const std::vector<ClassInfo>& classes);

        std::vector<std::string> findUndocumentedElements(const std::vector<ClassInfo>& classes);
    };

    class DocumentationGenerator {
    public:
        enum class OutputFormat {
            HTML,
            PDF,
            Markdown,
            XML,
            JSON
        };

        struct GenerationConfig {
            OutputFormat format;
            std::string templateDirectory;
            std::string outputDirectory;
            bool includePrivateMembers;
            bool generateCrossReferences;
            bool includeSourceCode;
            std::vector<std::string> excludePatterns;
        };

        bool generateDocumentation(const std::vector<CodeAnalyzer::ClassInfo>& classes,
            const GenerationConfig& config);

        bool updateExistingDocumentation(const std::filesystem::path& docPath,
            const std::vector<CodeAnalyzer::ClassInfo>& newClasses);

        std::string generateAPIReference(const CodeAnalyzer::ClassInfo& classInfo,
            OutputFormat format);

        bool validateDocumentationConsistency(const std::filesystem::path& docDirectory);

    private:
        std::string formatFunction(const CodeAnalyzer::FunctionInfo& func, OutputFormat format);
        std::string generateCrossReferences(const std::vector<CodeAnalyzer::ClassInfo>& classes);
        bool applyTemplate(const std::string& templatePath, const std::string& content,
            const std::string& outputPath);
    };

    class ContinuousDocumentation {
    public:
        struct CIConfig {
            std::string repositoryPath;
            std::string branchName;
            std::vector<std::string> watchedDirectories;
            std::string webhookUrl;
            bool autoPublish;
        };

        bool integrateWithCI(const CIConfig& config);

        bool detectDocumentationChanges(const std::string& commitHash);

        void scheduleDocumentationUpdate(const std::vector<std::filesystem::path>& changedFiles);

        bool publishDocumentation(const std::string& version, const std::string& publishUrl);

        std::vector<std::string> generateChangeLog(const std::string& fromVersion,
            const std::string& toVersion);
    };

}