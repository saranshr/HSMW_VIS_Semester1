#import time
#start_time = time.time()

symbols = " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz?!,."

def pot(a, n):                               # fast exponentiation
    if n == 0:
        return 1
    n = bin(n)[2:]
    result = 1
    for i in range(len(n)):
        result *= result
        if n[i] == '1':
            result *= a
    return result

def ZZ(a,b):
    result = 0
    for i in range(len(a)):
        #result += a[i]*(b**i)
        result += a[i]*pot(b,i)
    return result

def str2num(s):
    digits = [symbols.find(c) for c in s] 
    return ZZ(digits,len(symbols))

print(str2num('000'))

#print("--- %s seconds ---" % (time.time() - start_time))