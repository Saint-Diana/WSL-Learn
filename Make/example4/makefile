# 指定make命令搜索依赖文件和目标文件的目录（默认只在makefile当前所在目录下搜索）
vpath %.h ./headers # 到./headers文件夹下寻找以.h结尾的文件
vpath %.c ./sources # 到./sources文件夹下寻找以.c结尾的文件

objects = main.o max.o
# 或者写成 objects = *.o

main : $(objects)
	gcc -o main $(objects)

# 写法一：
# GNU Make功能非常强大，会根据我们所写的目标和依赖自动推断出命令
# 所以可以按照下面的简写形式
# main.o : max.h

# max.o : max.h global.h

# 感觉这种不是很好，不能直观地看出每一个目标文件所依赖的文件
# 写法二：
# 还可以把具有相同依赖的目标文件都写在一起
main.o max.o : max.h

max.o : global.h

# .PHONY表明后面clean是一个“伪目标”
.PHONY : clean
clean :
	-rm main $(objects)
