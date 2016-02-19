# OPERACIO 1: Numero de linies del document: NUM

def main():
	
	cont=0

	fitxer=open("textObama.txt")

	fitxerOut=open("obama.OUT.txt","w")

	for line in fitxer:
		cont=cont+1

	fitxerOut.write("Numero de linies del document: %i" % cont)

	fitxer.close()
	fitxerOut.close()


main()
