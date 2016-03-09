# OPERACIO 1: Numero de linies del document: NUM
#OPERACIO 2: Numero de paraules del document:NUM
#OPERACIO 3: Numero promig de paraules per linea del document:NUM
#Generar un histograma, amb les vegades que tenim numero de paraules per linies del document,
# indicant quantes linies tenen cada numero
#Finalment haurem de triar una forma grafica de representar aquest histograma

import pygal

def contParaules(palabra):
	words = palabra.split(" ")
	return len(words)#devuelve numero elementos de la lista

def main():
	
	contlinies=0
	contParaula=0
	string=""
	arraylinies=[]
	arrayParaules=[]
	arrayFreqParaules=[]
	
	try:
		fitxer=open("textObama.txt")
	except:
		print "El archivo no existe"
	
	fitxerOut=open("obama.OUT.txt","w")

	for i,line in enumerate(fitxer):
		contlinies+=1
		contParaula=contParaula + contParaules(line)
		arrayParaules.append(contParaules(line))
		arraylinies.append(i)
		



	fitxerOut.write("Numero de linies del document: %i \n" % contlinies)
	fitxerOut.write("Numero de paraules del document %i \n" %contParaula)
	fitxerOut.write("Numero promig de paraules per linea del document es: %i \n" % (contParaula/contlinies))

	#Create a histogram
	hist = pygal.Bar() # Then create a bar graph object
	hist.add('Words', arrayParaules) # Add some values
	
	hist.render_to_file('Histograma.svg') # Save the svg to a file


	fitxer.close()
	fitxerOut.close()

main()
