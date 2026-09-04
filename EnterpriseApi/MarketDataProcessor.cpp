#include "MarketDataProcessor.h"

#include <algorithm>
#include <cmath>

namespace FinancialEngineering {

    MarketDataProcessor::MarketDataProcessor(double threshold)
        : lastUpdate{}, volatilityThreshold(threshold) {
    }

    bool MarketDataProcessor::addPriceData(
        const std::string& symbol,
        double price,
        std::chrono::system_clock::time_point timestamp) {
        if (symbol.empty() || !std::isfinite(price) || price <= 0.0) {
            return false;
        }

        priceHistory[symbol].push_back(price);
        lastUpdate = timestamp;
        return true;
    }

    std::optional<double> MarketDataProcessor::calculateVolatility(
        const std::string& symbol,
        int windowSize) {
        const auto history = priceHistory.find(symbol);
        if (history == priceHistory.end() || windowSize <= 0 || history->second.size() < 2) {
            return std::nullopt;
        }

        const auto& prices = history->second;
        const std::size_t returnCount = std::min(
            static_cast<std::size_t>(windowSize), prices.size() - 1);
        const std::size_t firstPrice = prices.size() - returnCount - 1;

        std::vector<double> returns;
        returns.reserve(returnCount);
        for (std::size_t index = firstPrice + 1; index < prices.size(); ++index) {
            returns.push_back(std::log(prices[index] / prices[index - 1]));
        }

        double mean = 0.0;
        for (double value : returns) {
            mean += value;
        }
        mean /= static_cast<double>(returns.size());

        double variance = 0.0;
        for (double value : returns) {
            const double difference = value - mean;
            variance += difference * difference;
        }
        variance /= static_cast<double>(returns.size());

        return std::sqrt(variance);
    }

    std::vector<std::pair<std::string, double>>
        MarketDataProcessor::getHighVolatilityAssets() {
        std::vector<std::pair<std::string, double>> assets;

        for (const auto& entry : priceHistory) {
            const auto volatility = calculateVolatility(entry.first);
            if (volatility && *volatility > volatilityThreshold) {
                assets.emplace_back(entry.first, *volatility);
            }
        }

        return assets;
    }

    void MarketDataProcessor::clearHistoricalData(const std::string& symbol) {
        if (symbol.empty()) {
            priceHistory.clear();
            lastUpdate = {};
            return;
        }

        priceHistory.erase(symbol);
        if (priceHistory.empty()) {
            lastUpdate = {};
        }
    }

    void PortfolioOptimizer::addAsset(
        const std::string& symbol,
        double expectedReturn) {
        if (symbol.empty() || !std::isfinite(expectedReturn)) {
            return;
        }

        if (expectedReturns.find(symbol) == expectedReturns.end()) {
            assets.push_back(symbol);
        }
        expectedReturns[symbol] = expectedReturn;
    }

    void PortfolioOptimizer::updateCovarianceMatrix(
        const std::vector<std::vector<double>>& matrix) {
        covarianceMatrix = matrix;
    }

    std::map<std::string, double> PortfolioOptimizer::optimizePortfolio(
        double targetReturn,
        const std::map<std::string, double>& constraints) {
        (void)targetReturn;
        (void)constraints;

        std::map<std::string, double> weights;
        if (assets.empty()) {
            return weights;
        }

        const double equalWeight = 1.0 / static_cast<double>(assets.size());
        for (const auto& asset : assets) {
            weights[asset] = equalWeight;
        }

        return weights;
    }

    double PortfolioOptimizer::calculatePortfolioRisk(
        const std::map<std::string, double>& weights) {
        if (covarianceMatrix.size() != assets.size()) {
            return 0.0;
        }

        for (const auto& row : covarianceMatrix) {
            if (row.size() != assets.size()) {
                return 0.0;
            }
        }

        double variance = 0.0;
        for (std::size_t row = 0; row < assets.size(); ++row) {
            const auto rowWeight = weights.find(assets[row]);
            const double left = rowWeight == weights.end() ? 0.0 : rowWeight->second;

            for (std::size_t column = 0; column < assets.size(); ++column) {
                const auto columnWeight = weights.find(assets[column]);
                const double right = columnWeight == weights.end() ? 0.0 : columnWeight->second;
                variance += left * covarianceMatrix[row][column] * right;
            }
        }

        return std::sqrt(std::max(0.0, variance));
    }

    std::vector<std::map<std::string, double>>
        PortfolioOptimizer::generateEfficientFrontier(
            int numPoints,
            double minReturn,
            double maxReturn) {
        std::vector<std::map<std::string, double>> frontier;
        if (numPoints <= 0) {
            return frontier;
        }

        frontier.reserve(static_cast<std::size_t>(numPoints));
        for (int point = 0; point < numPoints; ++point) {
            const double interpolation = numPoints == 1
                ? 0.0
                : static_cast<double>(point) / static_cast<double>(numPoints - 1);
            const double targetReturn = minReturn + interpolation * (maxReturn - minReturn);
            frontier.push_back(optimizePortfolio(targetReturn));
        }

        return frontier;
    }

}
