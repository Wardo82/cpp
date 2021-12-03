/**
 * Example 2 – Tracking the constant velocity aircraft in one dimension
 * 
 * Now, it is time to examine a dynamic system that changes its state over time. 
 * In this example, we are going to track a constant-velocity aircraft in one dimension 
 * using the α-β filter.
 * 
 * Let us assume a one-dimensional world. We assume an aircraft that is moving radially 
 * away from the radar (or towards the radar). In the one-dimensional world, the angle 
 * to the radar is constant and the altitude of the aircraft is constant.
 */
#include "stdio.h"
#include <iostream>
#include <cstdlib>

#define mat float
#define NUM_ITERATIONS 10

void initialize(mat& currentStateX, mat& currentStateXhat);
inline void update(mat& previousStateX, mat& currentStateX,
                    mat& previousStateXhat, mat& currentStateXhat,
                    mat& alpha, mat& beta, mat& deltaT, mat& measurements);
inline void predict(mat& currentStateX, mat& nextStateX,
                    mat& currentStateXhat, mat& nextStateXhat,
                    mat& deltaT);
void kalman();

int main(int argc, char *argv[])
{
    srand(time(0));
    mat currentStateX = 0, nextStateX = 0,
        currentStateXhat = 0, nextStateXhat = 0;
    mat measurements[] = {30110, 30265, 30740, 30750, 31135, 31015, 31180, 31610, 31960, 31865};
    
    mat alpha = 0.2;
    mat beta = 0.1;
    mat deltaT = 5; // [s]
	// Iteration zero
    initialize(currentStateX, currentStateXhat);
    mat realState = currentStateX;
	mat realStateHat = currentStateXhat;
    
    // Initial guess
    currentStateX = realState + deltaT * realStateHat;
    currentStateXhat = realStateHat;

    std::cout << "Measurement | currentStateX | currentStateXhat | NextState" << std::endl;
    for(int i = 0; i < NUM_ITERATIONS; i++){
        update(currentStateX, currentStateX,
                currentStateXhat, currentStateXhat, 
                alpha, beta, deltaT, measurements[i]);
        predict(currentStateX, nextStateX,
                currentStateXhat, nextStateXhat, deltaT);
        std::cout << measurements[i] << " | " 
                  << currentStateX << " | " << currentStateXhat <<  " | "
                  << nextStateX  <<  " | " << nextStateXhat << std::endl;

        currentStateX = nextStateX;
        currentStateXhat = nextStateXhat;
    }

	return 0;
}

void initialize(mat& currentStateX, mat& currentStateXhat){
    currentStateX = 30000; // [m]
    currentStateXhat = 40; // [m/s]
}

/* Kalman Filter's Predict Step:
* x,X = These variables represent your state (ie. the things you care about and/or trying to filter). 
* For example, if you are controlling a robotic arm with three joints your state can be: [vel1, vel2, vel3, pos1, pos2, pos3]
* action = whatever the action is for the three joint robotic arm the actions can be: [voltage1, voltage2, voltage3]
* P,p = These numbers represent how confident the filter is with the solution. 
* Q = Is the covariance of the process (i.e. action) noise.
*/
inline void predict(mat& currentStateX, mat& nextStateX,
                    mat& currentStateXhat, mat& nextStateXhat,
                    mat& deltaT){
    nextStateX = currentStateX + currentStateXhat * deltaT;
    nextStateXhat = currentStateXhat;
};

/* Kalman Filter's Update Step: 
* K = This matrix gets updates as part of the measurement update stage. It is called the Kalman Gain
* H = Is a model of the sensors, but is hard to determine. 
* An easy approach is to initialize it as a diagonal identity matrix and tweak it to improve the final filter results.
* R = Similar to Q except this defines the confidence in each of the sensors. 
* This is the key matrix for conducting sensor fusion.
* z = These are the measurements that are returned from the sensors at each location. 
* I = an Identity matrix (also diagonal)
*/
inline void update(mat& previousStateX, mat& currentStateX,
                    mat& previousStateXhat, mat& currentStateXhat,
                    mat& alpha, mat& beta, mat& deltaT, mat& measurements){
    mat H=1, z = 1;
    z = H * measurements;
    currentStateX = previousStateX + alpha * (z - H * previousStateX); // State Update Equation
    currentStateXhat = previousStateXhat + beta * (z - H * previousStateX ) / deltaT;
};

void kalman(){
    //predict();
    //update();
};

// When you do not have any prior data then we need a more formal way to determine the A and B matrices. This approach can be difficult and involve a lot of math. The general idea is to start somewhere and perturb your system and record the states, perturb again, record again, etc.
void computeA(mat A, mat newState, mat lastState) {
    //A = newState * pinv(lastState);
}

// The B matrix can be made in the same way except that instead of perturbing the state we perturb the actions and record the states.
void computeB(mat A, mat B, mat currentState, mat lastState, mat action)
{
    //B = (currentState - (A*lastState))*pinv(action);
}

