#include "NormalBandit.h"
#include "Experiment.h"
#include <math.h>  
#include <iostream>
#include <fstream>
#include <time.h>   

int main(int argc, char *argv[]){

    if(argc!=3) {// even the executables name string is on argc
        printf("unexpected number of arguments\n");
        return -1;
    }

    int N = 10;
    double var = 1;
    double epsilon = 0.1;
    double learning_rate = 0.5;
    int run_length = 1000;
    int n_runs = 2000;
    double c = 0.5;
    double T = 0.1;

    double *re;
    int *op;
    double *ret = new double[n_runs*run_length];
    int *opt_action = new int[n_runs*run_length];
    double *means = new double[run_length];
    double *percentage_best_action = new double[run_length];
    double *stddev = new double[run_length];

    double Qmax = 0;

    std::ofstream myfile;
    myfile.open ("example2.txt");

    // ===================== ARRAYS INITIALIZATIONS ======================
    for (int i=0; i<n_runs; i++){
        for (int j=0; j<run_length; j++){
            means[j] = 0;
            stddev[j] = 0;
            percentage_best_action[j] = 0;
        }
    }

    // =========================== RUN LOOPS =========================
    for (int i=0; i<n_runs; i++){
        if (i%100 == 0){
            std::cout<<"Run number "<<i<<"\n";
        }
        srand(time(NULL));

        NormalBandit b(N, epsilon, learning_rate, var, Qmax);
        Experiment e(epsilon, learning_rate, run_length);

        //e.single_run(b);
        //e.single_run_UCB(b, c);
        e.single_run_Boltzmann(b, T);
        re = e.get_returns();
        op = e.get_opt_actions();
        
        if (i == 0){
            b.print_true_values();
        }
        for (int j=0; j<run_length; j++){
            ret[i*run_length + j] = *(re + j);
            opt_action[i*run_length + j] = *(op + j);
        }

        if (i == 0){
            b.print_q();
        }
    }

    // ========================== COMPUTE REWARD MEANS AND PERENTAGE OF CORRECT ACTION ========================
    for (int j=0; j<run_length; j++){
        for (int i=0; i<n_runs; i++){
            means[j] += ret[i*run_length + j];
            if (opt_action[i*run_length + j] == 1){
                percentage_best_action[j] += 1./n_runs;
            }
        }
        means[j] = means[j]/n_runs;
        for (int i=0; i<n_runs; i++){
            stddev[j] += (ret[i*run_length + j]-means[j])*(ret[i*run_length + j]-means[j]);
        }
        stddev[j] = sqrt(stddev[j]/n_runs);
        myfile << j << " " << ret[j] << " " << means[j] << " " << stddev[j] << " " << percentage_best_action[j] << "\n";
    }

    delete[] ret;
    delete[] means;
    delete[] percentage_best_action;
    delete[] stddev;
    delete[] opt_action;

    myfile.close();

    return 0;
}