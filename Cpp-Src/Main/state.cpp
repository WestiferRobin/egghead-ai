#include "egghead_comp.hpp"

State::State()
{
    stateValue = new double(0.0);
    pipeLine = nullptr;
}

State::~State()
{
    delete stateValue;
    delete pipeLine;
}