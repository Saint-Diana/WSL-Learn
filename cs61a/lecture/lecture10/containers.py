"""
# Lists
odds = [41, 43, 45, 47, 49]
print(odds[0])
print(odds[1])
print(odds[2])
print(odds[3])
print(odds[4])
print(len(odds))
print(odds[3] - odds[2])
print(odds[odds[3] - odds[2]])

print('-' * 30)
digits = [2//2, 2+2+2+2, 2, 2*2*2]
digits = [-1, -3] + digits * 2      # List * m 相当于m个List连接起来
                                    # ListA + ListB 相当于把两个List连接起来
for digit in digits:
    print(digit)
"""

def count(s, val):
    """Count the number of times that value of val in sequence s.
    
    s   - sequence
    val - the value to count
    """
    cnt = 0
    for digit in s:
        if digit == val:
            cnt += 1
    return cnt

def same_count(pairs):
    """Count the number of times that element of sequence pairs
    is a sequence with two elements which are same.
    
    pairs - sequence

    >>> same_count([[1, 2], [2, 2], [3, 3], [4, 5]])
    2

    >>> same_count([[2, 3], [4, 5], [6, 6]])
    1
    """
    cnt = 0
    for x, y in pairs: # Each name is bound to a value, as in multiple assignment
        if x == y:
            cnt += 1
    return cnt


# Ranges: a range is a sequence of consecutive integers.
def mysum(L):
    """Calculate the sum of the sequence L recursively.

    >>> mysum([2, 4, 1, 5])
    12
    """
    if L == []:
        return 0
    return L[0] + mysum(L[1:])

def sum_recursive(n):
    """
    >>> sum_recursive(5)
    15
    """
    if n == 0:
        return 0
    else:
        return n + sum_recursive(n - 1)

def divisors(n):
    return [1] + [x for x in range(2, n + 1) if n % x == 0]


# String
s = 'Good morning!\nI\'m glad to see you.'
s1 = """Good morning!
I'm glad to see you."""
s2 = r"Good morning!\nI\'m glad to see you."
print(s)
print(s1)
print(s2)

# Reversing a List(recursively)
# reverse('ward') == 'draw'
def reverse(s):
    if s == '':
        return ''
    else:
        return reverse(s[1:]) + s[0]

