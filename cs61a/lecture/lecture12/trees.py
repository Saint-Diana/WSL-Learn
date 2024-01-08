# Tree Data Structure

"""
Recursive description

A tree has a root label and a list of branches
Each branch is also a tree
a tree with zero branch is called a leaf

Relative description

Each location in a tree is called a node
Each node has a label that can be any value
One node can be the parent/child of another
"""

"""
Tree below:
                    3
            1               2
                        1       1

a root and a list of trees ==> tree(root, [trees])

tree(3, [tree(1, []), tree(2, [tree(1, []), tree(1, [])])])
"""
def tree(label, branches=[]):
    for branch in branches:
        assert is_tree(branch)
    return [label] + list(branches) # if branches is a list, then list() will not effect.

def label(t):
    return t[0]

def branches(t):
    return t[1:]

def is_tree(t):
    if type(t) != list or len(t) < 1:
        return False
    for branch in branches(t):
        if not is_tree(branch):
            return False
    return True

def is_leaf(t):
    # if a tree has zero branch, then it is a leaf
        return is_tree(t) and len(branches(t)) == 0

def fib_tree(n):
    if n <= 1:
        return tree(n)
    else:
        front, current, i = tree(0), tree(1), 1
        while i < n:
            front, current, i = current, tree(label(front) + label(current), [current, front]), i + 1
        return current

def fib_tree_recursive(n):
    if n <= 1:
        return tree(n)
    else:
        left, right = fib_tree(n - 1), fib_tree(n - 2)
        return tree(label(left) + label(right), [left, right])

def count_leaves(t):
    if is_leaf(t):
        return 1
    else:
        total = 0
        for branch in branches(t):
            total += count_leaves(branch)
        return total


# we can get an expression: count_leaves(fib_tree(n)) == root(fib_tree(n+1))[0]

def leaves(t):
    """return a list containing the leaf labels of tree"""
    if is_leaf(t):
        return [label(t)] # for example, tree == [1], then return [1]
    else:
        total = []
        for branch in branches(t):
            total.append(leaves(branch))
        # for example, total == [[1], [3], [5]]
        # we need to transfer [[1], [3], [5]] to [1, 3, 5]
        return sum(total, [])

def increment_leaves(t):
    """return a tree like t but with leaf labels incremented"""
    if is_leaf(t):
        return tree(label(t) + 1)
    else:
        bs = [increment_leaves(branch) for branch in branches(t)]
        return tree(label(t), bs)

def increment(t):
    """return a tree like t but with all labels incremented"""
    if is_leaf(t):
        return tree(label(t) + 1)
    else:
        bs = [increment(branch) for branch in branches(t)]
        return tree(label(t) + 1, bs)

def print_tree(t, indent=0):
    if not is_tree(t):
        return
    # Pre Order Traverse
    print('  ' * indent + str(label(t)))
    for branch in branches(t):
        print_tree(branch, indent + 3)