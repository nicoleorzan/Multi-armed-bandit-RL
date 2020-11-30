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
        double *preferences;
        double *true_values;
        int *nt;
        double best_action;
        double *UCBvalues;
        double *q_temperature;
        double avg_reward = 0;
        double *pii;

    Bandit(const int n, double e, double l);

    virtual ~Bandit(){
        delete[] q;
        delete[] preferences;
        delete[] true_values;
        delete[] nt;
        delete[] UCBvalues;
        delete[] q_temperature;
        delete[] pii;
    };

    void update_q(double r, int a);

    void update_q_n(double r, int a, int n);

    void update_avg_reward(int n, double r);

    void update_action_preferences(double r, int a);

    int get_best_action();

    void print_q() const noexcept;

    void print_true_values() const noexcept;

    void print_action_preferences() const noexcept;

    int take_action();

    int UCB(int t, double c);

    int Boltzmann_exploration(double T);

    int gradientBanditAction();

    virtual double sample_return(int a) = 0;

};

#endif