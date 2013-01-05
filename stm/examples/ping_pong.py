

from repeated_task import RepeatedTask

global PingPongMachine

from time import time

global PongMachine
global PingMachine


'''The PingPong machine contains the PingMachine and the PongMachine
'''

class StateMachine(RepeatedTask):
    class Status:
        (Playing, Suspended, Stopped) = range(0,3)

    def play(self):
        for submachine in self.submachines.values():
            submachine.play() 
        if self.status == self.Status.Stopped :
            print("Starting machine '" + self.name+"'")
            self.set_state("Initial")
            self.status = self.Status.Playing
            RepeatedTask.start(self)
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
        for submachine in self.submachines.values():
            submachine.stop() 
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


class PingPongMachineClass(StateMachine):

    def __init__(self, verbose=False):
        global PongMachine
        global PingMachine
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PingPongMachine"
        self.frequency = 1.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}
        PongMachine = PongMachineClass()
        self.submachines['PongMachine'] = PongMachine
        PingMachine = PingMachineClass()
        self.submachines['PingMachine'] = PingMachine

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        return self.state




'''The pong machine
'''



class PongMachineClass(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PongMachine"
        self.frequency = 5.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        if self.state == "Receive" :
            print(str(time() - PongMachine.begin))
        elif self.state == "Initial" :
            print('Starting pong machine')
            PongMachine.begin = time()

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Receive" :
            return "Send"
        elif self.state == "Initial" :
            return "Wait"
        elif self.state == "Send" :
            print("Pong ",end="")
            PingMachine.set_state("Receive")
            return "Wait"
        return self.state




'''The ping machine
'''



class PingMachineClass(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PingMachine"
        self.frequency = 10.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        if self.state == "Receive" :
            print(str(time() - PingMachine.begin) )
        elif self.state == "Initial" :
            print('Starting ping machine')
            self.begin = time()

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Receive" :
            return "Send"
        elif self.state == "Initial" :
            return "Send"
        elif self.state == "Send" :
            print("Ping ",end="")
            PongMachine.set_state("Receive")
            return "Wait"
        return self.state


if __name__ == '__main__':
    PingPongMachine = PingPongMachineClass()
    PingPongMachine.play()
