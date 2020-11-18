#ifndef ABANDIT
#define ABANDIT

#include "stdlib.h"
#include <iostream>
#include <random>

class Bandit{

    public:
        int N;
        double epsilon;
        double learning_rate;
        double *q;
        double *true_values;
        double best_action;

    Bandit(const int n, double e, double l);

    virtual ~Bandit(){
        delete[] q;
        delete[] true_values;
    };

    void update_q(double r, int a);

    int get_best_action();

    void print_q() const noexcept;

    void print_true_values() const noexcept;

    int take_action();

    virtual double sample_return(int a) = 0;

};

#endif