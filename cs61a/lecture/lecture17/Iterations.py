"""Iterations"""

s = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
# map(func, iterable):              Iterate over func(x) for x in iterable
def f(x):
    if x < 3:
        return 'Small'
    elif x < 6:
        return 'Middle'
    else:
        return 'Big'

for i in map(f, s):
    print(i)

# filter(func, iterable):           Iterate over x in iterable if func(x)
def g(x):
    return x < 5

print('-' * 50)
for i in filter(g, s):
    print(i)

# zip(first_iter, second_iter):     Iterate over co-indexed (x, y) pairs
s1, s2 = ['Zero', 'One', 'Two', 'Three'], [0, 1, 2, 3]

print('-' * 50)
for pair in zip(s1, s2):
    print(pair)

print('-' * 25)
d = dict(zip(s1, s2))
print(d)

# reversed(sequence):               Iterate over x in a sequence in reverse order
print('-' * 50)
name = 'shenhuichang'
for i in reversed(name):
    print(i)

# list(iterable):                   Create a list containing all x in iterable
print('-' * 50)
name = 'shenhuichang'
l = list(iter(name))
print(l)

# tuple(iterable):                  Create a tuple containing all x in iterable
print('-' * 50)
d = {'a': 97, 'b': 98}
t = tuple(iter(d.items()))
print(t)

# sorted(iterable):                 Create a sorted list containing x in iterable
print('-' * 50)
name = 'shenhuichang'
sortedList = sorted(iter(name))
print(sortedList)

print('-' * 25)
print(''.join(sortedList))

# Generators and Generator Functions: we can use generator to create an iterable
def plus_minus(x):
    yield x
    yield -x

print('-' * 50)
for i in plus_minus(10):
    print(i)

def evens(start, end):
    even = start + (start % 2)
    while even < end:
        yield even
        even += 2

print('-' * 25)
print(list(evens(21, 35)))

print('-' * 25)
print(list(evens(20, 35)))


print('-' * 50)
def a_then_b(a, b):
    yield from a
    yield from b
print(list(a_then_b([1, 3, 5], [2, 4, 6])))


print('-' * 50)
def countdown(k):
    if k > 0:
        yield k
        yield from countdown(k - 1)
print(list(countdown(20)))