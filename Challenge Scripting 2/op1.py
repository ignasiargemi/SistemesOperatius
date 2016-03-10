# OPERACIO 1: Numero de linies del document: NUM
#OPERACIO 2: Numero de paraules del document:NUM
#OPERACIO 3: Numero promig de paraules per linea del document:NUM
#Generar un histograma, amb les vegades que tenim numero de paraules per linies del document,
# indicant quantes linies tenen cada numero
#Finalment haurem de triar una forma grafica de representar aquest histograma

import pygal
#!/usr/bin/env python
# -*- coding: 850 -*-
# -*- coding: utf-8 -*-

fitxer = open("textObama.txt", "r")
fitxerOut = open("obama.OUT.txt","w")
numlinies=0
numparaules=0
numeroCaracters=0
diccionari={}
diccionarip={}
longitud=0
paraulesXlinia = []
lin = 1
numpar = 0
for linia in fitxer.readlines():
    if len(linia)>2:
    	numpar = 0
        paraules=linia.split()
        for paraula in paraules:
            paraula = paraula.replace('\n', '')
            paraula = paraula.replace('\xe9', '')
            paraula = paraula.replace('.','')
            paraula = paraula.replace('', '')
            paraula = paraula.replace('?', '')
            paraula = paraula.replace('-', '')
            paraula = paraula.replace(';', '')
            paraula = paraula.replace(':', '')
            paraula = paraula.replace('(', '')
            paraula = paraula.replace(')', '')
            paraula = paraula.replace("'", '')
            paraula = paraula.replace(',', '')
            paraula = paraula.replace('=', '')
            paraula = paraula.replace('"', '')
            paraula = paraula.replace('!', '')
            paraula = paraula.replace(' ', '')
            for lletra in paraula:
                if diccionari.has_key(lletra) and lletra!= ' ':
					diccionari[lletra]=diccionari[lletra]+1
					numeroCaracters+=1
                else:
                    if lletra !=' ':
                    	numeroCaracters+=1
                        diccionari.get(lletra)
                        diccionari[lletra]=1

            longitud= longitud + len(paraula)

            if diccionarip.has_key(paraula):

                diccionarip[paraula]=diccionarip[paraula]+ 1
            else:
                diccionarip.get(paraula)
                diccionarip[paraula]=1
            numpar+=1
        numlinies+=1
        numparaules = numparaules + len(linia.split(" "))
        paraulesXlinia.append([lin, numpar])
        lin+=1
'''
for i in paraulesXlinia:
	print("Num de linia: " + str(i[0]) + " num de paraules " + str(i[1]))
    '''
#Transformacio de les dades
llet = []
for key, value in diccionari.iteritems():
	#print("Clau: " + str(key) + " Valor: " + str(value))
	llet.append([key,value])

#print("\nParaules")
par = []
for key, value in diccionarip.iteritems():
	#print("Clau: " + str(key) + "\t\tValor: " + str(value))
	par.append([key,value])


mitpar = numparaules/numlinies
mitlon = longitud/numparaules
mitjanaCaracXPar = numeroCaracters/numparaules

fitxerOut.write("1. Numero de linies del document: "+str(numlinies)+ '\n\n')

fitxerOut.write("2. Numero de paraules del document: "+str(numparaules)+ '\n\n')

fitxerOut.write("3. Mitjana de paraules per linia: "+str(mitpar)+ '\n\n')

histogram = pygal.Bar()
for x in paraulesXlinia:
    histogram.add("Linia " + str(x[0]),x[1])
histogram.render_in_browser()


fitxerOut.write("4. Promig de lletres en el document: \n")

for key, value in diccionari.iteritems():
    fitxerOut.write("Caracter: " + str(key) + " Valor: " + str(value) + "\n")

histLletres = pygal.Bar(title='Caracters utilitzats en el text')

for val in llet:
	k = val[0]
	v = val[1]
	histLletres.add(k, v)
histLletres.render_in_browser()

fitxerOut.write("\n5. Promig de longitud de paraules en el document: ")
fitxerOut.write(str(mitlon)+ "\n")

fitxerOut.write("\n6. Promig de paraules en el document:\n")
for key, value in diccionarip.iteritems():
    fitxerOut.write("Paraula: " + str(key) + "\tValor: " + str(value) + "\n")
'''
fitxerOut.write(str(diccionarip.keys()))
fitxerOut.write("\n" + str(diccionarip.values()))
'''

fitxer.close()
fitxerOut.close()