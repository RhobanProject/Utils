

from repeated_task import RepeatedTask

from time import time
from random import randint
    
global TheDrunkSailorMachine


'''The drunk sailor starts 10 meters away from the cliffs on its left
If he reaches its house 20 meters on the right he is safe
If he reaches the cliffs he falls
'''

class TheDrunkSailorMachine(RepeatedTask):
    class Status:
        (Playing, Suspended, Stopped) = range(0,3)

    def play(self, threaded = True):
        if self.status == self.Status.Stopped :
            print("Starting machine '" + self.name+"'")
            globals()[self.name] = self
            self.set_state("Initial")
            self.status = self.Status.Playing
            if threaded : RepeatedTask.start(self)
        elif self.status == self.Status.Suspended :
            if self.debug : print("Resuming machine '"+ self.name+"'")
            self.status = self.Status.Playing
            
    def set_state(self, state):
        if state is not self.state:
            self.bye()
            self.state = state
            self.enter()
        self.state = state
        
    def stop(self, threaded = True):
        if self.debug : print("Stopping machine '"+ self.name+"'")
        self.status = self.Status.Stopped
        RepeatedTask.cancel(self)

    def step(self):
        try:
            if self.debug : print("Stepping machine '"+ self.name+"' with status " + str(self.status))
            if self.status == self.Status.Playing :
                self.loop()
                #print("Transition of machine " + self.name + " in state "+ str(self.state))
                self.set_state(self.transition())
                if self.state == "Final" :
                    if self.debug : print("Machine has reached its final state'"+ self.name+"'")
                    self.bye()
                    self.stop()
        except Exception as e:
            print("Exception in machine "+ self.name + ": "+ str(e))
            pass

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "TheDrunkSailorMachine"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False

    def enter(self):
        if self.state == "Initial" :
            print('Damned the pub is closed')
            self.position = 10
        elif self.state == "Safe" :
            print("Safe!")
        elif self.state == "Dead" :
            print("Oups...")

    def bye(self):
        pass
        

    def loop(self):
        if self.state == "Walk" :
            self.position = self.position + randint(-1,1)
            print("#Cliffs#" + self.position * " " + ":~)" + (20 - self.position) * " " + "#Home#")

    def transition(self):
        if self.state == "Initial" :
            return "Walk"
        elif self.state == "Safe" :
            return "Final"
        elif self.state == "Dead" :
            return "Final"
        elif self.state == "Walk" :
            if self.position >= 20:
                return "Safe"
            elif self.position <= 0:
                return "Dead"
        return self.state


if __name__ == '__main__':
    the_machine = TheDrunkSailorMachine()
    the_machine.play()
