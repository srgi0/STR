import numpy as np

class System:
    def __init__(self, *tasks):
        self.tasks = tasks
        self.n_tasks = len(self.tasks)
        self.tasks_matrix = np.array(self.tasks)
        self.tasks_names = []
        for i in range(self.n_tasks):
            self.tasks_names.append(f'T{i+1}')
        self.tasks_Pi = self.tasks_matrix[:,0]
        self.tasks_Di = self.tasks_matrix[:,1]
        self.tasks_Ci = self.tasks_matrix[:,2]

    def print_tasks (self):
        task_number = 0
        for task in self.tasks:
            task_number += 1
            print(f'Task {task_number}: (P{task_number}, D{task_number}, C{task_number}) = {task}')


class CyclicExecutive:
    def __init__(self, system):
        self.system = system
        self.major_cycle = 0
        self.minor_cycle = 0
        self.minor_cycle_selected = 0
        self.time_line_division = []
        self.time_line_tasks = []
        self.n_minor_cycle = 0
        self.time_line_tasks = 0
        self.time_line_tasks_priority = []

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

    def select_minor_cycle (self):
        if self.minor_cycle.size > 1:
            print(f'Select Minor Cycle: {self.minor_cycle}')
            self.minor_cycle_selected = int(input(f'Minor Cycle = '))

    def make_time_line (self):
        self.n_minor_cycle = int(self.major_cycle/self.minor_cycle_selected)
        self.time_line_division = np.ones(shape=(self.n_minor_cycle, self.minor_cycle_selected), dtype=str).tolist()
        
        self.time_line_tasks_priority = []
        for i in range(self.system.n_tasks):
            self.time_line_tasks_priority.append(self.system.tasks_names[np.argsort(self.system.tasks_Pi)[i]])
        


        self.time_line = (np.array(self.time_line_division).flatten()).tolist()

        for task in range(self.system.n_tasks):
            t = task
            while (t < self.major_cycle):
                if (self.time_line[t] == '1'):
                    self.time_line[t] = self.system.tasks_names[task]
                else:
                    self.time_line[t] = f'conflict: {self.system.tasks_names[task]} in {self.time_line[t]}'
                t += self.system.tasks_Pi[task]

        self.time_line = np.reshape(self.time_line, (self.n_minor_cycle,self.minor_cycle_selected))
        self.time_line = self.time_line.tolist()

if __name__ == '__main__':
    system = System((4,4,1), (5,5,1), (10,10,2))
    system.print_tasks()
    print(system.tasks_names)
    print(np.argsort(system.tasks_Pi))


    cyclic_executive = CyclicExecutive(system)
    cyclic_executive.create()
    print(f'Ciclo Maior é {cyclic_executive.major_cycle}')
    print(f'Opções para Ciclo Menor: {cyclic_executive.minor_cycle}')
    cyclic_executive.select_minor_cycle()
    cyclic_executive.make_time_line()
    print(cyclic_executive.time_line_division)
    print(cyclic_executive.time_line_tasks_priority)
    print(cyclic_executive.time_line)