# Monte Carlo Simulation Suite

This project contains C++ implementations of Monte Carlo simulation techniques for both mathematical approximation and financial modeling.

## Components

### 1. Monte Carlo Pi Estimation

A classic application of the Monte Carlo method to estimate the value of π by randomly sampling points within a square and determining how many fall within a unit circle.

### 2. Stock Price Simulation

An extension of Monte Carlo techniques to financial modeling using Geometric Brownian Motion to simulate stock price movements over time.

## Features

- **High-precision random number generation** using C++ standard library
- **Configurable simulation parameters** for both Pi estimation and stock price modeling
- **Statistical analysis** of simulation results
- **CSV export** of simulation data for further analysis or visualization
- **Performance optimized** for large-scale simulations

## Requirements

- C++11 compatible compiler
- Standard C++ libraries

## Build Instructions

```bash
# Clone the repository
git clone https://github.com/yourusername/monte-carlo-suite.git
cd monte-carlo-suite

# Compile the Pi estimation program
g++ -std=c++11 -O3 monte_carlo_pi.cpp -o monte_carlo_pi

# Compile the stock simulation program
g++ -std=c++11 -O3 stock_simulation.cpp -o stock_simulation
```

## Usage

### Pi Estimation

```bash
./monte_carlo_pi
```

The program will run multiple estimations with increasing precision and display the results.

### Stock Price Simulation

```bash
./stock_simulation
```

This will run a simulation with default parameters:
- Initial stock price: $100
- Expected annual return: 5%
- Annual volatility: 20%
- Time period: 1 year
- Time steps: 252 (trading days)
- Number of simulation paths: 1000

The results will be printed to the console and saved to `stock_simulation.csv`.

## Customization

You can modify the simulation parameters by editing the respective source files:

- For Pi estimation: Edit the `sampleSizes` array in `monte_carlo_pi.cpp`
- For stock simulation: Edit the `params` structure in `stock_simulation.cpp`

## Applications

- **Educational tool** for understanding Monte Carlo methods
- **Financial analysis** for risk assessment and option pricing
- **Numerical integration** for complex problems
- **Probability estimation** for statistical problems

## License

This project is licensed under the MIT License - see the LICENSE file for details.
