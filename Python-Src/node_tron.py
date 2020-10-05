from node import Node
from layer import Layer
from network import Network
from state import State
from pipe import Pipe
from math import exp, pow
import random

class NodeTron(Network):

    def __init__(self):
        Network.__init__(self)

    def build_network(self):
        main_node = Node(2, 1, 'mainNode')
        hidden_layer = Layer(self.learn_rate)
        self.input_layer = [State(), State()]
        self.output_layer = [State()]

        for state in self.input_layer:
            self.connect_state_to_node(state, main_node)
        for state in self.output_layer:
            self.connect_node_to_state(main_node, state)
        
        hidden_layer.add_node(main_node)

        self.layers.append(hidden_layer)
        
        print("finish building")


    def train_network(self, iterations=0, cases=[]):
        while iterations > 0:
            inst = cases[random.randint(0, len(cases) - 1)]
            self.run_forward([inst[0], inst[1]])
            self.run_backward([inst[2]])
            iterations -= 1