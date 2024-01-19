"""Objects"""
class Clown:
    nose = 'big and red'
    def dance():                # Notice: If the parameters don't have 'self', then the method is belong to the Class.
        return 'No thanks'      # When use object.method(), python will automatically transmit object as 'self' to the method.

class Account:
    interest = 0.02                         # A class attribute

    def __init__(self, account_holder):
        self.balance = 0                    # A object attribute 
        self.holder = account_holder        # A object attribute
    
    def deposit(self, amount):
        assert amount > 0, 'amount must be >= 0'
        self.balance += amount
        return self.balance
    
    def withdraw(self, amount):
        assert amount > 0, 'amount must be >= 0'
        if self.balance < amount:
            return 'Insufficient funds'
        self.balance -= amount
        return self.balance