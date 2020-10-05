from node import Node
from layer import Layer
from network import Network
from state import State
from pipe import Pipe
from math import exp, pow
import random

class XorTron(Network):
    
    def __init__(self):
        Network.__init__(self, learn_rate=0.1)

    def build_network(self):
        print("Starting to build XOR Model")
        self.input_layer = [State(), State()]
        self.output_layer = [State()]
        
        hidden_layer1 = Layer(learn_rate=self.learn_rate, name='layer1')
        node_list1 = [Node(2, name="n11"), Node(2, name="n21")]

        hidden_layer2 = Layer(learn_rate=self.learn_rate, name='layer2')
        node_list2 = [Node(2, name="n12")]

        for il in self.input_layer:
            for nd in node_list1:
                self.connect_state_to_node(il, nd)

        for n1 in node_list1:
            for n2 in node_list2:
                self.connect_pipeline(n1, n2)

        self.connect_node_to_state(node_list2[0], self.output_layer[0])

        for nd in node_list1:
            hidden_layer1.add_node(nd)

        for nd in node_list2:
            hidden_layer2.add_node(nd)

        self.add_layer(hidden_layer1)
        self.add_layer(hidden_layer2)

        print("finish building")

    def train_network(self, iterations=0, cases=[]):
        print("training network")
        if (cases == []):
            print("training did not have any cases.")
            return
        while iterations > 0:
            inst = cases[random.randint(0, len(cases)-1)]
            self.run_forward([inst[0], inst[1]])
            self.run_backward([inst[2]])
            iterations -= 1