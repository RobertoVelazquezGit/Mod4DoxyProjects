
/**
 * @file main.cpp
 * @brief Example usage of simulated documentation quality metrics.
 */
#include "DocQuality.h"
#include <iostream>

/**
 * @brief Runs a simple example of DocumentationQuality::QualityMetrics.
 * @details Displays a report with issues and recommendations, compares version
 * labels 1.0 and 2.0, lists documents not updated for at least 90 days, and
 * displays the fictional benchmark score.
 * @return 0 on successful completion.
 * @note All results use simulated data; no docs directory is required.
 */
int main()
{
    DocumentationQuality::QualityMetrics metrics;

    // Assess documentation using simulated data.
    const auto report = metrics.assessDocumentation("docs");
    std::cout << "Overall score: " << report.score.overallScore << '\n';

    std::cout << "Issues:\n";
    for (const auto& issue : report.issues) {
        std::cout << " - " << issue << '\n';
    }

    std::cout << "Recommendations:\n";
    for (const auto& recommendation : report.recommendations) {
        std::cout << " - " << recommendation << '\n';
    }

    const bool different = metrics.compareDocumentationVersions("1.0", "2.0");
    std::cout << "Different versions: " << (different ? "yes" : "no") << '\n';

    std::cout << "Documents not updated for at least 90 days:\n";
    for (const auto& document : metrics.identifyStaleDocumentation()) {
        std::cout << " - " << document << '\n';
    }

    const auto benchmark = metrics.benchmarkAgainstIndustryStandards();
    std::cout << "Mock reference score: " << benchmark.overallScore << '\n';

    return 0;
}

