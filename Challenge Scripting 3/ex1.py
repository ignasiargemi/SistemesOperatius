import pygal

nom = raw_input("Digam el nom del fitxer d'entrada:\n(Sense Extencio)\n")
fitxer = open(nom + ".log", "r")
opcio = raw_input("Digues quina opcio vols executar:\n(-l,-m,-t)\n")
if opcio != "-l" and opcio != "-m" and opcio != "-t":
    print "Error: opcio no valida.\n"
else:
    if opcio == "-t" or opcio == "-m":
        vulner = raw_input("Digues de quina vulnerabilitat vols tenir informacio:\n(Ha de ser en majuscules)\n")
    llegirTipus = False
    llegirPais = False
    vulnerabilitats = {}
    paisos = {}
    paisAct = ""

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
                        if vulnerabilitats[paraula].has_key(paisAct):
                            vulnerabilitats[paraula][paisAct] += 1
                        else:
                            vulnerabilitats[paraula].get(paisAct)
                            vulnerabilitats[paraula][paisAct] = 1
                    else:
                        vulnerabilitats.get(paraula)
                        vulnerabilitats[paraula] = {}
                        vulnerabilitats[paraula].get(paisAct)
                        vulnerabilitats[paraula][paisAct] = 1
                    llegirTipus = False

                if llegirPais:
                    paisAct = paraula.lower()
                    llegirPais = False

                if paraula == "country":
                    llegirPais = True

                if paraula == "type":
                    llegirTipus = True

    if opcio == "-l":
        print("Llista de vulnerabilitats:")
        for key, value in vulnerabilitats.iteritems():
            print(str(key))

    elif opcio == "-t":
        if vulnerabilitats.has_key(vulner):
            fitxerOUT = open("taula.html", "w")
            fitxerOUT.write("<!DOCTYPE html>\n")
            fitxerOUT.write("<html>\n")
            fitxerOUT.write("  <head>\n")
            fitxerOUT.write("Taula de vulnerabilitats\n")
            fitxerOUT.write("  </head>\n")
            fitxerOUT.write("  <body>\n")      
            fitxerOUT.write("<table width=""100%"" border=""2"" cellpadding=""1"" cellspacing=""1"" bordercolor=""#000000"" style=""border-collapse:collapse;"">\n")
            fitxerOUT.write("<tr>")
            fitxerOUT.write("<th>Pais</th><th>Atacs</th>")        
            fitxerOUT.write("</tr>\n")
            for key, value in vulnerabilitats[vulner].iteritems():
                fitxerOUT.write("<tr>")
                fitxerOUT.write("<td>"+ key +"</td><td> "+ str(value) +"</td>")        
                fitxerOUT.write("</tr>\n")
            fitxerOUT.write("</table>\n")
            fitxerOUT.write("  </body>\n")
            fitxerOUT.close()
        else:
            print("No existeix un vulnerabilitat amb nom " +  vulner)


    else:
        if vulnerabilitats.has_key(vulner):
            worldmap_chart = pygal.maps.world.World()
            worldmap_chart.title = 'Mapamundi dels atacs'
            worldmap_chart.add("Paisos", vulnerabilitats[vulner])
            worldmap_chart.render_in_browser()
        else:
            print("No existeix un vulnerabilitat amb nom " +  vulner)
fitxer.close()
