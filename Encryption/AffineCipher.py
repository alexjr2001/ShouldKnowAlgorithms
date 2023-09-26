##Project: Affine Cipher
##Date: 08/2020


#ENCRYPT
alfabeto="ABCDEFGHIJKLMNÑOPQRSTUVWXYZ" 
textoPlano=input("Ingrese el texto: ") #Insert text to cipher
textoPlano=textoPlano.upper()
a=int(input("Valor de a: "))   #Multiplication
while a%3==0:
    print("El valor necesita inverso, intente de nuevo")
    a=int(input("Valor de a: "))
b=int(input("Valor de b: "))   #How much the text will be moved
print("\n")
n=len(textoPlano)  
textoCifrado=""
for i in range(n):
    letra=textoPlano[i]  
    ubi=alfabeto.find(letra)  #Find the turn's letter
    print("Letra ",letra, "P=", ubi)
    newUbi=(a*ubi+b)%27  #Find out the new index of the cipher
    letraCifrada=alfabeto[newUbi]
    textoCifrado+=letraCifrada #Join the cipher letter to the cipher text
    print("Letra ",letraCifrada, "C=", newUbi)

print("\n")
print("Texto Cifrado: ", textoCifrado)
print("\n")


##DECRYPT

#Inverse - Extended euclidean
def InversoEE(a,b):
    u_1=1
    v_1=0
    u0=0
    v0=1
    import math
    aa=a
    bb=b
    while (a%b)!= 0:
        qk=math.floor(a/b)
        uk=u_1-qk*u0   #uk=uk_2-qk*uk_1
        vk=v_1-qk*v0  #vk=vk_2-qk*vk_1
        rk=aa*uk+bb*vk
        m=b
        a=m
        b=rk
        u_1=u0
        u0=uk
        v_1=v0
        v0=vk
    s=uk
    t=vk
    mcd=b
    if s<0:
        s+=27
    return s


####
alfabeto="ABCDEFGHIJKLMNÑOPQRSTUVWXYZ" 
textoPlano=input("Ingrese el texto cifrado: ") #Input: Cipher text
print("\n")
n=len(textoPlano)  
textoCifrado=""
for i in range(n):
    letra=textoPlano[i]  
    ubi=alfabeto.find(letra)  #Search the turn's letter
    print("Letra ",letra, "P=", ubi)
    newUbi=(InversoEE(a,27)*(ubi-b))%27  #Find out the index of the cipher
    letraCifrada=alfabeto[newUbi]
    textoCifrado+=letraCifrada #Join the cipher letter to the text
    print("Letra ",letraCifrada, "C=", newUbi)

print("\n")
print("Texto Descifrado: ", textoCifrado)

