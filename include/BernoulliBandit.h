#ifndef BERNOULLIBANDIT
#define BERNOULLIBANDIT

#include "Bandit.h"

class BernoulliBandit: public Bandit{

    public:

    BernoulliBandit(const int n, double e, double l, double Qmax);

    double sample_return(int a) override;

};

#endif