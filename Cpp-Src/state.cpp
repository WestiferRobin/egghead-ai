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

double State::getStateValue()
{
    return *stateValue;
}

Pipe State::getPipeline()
{
    return *pipeLine;
}

void State::loadValue(double newValue)
{
    delete stateValue;
    stateValue = &newValue;
}

void State::addPipeline(Pipe newPipeline)
{
    delete pipeLine;
    pipeLine = &newPipeline;
}