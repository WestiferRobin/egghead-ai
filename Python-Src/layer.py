from node import Node

class Layer:

    def __init__(self, learn_rate, name=""):
        self.learn_rate = learn_rate
        self.name = name
        self.nodes = []

    def forward(self):
        for node in self.nodes:
            node.calculate()

    def backward(self):
        for node in self.nodes:
            node.derive(self.learn_rate)

    def add_node(self, node):
        self.nodes.append(node)

    def to_string(self):
        return self.name