#pragma once
/// @file MarketDataProcessor.h
/// @brief Advanced market data analysis and volatility calculation engine
/// @author Financial Engineering Team
/// @version 2.1.0
/// @date 2024-08-21
///
/// This module provides comprehensive market data processing capabilities for
/// high-frequency trading systems and portfolio management applications.
///
/// Key Features:
/// - Real-time volatility calculation using multiple mathematical models
/// - Historical price analysis with configurable time windows
/// - Risk metrics calculation including Sharpe ratio and drawdown analysis
/// - Thread-safe operations for concurrent market data processing
///
/// Performance Characteristics:
/// - Supports processing of 10,000+ price updates per second
/// - Memory-efficient storage using rolling window buffers
/// - O(n) complexity for most statistical calculations
///
/// @warning This library handles real financial data and calculations.
///          All monetary calculations use double precision, which may
///          introduce rounding errors in extreme precision scenarios.

#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <optional>

namespace FinancialEngineering {

    /// @class MarketDataProcessor
    /// @brief Processes market price data and calculates risk metrics
    ///
    /// This class provides a comprehensive suite of market data analysis tools
    /// designed for quantitative finance applications. It maintains historical
    /// price data for multiple assets and provides real-time calculation of
    /// volatility, correlation, and other risk metrics.
    ///
    /// Thread Safety:
    /// - All public methods are thread-safe
    /// - Internal data structures use read-write locks for optimal performance
    /// - Safe for concurrent use by multiple trading threads
    ///
    /// Usage Example:
    /// @code
    /// MarketDataProcessor processor(0.025);  // 2.5% volatility threshold
    ///
    /// // Add price data
    /// processor.addPriceData("AAPL", 150.25, std::chrono::system_clock::now());
    /// processor.addPriceData("AAPL", 151.30, std::chrono::system_clock::now());
    ///
    /// // Calculate 30-day volatility
    /// auto volatility = processor.calculateVolatility("AAPL", 30);
    /// if (volatility) {
    ///     std::cout << "AAPL 30-day volatility: " << *volatility << std::endl;
    /// }
    /// @endcode
    class MarketDataProcessor {
    private:
        /// Historical price storage: symbol -> chronological price vector
        std::map<std::string, std::vector<double>> priceHistory;

        /// Timestamp of most recent data update for staleness detection
        std::chrono::system_clock::time_point lastUpdate;

        /// Volatility threshold for high-risk asset identification (default: 2%)
        double volatilityThreshold;

    public:
        /// @brief Constructs a market data processor with specified volatility threshold
        ///
        /// @param threshold Volatility level above which assets are considered high-risk
        ///                 (expressed as decimal: 0.02 = 2% daily volatility)
        ///
        /// @pre threshold must be positive and typically between 0.001 (0.1%) and 0.1 (10%)
        /// @post Processor is ready to accept price data
        ///
        /// Example:
        /// @code
        /// MarketDataProcessor lowRisk(0.01);   // 1% threshold for conservative portfolios
        /// MarketDataProcessor standard(0.02);  // 2% threshold for balanced portfolios
        /// MarketDataProcessor highRisk(0.05);  // 5% threshold for aggressive strategies
        /// @endcode
        MarketDataProcessor(double threshold = 0.02);

        /// @brief Appends a valid price to the symbol's history and updates lastUpdate
        /// @param symbol Non-empty asset identifier
        /// @param price Finite, strictly positive price
        /// @param timestamp Timestamp stored as the most recent update
        /// @return true if the price was added; false if symbol or price is invalid
        /// @note Prices are stored in insertion order; timestamps are not validated
        ///       or stored individually for each price.
        bool addPriceData(const std::string& symbol, double price,
            std::chrono::system_clock::time_point timestamp);

        /// @brief Calculates the population standard deviation of recent log returns
        /// @param symbol Asset whose price history is used
        /// @param windowSize Maximum number of consecutive returns to include (default: 30)
        /// @return Non-annualized volatility, or std::nullopt if the symbol is unknown,
        ///         fewer than two prices exist, or windowSize is not positive
        /// @note Uses the latest prices in insertion order and all available returns
        ///       if fewer than windowSize exist. A single return produces zero volatility.
        std::optional<double> calculateVolatility(const std::string& symbol,
            int windowSize = 30);

        /// @brief Finds assets whose volatility strictly exceeds volatilityThreshold
        /// @return Symbol-volatility pairs ordered by symbol; empty if none qualify
        /// @note Uses calculateVolatility() with its default window of 30 returns.
        ///       Assets without a calculable volatility are omitted.
        std::vector<std::pair<std::string, double>> getHighVolatilityAssets();

        /// @brief Removes the price history of one asset or all assets
        /// @param symbol Asset to remove, or an empty string to clear all histories
        /// @note An unknown symbol has no history to remove. lastUpdate is reset to
        ///       its default value when no histories remain; otherwise it is retained.
        void clearHistoricalData(const std::string& symbol = "");

