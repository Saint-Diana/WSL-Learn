def make_withdraw(balance):
    def withdraw(amount):
        nonlocal balance
        if balance < amount:
            return 'Insuffcient funds'
        else:
            balance -= amount
            return balance
    return withdraw

def make_mutable_rlist():
    contents = empty_rlist
    def dispatch(message, value=None):
        nonlocal contents
        if message == 'len':
            return len_rlist(contents)
        elif message == 'getitem':
            return getitem_rlist(contents, value)
        elif message == 'push_first':
            contents = make_rlist(value, contents)
        elif message == 'pop_first':
            f = first(contents)
            contents = rest(contents)
            return f
        elif message == 'str':
            return str(contents)
    return dispatch

def to_mutable_rlist(source):
    """Return a functional list with the same contents as source."""
    s = make_mutable_rlist()
    for element in reversed(source):
        s('push_first', element)
    return s


# Dictionary
def make_dict():
    """return a functional implementation of a dictionary."""
    records = []
    def getitem(key):
        for k, v in records:
            if k == key:
                return v
    def setitem(key, value):
        for item in records:
            if item[0] == key:
                item[1] = value
                return
        records.append([key, value])
    def dispatch(message, key=None, value=None):
        if message == 'getitem':
            return getitem(key)
        elif message == 'setitem':
            setitem(key, value)
        elif message == 'keys':
            return [item[0] for item in records]
        elif message == 'values':
            return [item[1] for item in records]
    return dispatch