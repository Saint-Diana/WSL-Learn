from math import pow

"""Lecture 4 Higher-Order Functions"""
def sum_naturals(n):
    """Compute the sum of naturals from 1 to N"""
    total, i = 0, 1
    while i <= n:
        total, i = total + i, i + 1
    return total

def sum_cubes(n):
    """Compute the sum of cube of natural from 1 to N"""
    total, i = 0, 1
    while i <= n:
        total, i = total + pow(i, 3), i + 1
    return total

def pi_sum(n):
    """Compute the sum of 8 / (1 * 3) + 8 / (5 * 7) + 8 / (9 * 11) + ······"""
    total, i = 0, 1
    while i <= n:
        total, i = total + 8 / (i * (i + 2)), i + 4
    return total

# 显然，上面三个函数具有很高的相似度。因此可以进行抽象。
"""
def <name>(n):
    total, i = 0, 1
    while i <= n:
        total, i = total + <term>(i), <next>(i)
    return total
"""
# 因此可以使用 Higher-Order Functions进行抽象
def summation(n, term, next):
    total, i = 0, 1
    while i <= n:
        total, i = total + term(i), next(i)
    return total

def term_naturals(i):
    return i

def next_naturals(i):
    return i + 1

def term_cube(i):
    return pow(i, 3)

def next_cube(i):
    return i + 1

def term_pi(i):
    return 8 / (i * (i + 2))

def next_pi(i):
    return i + 4

print('From 1 to 10, the sum of naturals is', summation(10, term_naturals, next_naturals))
print('From 1 to 10, the sum of cubes is', summation(10, term_cube, next_cube))
print('pi = ', summation(1e6, term_pi, next_pi))


# 迭代改进的一般方法
def iter_improve(update, test, guess=1):
    """The general function of iterator improvement.
    
    update  - The function to update guess value.
    test    - The function to test guess value.
    guess   - value
    """
    while not test(guess):      # 不满足 test 条件
        guess = update(guess)   # 持续改进
    return guess

# 判断f(x)和g(x)是否足够接近
def near(x, f, g):
    """Compare f(x) and g(x).
    
    x - formal parameter
    f - function f
    g - function g
    """
    return approx_eq(f(x), g(x))

# 判断x,y是否足够接近
def approx_eq(x, y, tolerance=1e-5):
    """Judge if abs(x - y) less than tolerance"""
    return abs(x - y) < tolerance

# 利用上面的高阶函数，计算golden rate
def golden_update(guess): # f_{i + 1} = 1 / f_{i} + 1；迭代公式
    return 1 / guess + 1

def square(x):
    return x * x

def successor(x):
    return x + 1

def golden_test(guess): # abs(guess ** 2 - (guess + 1)) < 1e-5
    return near(guess, square, successor)

def golden_iter(guess=1):
    return iter_improve(golden_update, golden_test, guess)


# 测试
phi = 1 / 2 + pow(5, 1 / 2) / 2
def near_test():
    assert near(phi, square, successor), 'phi * phi is not near phi + 1'

def iter_improve_test():
    assert approx_eq(phi, golden_iter()), 'phi differs from is\'s approximation'

def average(x, y):
    return (x + y) / 2

# 迭代求 sqrt(x)
# f_{i + 1} = (f_{i} + x / f_{i}) / 2
# 使用嵌套函数完成
def square_root(x):
    def update(guess):
        return average(guess, x / guess)
        
    def test(guess):
        return approx_eq(square(guess), x)
    
    return iter_improve(update, test)

print(square_root(4))



# 返回值是函数
def compose(f, g):
    """Return h(x) = f(g(x))"""
    def h(x):
        return f(g(x))
    
    return h

# 上面可以用 lambda 表达式代替
# compose = lambda f, g : lambda x : f(g(x))

h = compose(square, successor) # h(x) = square(x + 1)
print('square(15 + 1) =', h(15))

# lambda表达式创建匿名函数；要求这个函数只有一个return语句
anonymous = lambda x : x + 1
print(anonymous(10))

# 求 square_root(a) 相当于求 suqare(x) - a = 0 的根
def square_root(a):
    return find_root(lambda x : square(x) - a)

# 求 log_{2}a 相当于求 2^x - a = 0 的根
def logarithm(a, base=2, guess=1):
    return find_root(lambda x : pow(base, x) - a, guess)

# 牛顿法迭代求方程解
# 已知点(x_{0}, f(x_{0}))
# 过上述点的切线为 y = f'(x_{0}) * x + b
# f(x_{0}) = f'(x_{0}) * x_{0} + b
# b = f(x_{0}) - f'(x_{0}) * x_{0}
# 则切线可以表示为 y = f'(x_{0}) * x + f(x_{0}) - f'(x_{0}) * x_{0}
# 则切线与x轴的交点是 f'(x_{0}) * x = f'(x_{0}) * x_{0} - f(x_{0})
#                              x = x_{0} - f(x_{0}) / f'(x_{0})
# 也就是 (x_{0} - f(x_{0}) / f'(x_{0}), 0)
# 再以 x_{0} - f(x_{0}) / f'(x_{0}) 作为 x_{0}' 去求 (x_{0}', f(x_{0}'))
# 因此迭代方程就是 x' = x - f(x) / f'(x)
# 然后重复上述过程，直到根满足误差
def approx_derivative(f, x, delta=1e-5):
    """Return the derivative of x, equals f'(x)
    
    f       - function
    x       - f(x)
    delta   - dx

    f'(x) = dy / dx = (f(x + delta) - f(x)) / delta
    """
    df = f(x + delta) - f(x)
    return df / delta

# 牛顿迭代公式 x' = x - f(x) / f'(x)
def newton_update(f): # 相当于 lambda f : lambda x : x - f(x) / approx_derivative(f, x)
    def update(x):
        return x - f(x) / approx_derivative(f, x)
    return update

def find_root(f, init_guess=1):
    def test(x): # 根 x 满足 f(x) = 0
        return approx_eq(f(x), 0)
    return iter_improve(newton_update(f), test, init_guess)

print('log_{2}8 =', logarithm(8, 2, 2.99999))


# 函数装饰器
def trace1(fn): # Higher-Order Function trace1 return a function
    def wrapped(x):
        print('->', fn, '(', x, ')')
        return fn(x)
    return wrapped

@trace1 # triple的名称并没有绑定到这个函数上，而是绑定到了在新定义的函数triple上调用trace1的返回函数值上
def triple(x):
    return x * 3

"""
也就相当于
def triple(x):
    return x * 3
triple = trace1(triple) <==> wrapped
"""

print(triple(10)) # triple(10) 就等同于 wrapped(10)
# 类似于
print(trace1(lambda x : x * 3)(10))



# decorator 可以用来在函数执行前、后加上log
def log(f):
    """ Add log to function f"""
    def wrapped():
        print('log before execute')
        f()
        print('log after execute')
    
    return wrapped

@log
def foo():
    print('bar')

foo() # equals log(foo())() or wrapped() with f = foo

"""
本质上 @decorator_func 是一个语法糖，目的是将下面的流程进行简化，看起来舒服

1.
def foo(bar):
    def wrapped():
        *** your code ***
        bar()
        *** your code ***
    
    return wrapped

def foobar():
    print('xxxxx')
    *** your code ***

[ foobar = foo(foobar) ]

2.
def foo(bar):
    def wrapped():
        *** your code ***
        bar()
        *** your code ***
    
    return wrapped

[ @foo ]
def foobar():
    print('xxxxx')
    *** your code ***
    
"""