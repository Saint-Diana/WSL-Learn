# 测试
# def fib(n):
#     """ Compute the nth Fibonacci number, for n >= 2."""
#     pred, curr = 0, 1
#     k = 2
#     while k < n:
#         pred, curr = curr, pred + curr
#         k += 1
#     return curr

# def fib_test(): # 使用断言(assert)进行测试
#     assert fib(8) == 13, 'the 8th Fibonacci number should be 13'
#     assert fib(2) == 1, 'the 2th Fibonacci number should be 1'
#     assert fib(3) == 3, 'the 3th Fibonacci number should be 3'

# fib_test() # 调用测试用例

# 除此之外，还可以使用 Doctest
# def sum_naturals(n):
#     """Return the sum of the first n natural numbers
    
#     >>> sum_naturals(3)
#     6

#     >>> sum_naturals(5)
#     15

#     >>> sum_naturals(10)
#     20
#     """
#     total, k = 0, 1
#     while k <= n:
#         total += k
#         k += 1
#     return total

# if __name__ == "__main__":
#     import doctest
#     doctest.testmod()

"""Our first python source file."""
from operator import floordiv, mod

def divide_exact(n, d):
    """Return the quotient and remainder of dividing N by D.
    
    >>> q, r = divide_exact(2013, 10)
    >>> q
    201
    >>> r
    3
    """
    return floordiv(n, d), mod(n, d)

# default parameter
def default_parameter(p, q=10):
    print('p =', p, 'q =', q)

def absolute_value(x):
    """Return the absolute value of x
    
    >>> absolute_value(10)
    10
    >>> absolute_value(-5)
    5
    >>> absolute_value(0)
    0
    """
    if x > 0:
        return x
    elif x == 0:
        return 0
    else:
        return -x

def isprime(n):
    """If N is prime, return True. Otherwise return False"""
    if n <= 1:
        return False
    for i in range(2, n - 1):
        if n % i == 0:
            return False
    return True
    

def fundamental_theorem_of_arithmetic(n):
    """Use the product of several prime numbers to represent N. Require N > 1.

    >>> fundamental_theorem_of_arithmetic(858)
    2
    3
    11
    13

    >>> fundamental_theorem_of_arithmetic(8)
    2
    2
    2
    """
    # my solution:
    # while n != 1:
    #     # 实际上就是每次都从2开始除
    #     i = 2
    #     if n % i == 0:
    #         n //= i
    #         print(i)
    #     else: # 如果不能整除2，就找到第一个能够整除的素数
    #         while n % i != 0 or not isprime(i):
    #             i += 1
    #         n //= i
    #         print(i)

    # recommended solution:
    while n != 1:
        factor = smallest_prime_factor(n) # 每次都找到最小的素因数
        n //= factor
        print(factor)

def smallest_prime_factor(n):
    prime = 2
    while prime <= n:
        if n % prime == 0: # 这里不需要判断prime是不是素数。因为一个数要么本身是素数，要么会被素数整除。因此这里的prime一定是素数。
            return prime
        prime += 1

