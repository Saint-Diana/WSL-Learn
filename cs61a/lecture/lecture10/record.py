"""Lecture 10: Container"""

from datetime import date

today = date(2024, 1, 2)
# print(today)

# print(today - date(2023, 12, 28))

# print(today.year, today.month, today.day)

# print(today.strftime('%A, %B %d'))

# print(type(today), type(10))

from operator import getitem
from math import gcd

def make_rat(n, d):
    """返回分子为n，分母为d的有理数

    n - 分子
    d - 分母
    """
    n, d = n // gcd(n, d), d // gcd(n, d)
    return (n, d) # 使用 tuple 作为保存有理数的数据结构

def number(x):
    """返回有理数x的分子
    
    x - 有理数
    """
    return getitem(x, 0)

def denom(x):
    """返回有理数x的分母
    
    x - 有理数
    """
    return getitem(x, 1)

def add_rat(x, y):
    """有理数的加法操作

    x - 有理数
    y - 有理数
    """
    # 新的分母是 denom(x) * denom(y)
    # 新的分子是 number(x) * denom(y) + number(y) * denom(x)
    nx, dx = number(x), denom(x)
    ny, dy = number(y), denom(y)
    return make_rat(nx * dy + ny * dx, dx * dy)

def mul_rat(x, y):
    """有理数的乘法操作

    x - 有理数
    y - 有理数
    """
    nx, dx = number(x), denom(x)
    ny, dy = number(y), denom(y)
    return make_rat(nx * ny, dx * dy)

def eq_rat(x, y):
    """返回True，如果有理数x等于有理数y；否则返回False

    x - 有理数
    y - 有理数
    """
    nx, dx = number(x), denom(x)
    ny, dy = number(y), denom(y)
    return nx * dy == ny * dx

def str_rat(x):
    """返回有理数字符串格式
    
    x - 有理数
    """
    nx, dx = number(x), denom(x)
    if nx == dx and nx == 1:
        return '1'
    else:
        return '{0} / {1}'.format(nx, dx)

def make_pair(x, y):
    def dispatch(m):
        if m == 0:
            return x
        elif m == 1:
            return y
    return dispatch

def getitem_pair(p, i): # 这里的 p 实际上就是上面定义的 dispatch函数
    return p(i)

# 递归列表
empty_rlist = None
def make_rlist(first, rest):
    return (first, rest)

def first(s):
    return s[0]

def rest(s):
    return s[1]

def len_rlist(s):
    """return length of recursive list"""
    length = 0
    while s != None:
        s = rest(s)
        length += 1
    return length

def getitem_rlist(s, i):
    """return s[i]"""
    k = 0
    while k < i:
        s, k = rest(s), k + 1
    return first(s)

def count(s, value):
    """Count how many times does value occur in s ?"""
    length, cnt = len_rlist(s), 0
    for i in range(0, length):
        current_value = getitem_rlist(s, i)
        if value == current_value:
            cnt += 1
    return cnt

# 对前 n 个斐波那契数中的偶数进行求和
def fib(k):
    """Return the kth fibonacci number"""
    prev, curr = 0, 1
    for _ in range(k):
        prev, curr = curr, prev + curr
    return prev

def iseven(n):
    return n % 2 == 0

def sum_even_fib(n):
    """Sum the first n even Fibonacci numbers."""
    return sum(filter(iseven, map(fib, range(n + 1))))

# 缩写函数，将句子中的所有单词都缩写成首字母大写的形式
def iscap(word):
    return len(word) > 0 and word[0].isupper()

def first(word):
    return word[0]

def acronym(sentence):
    return tuple(map(first, filter(iscap, sentence.split())))

# 计算斐波那契数列中奇数的积
from functools import reduce
from operator import mul

def product_even_fibs(n):
    return reduce(mul, filter(iseven, map(fib, range(1, n + 1))))
