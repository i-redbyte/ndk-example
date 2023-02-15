/*
 * (c) https://github.com/NathanEpstein/markov
 * */
#include <cmath>
#include <vector>
#include <random>

bool sortAsc(double i, double j) {
    return (i < j);
}

std::vector<double> poissonProcess(double lambda, double T) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::poisson_distribution<> P(lambda * T);

    int n = P(gen);
    std::vector<double> myVec(n);
    for (int i = 0; i < n; i++) {
        myVec[i] = std::generate_canonical<double, 10>(gen) * T;
    }
    sort(myVec.begin(), myVec.end(), sortAsc);
    return myVec;
}

std::vector<double> brownian(double mu, double sigma, double T, int steps) {
    double dt = T / steps;
    std::vector<double> myVec(steps + 1);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> norm(mu * dt, sigma * sqrt(dt));

    myVec[0] = 0;
    for (int i = 0; i < steps; i++) {
        myVec[i + 1] = myVec[i] + norm(gen);
    }
    return myVec;
}

std::vector<double> geoBrownian(double S0, double mu, double sigma, double T, int steps) {
    std::vector<double> myVec = brownian(mu - (pow(sigma, 2) / 2), sigma, T, steps);
    for (int i = 0; i < myVec.size(); i++) {
        myVec[i] = S0 * exp(myVec[i]);
    }
    return myVec;
}

std::vector<int> DTMC(std::vector<std::vector<double> > trans, int steps, int start) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> myVec(steps + 1);
    myVec[0] = start;
    int count;
    double sum;
    double U;

    for (int i = 0; i < steps; i++) {
        count = 0;
        sum = 0;
        U = std::generate_canonical<double, 10>(gen);
        while (sum < U) {
            sum += trans[myVec[i]][count];
            if (sum > U) {
                myVec[i + 1] = count;
            }
            count++;
        }
    }
    return myVec;
}

class CTMC {
public:
    CTMC(std::vector<std::vector<double> > initMatrix);

    ~CTMC();

    void simulate(double T, int state);

    std::vector<int> getStates();

    std::vector<double> transTimes();

protected:
    std::vector<std::vector<double> > matrix;
    std::vector<int> states;
    std::vector<double> times;
};

CTMC::CTMC(std::vector<std::vector<double> > initMatrix) {
    matrix = initMatrix;
}

CTMC::~CTMC() {
}

std::vector<int> CTMC::getStates() {
    return states;
}

std::vector<double> CTMC::transTimes() {
    return times;
}

void CTMC::simulate(double T, int state) {
    std::random_device rd;
    std::mt19937 gen(rd());

    times.push_back(0); //start time
    states.push_back(state); //start state

    double t = 0;
    double lambda;
    double U;
    double sum;
    int j;
    std::vector<std::vector<double> > trans = matrix;

    while (t < T) {
        lambda = 0;
        state = states.back();
        for (int i = 0; i < trans[state].size(); i++) {
            lambda += trans[state][i];
        }
        std::exponential_distribution<> stepT(lambda);
        t += stepT(gen);
        if (t < T) {
            j = 0;
            sum = 0;
            U = std::generate_canonical<double, 10>(gen);
            while (sum < U) {
                sum += trans[state][j] / lambda;
                if (sum > U) {
                    //push time and state
                    times.push_back(t);
                    states.push_back(j);
                } else {
                    j++;
                }
            }
        }
    }
}