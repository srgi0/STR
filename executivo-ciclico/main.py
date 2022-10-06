import numpy as np

class System:
    def __init__(self, *tasks):
        self.tasks = tasks
        self.n_tasks = len(self.tasks)
        # a partir daqui tudo np.ndarray
        self.tasks_matrix = np.array(self.tasks)
        self.tasks_Pi = self.tasks_matrix[:,0]
        self.tasks_Di = self.tasks_matrix[:,1]
        self.tasks_Ci = self.tasks_matrix[:,2]

    def print_tasks (self):
        task_number = 0
        for task in self.tasks:
            task_number += 1
            print(f'Task {task_number}: (P{task_number}, D{task_number}, C{task_number}) = {task}')


class CyclicExecutive (System):
    def __init__(self, system):
        self.system = system
        self.major_cycle = 0
        self.minor_cycle = 0

    def calc_major_cycle_mmc (self):
        return np.lcm.reduce(self.system.tasks_Pi)

    def calc_minor_cycle_mdc (self):
        return np.gcd.reduce(self.system.tasks_Pi)

    def premise_1 (self):
        self.minor_cycle = np.arange(self.minor_cycle, self.major_cycle)

        copy = self.minor_cycle.copy()
        self.minor_cycle = []
        for CM in copy:
            if np.max(self.system.tasks_Ci) <= CM < self.major_cycle:
                self.minor_cycle.append(CM)
        
    def premise_2 (self):
        copy = self.minor_cycle.copy()
        self.minor_cycle = []
        for CM in copy:
            if self.major_cycle%CM == 0:
                self.minor_cycle.append(CM)
    
    def premise_3 (self):
        copy = self.minor_cycle.copy()
        self.minor_cycle = []
        for CM in copy:
            if CM <= np.min(self.system.tasks_Di):
                self.minor_cycle.append(CM)

    def premise_4 (self):
        copy = self.minor_cycle.copy()
        self.minor_cycle = []
        for CM in copy:
            for i in range(self.system.n_tasks):
                if 2*CM - np.gcd(self.system.tasks_Pi[i], CM) <= self.system.tasks_Di[i] :
                    self.minor_cycle.append(CM)
        self.minor_cycle = np.unique(self.minor_cycle)
                

    def create (self):
        self.major_cycle = self.calc_major_cycle_mmc()
        self.minor_cycle = self.calc_minor_cycle_mdc()
        self.premise_1()
        self.premise_2()
        self.premise_3()
        self.premise_4()

        


if __name__ == '__main__':
    system = System((4,4,1), (5,5,1), (10,10,2))
    system.print_tasks()
    cyclic_executive = CyclicExecutive(system)
    cyclic_executive.create()
    print(f'Ciclo Maior é {cyclic_executive.major_cycle}')
    print(f'Opções para Ciclo Menor: {cyclic_executive.minor_cycle}')