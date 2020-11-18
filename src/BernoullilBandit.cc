#include "BernoulliBandit.h"

BernoulliBandit::BernoulliBandit(const int n, double e, double l, double Qmax): Bandit(n, e, l) {

    for (int i=0; i<N; i++){
        true_values[i] = ((double) rand() / (RAND_MAX));
        q[i] = Qmax;
    }
};

double BernoulliBandit::sample_return(int a){
    double r = 0;
    std::default_random_engine generator;
    std::bernoulli_distribution distribution(true_values[a]);
    r = distribution(generator);
    return r;
};