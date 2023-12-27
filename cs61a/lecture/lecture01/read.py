novel = open('./道诡异仙.txt')
text = novel.read().split(' ')
print(len(text))                    # text数组长度
print(text[:30])                    # 打印前30个
print(text.count(''))               # ''的数量
print(text.count('') / len(text))   # ''的比率

words = set(text)                   # 去重
print(len(words))
print('' in words)
print(' ' in words)

words.remove('')                    # 去除''
print({w[0] for w in words})

print('draw'[::-1])                 # 倒序输出