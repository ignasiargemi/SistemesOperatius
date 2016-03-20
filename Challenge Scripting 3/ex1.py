import pygal


fitxer = open("LAST.log","r")
opcio = raw_input("Digues quina opcio vols executar:\n(-l,-m VULNERABILITAT,-t VULNERABILITAT)\n")
if opcio != "-l" and opcio != "-m" and opcio != "-t VULNERABILITAT":
    print "Error: opcio no valida.\n"
else:
    llegirTipus = False
    llegirPais = False
    vulnerabilitats = {}
    paisos = {}

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

                if llegirPais:
                    if paisos.has_key(paraula.lower()):
                        paisos[paraula.lower()] += 1
                    else:
                        paisos.get(paraula.lower())
                        paisos[paraula.lower()] = 1
                    llegirPais = False

                if paraula == "country":
                    llegirPais = True

                if paraula == "type":
                    llegirTipus = True

    if opcio == "-l":
        print("Llista de vulnerabilitats:")
        for key, value in vulnerabilitats.iteritems():
            print(str(key))

    elif opcio == "-t VULNERABILITAT":
        print("Taula de vulnerabilitats:")
        for key, value in vulnerabilitats.iteritems():
            print("Tipus: " + str(key) + "\tNumero d'atacs: " + str(value))

    else:
        worldmap_chart = pygal.maps.world.World()
        worldmap_chart.title = 'Mapamundi dels atacs'
        
        worldmap_chart.add("Paisos", paisos)

        worldmap_chart.render_in_browser()
