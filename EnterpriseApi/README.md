# Enterprise API

Example C++ project demonstrating market data processing
and portfolio optimization.

## Overview

This project provides examples of financial engineering components
implemented using modern C++.

The project contains two main classes:

- `MarketDataProcessor`: stores historical market prices and calculates
  volatility and other financial metrics.
- `PortfolioOptimizer`: manages portfolio assets, covariance data,
  portfolio risk, and portfolio allocations.

## Main Features

- Historical market price storage
- Log-return calculation
- Volatility calculation
- High-volatility asset detection
- Portfolio risk calculation
- Portfolio optimization
- Efficient frontier generation
- Template-based financial calculations

## Main Classes

- FinancialEngineering::MarketDataProcessor
- FinancialEngineering::PortfolioOptimizer

## Requirements

- C++17 or later
- Doxygen
- Graphviz

## Documentation

The documentation is generated using Doxygen.

From the project root:

    doxygen Doxyfile

The generated HTML documentation can then be opened from:

    docs/html/index.html