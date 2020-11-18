#ifndef EXPERIMENT
#define EXPERIMENT

#include "Bandit.h"

class Experiment{

    public:
        double epsilon;
        double learning_rate;
        int run_length;

        double *returns;
        int *opt_actions;
        
    Experiment(double e, double l, int rl) {
        epsilon = e;
        learning_rate = l;
        run_length = rl;
        returns = new double[run_length];
        opt_actions = new int[run_length];
    };

    ~Experiment(){
        delete[] returns;
        delete[] opt_actions;
    };

    void single_run(Bandit &b);

    double* get_returns();

    int* get_opt_actions();
};

#endif