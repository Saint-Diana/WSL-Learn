# gcc重要编译参数
## 1.-g 编译带调试信息的可执行文件
```shell
# -g 选项告诉GCC产生能被GNU调试器GDB使用的调试信息，以调试程序。
# 产生带调试信息的可执行文件test
gcc -g test.c -o test
```

## 2.-O[n] 优化源代码
```shell
# -O[n] 这里的n是指优化级别，一般到2即可
gcc -O2 test.c
```

## 3.-l 和 -L 指定库文件 | 指定库文件路径
```shell
# -l 参数就是用来指定程序要链接的库，-l参数紧跟着就是库名
# 在/lib和/usr/lib和/usr/local/lib里的库直接用-l参数就能链接

# 链接glog库
gcc -lglog test.c

# 如果库文件没有放在上面三个目录中，则需要使用-L指定库文件所在目录
# -L参数紧跟着的是库文件所在目录名

# 链接mytest库，libmytest.so在/home/shenhuichang/mytestlibfolder下
gcc -L/home/shenhuichang/mytestlibfolder -lmytest test.c
```

## 4.-I 指定头文件搜索目录
```shell
# -I
# /usr/include目录一般是不用指定的，gcc知道去那里找，但是如果头文件不在/usr/include当中，我们就要用-I参数指定。
# 例如头文件放在/myinclude中，那么编译命令就要加上-I/myinclude参数。-I可以使用相对路径。

gcc -I/myinclude test.c
```

## 5.-Wall 打印警告信息
```shell
# 打印出gcc提供的警告信息
gcc -Wall test.c
```

## 6.-w 关闭警告信息
```shell
# 关闭所有警告信息
gcc -w test.c
```

## 7.-std=c99 设置编译标准
```shell
# 使用 c99 标准编译 test.c
gcc -std=c99 test.c 
```