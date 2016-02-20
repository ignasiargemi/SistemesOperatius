# OPERACIO 1: Numero de linies del document: NUM
#OPERACIO 2: Numero de paraules del document:NUM
#OPERACIO 3: Numero promig de paraules per linea del document:NUM

def contParaules(palabra):
	words = palabra.split(" ")
	return len(words)#devuelve numero elementos de la lista

def main():
	
	contlinies=0
	contParaula=0
	string=""
	#mmmm....NO SE SI VAN LAS EXCPTION, IGNASI TE ACUERDAS QUE NO BAJARON PUNTOS POR ESTO?O NO?
	try:
		fitxer=open("textObama.txt")
	except:
		print "El archivo no existe"
	
	fitxerOut=open("obama.OUT.txt","w")

	for line in fitxer:
		contlinies+=1
		contParaula=contParaula + contParaules(line)


	fitxerOut.write("Numero de linies del document: %i \n" % contlinies)
	fitxerOut.write("Numero de paraules del document %i \n" %contParaula)
	fitxerOut.write("Numero promig de paraules per linea del document es: %i \n" % (contParaula/contlinies))


	fitxer.close()
	fitxerOut.close()

main()
	


