from math import exp, pow
import random

class Node:

    def __init__(self, size, active_flag=1, name=''):
        self.name = name
        self.active_flag = active_flag
        self.basis = random.random()
        lst = []
        for index in range(0, size):
            lst.append(random.random())
        self.weights = lst
        self.front_pipes = []
        self.back_pipes = []

    def derive(self, learn_rate):
        t = self.__calculateT()
        outter_der = self.dev_active(t)
        param_der = 0.0
        for pipe in self.front_pipes:
            param_der += pipe.backward_result
        outter_der *= param_der
        for index in range(0, len(self.weights)):
            inner_der = self.back_pipes[index].forward_result
            self.weights[index] -= float(learn_rate * outter_der * inner_der)
            self.back_pipes[index].backward_result = outter_der * self.weights[index]
        self.basis -= float(learn_rate * outter_der)

    def calculate(self):
        t = self.__calculateT()
        for pipe in self.front_pipes:
            pipe.forward_result = self.active(t)

    def __calculateT(self):
        ans = float(self.basis)
        if len(self.back_pipes) != len(self.weights):
            print("This node is not working due to pipe and or weight configuration.")
        for index in range(0, len(self.weights)):
            ans += float(self.back_pipes[index].forward_result * self.weights[index])
        return ans

    def active(self, value):
        if self.active_flag == 1:
            return float(1.0 / (1.0 + exp(-value)))
        else:
            return 0.0

    def dev_active(self, value):
        if self.active_flag == 1:
            sig = self.active(value)
            return float(sig * (1.0 - sig))
        else:
            return 0.0

    def add_front_pipe(self, pipe):
        self.front_pipes.append(pipe)

    def add_back_pipe(self, pipe):
        self.back_pipes.append(pipe)

    def to_string(self):
        ans = "NODE " + self.name + "\n"
        ans += ("weights: " + str(self.weights)) + "\n"
        ans += ("basis: " + str(self.basis))
        return ans