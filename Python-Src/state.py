class State():

    def __init__(self):
        self.state_value = 0.0
        self.pipe_line = None
    
    def load_value(self, value):
        self.state_value = value

    def add_pipeline(self, pipeline):
        self.pipe_line = pipeline