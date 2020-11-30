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

        //std::vector<double> re;
        //std::vector<double> opa;
        
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

    void single_run_UCB(Bandit &b, double c);

    void single_run_Boltzmann(Bandit &b, double T);

    void single_run_gradient(Bandit &b);

    double* get_returns();
    
    std::vector<double> get_returns_vector();

    int* get_opt_actions();
};

#endif