
#include "MarketDataProcessor.h"

#include <chrono>
#include <iostream>
#include <map>
#include <vector>

using namespace FinancialEngineering;

int main()
{
    // ------------------------------------------------------------
    // Test MarketDataProcessor
    // ------------------------------------------------------------

    MarketDataProcessor processor(0.02);

    auto now = std::chrono::system_clock::now();

    processor.addPriceData("AAPL", 100.0, now);
    processor.addPriceData("AAPL", 102.0, now);
    processor.addPriceData("AAPL", 101.0, now);
    processor.addPriceData("AAPL", 105.0, now);
    processor.addPriceData("AAPL", 108.0, now);

    processor.addPriceData("MSFT", 200.0, now);
    processor.addPriceData("MSFT", 201.0, now);
    processor.addPriceData("MSFT", 200.5, now);
    processor.addPriceData("MSFT", 202.0, now);

    auto volatility = processor.calculateVolatility("AAPL", 3);

    if (volatility)
    {
        std::cout << "AAPL volatility: "
            << *volatility << '\n';
    }
    else
    {
        std::cout << "Could not calculate AAPL volatility.\n";
    }

    auto highVolatilityAssets =
        processor.getHighVolatilityAssets();

    std::cout << "\nHigh volatility assets:\n";

    for (const auto& asset : highVolatilityAssets)
    {
        std::cout << asset.first
            << " -> "
            << asset.second
            << '\n';
    }

    // Simple test of the template function.
    std::vector<double> returns{
        0.01,
        0.02,
        0.03,
        -0.01
    };

    double sharpe =
        processor.calculateSharpeRatio(returns);

    std::cout << "\nSimplified Sharpe result: "
        << sharpe << '\n';


    // ------------------------------------------------------------
    // Test PortfolioOptimizer
    // ------------------------------------------------------------

    PortfolioOptimizer optimizer;

    optimizer.addAsset("AAPL", 0.08);
    optimizer.addAsset("MSFT", 0.06);

    std::vector<std::vector<double>> covarianceMatrix{
        {0.04, 0.01},
        {0.01, 0.09}
    };

    optimizer.updateCovarianceMatrix(covarianceMatrix);

    std::map<std::string, double> weights{
        {"AAPL", 0.60},
        {"MSFT", 0.40}
    };

    double risk =
        optimizer.calculatePortfolioRisk(weights);

    std::cout << "\nPortfolio risk: "
        << risk << '\n';

    auto optimized =
        optimizer.optimizePortfolio(0.07);

    std::cout << "\nOptimized portfolio:\n";

    for (const auto& asset : optimized)
    {
        std::cout << asset.first
            << " -> "
            << asset.second
            << '\n';
    }

    auto frontier =
        optimizer.generateEfficientFrontier(
            5,
            0.05,
            0.15
        );

    std::cout << "\nEfficient frontier:\n";

    int point = 1;

    for (const auto& portfolio : frontier)
    {
        std::cout << "Point " << point++ << ":\n";

        for (const auto& asset : portfolio)
        {
            std::cout << "  "
                << asset.first
                << " -> "
                << asset.second
                << '\n';
        }
    }

    return 0;
}
