import math
import numpy


def gcd(a,b):
    if a%b == 0:
        return b
    else :
        return gcd(b,a%b)

def ExGcd(a,b):
    if b==0:
        return 1,0
    else:
        k = a // b
        remainder = a % b		
        x1, y1 = ExGcd(b, remainder)
        x, y = y1, x1 - k * y1			
    return x,y

def getInverse(a,p):
    if gcd(a,p)!=1:
        return -1
    x,y=ExGcd(a,p)
    return x%p
def finde(r):
    for i in range(2,int(r/2)):
        if gcd(i,r)==1:
            return i
            break

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

def findsk(e):
    r=e
    while(gcd(e,r)!=1):
        p=proBin(16)
        q=proBin(16)
        r=(p-1)*(q-1)
    sk=[]
    sk.append(p)
    sk.append(q)
    sk.append(e)
    sk.append(r)
    return sk




n=919293
e=5
sk=findsk(e)
d=getInverse(e,sk[3])
sk.append(d)
N=sk[0]*sk[1]
c=(pow(n,e))%N
print(c)
print(sk)
m=(pow(c,d))%N
print(m)