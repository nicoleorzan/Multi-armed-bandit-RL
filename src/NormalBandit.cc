#include "NormalBandit.h"

NormalBandit::NormalBandit(const int n, double e, double l, double v, double Qmax): Bandit(n, e, l), var{v} {
    
    std::default_random_engine generator;
    for (int i=0; i<N; i++){
        std::normal_distribution<double> distribution(0, var);
        true_values[i] = distribution(generator);
        q[i] = Qmax;
        UCBvalues[i] = 10000;
        nt[i] = 0;
    }

};

double NormalBandit::sample_return(int a){
    
    double r = 0;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(true_values[a], var);
    r = distribution(generator);
    return r;

};