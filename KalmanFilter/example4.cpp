/**
 * Example 4 – Tracking accelerating aircraft with the α−β−γ filter
 * 
 * 
 * In this example, we are going to track an aircraft that is moving with constant 
 * acceleration with the α−β−γ filter. 
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


    MAT_TYPE radarMeasurements[] = {30160, 30365, 30890, 31050, 31785,
                                    32215, 33130, 34510, 36010, 37265};
    
	// Iteration zero

    // Initial guess
    Eigen::Matrix3f transitionMatrix;
    MAT_TYPE deltat = 5;
    transitionMatrix << 1,                      0, 0,
                        deltat,                 1, 0,
                        deltat*deltat / 2, deltat, 1;
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
    currentState << 30000, 50, 0; // [m] [m/s] [m/s²]

    // alpha-beta-gamma filter parameter initialisation
    MAT_TYPE alpha = 0.5;
    MAT_TYPE beta = 0.4;
    MAT_TYPE gamma = 0.1;
    // With the delta track-to-track interval of 5 seconds
    MAT_TYPE deltat = 5;    // [s]
    coefficients << alpha, 
                    beta / deltat,
                    gamma / (0.5*deltat*deltat);
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