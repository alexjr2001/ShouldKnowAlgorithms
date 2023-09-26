import numpy as np

class Cluster():
    def __init__(self,_pos,_points=np.empty((0,2), int)) -> None:
        self.pos=_pos
        self.group=_points 
        
