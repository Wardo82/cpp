#include "stdio.h"
#include <iostream>
#include <cstdlib>

#define mat float
#define NUM_ITERATIONS 10


void initialize(mat& currentState);
inline void update(mat& currentState, mat& nextState, mat& K, mat& measurements);
void kalman();

int main(int argc, char *argv[])
{
    srand(time(0));
    mat currentState, nextState = 0, K = 0, measurements = 0;
	// Iteration zero
    initialize(currentState);
	std::cout << "Measurement | K | currentState | NextState" << std::endl;
    for(int i = 0; i < NUM_ITERATIONS; i++){
        std::cout << measurements << " | " << K << " | " << currentState << " | " << nextState << std::endl;
        measurements = 1010 + (float)(rand()%20 - 10);
        K = float(1)/float(i+1);
        update(currentState, nextState, K, measurements);
        currentState = nextState;
    }

	return 0;
}

void initialize(mat& currentState){
    currentState = 1000;
}

/* Kalman Filter's Predict Step:
* x,X = These variables represent your state (ie. the things you care about and/or trying to filter). 
* For example, if you are controlling a robotic arm with three joints your state can be: [vel1, vel2, vel3, pos1, pos2, pos3]
* action = whatever the action is for the three joint robotic arm the actions can be: [voltage1, voltage2, voltage3]
* P,p = These numbers represent how confident the filter is with the solution. 
* Q = Is the covariance of the process (i.e. action) noise.
*/
inline void predict(mat A,mat B,mat Q,
                    mat lastState, mat action, mat p, mat P){
	//x = A*lastState + B*action;
    //p = A*P*A’ + Q;
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
inline void update(mat& currentState, mat& nextState, mat& K, mat& measurements){
    mat H=1, z = 1;
    //K = p*H'*pinv(H*p*H’+R);
    z=H* measurements;
    nextState = currentState + K * (z-H *currentState); // State Update Equation
    //P = (I – K*H)*p;
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

