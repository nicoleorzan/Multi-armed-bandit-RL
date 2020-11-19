#include "Bandit.h"
#include <algorithm>

Bandit::Bandit(const int n, double e, double l) {
    N = n;
    epsilon = e;
    learning_rate = l;
    q = new double[N];
    true_values = new double[N];
    nt = new int[N];
    UCBvalues = new double[N];
    q_temperature = new double[N];
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

    //nt[action] += 1;

    return action;
};

int Bandit::UCB(int t, double c){

    int action = 0;

    for (int j=0; j<N; j++){
        if (nt[j] != 0){
            UCBvalues[j] = q[j] + c*sqrt(log(float(t))/nt[j]);
        }
        else{
            UCBvalues[j] = 10000;
        }
    }
    action = std::distance(UCBvalues, std::max_element(UCBvalues, UCBvalues + N));

    if (action ==  std::distance(true_values, std::max_element(true_values, true_values + N))){
        best_action = 1;
    } else { best_action = 0; }

    nt[action] += 1;

    return action;
};

int Bandit::Boltzmann_exploration(double T){

    int action = 0;
    double max_val = 0;
    double denom = 0;
    
    std::vector<double> weights;

    for (int i=0; i<N; i++){
        q_temperature[i] = q[i]/T;
        if (q[i] > max_val){
            max_val = q[i];
        }
    }
    
    for (int i=0; i<N; i++){
        denom += exp(q_temperature[i] - max_val);
    }

    for (int i=0; i<N; i++){
        weights.push_back(exp(q_temperature[i] - max_val)/denom);
    }

    std::random_device rd;
    std::mt19937 generator(rd());

    std::discrete_distribution<int> distribution (weights.begin(), weights.end());
    action = distribution(generator);

    if (action ==  std::distance(true_values, std::max_element(true_values, true_values + N))){
        best_action = 1;
    } else { best_action = 0; }

    //nt[action] += 1;

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