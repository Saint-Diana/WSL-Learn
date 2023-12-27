from operator import add, sub

def a_plus_abs_b(a, b):
    """Return a+abs(b), but without calling abs.

    >>> a_plus_abs_b(2, 3)
    5
    >>> a_plus_abs_b(2, -3)
    5
    >>> # a check that you didn't change the return statement!
    >>> import inspect, re
    >>> re.findall(r'^\s*(return .*)', inspect.getsource(a_plus_abs_b), re.M)
    ['return f(a, b)']
    """
    if b < 0: # if b < 0, then a + abs(b) equals a + (-b)
        f = sub
    else:
        f = add
    return f(a, b)


def two_of_three(x, y, z):
    """Return a*a + b*b, where a and b are the two smallest members of the
    positive numbers x, y, and z.

    >>> two_of_three(1, 2, 3)
    5
    >>> two_of_three(5, 3, 1)
    10
    >>> two_of_three(10, 2, 8)
    68
    >>> two_of_three(5, 5, 5)
    50
    >>> # check that your code consists of nothing but an expression (this docstring)
    >>> # a return statement
    >>> import inspect, ast
    >>> [type(x).__name__ for x in ast.parse(inspect.getsource(two_of_three)).body[0].body]
    ['Expr', 'Return']
    """
    # 求出 x, y, z中的最小的两个值，然后运算。共有以下三种情况：
    # x ** 2 + y ** 2
    # x ** 2 + z ** 2
    # y ** 2 + z ** 2
    # 转换为求三者的最小值
    return min(x ** 2 + y ** 2, x ** 2 + z ** 2, y ** 2 + z ** 2)


def largest_factor(n):
    """Return the largest factor of n that is smaller than n.

    >>> largest_factor(15) # factors are 1, 3, 5
    5
    >>> largest_factor(80) # factors are 1, 2, 4, 5, 8, 10, 16, 20, 40
    40
    >>> largest_factor(13) # factor is 1 since 13 is prime
    1
    """
    for i in range(n - 1, 0, -1):
        if(n % i == 0):
            return i


def if_function(condition, true_result, false_result):
    """Return true_result if condition is a true value, and
    false_result otherwise.

    >>> if_function(True, 2, 3)
    2
    >>> if_function(False, 2, 3)
    3
    >>> if_function(3==2, 3+2, 3-2)
    1
    >>> if_function(3>2, 3+2, 3-2)
    5
    """
    if condition:
        return true_result
    else:
        return false_result


def with_if_statement():
    """
    >>> result = with_if_statement() # 调用 with_if_statement() 会打印 47，没有返回值；也就是执行了 false_func()；因此cond()的返回值必须是False
    47
    >>> print(result)
    None
    """
    if cond():
        return true_func()
    else:
        return false_func()

def with_if_function():
    """
    >>> result = with_if_function() # 调用 with_if_function() 会打印 42 和 47，没有返回值
    42
    47
    >>> print(result)
    None
    """
    return if_function(cond(), true_func(), false_func()) # 会先去计算 cond()、true_func()和false_func()，然后再把结果作为参数传递到if_function()中进行调用
def cond():
    return False

def true_func():
    print(42)
    return None

def false_func():
    print(47)
    return None


def hailstone(n):
    """Print the hailstone sequence starting at n and return its
    length.

    Hailstone sequence（冰雹序列），也称为Collatz序列，是一个数学上的数列，以其简单的定义而著称。该序列以正整数开始，如果当前数字是偶数，则将其除以2，如果是奇数，则将其乘以3并加1。通过重复这个过程，最终会得到1。

    >>> a = hailstone(10)
    10
    5
    16
    8
    4
    2
    1
    >>> a
    7
    """
    cnt = 1
    print(n)
    while n != 1:
        if n % 2 == 0:
            n //= 2
        else:
            n = n * 3 + 1
        cnt += 1
        print(n)
    return cnt


