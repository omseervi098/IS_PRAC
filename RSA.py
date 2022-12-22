# Take a string p. Calculate the Length of the string. Convert that length to the nearest prime number value. 
# Take another string q (Passphrase). Calculate its length. Convert the length to the nearest prime number value. 
# Make sure both p and q are different, If not change the value of q to the immediate next prime number 
# Calculate n=p*q 
# Calculate Totient Function(phi) =(p-1)(q-1) 
# Select e such that it is relatively prime to phi. 
# Calculate d using the formula : 
# (d*e)mod phi ≡ 1 
# Perform Encryption: CT = (PT)e mod n 
# Perform Decryption: PT =(CT)d mod n
from math import gcd


def nearestPrime(n):
    for i in range(n,2,-1):
        flag=1
        for j in range(2,i//2+1):
            if i%j==0:
                flag=0
                break
        if flag==1:
            return i
    return 2
x=input("Enter the string:")
p_len=len(x)
y=input("Enter the passphrase:")
q_len=len(y)
p,q=nearestPrime(p_len),nearestPrime(q_len)
if p==q:
    q=nearestPrime(q-1)
print(f"value of p={p},q={q}")
n=p*q
phi=(p-1)*(q-1)
e=2
while e<phi:
    if gcd(e,phi)==1:
        if e!=p and e!=q:
            break
    e+=1
d=2
while True:
    if(d*e)%phi==1:
        if(d!=p and d!=q and d!=e):
            break
    d+=1
print(f"Value of e={e},d={d}")
pt=int(input(f"Enter the plain text less than {phi}:"))
if pt>=phi:
    pt%=phi
ct=(pt**e)%n
print(f"Encrypted text:{ct}")
pt=(ct**d)%n
print(f"Decrypted text:{pt}")