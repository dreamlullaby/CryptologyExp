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
def isprime(num):
    if num==2:
        return True
    else:
        for i in range(2,int(math.sqrt(num))):
            if num%i==0:
                return False
    return True

def genrandbits(w):  # w表示产生位数
    list = []
    list.append('1')  
    for i in range(w - 2):
        c = numpy.random.choice(['0', '1'])
        list.append(c)
    list.append('1') 
    print(list)
    res = int(''.join(list),2)
    return res

def genbigprime(w):
    bigprime=genrandbits(w)
    while not isprime(bigprime):
        bigprime=genrandbits(w)
        for i in range(50):
            bigprime=bigprime+2*i
            if isprime(bigprime):
                return bigprime
            else:
                continue
    return bigprime

def findsk(e):
    r=e
    while(gcd(e,r)!=1):
        p=genbigprime(16)
        q=genbigprime(16)
        r=(p-1)*(q-1)
    sk=[]
    sk.append(p)
    sk.append(q)
    sk.append(e)
    sk.append(r)
    return sk

#p=genbigprime(16)
#print(p)
def fastpow(a,m,n):
    result=1
    buffer=[]
    while m!=0:
        buffer.append(m%2)
        m=int(m/2)
    while buffer:
        rem=buffer.pop()
        result=((a**rem)*result**2)%n     
    return result

raw_message=919293              #abc的ascii码对应值
e=5                             #公钥e
sk=findsk(e)                    #生成私钥
d=getInverse(e,sk[3])           #求e模r的逆
sk.append(d)
n=sk[0]*sk[1]
c=(pow(raw_message,e))%n
message=fastpow(c,d,n)
pk=[e,n]
sk=[d,sk[0],sk[1]]
print("初始明文为",raw_message)
print("公钥public key:{},私钥secret key:{}".format(pk,sk))
print("加密所得密文为：%s"%c)
print("解密得到明文%s"%message)
