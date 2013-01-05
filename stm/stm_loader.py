'''
/*************************************************
* Publicly released by Rhoban System, September 2012
* www.rhoban-system.fr
*
* Freely usable for non-commercial purposes
*
* Licence Creative Commons *CC BY-NC-SA
* http://creativecommons.org/licenses/by-nc-sa/3.0
*************************************************/
'''
from repeated_task import RepeatedTask
from time import time

'''A loader for state machines, check stm.py for documentation'''

class StateMachineLoader(RepeatedTask):

    class ScheduledMachine():
        def __init__(self, machine):
            self.machine = machine
            self.max_counter = 1
            self.counter = 0
            self.begin = time()                
                
        def get_interval(self):
            return self.machine.interval

        interval = property(get_interval) 


    def __init__(self):
        RepeatedTask.__init__(self,0.1,self.step)
        self.machines = []
        RepeatedTask.start(self)

    ''' Load a machine or a list of machines,
     with an optional maximum duration
     and optionally waiting for the machine to stop
     and optionally waiting for the machine to be started stopped'''
    def load(self, machine, wait_stop = False, duration = float("inf"), start_stopped = False):
        self.lock.acquire()
        print("Loading machine "+ machine.name)
        if machine.status is not machine.Status.Stopped :
            raise BaseException("Cannot load a running machine")
        for submachine in machine.submachines.values() :
            self.load(submachine, False, duration, True)
        self.machines.append( StateMachineLoader.ScheduledMachine(machine) )
        self.update_frequencies()
        self.lock.release()
        if not start_stopped:
            machine.play(wait_stop, duration, False)
   
    def update_frequencies(self):
        self.lock.acquire()
        self.interval = 0.1
        for machine in self.machines:
            self.interval = min(self.interval, machine.interval)
        for machine in self.machines:
            machine.counter = 0
            machine.max_counter =  int(round(machine.interval / self.interval))
        self.lock.release()
    
    def step(self):
        for machine in self.machines:
            machine.counter = machine.counter + 1
            if machine.counter >= machine.max_counter :
                machine.counter = 0
                machine.machine.step()
                
