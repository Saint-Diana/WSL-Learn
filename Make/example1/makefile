# 生成可执行文件main需要依赖所有.c文件生成的目标文件.o
main : main.o
	gcc -o main main.o

# xxxx.o文件所依赖的就是xxxx.c文件和这个文件中包含的.h文件
main.o : main.c global.h
	gcc -c main.c

# 定义一个clean命令，将编译、链接过程中产生的文件(目标文件和可执行文件)都删掉
clean :
	rm main main.o

# 这样就能实现只重新编译发生过修改的文件

# Makefile中可以自己定义变量
# 通常会把所有的目标文件字符串定义成一个变量，便于调用和修改
objects = main.o hello.o
# 使用$(var)引用变量
#$(objects)