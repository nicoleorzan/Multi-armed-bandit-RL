#include "Experiment.h"

void Experiment::single_run(Bandit &b){

    int a = 0;
    double r = 0;

    for (int j=0; j<run_length; j++){
        a = b.take_action();
        opt_actions[j] = b.get_best_action();
        r = b.sample_return(a);
        returns[j] = r;
        b.update_q(r, a);
    }
};

void Experiment::single_run_UCB(Bandit &b, double c){

    int a = 0;
    double r = 0;

    for (int j=0; j<run_length; j++){
        a = b.UCB(j, c);
        opt_actions[j] = b.get_best_action();
        r = b.sample_return(a);
        returns[j] = r;
        b.update_q(r, a);
    }
};

void Experiment::single_run_Boltzmann(Bandit &b, double T){

    int a = 0;
    double r = 0;

    for (int j=0; j<run_length; j++){
        a = b.Boltzmann_exploration(T);
        opt_actions[j] = b.get_best_action();
        r = b.sample_return(a);
        returns[j] = r;
        b.update_q(r, a);
    }
};

double* Experiment::get_returns(){
    return returns;
};

int* Experiment::get_opt_actions(){
    return opt_actions;
};