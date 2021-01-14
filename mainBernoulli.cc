#include "BernoulliBandit.h"
#include "Experiment.h"
#include <math.h>  
#include <iostream>
#include <fstream>
#include <time.h>   


int main(){

    std::cout<<"\n======\nWelcome to the Bernoulli Multi-Armed Bandit simulator! In order to proceed with the simultion I need:"<<std::endl;
    std::cout<<"* The number of arms\n";
    std::cout<<"* The length of each run\n";
    std::cout<<"* The number of runs\n";
    std::cout<<"* The exploration strategy as an integer, where:\n";
    std::cout<<"  * 0 stays for epsilon-greedy\n";
    std::cout<<"  * 1 stays for Boltzmann\n";
    std::cout<<"  * 2 stays for UCB\n";
    std::cout<<"  * 3 stays for gradient bandit with softmax action preference\n=====\n";

    int N;
    int run_length;
    int n_runs;
    int exploration_strategy;

    std::cin>>N;
    std::cin>>run_length;
    std::cin>>n_runs;
    std::cin>>exploration_strategy;

    if (exploration_strategy>3 || exploration_strategy<0) {
        printf("*****\nUnexpected number for the exploration strategy\n*****\n");
        return -1;
    }

    double epsilon = 0.05;
    double learning_rate = 0.7;
    double c = 0.01;
    double T = 1.;

    double *re;
    int *op;
    double *ret = new double[n_runs*run_length];
    int *opt_action = new int[n_runs*run_length];
    double *means = new double[run_length]();
    double *means1 = new double[run_length]();
    double *percentage_best_action = new double[run_length]();
    double *stddev = new double[run_length]();

    double Qmax = 0.;
    std::ofstream myfile;
    myfile.open ("data_bernoulli.txt");
    myfile << "step   first_run   mean_reward_runs   std_reward_runs   percentage_opt_action\n";
    
    // =========================== RUN LOOPS =========================
    for (int i=0; i<n_runs; i++){
        if (i%100 == 0){
            std::cout<<"Run number "<<i<<"\n";
        }

        BernoulliBandit b(N, epsilon, learning_rate, Qmax);
        Experiment e(epsilon, learning_rate, run_length);

        if (exploration_strategy == 0){
            e.single_run(b);
        } else if (exploration_strategy == 1){
            e.single_run_Boltzmann(b, T);

        }else if (exploration_strategy == 2){
            e.single_run_UCB(b, c);

        }else if (exploration_strategy == 3){
            e.single_run_gradient(b);

        }
        
        re = e.get_returns();
        op = e.get_opt_actions();
        
        if (i == 0 || i==n_runs-1){
            b.print_true_values();
        }
        for (int j=0; j<run_length; j++){
            ret[i*run_length + j] = *(re + j);
            opt_action[i*run_length + j] = *(op + j);
        }

        if (i == 0 || i==n_runs-1){
            b.print_q();
            b.print_action_preferences();
        }
    }

    // ========================== COMPUTE REWARD MEANS AND PERENTAGE OF CORRECT ACTION ========================

    std::vector<std::vector<double> >::iterator it;
    std::vector<double>::iterator i;

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

    std::cout<<"Simulation data saved in data_bernoulli.txt"<<std::endl;

    delete[] ret;
    delete[] means;
    delete[] means1;
    delete[] percentage_best_action;
    delete[] stddev;
    delete[] opt_action;

    myfile.close();

    return 0;
}