#include <iostream>
//#include "egghead_comp.hpp"
#include "test_case.hpp"

using namespace std;

const int TRAIN_TIMES = 1000000;

void runPostTron(bool flag)
{
    Network* caseInst = new PosTron();
    vector<vector<double>*>* cases = new vector<vector<double>*>();
    if (flag)
    {
        cases->push_back(new vector<double>{ 0.0, 0.0, 0.0 });
        cases->push_back(new vector<double>{ 0.0, 1.0, 0.0 });
        cases->push_back(new vector<double>{ 1.0, 0.0, 0.0 });
        cases->push_back(new vector<double>{ 1.0, 1.0, 1.0 });

    }
    else
    {
        cases->push_back(new vector<double>{ 0.0, 0.0, 0.0 });
        cases->push_back(new vector<double>{ 0.0, 1.0, 1.0 });
        cases->push_back(new vector<double>{ 1.0, 0.0, 1.0 });
        cases->push_back(new vector<double>{ 1.0, 1.0, 1.0 });
    }
    caseInst->buildNetwork();
    caseInst->trainNetwork(TRAIN_TIMES, cases);
    for (int index = 0; index < cases->size(); index++)
    {
        double ans = caseInst->runNormal({cases->at(index)->at(0), cases->at(index)->at(1)}, true)[0];
        string resultName = "[" + to_string(cases->at(index)->at(0)) + ", " + to_string(cases->at(index)->at(1)) + ", " + to_string(cases->at(index)->at(2)) + ", " + "]";
        cout << resultName + " has the result of " + to_string(ans) << endl;
    }
}

void runXorTron()
{
    Network* caseInst = new XorTron();
    vector<vector<double>*>* cases = new vector<vector<double>*>();
    cases->push_back(new vector<double>{ 0.0, 0.0, 0.0 });
    cases->push_back(new vector<double>{ 0.0, 1.0, 1.0 });
    cases->push_back(new vector<double>{ 1.0, 0.0, 1.0 });
    cases->push_back(new vector<double>{ 1.0, 1.0, 0.0 });
    caseInst->buildNetwork();
    caseInst->trainNetwork(TRAIN_TIMES, cases);
    for (int index = 0; index < cases->size(); index++)
    {
        double ans = caseInst->runNormal({ cases->at(index)->at(0), cases->at(index)->at(1) }, true)[0];
        string resultName = "[" + to_string(cases->at(index)->at(0)) + ", " + to_string(cases->at(index)->at(1)) + ", " + to_string(cases->at(index)->at(2)) + ", " + "]";
        cout << resultName + " has the result of " + to_string(ans) << endl;
    }
}

int main()
{
    for (int index = 1; index <= 3; index++)
    {
        switch (index)
        {
        case 2:
            cout << "AND Model" << endl;
            runPostTron(true);
            break;
        case 3:
            cout << "OR Model" << endl;
            runPostTron(false);
            break;
        case 1:
            cout << "XOR Model" << endl;
            runXorTron();
            break;
        }
        cout << endl;
    }
    return 0;
}