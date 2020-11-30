#include "BernoulliBandit.h"
#include "Experiment.h"
#include <math.h>  
#include <iostream>
#include <fstream>
#include <time.h>   

#define N 10

int main(int argc, char *argv[]){

    if(argc!=3) {
        printf("*****\nUnexpected number of arguments (I need the length of each run and the total number of runs)\n*****\n");
        return -1;
    }

    int run_length = atoi(argv[1]);
    int n_runs = atoi(argv[2]);

    double epsilon = 0.1;
    double learning_rate = 0.1;
    //double c = 10;
    //double T = 0.01;

    double *re;
    int *op;
    double *ret = new double[n_runs*run_length];
    int *opt_action = new int[n_runs*run_length];
    double *means = new double[run_length]();
    double *means1 = new double[run_length]();
    double *percentage_best_action = new double[run_length]();
    double *stddev = new double[run_length]();

    double Qmax = 0.;
    std::ofstream myfile;
    myfile.open ("data_bernoulli/data_N10_normale_epsilon01_alpha01.txt");
    myfile << "step   first_run   mean_reward_runs   std_reward_runs   percentage_opt_action\n";

    // =========================== RUN LOOPS =========================
    for (int i=0; i<n_runs; i++){
        if (i%100 == 0){
            std::cout<<"Run number "<<i<<"\n";
        }
        double value = float(i)*10;
        srand(value);
        //std::cout<<value<<std::endl;
        //srand(i);
        BernoulliBandit b(N, epsilon, learning_rate, Qmax);
        Experiment e(epsilon, learning_rate, run_length);

        e.single_run(b);
        //e.single_run_UCB(b, c);
        //e.single_run_Boltzmann(b, T);
        //e.single_run_gradient(b);
        //std::cout<<"quo\n";
        
        re = e.get_returns();
        //std::cout<<"qua\n";
        op = e.get_opt_actions();

        //returns.push_back(e.get_returns_vector());
        
        if (i == 0 || i==n_runs-1){
            b.print_true_values();
        }
        for (int j=0; j<run_length; j++){
            ret[i*run_length + j] = *(re + j);
            opt_action[i*run_length + j] = *(op + j);
        }

        if (i == 0 || i==n_runs-1){
            b.print_q();
            b.print_action_preferences();
        }
    }

    // ========================== COMPUTE REWARD MEANS AND PERENTAGE OF CORRECT ACTION ========================

    std::vector<std::vector<double> >::iterator it;
    std::vector<double>::iterator i;

    /*for (it = returns.begin(); it != returns.end(); it++){
        std::cout << (*(*it).begin()) << std::endl;
        for (i = (*it).begin(); i != (*it).end(); i++) {
            std::cout << (*i) << std::endl;
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;*/

    for (int j=0; j<run_length; j++){
        for (int i=0; i<n_runs; i++){
            means[j] += ret[i*run_length + j];
            if (opt_action[i*run_length + j] == 1){
                percentage_best_action[j] += 1./n_runs;
            }
        }
        means[j] = means[j]/n_runs;
        for (int i=0; i<n_runs; i++){
            stddev[j] += (ret[i*run_length + j]-means[j])*(ret[i*run_length + j]-means[j]);
        }
        stddev[j] = sqrt(stddev[j]/n_runs);
        myfile << j << " " << ret[j] << " " << means[j] << " " << stddev[j] << " " << percentage_best_action[j] << "\n";
    }

    /*double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();

    double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size() - mean * mean);
    */

    delete[] ret;
    delete[] means;
    delete[] means1;
    delete[] percentage_best_action;
    delete[] stddev;
    delete[] opt_action;

    myfile.close();

    return 0;
}