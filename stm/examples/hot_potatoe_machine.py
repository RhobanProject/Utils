

from repeated_task import RepeatedTask

from random import randint
global HotPotatoeMachine




































































































global PotatoeCatcher[11]
global PotatoeCatcher[34]
global PotatoeCatcher[50]
global PotatoeCatcher[58]
global PotatoeCatcher[22]
global PotatoeCatcher[42]
global PotatoeCatcher[2]
global PotatoeCatcher[19]
global PotatoeCatcher[75]
global PotatoeCatcher[94]
global PotatoeCatcher[61]
global PotatoeCatcher[86]
global PotatoeCatcher[43]
global PotatoeCatcher[10]
global PotatoeCatcher[18]
global PotatoeCatcher[33]
global PotatoeCatcher[23]
global PotatoeCatcher[3]
global PotatoeCatcher[87]
global PotatoeCatcher[100]
global PotatoeCatcher[74]
global PotatoeCatcher[97]
global PotatoeCatcher[62]
global PotatoeCatcher[17]
global PotatoeCatcher[36]
global PotatoeCatcher[9]
global PotatoeCatcher[28]
global PotatoeCatcher[76]
global PotatoeCatcher[88]
global PotatoeCatcher[20]
global PotatoeCatcher[44]
global PotatoeCatcher[68]
global PotatoeCatcher[92]
global PotatoeCatcher[67]
global PotatoeCatcher[80]
global PotatoeCatcher[57]
global PotatoeCatcher[69]
global PotatoeCatcher[16]
global PotatoeCatcher[35]
global PotatoeCatcher[51]
global PotatoeCatcher[29]
global PotatoeCatcher[59]
global PotatoeCatcher[89]
global PotatoeCatcher[21]
global PotatoeCatcher[45]
global PotatoeCatcher[95]
global PotatoeCatcher[60]
global PotatoeCatcher[81]
global PotatoeCatcher[1]
global PotatoeCatcher[56]
global PotatoeCatcher[26]
global PotatoeCatcher[78]
global PotatoeCatcher[46]
global PotatoeCatcher[98]
global PotatoeCatcher[15]
global PotatoeCatcher[30]
global PotatoeCatcher[90]
global PotatoeCatcher[6]
global PotatoeCatcher[39]
global PotatoeCatcher[82]
global PotatoeCatcher[55]
global PotatoeCatcher[71]
global PotatoeCatcher[49]
global PotatoeCatcher[8]
global PotatoeCatcher[27]
global PotatoeCatcher[77]
global PotatoeCatcher[47]
global PotatoeCatcher[14]
global PotatoeCatcher[37]
global PotatoeCatcher[93]
global PotatoeCatcher[7]
global PotatoeCatcher[66]
global PotatoeCatcher[38]
global PotatoeCatcher[83]
global PotatoeCatcher[54]
global PotatoeCatcher[70]
global PotatoeCatcher[40]
global PotatoeCatcher[64]
global PotatoeCatcher[13]
global PotatoeCatcher[32]
global PotatoeCatcher[24]
global PotatoeCatcher[84]
global PotatoeCatcher[4]
global PotatoeCatcher[53]
global PotatoeCatcher[73]
global PotatoeCatcher[96]
global PotatoeCatcher[63]
global PotatoeCatcher[25]
global PotatoeCatcher[79]
global PotatoeCatcher[41]
global PotatoeCatcher[65]
global PotatoeCatcher[12]
global PotatoeCatcher[99]
global PotatoeCatcher[31]
global PotatoeCatcher[85]
global PotatoeCatcher[5]
global PotatoeCatcher[52]
global PotatoeCatcher[72]
global PotatoeCatcher[48]
global PotatoeCatcher[91]


'''Contains 100 people playing hot potatoe'''

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


