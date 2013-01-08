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
from threading import Thread, Event, RLock

class RepeatedTask(Thread):
    """Call a function after every specified number of seconds:

    t = RepeatedTask(30.0, f)
    t.start()
    t.cancel() # stop the timer's action if it's still waiting
    """
    def __init__(self, interval, function):
        Thread.__init__(self)
        self.interval = interval
        self.function = function
        self.finished = Event()
        self.lock = RLock()

    def get_frequency(self):
        return 1.0 / self.interval

    def set_frequency(self, frequency):
        if frequency > 0.001 and frequency < 500 :
            self.interval = 1.0 / frequency

    frequency = property(get_frequency, set_frequency) 

    def cancel(self):
        """Stop the timer if it hasn't finished yet"""
        self.lock.acquire()
        self.finished.set()
        self.lock.release()

    def run(self):
        while not self.finished.is_set() :
            self.lock.acquire()
            self.function()
            self.lock.release()
            #print("Repeated timer waiting " + str(self.interval) + " at " + str(time()))
            self.finished.wait(self.interval)
        
    '''Waits for the machine to be stopped'''
    def wait_stopped(self):
        self.finished.wait()
        
 