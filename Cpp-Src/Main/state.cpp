#include "egghead_comp.hpp"

State::State()
{
    stateValue = new double(0.0);
    pipeline = nullptr;
}

State::~State()
{
    delete stateValue;
    delete pipeline;
}