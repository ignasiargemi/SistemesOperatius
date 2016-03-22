import pygal
from wordcloud import WordCloud
from os import path
import numpy as np

# Declaracio de variables
nom = raw_input("Digam el nom del fitxer d'entrada:\n(Sense Extencio//S'ha d'escollir un fitxer .txt)\n")
fitxer = open(nom + ".txt", "r")
fitxerOut = open(nom + ".OUT.txt","w")
numeroLinies=0
numeroParaules=0
numeroCaracters=0
MapDeLletres={}
MapDeParaules={}
paraulesXlinia = []
lin = 1
numpar = 0
longXpar = {}

# Lectura del fitxer
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
                if MapDeLletres.has_key(lletra) and lletra!= ' ':
					MapDeLletres[lletra]=MapDeLletres[lletra]+1
					numeroCaracters+=1
                else:
                    if lletra !=' ':
                    	numeroCaracters+=1
                        MapDeLletres.get(lletra)
                        MapDeLletres[lletra]=1

            if longXpar.has_key(len(paraula)):
                longXpar[len(paraula)] += 1
            else:
                longXpar.get(len(paraula))
                longXpar[len(paraula)] = 1

            if MapDeParaules.has_key(paraula):

                MapDeParaules[paraula]=MapDeParaules[paraula]+ 1
            else:
                MapDeParaules.get(paraula)
                MapDeParaules[paraula]=1
            numpar+=1
        numeroLinies+=1
        numeroParaules = numeroParaules + len(linia.split(" "))
        paraulesXlinia.append([lin, numpar])
        lin+=1

#Transformacio de les dades
vecLongPar = []
for key, value in longXpar.iteritems():
    vecLongPar.append([key,value])

llet = []
for key, value in MapDeLletres.iteritems():
	llet.append([key,value])

par = []
for key, value in MapDeParaules.iteritems():
	par.append([key,value])

# Exposicio de les dades
mitpar = numeroParaules/numeroLinies
mitjanaCaracXPar = numeroCaracters/numeroParaules

fitxerOut.write("1. Numero de linies del document: "+str(numeroLinies)+ '\n\n')

fitxerOut.write("2. Numero de paraules del document: "+str(numeroParaules)+ '\n\n')

fitxerOut.write("3. Mitjana de paraules per linia: "+str(mitpar)+ '\n\n')

histogram = pygal.Bar(title='Paraules per linia')
for x in paraulesXlinia:
    histogram.add("Linia " + str(x[0]),x[1])
histogram.render_in_browser()


fitxerOut.write("4. Promig de lletres en el document: \n")

for key, value in MapDeLletres.iteritems():
    fitxerOut.write("Caracter: " + str(key) + " Valor: " + str(value) + "\n")

histLletres = pygal.Pie(title='Caracters utilitzats en el text')

for val in llet:
	k = val[0]
	v = val[1]
	histLletres.add(str(k), v)
histLletres.render_in_browser()

fitxerOut.write("\n5. Promig de longitud de paraules en el document: " + str(mitjanaCaracXPar)+ "\n")

histLong = pygal.HoritzontalBar(title='Longitud de les paraules')
for val in vecLongPar:
    k = val[0]
    v = val[1]
    histLong.add(str(k), v)
histLong.render_in_browser()

fitxerOut.write("\n6. Promig de paraules en el document:\n")
for key, value in MapDeParaules.iteritems():
    fitxerOut.write("Paraula: " + str(key) + "\t\tValor: " + str(value) + "\n")

d = path.dirname(__file__)

text = open(path.join(d, nom + '.txt')).read()

wc = WordCloud(background_color="white", max_words=2000)

wc.generate(text)

wc.to_file(path.join(d, nom + ".OUT.png"))

fitxerOut.close()
fitxer.close()