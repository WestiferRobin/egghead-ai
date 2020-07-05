from node import Node
from layer import Layer
from network import Network
from state import State
from pipe import Pipe
from math import exp, pow
import random

and_cases = [
    [1.0, 1.0, 1.0],
    [0.0, 0.0, 0.0],
    [1.0, 0.0, 0.0],
    [0.0, 1.0, 0.0]
]

or_cases = [
    [1.0, 1.0, 1.0],
    [0.0, 0.0, 0.0],
    [1.0, 0.0, 1.0],
    [0.0, 1.0, 1.0]
]

class NodeTron(Network):

    def __init__(self):
        Network.__init__(self)

    def build_network(self):
        main_node = Node(2)
        hidden_layer = Layer(learn_rate=self.learn_rate)
        
        state_x = State()
        state_y = State()
        state_o = State()
        
        self.connect_state_to_node(state_x, main_node)

        self.connect_state_to_node(state_y, main_node)

        self.connect_node_to_state(main_node, state_o)

        hidden_layer.add_node(main_node)

        self.input_layer = [state_x, state_y]

        self.add_layer(hidden_layer)

        self.output_layer = [state_o]

        print("finish building")


    def train_network(self, iterations=0, cases=[]):
        while iterations > 0:
            inst = cases[random.randint(0, 3)]
            self.run_forward([inst[0], inst[1]])
            self.run_backward([inst[2]])
            iterations -= 1


if __name__ == "__main__":
    targ_cases = or_cases
    the_network = NodeTron()
    the_network.build_network()
    the_network.train_network(10000, targ_cases)
    for case in targ_cases:
        ans = the_network.run_normal([case[0], case[1]], return_raw=True)[0]
        print(str(case) + ": " + str(ans))