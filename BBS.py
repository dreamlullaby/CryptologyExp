import math
import random
import numpy
def proBin(w):  # w表示希望产生位数
    list = []
    list.append('1')  #最高位定为1
    for i in range(w - 2):
        c = numpy.random.choice(['0', '1'])
        list.append(c)
    list.append('1') # 最低位定为1
    print(list)
    res = int(''.join(list),2)
    return res

def gcd(a,b):
    if a%b == 0:
        return b
    else :
        return gcd(b,a%b)

def gen_n(w):
    p=1
    q=1
    while(p%4!=3):
       p=proBin(w)
    while(q%4!=3):
       q=proBin(w)
    return p*q

def finds(n):
    s=random.randint(2,int(math.sqrt(n)))
    while(gcd(s,n)!=1):
        s=random.randint(2,int(math.sqrt(n)))
    return s
def bbs(n,s):
    x=pow(s,2,n)
    b=[]
    count=20
    while(count>0):
        x=pow(x,2,n)
        b.append(x%2)
        count=count-1
    return b
n=gen_n(16)
s=finds(n)
bitset=bbs(n,s)
print(''.join(str(x) for x in bitset))
