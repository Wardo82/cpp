/**
 * Example 5 – Estimating the height of a building
 * 
 * Assume that we would like to estimate the height of a building using a very 
 * imprecise altimeter.
 * 
 * We know for sure, that the building height doesn’t change over time, at least
 * during the short measurement process. 
 */
#include "stdio.h"
#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>

#define MAT_TYPE float
#define NUM_ITERATIONS 10
#define COL_VECTOR Eigen::Matrix<MAT_TYPE, 1, 3>

void initialize(COL_VECTOR &currentState,
                COL_VECTOR &coefficients);
inline void update(COL_VECTOR &currentState, COL_VECTOR &nextState,
                   COL_VECTOR &coefficients,
                   MAT_TYPE radarMeasurement);
inline void predict(COL_VECTOR &currentState,
                    COL_VECTOR &nextState,
                    Eigen::Matrix<MAT_TYPE, 3, 3> &transitionMatrix);
void kalman();

int main(int argc, char *argv[])
{
    srand(time(0));
    COL_VECTOR currentState, nextState, intermediateState;     // This is the state vector with d, v and a
    COL_VECTOR coefficients;     // This is the alpha-beta-gamma column

    initialize(currentState, coefficients);


    MAT_TYPE radarMeasurements[] = {48.54, 47.11, 55.01, 55.15, 49.89,
                                    40.85, 46.72, 50.05, 51.27, 49.95};
    
	// Iteration zero

    // Initial guess
    Eigen::Matrix3f transitionMatrix;
    transitionMatrix << 1, 0, 0,
                        0, 1, 0,
                        0, 0, 1;
    nextState = currentState * transitionMatrix;
    currentState = nextState;
    std::cout << "First guess is: " << currentState << std::endl;

    std::cout << "Measurement | Current State | Next State" << std::endl;
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        update(currentState, intermediateState, coefficients, radarMeasurements[i]);
        predict(intermediateState, nextState, transitionMatrix);
        std::cout << radarMeasurements[i] << " | "
                  << currentState << " | "
                  << nextState << std::endl;

        currentState = nextState;
    }

    return 0;
}

void initialize(COL_VECTOR &currentState,
                COL_VECTOR &coefficients)
{
    std::cout << "Initialising matrices..." << std::endl;
    currentState << 60, 0, 0; // [m] [m/s] [m/s²]

    // alpha-beta-gamma filter parameter initialisation
    MAT_TYPE human_std_dev = 15; // [m]
    MAT_TYPE human_varianz = human_std_dev * human_std_dev;
    coefficients << human_varianz, 
                    0,
                    0;
    std::cout << "Init done." << std::endl;
}

inline void predict(COL_VECTOR &currentState,
                    COL_VECTOR &nextState,
                    Eigen::Matrix<MAT_TYPE, 3, 3> &transitionMatrix){
    nextState = currentState * transitionMatrix;
};

inline void update(COL_VECTOR &currentState, COL_VECTOR &nextState,
                   COL_VECTOR &coefficients,
                   MAT_TYPE radarMeasurement){
    MAT_TYPE diff = radarMeasurement - currentState(0, 0);
    nextState = currentState.array() + coefficients.array() * diff;
};

void kalman(){
    //predict();
    //update();
};