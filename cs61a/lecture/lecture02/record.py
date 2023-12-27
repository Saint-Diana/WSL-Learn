# First
# x = 10

# def f(v):
#     global x # 如果在函数内想要使用全局变量，需要加上'global'
#     x += 3
#     print(x)

# f(x)
# print(x)


# Second
x = 20 # global frame

def a(y):
    x = 30
    x += 3
    print(x, y)
    b(x)

def b(y):           # parent = Global
    global x        # 所以这里的x仍然是Gloabl Frame中的x，而不是调用者的x
    x = 15
    print(x, y)

print(x)    # 20
a(x)        # 33 20
            # 15 33
print(x)    # 15