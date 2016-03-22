Documentació

Aquí s'explica el funcionament i la sortida dels scripts Part1.py i Part2.py
La sortida consta d'un fitxer de text on hi trobem el resultat de 6 operacions que es detallaran posteriorment, i el contingut d'aquestes variarà en funció del text que li diguem que volem analitzar.
En el Part1.py es llegeix sempre l'arxiu textObama.txt i en el Part2.py, l'usuari introdueix el nom de l'arxiu que es vol analitzar. L'usuari ha d'escollir un fitxer .txt. Quan el programa li demani l'arxiu només ha de posar el nom sense extenció.

El codi dels dos scripts és gairebé igual, només canvia la part d'escollir fitxer d'entrada.
Just al començament es fan els dos imports principals: pygal i wordcloud, que són necessaris per a poder fer els diagrames i el núvol de paraules. Hi han dos imports més que es fan per a poder emmagatzemar el wordcloud en el directori on estan guardats els scripts.

Seguidament es detallen les operacions que s'han mencionat previament:

1. Operació 1
Retorna el número de linies que té el document.

2. Operació 2
Retorna el número de paraules que té el document.

3. Operació 3
Retorna una llista i un diagrama de barres verticals amb el número de paraules per linia.

4. Operació 4
Retorna una llista i un diagrama de 'formatgets' amb tots els caràcters i el número de vegades que han aparegut en el text i el número d'aparicions.

5. Operació 5
Retorna la mitjana del número de caràcters tenen totes les paraules del text. També retorna un diagrama de barres horitzontal amb les vegades que tenim paraules de cadascuna de les mides.

6. Operació 6
Retorna la mitjana de la freqüència de les paraules del document. A més a més, retorna un núvol de paraules amb les paraules més freqüents en el text.

Sortida dels diagrames

Un cop hem executat l'script, el navegador s'obra automàticament i allà es poden els diagrames de les operacions 3, 4 i 5.
El wordcloud es guarda al mateix directori des d'on s'excuten els scripts i és una imatge .png.