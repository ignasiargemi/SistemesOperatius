import pygal
import matplotlib.pyplot as plt
from wordcloud import WordCloud
from os import path
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

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
longXpar = {}
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
            if longXpar.has_key(len(paraula)):
                longXpar[len(paraula)] += 1
            else:
                longXpar.get(len(paraula))
                longXpar[len(paraula)] = 1

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

#Transformacio de les dades
vecLongPar = []
for key, value in longXpar.iteritems():
    vecLongPar.append([key,value])

llet = []
for key, value in diccionari.iteritems():
	llet.append([key,value])

par = []
for key, value in diccionarip.iteritems():
	par.append([key,value])


mitpar = numparaules/numlinies
mitlon = longitud/numparaules
mitjanaCaracXPar = numeroCaracters/numparaules

fitxerOut.write("1. Numero de linies del document: "+str(numlinies)+ '\n\n')

fitxerOut.write("2. Numero de paraules del document: "+str(numparaules)+ '\n\n')

fitxerOut.write("3. Mitjana de paraules per linia: "+str(mitpar)+ '\n\n')

histogram = pygal.Bar(title='Paraules per linia')
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
	histLletres.add(str(k), v)
histLletres.render_in_browser()

fitxerOut.write("\n5. Promig de longitud de paraules en el document: " + str(mitjanaCaracXPar)+ "\n")

histLong = pygal.Bar(title='Longitud de les paraules')
for val in vecLongPar:
    k = val[0]
    v = val[1]
    histLong.add(str(k), v)
histLong.render_in_browser()

fitxerOut.write("\n6. Promig de paraules en el document:\n")
for key, value in diccionarip.iteritems():
    fitxerOut.write("Paraula: " + str(key) + "\t\t\t\tValor: " + str(value) + "\n")

d = path.dirname(__file__)

# Read the whole text.
text = open(path.join(d, 'textObama.txt')).read()

wc = WordCloud(background_color="white", max_words=2000)
# generate word cloud
wc.generate(text)

# store to file
wc.to_file(path.join(d, "obama.png"))

# show
plt.imshow(wc)
plt.axis("off")
plt.show()

fitxer.close()
fitxerOut.close()