def rational(n, d):
    return (n, d)

def numer(x):
    return x[0]

def denom(x):
    return x[1]

def mul_rational(x, y):
    return rational(numer(x) * numer(y), denom(x) * denom(y))

def add_rational(x, y):
    nx, dx = numer(x), denom(x)
    ny, dy = numer(y), denom(y)
    return rational(nx * dy + ny * dx, dx * dy)

def equal_rational(x, y):
    nx, dx = numer(x), denom(x)
    ny, dy = numer(y), denom(y)
    return nx * dy == ny * dx

def print_rational(x):
    print(numer(x), '/', denom(x))