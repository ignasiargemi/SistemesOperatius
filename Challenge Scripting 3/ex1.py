import pygal


fitxer = open("LAST.log","r")
opcio = raw_input("Digues quina opcio vols executar:\n(-l,-m VULNERABILITAT,-t VULNERABILITAT)\n")
if opcio != "-l" and opcio != "-m VULNERABILITAT" and opcio != "-t VULNERABILITAT":
    print "Error: opcio no valida.\n"
else:
    llegirTipus = False
    vulnerabilitats = {}

    for linia in fitxer.readlines():
        if len(linia)>2:
            paraules = linia.split()
            for paraula in paraules:
                paraula = paraula.replace(':', '')
                paraula = paraula.replace('{', '')
                paraula = paraula.replace('}', '')
                paraula = paraula.replace('[', '')
                paraula = paraula.replace(']', '')
                paraula = paraula.lstrip("u'")
                paraula = paraula.replace("'", '')
                paraula = paraula.replace(',', '')

                if llegirTipus:
                    if vulnerabilitats.has_key(paraula):
                        vulnerabilitats[paraula] += 1
                    else:
                        vulnerabilitats.get(paraula)
                        vulnerabilitats[paraula] = 1
                    llegirTipus = False

                if paraula == "type":
                    llegirTipus = True

    if opcio == "-l":
        print("Llista de vulnerabilitats:")
        for key, value in vulnerabilitats.iteritems():
            print(str(key))

    elif opcio == "-t VULNERABILITAT":
        for key, value in vulnerabilitats.iteritems():
            print("Tipus: " + str(key) + " Numero d'atacs: " + str(value))