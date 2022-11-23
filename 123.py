import sys
file = open('_in.txt','w',encoding='utf-8')
sys.stdout = file
with open('123.txt','r',encoding='utf-8') as f:
    for i in f:
        print(i[:-1]+' '+i,end='')
file.close()

