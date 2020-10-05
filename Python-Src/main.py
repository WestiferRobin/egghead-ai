from node_tron import NodeTron
from xor import XorTron

TRAIN_TIMES = 100000;

def run_node_tron(isAnd):
    cases = []
    if isAnd:
        cases = [
            [1.0, 1.0, 1.0],
            [0.0, 0.0, 0.0],
            [1.0, 0.0, 0.0],
            [0.0, 1.0, 0.0]
        ]
    else:
        cases = [
            [1.0, 1.0, 1.0],
            [0.0, 0.0, 0.0],
            [1.0, 0.0, 1.0],
            [0.0, 1.0, 1.0]
        ]
    model = NodeTron()
    model.build_network()
    model.train_network(TRAIN_TIMES, cases)
    for case in cases:
        ans = model.run_normal([case[0], case[1]])[0]
        print(str(case) + ": " + str(ans))

def run_xor():
    cases = [
        [1.0, 1.0, 0.0],
        [0.0, 1.0, 1.0],
        [0.0, 0.0, 0.0],
        [1.0, 0.0, 1.0]
    ]
    model = XorTron()
    model.build_network()
    model.train_network(TRAIN_TIMES, cases)
    for case in cases:
        ans = model.run_normal([case[0], case[1]])[0]
        print(str(case) + ": " + str(ans))



if __name__ == "__main__":
    for index in range(1, 4):
        if index == 1:
            print("Xor Model")
            run_xor()
        elif index == 2:
            print("Node Tron Model: And")
            run_node_tron(True)
        elif index == 3:
            print("Node Tron Model: Or")
            run_node_tron(False)