class HotPotatoeMachineClass(StateMachine):

    def __init__(self, verbose=False):
        global PotatoeCatcher[11]
        global PotatoeCatcher[34]
        global PotatoeCatcher[50]
        global PotatoeCatcher[58]
        global PotatoeCatcher[22]
        global PotatoeCatcher[42]
        global PotatoeCatcher[2]
        global PotatoeCatcher[19]
        global PotatoeCatcher[75]
        global PotatoeCatcher[94]
        global PotatoeCatcher[61]
        global PotatoeCatcher[86]
        global PotatoeCatcher[43]
        global PotatoeCatcher[10]
        global PotatoeCatcher[18]
        global PotatoeCatcher[33]
        global PotatoeCatcher[23]
        global PotatoeCatcher[3]
        global PotatoeCatcher[87]
        global PotatoeCatcher[100]
        global PotatoeCatcher[74]
        global PotatoeCatcher[97]
        global PotatoeCatcher[62]
        global PotatoeCatcher[17]
        global PotatoeCatcher[36]
        global PotatoeCatcher[9]
        global PotatoeCatcher[28]
        global PotatoeCatcher[76]
        global PotatoeCatcher[88]
        global PotatoeCatcher[20]
        global PotatoeCatcher[44]
        global PotatoeCatcher[68]
        global PotatoeCatcher[92]
        global PotatoeCatcher[67]
        global PotatoeCatcher[80]
        global PotatoeCatcher[57]
        global PotatoeCatcher[69]
        global PotatoeCatcher[16]
        global PotatoeCatcher[35]
        global PotatoeCatcher[51]
        global PotatoeCatcher[29]
        global PotatoeCatcher[59]
        global PotatoeCatcher[89]
        global PotatoeCatcher[21]
        global PotatoeCatcher[45]
        global PotatoeCatcher[95]
        global PotatoeCatcher[60]
        global PotatoeCatcher[81]
        global PotatoeCatcher[1]
        global PotatoeCatcher[56]
        global PotatoeCatcher[26]
        global PotatoeCatcher[78]
        global PotatoeCatcher[46]
        global PotatoeCatcher[98]
        global PotatoeCatcher[15]
        global PotatoeCatcher[30]
        global PotatoeCatcher[90]
        global PotatoeCatcher[6]
        global PotatoeCatcher[39]
        global PotatoeCatcher[82]
        global PotatoeCatcher[55]
        global PotatoeCatcher[71]
        global PotatoeCatcher[49]
        global PotatoeCatcher[8]
        global PotatoeCatcher[27]
        global PotatoeCatcher[77]
        global PotatoeCatcher[47]
        global PotatoeCatcher[14]
        global PotatoeCatcher[37]
        global PotatoeCatcher[93]
        global PotatoeCatcher[7]
        global PotatoeCatcher[66]
        global PotatoeCatcher[38]
        global PotatoeCatcher[83]
        global PotatoeCatcher[54]
        global PotatoeCatcher[70]
        global PotatoeCatcher[40]
        global PotatoeCatcher[64]
        global PotatoeCatcher[13]
        global PotatoeCatcher[32]
        global PotatoeCatcher[24]
        global PotatoeCatcher[84]
        global PotatoeCatcher[4]
        global PotatoeCatcher[53]
        global PotatoeCatcher[73]
        global PotatoeCatcher[96]
        global PotatoeCatcher[63]
        global PotatoeCatcher[25]
        global PotatoeCatcher[79]
        global PotatoeCatcher[41]
        global PotatoeCatcher[65]
        global PotatoeCatcher[12]
        global PotatoeCatcher[99]
        global PotatoeCatcher[31]
        global PotatoeCatcher[85]
        global PotatoeCatcher[5]
        global PotatoeCatcher[52]
        global PotatoeCatcher[72]
        global PotatoeCatcher[48]
        global PotatoeCatcher[91]
        RepeatedTask.__init__(self,1,self.step)
        self.name = "HotPotatoeMachine"
        self.frequency = 1.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}
        PotatoeCatcher[11] = PotatoeCatcher[11]Class()
        self.submachines['PotatoeCatcher[11]'] = PotatoeCatcher[11]
        PotatoeCatcher[34] = PotatoeCatcher[34]Class()
        self.submachines['PotatoeCatcher[34]'] = PotatoeCatcher[34]
        PotatoeCatcher[50] = PotatoeCatcher[50]Class()
        self.submachines['PotatoeCatcher[50]'] = PotatoeCatcher[50]
        PotatoeCatcher[58] = PotatoeCatcher[58]Class()
        self.submachines['PotatoeCatcher[58]'] = PotatoeCatcher[58]
        PotatoeCatcher[22] = PotatoeCatcher[22]Class()
        self.submachines['PotatoeCatcher[22]'] = PotatoeCatcher[22]
        PotatoeCatcher[42] = PotatoeCatcher[42]Class()
        self.submachines['PotatoeCatcher[42]'] = PotatoeCatcher[42]
        PotatoeCatcher[2] = PotatoeCatcher[2]Class()
        self.submachines['PotatoeCatcher[2]'] = PotatoeCatcher[2]
        PotatoeCatcher[19] = PotatoeCatcher[19]Class()
        self.submachines['PotatoeCatcher[19]'] = PotatoeCatcher[19]
        PotatoeCatcher[75] = PotatoeCatcher[75]Class()
        self.submachines['PotatoeCatcher[75]'] = PotatoeCatcher[75]
        PotatoeCatcher[94] = PotatoeCatcher[94]Class()
        self.submachines['PotatoeCatcher[94]'] = PotatoeCatcher[94]
        PotatoeCatcher[61] = PotatoeCatcher[61]Class()
        self.submachines['PotatoeCatcher[61]'] = PotatoeCatcher[61]
        PotatoeCatcher[86] = PotatoeCatcher[86]Class()
        self.submachines['PotatoeCatcher[86]'] = PotatoeCatcher[86]
        PotatoeCatcher[43] = PotatoeCatcher[43]Class()
        self.submachines['PotatoeCatcher[43]'] = PotatoeCatcher[43]
        PotatoeCatcher[10] = PotatoeCatcher[10]Class()
        self.submachines['PotatoeCatcher[10]'] = PotatoeCatcher[10]
        PotatoeCatcher[18] = PotatoeCatcher[18]Class()
        self.submachines['PotatoeCatcher[18]'] = PotatoeCatcher[18]
        PotatoeCatcher[33] = PotatoeCatcher[33]Class()
        self.submachines['PotatoeCatcher[33]'] = PotatoeCatcher[33]
        PotatoeCatcher[23] = PotatoeCatcher[23]Class()
        self.submachines['PotatoeCatcher[23]'] = PotatoeCatcher[23]
        PotatoeCatcher[3] = PotatoeCatcher[3]Class()
        self.submachines['PotatoeCatcher[3]'] = PotatoeCatcher[3]
        PotatoeCatcher[87] = PotatoeCatcher[87]Class()
        self.submachines['PotatoeCatcher[87]'] = PotatoeCatcher[87]
        PotatoeCatcher[100] = PotatoeCatcher[100]Class()
        self.submachines['PotatoeCatcher[100]'] = PotatoeCatcher[100]
        PotatoeCatcher[74] = PotatoeCatcher[74]Class()
        self.submachines['PotatoeCatcher[74]'] = PotatoeCatcher[74]
        PotatoeCatcher[97] = PotatoeCatcher[97]Class()
        self.submachines['PotatoeCatcher[97]'] = PotatoeCatcher[97]
        PotatoeCatcher[62] = PotatoeCatcher[62]Class()
        self.submachines['PotatoeCatcher[62]'] = PotatoeCatcher[62]
        PotatoeCatcher[17] = PotatoeCatcher[17]Class()
        self.submachines['PotatoeCatcher[17]'] = PotatoeCatcher[17]
        PotatoeCatcher[36] = PotatoeCatcher[36]Class()
        self.submachines['PotatoeCatcher[36]'] = PotatoeCatcher[36]
        PotatoeCatcher[9] = PotatoeCatcher[9]Class()
        self.submachines['PotatoeCatcher[9]'] = PotatoeCatcher[9]
        PotatoeCatcher[28] = PotatoeCatcher[28]Class()
        self.submachines['PotatoeCatcher[28]'] = PotatoeCatcher[28]
        PotatoeCatcher[76] = PotatoeCatcher[76]Class()
        self.submachines['PotatoeCatcher[76]'] = PotatoeCatcher[76]
        PotatoeCatcher[88] = PotatoeCatcher[88]Class()
        self.submachines['PotatoeCatcher[88]'] = PotatoeCatcher[88]
        PotatoeCatcher[20] = PotatoeCatcher[20]Class()
        self.submachines['PotatoeCatcher[20]'] = PotatoeCatcher[20]
        PotatoeCatcher[44] = PotatoeCatcher[44]Class()
        self.submachines['PotatoeCatcher[44]'] = PotatoeCatcher[44]
        PotatoeCatcher[68] = PotatoeCatcher[68]Class()
        self.submachines['PotatoeCatcher[68]'] = PotatoeCatcher[68]
        PotatoeCatcher[92] = PotatoeCatcher[92]Class()
        self.submachines['PotatoeCatcher[92]'] = PotatoeCatcher[92]
        PotatoeCatcher[67] = PotatoeCatcher[67]Class()
        self.submachines['PotatoeCatcher[67]'] = PotatoeCatcher[67]
        PotatoeCatcher[80] = PotatoeCatcher[80]Class()
        self.submachines['PotatoeCatcher[80]'] = PotatoeCatcher[80]
        PotatoeCatcher[57] = PotatoeCatcher[57]Class()
        self.submachines['PotatoeCatcher[57]'] = PotatoeCatcher[57]
        PotatoeCatcher[69] = PotatoeCatcher[69]Class()
        self.submachines['PotatoeCatcher[69]'] = PotatoeCatcher[69]
        PotatoeCatcher[16] = PotatoeCatcher[16]Class()
        self.submachines['PotatoeCatcher[16]'] = PotatoeCatcher[16]
        PotatoeCatcher[35] = PotatoeCatcher[35]Class()
        self.submachines['PotatoeCatcher[35]'] = PotatoeCatcher[35]
        PotatoeCatcher[51] = PotatoeCatcher[51]Class()
        self.submachines['PotatoeCatcher[51]'] = PotatoeCatcher[51]
        PotatoeCatcher[29] = PotatoeCatcher[29]Class()
        self.submachines['PotatoeCatcher[29]'] = PotatoeCatcher[29]
        PotatoeCatcher[59] = PotatoeCatcher[59]Class()
        self.submachines['PotatoeCatcher[59]'] = PotatoeCatcher[59]
        PotatoeCatcher[89] = PotatoeCatcher[89]Class()
        self.submachines['PotatoeCatcher[89]'] = PotatoeCatcher[89]
        PotatoeCatcher[21] = PotatoeCatcher[21]Class()
        self.submachines['PotatoeCatcher[21]'] = PotatoeCatcher[21]
        PotatoeCatcher[45] = PotatoeCatcher[45]Class()
        self.submachines['PotatoeCatcher[45]'] = PotatoeCatcher[45]
        PotatoeCatcher[95] = PotatoeCatcher[95]Class()
        self.submachines['PotatoeCatcher[95]'] = PotatoeCatcher[95]
        PotatoeCatcher[60] = PotatoeCatcher[60]Class()
        self.submachines['PotatoeCatcher[60]'] = PotatoeCatcher[60]
        PotatoeCatcher[81] = PotatoeCatcher[81]Class()
        self.submachines['PotatoeCatcher[81]'] = PotatoeCatcher[81]
        PotatoeCatcher[1] = PotatoeCatcher[1]Class()
        self.submachines['PotatoeCatcher[1]'] = PotatoeCatcher[1]
        PotatoeCatcher[56] = PotatoeCatcher[56]Class()
        self.submachines['PotatoeCatcher[56]'] = PotatoeCatcher[56]
        PotatoeCatcher[26] = PotatoeCatcher[26]Class()
        self.submachines['PotatoeCatcher[26]'] = PotatoeCatcher[26]
        PotatoeCatcher[78] = PotatoeCatcher[78]Class()
        self.submachines['PotatoeCatcher[78]'] = PotatoeCatcher[78]
        PotatoeCatcher[46] = PotatoeCatcher[46]Class()
        self.submachines['PotatoeCatcher[46]'] = PotatoeCatcher[46]
        PotatoeCatcher[98] = PotatoeCatcher[98]Class()
        self.submachines['PotatoeCatcher[98]'] = PotatoeCatcher[98]
        PotatoeCatcher[15] = PotatoeCatcher[15]Class()
        self.submachines['PotatoeCatcher[15]'] = PotatoeCatcher[15]
        PotatoeCatcher[30] = PotatoeCatcher[30]Class()
        self.submachines['PotatoeCatcher[30]'] = PotatoeCatcher[30]
        PotatoeCatcher[90] = PotatoeCatcher[90]Class()
        self.submachines['PotatoeCatcher[90]'] = PotatoeCatcher[90]
        PotatoeCatcher[6] = PotatoeCatcher[6]Class()
        self.submachines['PotatoeCatcher[6]'] = PotatoeCatcher[6]
        PotatoeCatcher[39] = PotatoeCatcher[39]Class()
        self.submachines['PotatoeCatcher[39]'] = PotatoeCatcher[39]
        PotatoeCatcher[82] = PotatoeCatcher[82]Class()
        self.submachines['PotatoeCatcher[82]'] = PotatoeCatcher[82]
        PotatoeCatcher[55] = PotatoeCatcher[55]Class()
        self.submachines['PotatoeCatcher[55]'] = PotatoeCatcher[55]
        PotatoeCatcher[71] = PotatoeCatcher[71]Class()
        self.submachines['PotatoeCatcher[71]'] = PotatoeCatcher[71]
        PotatoeCatcher[49] = PotatoeCatcher[49]Class()
        self.submachines['PotatoeCatcher[49]'] = PotatoeCatcher[49]
        PotatoeCatcher[8] = PotatoeCatcher[8]Class()
        self.submachines['PotatoeCatcher[8]'] = PotatoeCatcher[8]
        PotatoeCatcher[27] = PotatoeCatcher[27]Class()
        self.submachines['PotatoeCatcher[27]'] = PotatoeCatcher[27]
        PotatoeCatcher[77] = PotatoeCatcher[77]Class()
        self.submachines['PotatoeCatcher[77]'] = PotatoeCatcher[77]
        PotatoeCatcher[47] = PotatoeCatcher[47]Class()
        self.submachines['PotatoeCatcher[47]'] = PotatoeCatcher[47]
        PotatoeCatcher[14] = PotatoeCatcher[14]Class()
        self.submachines['PotatoeCatcher[14]'] = PotatoeCatcher[14]
        PotatoeCatcher[37] = PotatoeCatcher[37]Class()
        self.submachines['PotatoeCatcher[37]'] = PotatoeCatcher[37]
        PotatoeCatcher[93] = PotatoeCatcher[93]Class()
        self.submachines['PotatoeCatcher[93]'] = PotatoeCatcher[93]
        PotatoeCatcher[7] = PotatoeCatcher[7]Class()
        self.submachines['PotatoeCatcher[7]'] = PotatoeCatcher[7]
        PotatoeCatcher[66] = PotatoeCatcher[66]Class()
        self.submachines['PotatoeCatcher[66]'] = PotatoeCatcher[66]
        PotatoeCatcher[38] = PotatoeCatcher[38]Class()
        self.submachines['PotatoeCatcher[38]'] = PotatoeCatcher[38]
        PotatoeCatcher[83] = PotatoeCatcher[83]Class()
        self.submachines['PotatoeCatcher[83]'] = PotatoeCatcher[83]
        PotatoeCatcher[54] = PotatoeCatcher[54]Class()
        self.submachines['PotatoeCatcher[54]'] = PotatoeCatcher[54]
        PotatoeCatcher[70] = PotatoeCatcher[70]Class()
        self.submachines['PotatoeCatcher[70]'] = PotatoeCatcher[70]
        PotatoeCatcher[40] = PotatoeCatcher[40]Class()
        self.submachines['PotatoeCatcher[40]'] = PotatoeCatcher[40]
        PotatoeCatcher[64] = PotatoeCatcher[64]Class()
        self.submachines['PotatoeCatcher[64]'] = PotatoeCatcher[64]
        PotatoeCatcher[13] = PotatoeCatcher[13]Class()
        self.submachines['PotatoeCatcher[13]'] = PotatoeCatcher[13]
        PotatoeCatcher[32] = PotatoeCatcher[32]Class()
        self.submachines['PotatoeCatcher[32]'] = PotatoeCatcher[32]
        PotatoeCatcher[24] = PotatoeCatcher[24]Class()
        self.submachines['PotatoeCatcher[24]'] = PotatoeCatcher[24]
        PotatoeCatcher[84] = PotatoeCatcher[84]Class()
        self.submachines['PotatoeCatcher[84]'] = PotatoeCatcher[84]
        PotatoeCatcher[4] = PotatoeCatcher[4]Class()
        self.submachines['PotatoeCatcher[4]'] = PotatoeCatcher[4]
        PotatoeCatcher[53] = PotatoeCatcher[53]Class()
        self.submachines['PotatoeCatcher[53]'] = PotatoeCatcher[53]
        PotatoeCatcher[73] = PotatoeCatcher[73]Class()
        self.submachines['PotatoeCatcher[73]'] = PotatoeCatcher[73]
        PotatoeCatcher[96] = PotatoeCatcher[96]Class()
        self.submachines['PotatoeCatcher[96]'] = PotatoeCatcher[96]
        PotatoeCatcher[63] = PotatoeCatcher[63]Class()
        self.submachines['PotatoeCatcher[63]'] = PotatoeCatcher[63]
        PotatoeCatcher[25] = PotatoeCatcher[25]Class()
        self.submachines['PotatoeCatcher[25]'] = PotatoeCatcher[25]
        PotatoeCatcher[79] = PotatoeCatcher[79]Class()
        self.submachines['PotatoeCatcher[79]'] = PotatoeCatcher[79]
        PotatoeCatcher[41] = PotatoeCatcher[41]Class()
        self.submachines['PotatoeCatcher[41]'] = PotatoeCatcher[41]
        PotatoeCatcher[65] = PotatoeCatcher[65]Class()
        self.submachines['PotatoeCatcher[65]'] = PotatoeCatcher[65]
        PotatoeCatcher[12] = PotatoeCatcher[12]Class()
        self.submachines['PotatoeCatcher[12]'] = PotatoeCatcher[12]
        PotatoeCatcher[99] = PotatoeCatcher[99]Class()
        self.submachines['PotatoeCatcher[99]'] = PotatoeCatcher[99]
        PotatoeCatcher[31] = PotatoeCatcher[31]Class()
        self.submachines['PotatoeCatcher[31]'] = PotatoeCatcher[31]
        PotatoeCatcher[85] = PotatoeCatcher[85]Class()
        self.submachines['PotatoeCatcher[85]'] = PotatoeCatcher[85]
        PotatoeCatcher[5] = PotatoeCatcher[5]Class()
        self.submachines['PotatoeCatcher[5]'] = PotatoeCatcher[5]
        PotatoeCatcher[52] = PotatoeCatcher[52]Class()
        self.submachines['PotatoeCatcher[52]'] = PotatoeCatcher[52]
        PotatoeCatcher[72] = PotatoeCatcher[72]Class()
        self.submachines['PotatoeCatcher[72]'] = PotatoeCatcher[72]
        PotatoeCatcher[48] = PotatoeCatcher[48]Class()
        self.submachines['PotatoeCatcher[48]'] = PotatoeCatcher[48]
        PotatoeCatcher[91] = PotatoeCatcher[91]Class()
        self.submachines['PotatoeCatcher[91]'] = PotatoeCatcher[91]

    def enter(self):
        if self.state == "Initial" :
            print("HotPotatoeMachine says \"A potatoe catcher shall not give the potatoe to itself\"")
            PotatoeCatcher[1].set_state("Potatoe")

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "KillAll" :
            print("Boum!!")
            for i in range(1,101):
                PotatoeCatcher[i].set_state("Final")
            return "Final"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[11]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[11]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[34]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[34]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[50]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[50]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[58]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[58]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[22]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[22]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[42]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[42]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[2]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[2]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[19]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[19]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[75]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[75]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[94]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[94]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[61]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[61]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[86]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[86]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[43]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[43]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[10]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[10]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[18]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[18]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[33]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[33]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[23]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[23]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[3]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[3]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[87]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[87]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[100]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[100]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[74]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[74]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[97]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[97]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[62]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[62]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[17]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[17]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[36]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[36]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[9]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[9]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[28]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[28]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[76]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[76]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[88]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[88]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[20]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[20]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[44]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[44]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[68]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[68]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[92]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[92]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[67]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[67]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[80]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[80]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[57]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[57]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[69]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[69]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[16]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[16]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[35]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[35]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[51]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[51]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[29]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[29]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[59]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[59]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[89]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[89]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[21]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[21]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[45]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[45]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[95]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[95]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[60]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[60]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[81]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[81]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[1]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[1]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[56]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[56]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[26]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[26]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[78]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[78]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[46]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[46]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[98]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[98]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[15]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[15]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[30]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[30]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[90]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[90]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[6]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[6]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[39]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[39]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[82]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[82]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[55]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[55]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[71]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[71]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[49]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[49]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[8]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[8]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[27]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[27]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[77]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[77]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[47]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[47]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[14]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[14]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[37]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[37]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[93]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[93]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[7]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[7]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[66]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[66]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[38]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[38]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[83]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[83]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[54]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[54]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[70]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[70]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[40]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[40]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[64]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[64]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[13]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[13]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[32]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[32]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[24]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[24]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[84]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[84]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[4]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[4]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[53]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[53]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[73]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[73]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[96]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[96]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[63]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[63]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[25]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[25]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[79]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[79]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[41]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[41]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[65]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[65]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[12]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[12]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[99]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[99]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[31]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[31]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[85]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[85]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[5]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[5]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[52]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[52]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[72]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[72]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[48]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[48]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state




'''A potatoe catcher chooses randomly another potatoe catcher to give the potatoe to
'''



class PotatoeCatcher[91]Class(StateMachine):

    def __init__(self, verbose=False):
        RepeatedTask.__init__(self,1,self.step)
        self.name = "PotatoeCatcher[91]"
        self.frequency = 20.0
        self.status = self.Status.Stopped 
        self.state = None
        self.debug = False
        self.submachines = {}

    def enter(self):
        pass

    def bye(self):
        pass

    def loop(self):
        pass

    def transition(self):
        if self.state == "Potatoe" :
            index = randint(1,100)
            print(self.name + " giving potatoe to " + PotatoeCatcher[index].name)
            if index != self.index:
                PotatoeCatcher[index].set_state("Potatoe")
            else:
                print("Oh no!")
                HotPotatoeMachine.set_state("KillAll")
            return "Initial"
        return self.state


if __name__ == '__main__':
    HotPotatoeMachine = HotPotatoeMachineClass()
    HotPotatoeMachine.play()
