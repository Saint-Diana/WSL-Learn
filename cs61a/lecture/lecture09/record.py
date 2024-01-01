"""Tree Recursion"""

from ucb import trace

def cascade(n):
    if n < 10:
        print(n)
    else:
        print(n)
        cascade(n // 10)
        print(n)

def inverse_cascade(n):
    """
    >>> inverse_cascade(1234)
    1
    12
    123
    1234
    123
    12
    1
    """
    upper_cascade(n)
    lowwer_cascade(n // 10)

def upper_cascade(n):
    if n < 10:
        print(n)
    else:
        upper_cascade(n // 10)
        print(n)

def lowwer_cascade(n):
    if n < 10:
        print(n)
    else:
        print(n)
        lowwer_cascade(n // 10)

@trace
def fibonacci(n):
    """Return nth fibonacci number"""
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibonacci(n - 2) + fibonacci(n - 1)

# @trace
def hanoi(n, a, b):
    """Move n disks from post a to b

    n - a positive integer represents the number of disks
    a - a positive integer belongs to [1, 3] represents the start position
    b - a positive integer belongs to [1, 3] represents the end position
    """
    if n == 1:
        move(n, a, b)                                           # only one disk, so we can move it from a to b immediately
    else:
        c = 6 - (a + b)
        hanoi(n - 1, a, c)                                      # move upper (n - 1) disks from a to c
        move(n, a, b)                                           # move the lowwerest disk from a to b
        hanoi(n - 1, c, b)                                      # move (n - 1) disks moved before from c to b

def move(n, a, b):
    """Do the real moving operation, move disk n from peg a to peg b
    
    n - disk number
    a - start peg number
    b - end peg number
    """
    print("move disk", n, "from peg", a, "to peg", b)

def count_partitions(n, m):
    """The number of partitions of a positive integer n, using parts up to size m, is the number
    of ways in which n can be expressed as the sum of positive integer parts up to m in
    increasing order.

    n - a positive integer n
    m - size m

    for example: count_partitions(6, 4)
    2 + 4 = 6
    1 + 1 + 4 = 6
    3 + 3 = 6
    1 + 2 + 3 = 6
    1 + 1 + 1 + 3 = 6
    2 + 2 + 2 = 6
    1 + 1 + 2 + 2 = 6
    1 + 1 + 1 + 1 + 2 = 6
    1 + 1 + 1 + 1 + 1 + 1 = 6

    There're two cases:
        1. with m. count_partitions(n - m, m) types.
        2. without m. count_partitions(n, m - 1) types.
    so count_partitions(n, m) = count_partitions(n - m, m) + count_partitions(n, m - 1)

    >>> count_partitions(6, 4)
    9
    """
    if n == 2:
        return 1
    else:
        return count_partitions(n - m, m) + count_partitions(n, m - 1)

