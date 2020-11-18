#include "Bandit.h"
#include <algorithm>

Bandit::Bandit(const int n, double e, double l) {
    N = n;
    epsilon = e;
    learning_rate = l;
    q = new double[N];
    true_values = new double[N];
};

int Bandit::take_action(){

    int action = 0;
    double rand_num = ((double) rand() / (RAND_MAX));

    if (rand_num < epsilon){   //random action
        action = rand() % (( N ));
    } else {   //greedy action
        action = std::distance(q, std::max_element(q, q + N));
    }

    if (action ==  std::distance(true_values, std::max_element(true_values, true_values + N))){
        best_action = 1;
    } else { best_action = 0; }

    return action;
};

void Bandit::print_q() const noexcept {
    std::cout<<"\n";
    for (int i=0; i<N; i++){
        std::cout<<"i="<<i<<", q["<<i<<"]="<<q[i]<<"\n";
    }
    std::cout<<"\n";
};

void Bandit::print_true_values() const noexcept {
    std::cout<<"\n";
    for (int i=0; i<N; i++){
        std::cout<<"i="<<i<<", tru_value["<<i<<"]="<<true_values[i]<<"\n";
    }
    std::cout<<"\n";
};

void Bandit::update_q(double r, int a){
    q[a] += learning_rate*(r - q[a]);
};

int Bandit::get_best_action(){
    return best_action;
};