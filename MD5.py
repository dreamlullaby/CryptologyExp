#-*- coding: utf-8 -*-
#python 2.7
import struct
import math
import binascii
leftshift = lambda x,n: (x << n)|(x >> 32- n)
#初始向量
A, B, C, D = (0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476)
#循环左移的位数
s = [   7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
         4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
         6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
        ]
T =  [int(math.floor(abs(math.sin(i + 1)) * (2 ** 32))) for i in range(64)]
def MD5_init(message):
    global A
    global B
    global C
    global D
    A, B, C, D = (0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476)
    length = struct.pack('<Q', len(message)*8) 
    while len(message) > 64:
        fun(message[:64])
        message = message[64:]
    if len(message)<=56:
        message += '\x80'
        message += '\x00' * (56 - len(message) % 64)
        message += length
    else:
        message += '\x80'
        message += '\x00' * (120- len(message) % 64)
        message += length
        fun(message[:64])
        message = message[64:]
    fun(message[:64])
def fun(expand_message):
    global A
    global B
    global C
    global D
    w = list(struct.unpack('<' + 'I' * 16, expand_message))  #分成16个组
    a, b, c, d = A, B, C, D
    for i in range(64):  #64轮运算
        if i < 16:
            f = ( b & c)|((~b) & d)
            flag  = i    #标识处于第几组
        elif i < 32:
            f = (b & d)|(c & (~d))
            flag = (5 * i +1) %16
        elif i < 48:
            f = (b ^ c ^ d)
            flag  = (3 * i + 5)% 16
        else:
            f = c ^(b |(~d))
            flag  = (7 * i ) % 16
        tmp = b + leftshift((a + f + T[i] + w[flag])& 0xffffffff,s[i])
        a, b, c, d = d, tmp & 0xffffffff, b, c
    A = (A + a) & 0xffffffff
    B = (B + b) & 0xffffffff
    C = (C + c) & 0xffffffff
    D = (D + d) & 0xffffffff
def format_adjust():
    global A
    global B
    global C
    global D
    return struct.pack('<IIII',A,B,C,D)
def byte2hex():
    return binascii.hexlify(format_adjust()).decode()

def MD5(message):
    MD5_init(message)
    md5=byte2hex()
    return md5
mess1 = "SoutheastuniversitySoutheastuniversitySoutheastuniversity"
mess2 = "SoutheastuniversitySoutheastuniversitySoutheastunIversity"

md5_1 = MD5(mess1)
md5_2 = MD5(mess2)
print mess1,"的MD5值为",md5_1
print mess2,"的MD5值为",md5_2