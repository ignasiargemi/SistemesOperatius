# OPERACIO 1: Numero de linies del document: NUM
#OPERACIO 2: Numero de paraules del document:NUM

def main():
	
	contlinies=0
	contParaules=0

	fitxer=open("textObama.txt")
	fitxerOut=open("obama.OUT.txt","w")

	for line in fitxer:
		contlinies+=1
		palabras = line.split(" ")
		contParaules=contParaules + len(palabras)

	fitxerOut.write("Numero de linies del document: %i \n" % contlinies)
	fitxerOut.write("Numero de paraules del document %i \n" %contParaules)

	fitxer.close()
	fitxerOut.close()



main()
	


