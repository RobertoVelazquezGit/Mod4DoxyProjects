#include "DocQuality.h"
#include <iostream>

namespace DocumentationQuality {

    // Mock implementation: all documents and scores are simulated.
    QualityMetrics::QualityReport QualityMetrics::assessDocumentation(
        const std::filesystem::path& docPath) {
        QualityReport report{};
        if (docPath.empty()) {
            report.issues = { "No documentation path provided." };
            report.recommendations = { "Provide a documentation path." };
            return report;
        }

        const std::vector<std::string> documents = {
            "Getting started", "API reference", "Examples", ""
        };
        report.score.completeness = calculateCompletenessScore(documents);
        report.score.clarity = analyzeClarityMetrics(documents.front());
        report.score.accuracy = validateTechnicalAccuracy(
            "Example API documentation", "Example source code") ? 0.9 : 0.0;
        report.score.maintainability = 0.7;
        report.score.overallScore =
            0.3 * report.score.completeness +
            0.2 * report.score.clarity +
            0.3 * report.score.accuracy +
            0.2 * report.score.maintainability;
        report.issues = { "Mock: one section is missing.",
                          "Mock: some examples need updating." };
        report.recommendations = { "Complete the missing section.",
                                   "Review the code examples." };
        report.statisticsByType = { { "guides", 1 }, { "api", 1 },
                                    { "examples", 1 }, { "missing", 1 } };
        return report;
    }

    bool QualityMetrics::compareDocumentationVersions(
        const std::string& version1, const std::string& version2) {
        // Mock: true means both version labels are nonempty and different.
        return !version1.empty() && !version2.empty() && version1 != version2;
    }

    std::vector<std::string> QualityMetrics::identifyStaleDocumentation(
        int daysSinceUpdate) {
        // Fixed sample ages; the threshold is inclusive.
        if (daysSinceUpdate < 0) {
            return {};
        }
        std::vector<std::string> documents;
        if (120 >= daysSinceUpdate) {
			documents.push_back("api_reference.md");  // emplace_back could also be used
        }
        if (200 >= daysSinceUpdate) {
            documents.push_back("legacy_guide.md");
        }
        return documents;
    }

    QualityMetrics::DocumentationScore
        QualityMetrics::benchmarkAgainstIndustryStandards() {
        // Fictional reference values, not actual industry standards.
        DocumentationScore score{ 0.9, 0.85, 0.95, 0.8, 0.0 };
        score.overallScore = 0.3 * score.completeness + 0.2 * score.clarity +
            0.3 * score.accuracy + 0.2 * score.maintainability;
        return score;
    }

    double QualityMetrics::calculateCompletenessScore(
        const std::vector<std::string>& documents) {
        if (documents.empty()) {
            return 0.0;
        }
        std::size_t completed = 0;
        for (const auto& document : documents) {
            if (!document.empty()) {
                ++completed;
            }
        }
        return static_cast<double>(completed) / documents.size();  // return (static_cast<double>(completed)) / (documents.size());
    }

    double QualityMetrics::analyzeClarityMetrics(const std::string& content) {
        // Mock: any nonempty text receives the same clarity score.
        return content.empty() ? 0.0 : 0.8;
    }

    bool QualityMetrics::validateTechnicalAccuracy(
        const std::string& documentation, const std::string& sourceCode) {
        // Mock: only checks that both inputs contain text.
        return !documentation.empty() && !sourceCode.empty();
    }

}
