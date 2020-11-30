#include "Experiment.h"

void Experiment::single_run(Bandit &b){

    int a = 0;
    double r = 0;

    for (int j=0; j<run_length; j++){
        a = b.take_action();
        opt_actions[j] = b.get_best_action();
        r = b.sample_return(a);
        //re.push_back(r);
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
        //re.push_back(r);
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
        //re.push_back(r);
        returns[j] = r;
        b.update_q(r, a);
    }
};


void Experiment::single_run_gradient(Bandit &b){

    int a = 0;
    double r = 0;

    for (int j=0; j<run_length; j++){
        a = b.gradientBanditAction();
        //std::cout<<"qua\n";
        opt_actions[j] = b.get_best_action();
        //std::cout<<"quos\n";
        r = b.sample_return(a);
        //std::cout<<"quas\n";
        //re.push_back(r);
        returns[j] = r;
        //std::cout<<"quosquas\n";
        b.update_avg_reward(j, r);
        //std::cout<<"ques\n";
        b.update_action_preferences(r, a);
    }
};

double* Experiment::get_returns(){
    return returns;
};

/*std::vector<double> Experiment::get_returns_vector(){
    return re;
};
*/
int* Experiment::get_opt_actions(){
    return opt_actions;
};