#include <iostream>
#include <random>
#include <cmath>
#include <iomanip>

//function to estimate pi using Monte Carlo method

double estimatePi(long long numPoints){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    long long pointInCircle = 0;

    for (long long i=0;i<numPoints;i++){
        double x = dis(gen);
        double y = dis(gen);

        //check if point (x,y) lies inside the circle
        if (x*x + y*y <= 1.0){
            pointInCircle++;
        }
    }
    //Pi estimation: (points in circle /  total points) * 4
    return (pointInCircle * 4.0) / numPoints;
}

int main(){
    std::cout << "Monte Carlo Pi Estimation" << std ::endl;
    std::cout << "----------------" << std::endl;

    //different sample sizes to demonstrate convergence
    long long sampleSizes[] = {1000, 10000, 100000, 1000000, 10000000};

    for (auto samples:sampleSizes){
        double piEstimate = estimatePi(samples);
        double error = std::abs(piEstimate - M_PI);

        std::cout << "Samples: " << std::setw(10) << samples
                  << "| Pi Estimate: " << std::setprecision(10) << piEstimate
                  << "| Error: " << error << std::endl;
    }
    return 0;
}

