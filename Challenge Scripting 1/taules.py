def system_interface():

    cont=0
    linia = f.readline()
    linia = linia.rstrip()

    while linia != "config system interface":
        linia = f.readline()
        linia = linia.rstrip()
        cont +=1

    bol = False

    x1 = ["Interficie","Alias","Address","DHCPRelay"]
    y = []
    y.append(x1)

    items = ["-" for i in range(4)]

    entrado = False

    while linia != "end":
        linia = linia.replace('"','').strip()

        paraules = linia.split()

        #print linia
        if linia == "next":
            entrado = False

        for paraula in paraules:

            if bol and entrado == False:
                items[0] = paraula  #edit
                entrado = True

            elif paraula == "edit":
                bol = True

            if bol == False:

                for paraula in paraules:

                    if bol:
                        items[1] = paraula

                    elif paraula == "alias":
                        bol = True

                if bol == False:

                    for paraula in paraules:

                        if bol:
                            items[2] = paraula

                        elif paraula == "ip":
                            bol = True

                        if bol == False:

                            for paraula in paraules:

                                if bol:
                                    items[3] = paraula

                                elif paraula == "dhcp-relay-ip":
                                    bol = True

                                if bol == False:

                                    for paraula in paraules:

                                        if paraula == "next":

                                            x1 = [items[0],items[1], items[2], items[3]]

                                            y.append(x1)

                                            items = ["-" for i in range(4)]

        bol = False

        linia = f.readline()

        #print linia
        linia = linia.rstrip()

    f2.write("<h2>Interficies</h2>")
    print("\n\nCONFIG SYSTEM INTERFACE\n")

    printTable(y)

    f2.write("\n")

def router_static():

    cont=0

    linia = f.readline()
    linia = linia.rstrip()

    while linia != "config router static":
        linia = f.readline()
        linia = linia.rstrip()
        cont +=1

    bol = False

    x1 = ["GW","Interficie","Prioritat"]
    y = []
    y.append(x1)

    items = ["-" for i in range(3)]

    entrado = False

    while linia != "end":

        #entrado = False
        #print linia

        linia = linia.replace('"','').strip()

        paraules = linia.split()

        if linia == "next":
            entrado = False

        for paraula in paraules:

            if bol and entrado == False:
                items[0] = paraula  #Gateway
                entrado = True

            elif paraula == "gateway":
                bol = True

            if bol == False:

                for paraula in paraules:

                    if bol:
                        items[1] = paraula

                    elif paraula == "device":
                        bol = True

                if bol == False:

                    for paraula in paraules:

                        if bol:
                            items[2] = paraula  #prioridad ej 10

                        elif paraula == "priority":
                            bol = True

                        if bol == False:

                            for paraula in paraules:

                                if paraula == "next":

                                    x1 = [items[0],items[1], items[2]]

                                    y.append(x1)

                                    items = ["-" for i in range(3)]

        bol = False

        linia = f.readline()

        #print linia

        linia = linia.rstrip()

    f2.write("<h2>Taula d'enrutament</h2>")
    print("\n\nCONFIG ROUTER STATIC\n")

    printTable(y)

    f2.write("\n")

def printTable (tbl, borderHorizontal = '-', borderVertical = '|', borderCross = '+', inicioLinia = '<tr>', finalLinia = '</tr>', inicioCelda ='<td>', finalCelda = '</td>'):
    cols = [list(x) for x in zip(*tbl)]
    lengths = [max(map(len, map(str, col))) for col in cols]
    f = borderVertical + borderVertical.join(' {:>%d} ' % l for l in lengths) + borderVertical
    s = borderCross + borderCross.join(borderHorizontal * (l+2) for l in lengths) + borderCross

    fW = inicioCelda + inicioCelda.join(' {:>%d} </td> ' % l for l in lengths)
    sW = finalLinia + inicioLinia

    print(s)
    f2.write("<table border='1'><tr>")
    for row in tbl:
        print(f.format(*row))
        print(s)

        f2.write(fW.format(*row))
        f2.write("\n")
        f2.write(sW)
        f2.write("\n")
    f2.write("</tr></table>")


#print "freq"
f = open("FW_1238.conf", "r")
f2 = open("sortida.html", "w")

"""
for linea in f:
    if linea == "end":
        print "joder"
        break
    print linea



for linea in f.readlines()[10:]:
    print linea
"""
system_interface()
router_static()
