"""Functions that simulate dice rolls. 模拟掷骰子的过程

A dice function takes no arguments and returns a number from 1 to n
(inclusive), where n is the number of sides on the dice.

Types of dice:

 -  Dice can be fair, meaning that they produce each possible outcome with equal
    probability. Examples: four_sided, six_sided

 -  For testing functions that use dice, deterministic test dice always cycle
    through a fixed sequence of values that are passed as arguments to the
    make_test_dice function.
"""

from random import randint

def make_fair_dice(sides): # example: make_fair_dice(6)() will return a randint between 1 and 6
    """Return a die that returns 1 to SIDES with equal chance."""
    assert type(sides) == int and sides >= 1, 'Illegal value for sides' # check the formal parameter
    def dice():
        return randint(1,sides)
    return dice

four_sided = make_fair_dice(4) # four_sided() will return a randint between 1 and 4
six_sided = make_fair_dice(6) # six_sided() will return a randint between 1 and 6

def make_test_dice(*outcomes): # the formal parameter 'output' is a tuple beacause there's a '*' before it. for example: make_test_dice(1, 2, 3)() will rerurn 1
    """Return a die that cycles deterministically through OUTCOMES.

    >>> dice = make_test_dice(1, 2, 3)
    >>> dice()
    1
    >>> dice()
    2
    >>> dice()
    3
    >>> dice()
    1
    >>> dice()
    2

    This function uses Python syntax/techniques not yet covered in this course.
    The best way to understand it is by reading the documentation and examples.
    """
    assert len(outcomes) > 0, 'You must supply outcomes to make_test_dice' # make sure the outcomes is not empty
    for o in outcomes:
        assert type(o) == int and o >= 1, 'Outcome is not a positive integer' # make sure the formal parameters you input are int and >= 1
    # after check the input
    index = len(outcomes) - 1 # reverse traversal. index = 3 - 1 = 2
    def dice():
        nonlocal index # index = 2
        index = (index + 1) % len(outcomes) # index = 3 % 3 = 0 => next time index = 1 % 3 = 1 => next time index = 2 % 3 = 2 => next time index = 3 % 3 = 0. So that's a cycle.
        return outcomes[index] # return outcomes[0] = 1 => next time return outcomes[1] = 2 => next time return outcomes[2] = 3.
    return dice