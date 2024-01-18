"""Mutable Functions"""
# def make_withdraw(balance):
#     """Return a withdraw function with a starting balance."""
#     def withdraw(amount):
#         nonlocal balance
#         if amount > balance:
#             return 'Insufficient funds'
#         balance -= amount
#         return balance
#     return withdraw


# 除了使用 nonlocal 语句外
# 还可以使用 python 中 mutable 的数据结构保存外部变量
def make_withdraw(balance):
    b = [balance] # 使用列表将 balance 封装，列表是 mutable 的
    def withdraw(amount):
        if amount > b[0]:
            return 'Insufficient funds'
        b[0] -= amount # 注意，这里只是修改了列表的内容，而指针 b 本身是没有发生改变的
        return b[0]
    return withdraw

def combo(a, b):
    """Return the smallest integer with all of the digits of a and b (in order).
    
    >>> combo(531, 432)             # 45312 contains both _531_ and 4_3_2.
    45312
    
    >>> combo(535, 335)             # combo(535, 335) ==> combo(53, 33) * 10 + 5 ==> (combo(5, 3) * 10 + 3) * 10 + 5 ==> (35 * 10 + 3) * 10 + 5 ==> 3535
    3535

    >>> combo(0, 321)               # The number 0 has no digits, so 0 is not in the result.
    321
    """
    if a == 0 or b == 0:
        return a + b
    elif a % 10 == b % 10:
        return combo(a // 10, b // 10) * 10 + a % 10
    else:
        return min(combo(a // 10, b) * 10 + a % 10, combo(a, b // 10) * 10 + b % 10)