#ifndef NORMALBANDIT
#define NORMALBANDIT

#include "Bandit.h"

class NormalBandit: public Bandit{

    public:
    double var;

    NormalBandit(const int n, double e, double l, double v, double Qmax);

    double sample_return(int a) override;

};

#endif