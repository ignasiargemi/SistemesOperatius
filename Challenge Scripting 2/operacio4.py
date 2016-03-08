# OPERACIO 4: Frequencia de caracters en el document

try:
	fitxer = open("textObama.txt")
except:
	print "El archivo no existe"

fitxerOut = open("obama.OUT.txt","w")

def contar(paraules, ignorarMaj=1):
    frecuencia={}
    for paraula in paraules:
        if ignorarMaj: paraula.lower() #passa les majuscules a minuscules
        for lletra in paraula:
            try:
                frecuencia[lletra]+=1 #conta totes les lletres
            except KeyError:
                frecuencia[lletra]=1
    return frecuencia