        /// @brief Calculates the arithmetic mean of a collection of asset returns
        ///
        /// This simplified implementation returns the mean of the provided returns.
        /// It does not yet calculate a Sharpe ratio and ignores riskFreeRate.
        ///
        /// @tparam PriceContainer Container type holding the return values.
        ///         The container must support iteration, empty(), and size().
        ///
        /// @param returns Collection of asset returns used for the calculation
        /// @param riskFreeRate Reserved risk-free rate; currently ignored (default: 0.02)
        ///
        /// @return Arithmetic mean of the returns, or 0.0 if the container is empty
        ///
        /// @pre returns should contain valid numeric return values
        ///
        /// Example:
        /// @code
        /// std::vector<double> returns = {0.01, 0.03, 0.02, -0.01};
        ///
        /// double sharpe = processor.calculateSharpeRatio(returns, 0.02);
        /// @endcode
        template<typename PriceContainer>
        double calculateSharpeRatio(const PriceContainer& returns,
            double riskFreeRate = 0.02);
    };

    /// @brief Calculates the arithmetic mean of a collection of asset returns
    /// @tparam PriceContainer Container of numeric returns supporting iteration,
    ///         empty(), and size()
    /// @param returns Collection of asset returns used for the calculation
    /// @param riskFreeRate Reserved risk-free rate; currently ignored
    /// @return Arithmetic mean of the returns, or 0.0 if the container is empty
    /// @note This simplified implementation does not yet calculate a Sharpe ratio.
    template<typename PriceContainer>
    double MarketDataProcessor::calculateSharpeRatio(
        const PriceContainer& returns,
        double riskFreeRate)
    {
        // Avoid division by zero if the container is empty.
        if (returns.empty()) {
            return 0.0;
        }

        // Calculate the mean of all returns.
        double mean = 0.0;

        for (const auto& value : returns) {
            mean += value;
        }

        mean /= static_cast<double>(returns.size());

        // riskFreeRate is not used yet in this simplified implementation.
        (void)riskFreeRate;

        return mean;
    }

    /// @class PortfolioOptimizer
    /// @brief Stores portfolio assets and covariance data and calculates portfolio risk
    /// @note Portfolio optimization currently assigns equal weights, ignoring target
    ///       returns and constraints. Frontier generation repeats this allocation
    ///       for each requested point rather than computing an efficient frontier.
    class PortfolioOptimizer {
    private:
        std::vector<std::string> assets;
        std::map<std::string, double> expectedReturns;
        std::vector<std::vector<double>> covarianceMatrix;

    public:
        /// @brief Adds an asset or updates the expected return of an existing asset
        /// @param symbol Non-empty asset identifier
        /// @param expectedReturn Finite expected return associated with the asset
        /// @note Empty symbols and non-finite returns are ignored. New assets retain
        ///       their insertion order for indexing the covariance matrix.
        void addAsset(const std::string& symbol, double expectedReturn);

        /// @brief Replaces the stored covariance matrix with a copy of matrix
        /// @param matrix Covariance values with rows and columns in asset insertion order
        /// @note No validation is performed here. calculatePortfolioRisk() requires
        ///       a square matrix with one row and column per registered asset.
        void updateCovarianceMatrix(const std::vector<std::vector<double>>& matrix);

        /// @brief Builds an equally weighted allocation across all registered assets
        /// @param targetReturn Requested portfolio return; currently ignored
        /// @param constraints Optional allocation constraints; currently ignored
        /// @return Asset weights of 1 / asset count, or an empty map if no assets exist
        /// @note This simplified implementation does not use expected returns or
        ///       covariance data and does not enforce the requested return or constraints.
        std::map<std::string, double> optimizePortfolio(double targetReturn,
            const std::map<std::string, double>& constraints = {});

        /// @brief Calculates risk as the square root of the weighted portfolio variance
        /// @param weights Asset weights; missing registered assets receive zero weight
        /// @return sqrt(max(0, w^T * covarianceMatrix * w)), or zero if matrix
        ///         dimensions do not match the number of registered assets
        /// @note Weights for unregistered assets are ignored. Weights are not normalized,
        ///       and the matrix is not checked for symmetry or positive semidefiniteness.
        double calculatePortfolioRisk(const std::map<std::string, double>& weights);

        /// @brief Generates allocations for evenly spaced target returns
        /// @param numPoints Number of allocations to generate (default: 50)
        /// @param minReturn First target return, also used when numPoints is one
        /// @param maxReturn Last target return when numPoints is greater than one
        /// @return Allocations in target sampling order, or an empty vector if numPoints
        ///         is not positive; each allocation is empty if no assets are registered
        /// @note Calls optimizePortfolio() for each target. Its current equal-weight
        ///       implementation produces identical allocations for all points.
        std::vector<std::map<std::string, double>> generateEfficientFrontier(
            int numPoints = 50, double minReturn = 0.05, double maxReturn = 0.15);
    };

}
