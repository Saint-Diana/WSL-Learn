def digit_sum(a):
    """Compute sum of every digit of a number

    a - the given number
    """
    total = 0
    while a:
        total += a % 10
        a //= 10
    return total

# we can use recursion function instead of a while statement
def digit_sum_recursion(a):
    """Compute sum of every digit of a number through recursion

    >>> digit_sum_recursion(123)
    6

    >>> digit_sum_recursion(235)
    10

    >>> digit_sum_recursion(10)
    1

    >>> digit_sum_recursion(0)
    0
    """
    if a == 0:
        return 0
    return a % 10 + digit_sum_recursion(a // 10)

def fact(n):
    if n == 0:
        return 1
    return n * fact(n - 1)

def fact_iter(n):
    total, k = 1, 1
    while k <= n:
        total, k = total * k, k + 1
    return total

# def luhn_sum(card_number):
#     """Compute the luhn sum of a credit card

#     card_number - a string describing the credit card number
#     """
#     total, i = 0, 0
#     while i < len(card_number):
#         if i % 2 == 0:
#             total += int(card_number[i])
#         else:
#             total += digit_sum_recursion(2 * int(card_number[i]))
#         i += 1
#     return total

# def isvalid(card_number):
#     """Return True if card number is valid, return False otherwise

#     card_number - a string describing the credit card number
#     """
#     return not luhn_sum(card_number) % 10

def split(n):
    """for n >= 10, return all digits but last and the last digit"""
    return n // 10, n % 10

def luhn_sum(n):
    """
    >>> luhn_sum(138743)
    30

    >>> luhn_sum(138745)
    32
    """
    if n < 10:
        return n
    else:
        digits_but_last, last_digit = split(n)
        return luhn_sum_double(digits_but_last) + last_digit

def luhn_sum_double(n):
    digits_but_last, last_digit = split(n)
    luhn_digit = digit_sum_recursion(last_digit * 2)
    if n < 10:
        return luhn_digit
    else:
        return luhn_sum(digits_but_last) + luhn_digit