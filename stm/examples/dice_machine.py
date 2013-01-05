

from repeated_task import RepeatedTask

from random import randint

def throw_dice():
    print('Throwing dice')
    TheDiceMachine.dice = randint(1,6)
    TheDiceMachine.tries += 1
    print('Dice is ', TheDiceMachine.dice)

    
global TheDiceMachine


'''Simulates a game where we throw a dice and win iff we make a six in less than
n tries
    
'''

class TheDiceMachine(RepeatedTask):
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
        self.name = "TheDiceMachine"
        self.frequency = 50.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False

    def enter(self):
        if self.state == "Initial" :
            TheDiceMachine.tries = 0
            TheDiceMachine.dice = 0

    def bye(self):
        if self.state == "Lost" :
            print("Game Over")

    def loop(self):
        if self.state == "Initial" :
            throw_dice()
        elif self.state == "Final" :
            print('Over, dice is ', TheDiceMachine.dice)
        elif self.state == "Lost" :
            print("You've lost")

    def transition(self):
        if self.state == "Initial" :
            if TheDiceMachine.dice==6:
                return "Won"
            elif TheDiceMachine.tries>5:
                TheDiceMachine.tries=0
                return "Lost"
        elif self.state == "Won" :
            print("You've won an extra game!")
            return "Initial"
        elif self.state == "Lost" :
            return "Final"
        return self.state


if __name__ == '__main__':
    the_machine = TheDiceMachine()
    the_machine.play()
