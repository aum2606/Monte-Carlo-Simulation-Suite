#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>
#include <fstream>

//structure to hold simulation parameters
struct SimulationParams{
    double S0; //initial stock price
    double mu; // expected return (annualized)
    double sigma; // volatility(annualized)
    double T; //time period in years
    int numSteps; // number of time steps
    int numPaths; // number of simulation paths 
};

//Function to stimulate stock price using geometric brownian motion
std::vector<std::vector<double>> simulateStockPrices(const SimulationParams& params){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> normalDist(0.0, 1.0);

    double dt = params.T / params.numSteps;
    double sqrtDt = std::sqrt(dt);

    //Initialize results matrix (paths x steps)
    std::vector<std::vector<double>> stockPaths(params.numPaths, std::vector<double>(params.numSteps + 1));

    //set initial stock price for all paths
    for (int i=0;i<params.numPaths;i++){
        stockPaths[i][0] = params.S0; 
    }

     // Simulate each path
    for (int i = 0; i < params.numPaths; i++) {
        for (int j = 0; j < params.numSteps; j++) {
            double Z = normalDist(gen);
            
            // Geometric Brownian Motion formula:
            // S(t+dt) = S(t) * exp((mu - 0.5 * sigma^2) * dt + sigma * sqrt(dt) * Z)
            stockPaths[i][j+1] = stockPaths[i][j] * 
                                 std::exp((params.mu - 0.5 * params.sigma * params.sigma) * dt + 
                                          params.sigma * sqrtDt * Z);
        }
    }
    
    return stockPaths;
}

//calculate statistics from simulation results
void calculateStatistics(const std::vector<std::vector<double>>& stockPaths,
                         const SimulationParams& params){
    //collect final prices
    std::vector<double> finalPrices;
    for(const auto& path:stockPaths){
        finalPrices.push_back(path.back());
    }

    //calculate statistics
    double sum = 0.0;
    double sumSq = 0.0;
    double min = finalPrices[0];
    double max = finalPrices[0];

    for(double price : finalPrices){
        sum += price;
        sumSq += price * price;
        if(price<min) min = price;
        if(price>max) max = price;
    }

    double mean = sum/params.numPaths;
    double variance = (sumSq / params.numPaths) - (mean * mean);
    double stdDev = std::sqrt(variance);

    // Output statistics
    std::cout << "Simulation Statistics:" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "Number of paths: " << params.numPaths << std::endl;
    std::cout << "Initial price: $" << params.S0 << std::endl;
    std::cout << "Time period: " << params.T << " years" << std::endl;
    std::cout << "Mean final price: $" << std::fixed << std::setprecision(2) << mean << std::endl;
    std::cout << "Standard deviation: $" << std::fixed << std::setprecision(2) << stdDev << std::endl;
    std::cout << "Min final price: $" << std::fixed << std::setprecision(2) << min << std::endl;
    std::cout << "Max final price: $" << std::fixed << std::setprecision(2) << max << std::endl;
    

    //calculate theoretical expected price based on GBM properties
    double theoreticalMean = params.S0 * std::exp(params.mu * params.T);
    std::cout <<"Theoretical expected price: $" << std::fixed << std::setprecision(2) << theoreticalMean << std::endl;
}

//function to save simulation paths to csv file
void saveToCSV(const std::vector<std::vector<double>>& stockPaths,
              const SimulationParams& params,
              const std::string& filename){
    std::ofstream outFile(filename);

    if (!outFile.is_open()){
        std::cerr << "Error: Could not open file " <<filename << std::endl;
        return;
    }

    // Write each path
    for (int i = 0; i < params.numPaths; i++) {
        outFile << i + 1;
        for (int j = 0; j <= params.numSteps; j++) {
            outFile << "," << stockPaths[i][j];
        }
        outFile << std::endl;
    }
    outFile.close();
    std::cout << "Simulation results saved to " << filename << std::endl;
}

int main(){
    std::cout << "Stock price simulation using geometric brownian motion" << std::endl;
    std::cout << "---------------------" << std::endl;

    //set simulation parameters
    SimulationParams params;
    params.S0 = 100.0;      //initial stock price
    params.mu = 0.05;       // expected return (annualized) 
    params.sigma = 0.20;    // volatility (20% annualized)
    params.T = 1.0;         // 1 year time period
    params.numSteps = 252;  // daily steps
    params.numPaths = 1000; // number of simulation paths

    //run simulation
    std::vector<std::vector<double>> stockPaths = simulateStockPrices(params);

    //calculate and display statistics
    calculateStatistics(stockPaths, params);

    //save simulation paths to csv file
    saveToCSV(stockPaths, params, "stockPrices.csv");

    return 0;
}