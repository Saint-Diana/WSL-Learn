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
def sum_naturals(n):
    """Return the sum of the first n natural numbers
    
    >>> sum_naturals(3)
    6

    >>> sum_naturals(5)
    15

    >>> sum_naturals(10)
    20
    """
    total, k = 0, 1
    while k <= n:
        total += k
        k += 1
    return total

if __name__ == "__main__":
    import doctest
    doctest.testmod()
