import re

def main():	

	with open("FW_1238.conf") as fp:
		sortida=open("fitxerNou.doc","w")
		#part 2.1
		listaComandos=[];
		listaResustado=[];
		
		
		for result in re.findall('config-version=(.*?)-',fp.read(),re.S):
			
			listaComandos.append("Marca-model")
			listaResustado.append(result.rstrip())
			break

		sortida.write(str(listaComandos))	
		sortida.write(str(listaResustado))

		sortida.close()

	fp.close()
main()








