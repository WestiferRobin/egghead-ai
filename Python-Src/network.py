from math import exp, pow
from pipe import Pipe
from state import State
from node import Node

class Network:

    def __init__(self, learn_rate = 0.001, layers = []):
        self.learn_rate = learn_rate
        self.layers = layers
        self.input_layer = []
        self.output_layer = []

    # THIS IS "ABSTRACT METHOD"
    def build_network(self):
        pass

    # THIS IS "ABSTRACT METHOD"
    def train_network(self, iterations=0, cases=[]):
        pass

    def connect_pipeline(self, source_node, target_node):
        pipe_line = Pipe()
        source_node.add_front_pipe(pipe_line)
        target_node.add_back_pipe(pipe_line)

    def connect_state_to_node(self, source_state, target_node):
        if source_state.pipe_line == None:
            pipe_line = Pipe()
            source_state.add_pipeline(pipe_line)
            target_node.add_back_pipe(pipe_line)
        else:
            target_node.add_back_pipe(source_state.pipe_line)

    def connect_node_to_state(self, source_node, target_state):
        if target_state.pipe_line == None:
            pipe_line = Pipe()
            source_node.add_front_pipe(pipe_line)
            target_state.add_pipeline(pipe_line)
        else:
            source_node.add_front_pipe(target_state.pipe_line)

    def add_layer(self, layer):
        self.layers.append(layer)

    def run_normal(self, inputs, return_raw=False):
        self.__forward(inputs)
        ans = []
        for output_state in self.output_layer:
            if return_raw:
                ans.append(output_state.state_value)
            else:
                if (0.5 <= output_state.state_value):
                    ans.append(1)
                else:
                    ans.append(0)
        return ans

    def run_forward(self, inputs):
        self.__forward(inputs)

    def __forward(self, inputs):
        if len(inputs) != len(self.input_layer):
            print("Inputs don\'t aline with input states. Please check again.")
        for index in range(0, len(inputs)):
            self.input_layer[index].load_value(float(inputs[index]))
        for input_state in self.input_layer:
            input_state.pipe_line.forward_result = input_state.state_value
        for layer in self.layers:
            layer.forward()
        for output_state in self.output_layer:
            output_state.load_value(output_state.pipe_line.forward_result)

    def run_backward(self, expected):
        self.__backward(expected)

    def __backward(self, expected):
        if len(expected) != len(self.output_layer):
            print("Error: expected and actual length isn\'t valid.")
            return
        constant = 1.0 / len(expected)
        res = []
        for index in range(0, len(expected)):
            self.output_layer[index].pipe_line.backward_result = (-1.0 * constant * (expected[index] - self.output_layer[index].state_value))
        index_layer = len(self.layers) - 1
        while index_layer >= 0:
            # print(self.layers[index_layer].to_string())
            self.layers[index_layer].backward(self.learn_rate)
            index_layer -= 1