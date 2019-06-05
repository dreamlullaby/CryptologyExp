from hashlib import sha1
import Crypto.Util.number as num

'''生成系统参数p,g,y'''
def generatekey():
    global h,g,x,y,p,q
    q = num.getPrime(160)
    p = 0
    h = 0
    x = num.getRandomRange(0, q)
    y = 0
    multi=1
    while 1:
        print("trying to generate a new num")
        while multi % 2 == 1:
           multi = num.getRandomNBitInteger(512 - 160)
        for i in range(1 ,50):
            multi = multi + 2 * i
            p1 = multi * q
            p = p1 + 1
            if num.isPrime(p)and num.size(p) == 512:
                break
        if num.isPrime(p) and num.size(p) == 512:
            break
    power=divmod(p-1,q)[0]
    while not pow(h,power,p)>1:
        h = num.getRandomRange(2, p - 1)
    g = pow(h,power,p)
    y = pow(g, x, p)
'''签名'''
def sign(M):
    s1 = sha1()
    s1.update(M.encode('utf-8'))
    res = int(s1.hexdigest(), 16)
    global k_inverse,s,r,g
    k=num.getRandomRange(1,q)
    r = pow(g,k,p)%q
    k_inverse= num.inverse(k,q)
    s=(k_inverse*(res+x*r))%q
    sig=(r,s)
    print(M,"的DSA签名为：",sig)
    return sig
'''解签及验证'''
def verify(M,sig):
    s1 = sha1()
    s1.update(M.encode('utf-8'))
    res = int(s1.hexdigest(), 16)
    r=sig[0]
    w=num.inverse(s,q)
    u1=(res*w)%q
    u2=(r*w)%q
    v=(pow(g,u1,p)*pow(y,u2,p)%p)%q
    if r == v:
        print("signature pass verify")
    else:
        print("signature invalid")
'''测试'''
generatekey()
sig=sign("Southeast University")
verify("Southeast University",sig)
sig=sign("SoutheastUniversity")
verify("Southeast University",sig)
