LAB_SOURCE_FILE = __file__



this_file = __file__

def skip_add(n):
    """ Takes a number n and returns n + n-2 + n-4 + n-6 + ... + 0.

    >>> skip_add(5)  # 5 + 3 + 1 + 0
    9
    >>> skip_add(10) # 10 + 8 + 6 + 4 + 2 + 0
    30
    >>> # Do not use while/for loops!
    >>> from construct_check import check
    >>> # ban iteration
    >>> check(this_file, 'skip_add',
    ...       ['While', 'For'])
    True
    """
    if n <= 0:
        return 0
    else:
        return n + skip_add(n - 2)


def summation(n, term):

    """Return the sum of the first n terms in the sequence defined by term.
    Implement using recursion!

    >>> summation(5, lambda x: x * x * x) # 1^3 + 2^3 + 3^3 + 4^3 + 5^3
    225
    >>> summation(9, lambda x: x + 1) # 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10
    54
    >>> summation(5, lambda x: 2**x) # 2^1 + 2^2 + 2^3 + 2^4 + 2^5
    62
    >>> # Do not use while/for loops!
    >>> from construct_check import check
    >>> # ban iteration
    >>> check(this_file, 'summation',
    ...       ['While', 'For'])
    True
    """
    assert n >= 1
    if n == 1:
        return term(n)
    else:
        return term(n) + summation(n - 1, term)


def paths(m, n):
    """Return the number of paths from one corner of an
    M by N grid to the opposite corner.

    >>> paths(2, 2)
    2
    >>> paths(5, 7)
    210
    >>> paths(117, 1)
    1
    >>> paths(1, 157)
    1
    """
    # n 行 m 列. 从 (1, 1) 到 (m, n)
    if m == 1 and n == 1:
        return 0
    elif m == 1 or n == 1:
        # 只能向下走或向左走
        return 1
    else:
        # 既可以向下走，又可以向左走
        return paths(m - 1, n) + paths(m, n - 1)


def max_subseq(n, t):
    """
    Return the maximum subsequence of length at most t that can be found in the given number n.
    For example, for n = 20125 and t = 3, we have that the subsequences are
        2
        0
        1
        2
        5
        20
        21
        22
        25
        01
        02
        05
        12
        15
        25
        201
        202
        205
        212
        215
        225
        012
        015
        025
        125
    and of these, the maxumum number is 225, so our answer is 225.

    >>> max_subseq(20125, 3)
    225
    >>> max_subseq(20125, 5)
    20125
    >>> max_subseq(20125, 6) # note that 20125 == 020125
    20125
    >>> max_subseq(12345, 3)
    345
    >>> max_subseq(12345, 0) # 0 is of length 0
    0
    >>> max_subseq(12345, 1)
    5
    """
    # def max_subseq(n, t)
    # 动态规划，划分为两种情况：1、包含最后一个数字；2、不包含最后一个数字
    length, temp = 0, n
    while temp > 0:
        length, temp = length + 1, temp // 10
    if length <= t:
        return n
    elif t == 0:
        return 0
    else:
        digit_last, digits_but_last = n % 10, n // 10
        res1 = digit_last + 10 * max_subseq(digits_but_last, t - 1)
        res2 = max_subseq(digits_but_last, t)
        return max(res1, res2)



def add_chars(w1, w2):
    """
    Return a string containing the characters you need to add to w1 to get w2.

    You may assume that w1 is a subsequence of w2.

    >>> add_chars("owl", "howl")
    'h'
    >>> add_chars("want", "wanton")
    'on'
    >>> add_chars("rat", "radiate")
    'diae'
    >>> add_chars("a", "prepare")
    'prepre'
    >>> add_chars("resin", "recursion")
    'curo'
    >>> add_chars("fin", "effusion")
    'efuso'
    >>> add_chars("coy", "cacophony")
    'acphon'
    >>> from construct_check import check
    >>> # ban iteration and sets
    >>> check(LAB_SOURCE_FILE, 'add_chars',
    ...       ['For', 'While', 'Set', 'SetComp']) # Must use recursion
    True
    """
    def helper(i, j):
        if i < len(w1) and j < len(w2):
            if w1[i] == w2[j]:
                return helper(i + 1, j + 1)
            else:
                return w2[j] + helper(i, j + 1)
        else:
            return w2[j:]
    
    return helper(0, 0)


    # 如果用循环来做
    # res = ""
    # len1, len2 = len(w1), len(w2)
    # i, j = 0, 0
    # while i < len1 and j < len2:
    #     if w1[i] == w2[j]:
    #         i += 1
    #         j += 1
    #     else:
    #         res = res + w2[j]
    #         j += 1
    # while j < len2:
    #     res = res + w2[j]
    #     j += 1
    # return res

