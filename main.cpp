#include <istream>
#include <iostream>
#include <fstream>
using namespace std;


double discount = 0.8;
double d = 10;
double dMin = -3;
int maxN = 5;

double states[2][3];
double sPrime[2][3];
double reward[2][3];
double terminalReward = 0;

int main(int argc, char** argv)
{
    ofstream myfile;
    myfile.open("Output.txt");

    myfile << "Q1)" << endl;
    for(int i = 0; i<2; i++){
        for(int j = 0; j<3; j++){
            sPrime[i][j] = 0;
            reward[i][j] = 0;
        }
    }

    int n = 0;

    do{     
        n++;
        for(int i = 0; i<2; i++){
            for(int j = 0; j<3; j++){
                states[i][j] = sPrime[i][j];
        }

        d = 0;
        for(int i = 0; i<2; i++){
            for(int j = 0; j<3; j++){

                reward[0][2] = terminalReward;

                //make changes to subStates
                double actions[4];

                if((i==0 && j ==2)){
                    sPrime[i][j] = reward[i][j];
                }

                
                else{
                    
                    double moveUp = 0;
                    double moveDown = 0;
                    double moveLeft = 0;
                    double moveRight = 0;

                    //moveUp
                    
                    if(i == 0){
                        moveUp = states[i][j];
                    }
                    else{
                        moveUp = states[i-1][j];
                    }

                    //moveDown
                    if(i==1){
                        moveDown = states[i][j];
                    }
                    else{
                        moveDown = states[i+1][j];
                    }

                    //moveLeft
                    if(j==0){
                        moveLeft = states[i][j];
                    }
                    else{
                        moveLeft = states[i][j-1];
                    }

                    //moveRight
                    
                    if(j==2){
                        moveRight = states[i][j];
                    } 
                    else{
                        moveRight = states[i][j+1];
                    }
                    
                    //possible
                    actions[0] = moveUp;
                    actions[1] = moveDown;
                    actions[2] = moveLeft;
                    actions[3] = moveRight;


                    double k = actions[0];

                    for(int i = 1; i <4; i++){
                        if(actions[i]>k){
                            k = actions[i];
                        }
                    }
                    if((k == moveUp) && (i == 1 && j == 2)){
                        terminalReward = 100;
                    }
                    else if((k == moveRight) && (i == 0 && j == 1)){
                        terminalReward = 50;
                    }
                    else{
                        terminalReward = 0;
                        
                    }

                    sPrime[i][j] = reward[i][j] + discount*k;
                }

                //changes made
                double difference = (sPrime[i][j]-states[i][j]);
                if(difference <0){
                    difference *= -1;
                }

                if(difference > d){
                    d = difference;
                }

                
            }
        }
    }
    if(n!=1){
        myfile << "Iteration " << n-1 << ": " << endl;
        for(int i = 0; i<2; i++){
            for(int j = 0; j<3; j++){
                myfile << states[i][j] << " |";
            }
            myfile << endl;
    }
    myfile << endl;

    }
    

    }
    while(n<maxN && d>dMin);
    

    myfile << "Number of iterations: " << n-1 << endl;
    myfile << endl;
    myfile << "Q2) Optimal Policy: S1 -> S2 -> S5 -> S6 -> S3" << endl;
    myfile << endl;
    myfile << "Q3) Yes, you could multiply each immediate reward by a constant factor - such as double each reward - this would result in V* changing, while the optimal policy would remain the same." << endl;
 
}
