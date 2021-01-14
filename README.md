# Multi-Armed Bandit with Reinforcement Learning

This repository contains a C++ implementation of the Multi-Armed Bandit described in "Reinforcement Learning - An introduction" by Sutton and Barto.

---

The following exploration policies have been implemented:
* Epsilon-greedy
* Boltzmann (softmax)
* UCB
* Gradient Bandit Algorithm with softmax action preferences

---

## Quick start

To compile Gaussian Bandit code use:
```
make -f Makefile.gaus
```

run the executable with `./a.out` and insert the requested parameters. 


In the same way, to compile Bernoulli Bandit code use:
```
make -f Makefile.bern
```
