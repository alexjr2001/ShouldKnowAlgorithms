##Project: Block cipher
##Date: 08/2022

import numpy as np 
alfabeto="ABCDEFGHIJKLMNÑOPQRSTUVWXYZ" 
textoPlano=input("Ingrese el texto: ") #Ingresamos texto a cifrar
def determinante(a):
	det=a[0][0]*a[1][1]-a[0][1]*a[1][0]
	return det
def InversoEE(a,b):
			inverso=False
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
			if s<0: s+=27
			mcd=b
			if(mcd==1):
				inverso=True
			else:
				print("La matriz no tiene inverso,ingrese de nuevo")
			return inverso
def InversoEE2(a,b):
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
A=np.array([[0,0],[0,0]])
correcto=False
while(correcto==False):
	A[0][0]= int(input("Ingrese valor de matriz(1,1): "))
	A[1][0]= int(input("Ingrese valor de matriz(2,1): "))
	A[0][1]= int(input("Ingrese valor de matriz(1,2): "))
	A[1][1]= int(input("Ingrese valor de matriz(2,2): "))
	correcto=InversoEE(determinante(A),27)

MatrizTemporal=np.array([[0],[0]])

length=len(textoPlano)
if length%2==1:
	textoPlano+="X"
	length+=1
textoCifrado=""
matrizMultiplicada=[[0],[0]]
for i in range(0,length,2):
	numero=alfabeto.find(textoPlano[i])
	MatrizTemporal[0]=numero
	numero=alfabeto.find(textoPlano[i+1])
	MatrizTemporal[1]=numero
	matrizMultiplicada=np.dot(A,MatrizTemporal)
	matrizMultiplicada=matrizMultiplicada%27
	textoCifrado+=alfabeto[int(matrizMultiplicada[0])]
	textoCifrado+=alfabeto[int(matrizMultiplicada[1])]
	
print(textoCifrado)


##DESCIFRADO
temp=A[0][0]
A[0][0]=A[1][1]
A[1][1]=temp
A[1][0]=-A[1][0]
A[0][1]=-A[0][1]

A=np.dot(InversoEE2(determinante(A),27),A)
A=A%27
print(A)
length=len(textoCifrado)
textoDescifrado=""
for i in range(0,length,2):
  numero=alfabeto.find(textoCifrado[i])
  MatrizTemporal[0]=numero
  numero=alfabeto.find(textoCifrado[i+1])
  MatrizTemporal[1]=numero
  print(MatrizTemporal[0])
  print(MatrizTemporal[1])
  matrizMultiplicada=np.dot(A,MatrizTemporal)
  matrizMultiplicada=matrizMultiplicada%27
  print(matrizMultiplicada)
  textoDescifrado+=alfabeto[int(matrizMultiplicada[0])]
  textoDescifrado+=alfabeto[int(matrizMultiplicada[1])]
  
print(textoDescifrado)



