/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Texte.h"
#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"

Texte::Texte(Jeu* jeu) : gpJeu(jeu), vitesse(40), av(0), x(0), y(0), w(0), h(0),
id(0), idsuiv(0), def(false), cadre(false), texte(""), buffer("") {
    lastAnimTime = SDL_GetTicks();
    imageFont = IMG_Load("data/images/texte/font.png");
    SDL_SetColorKey(imageFont,SDL_TRUE,SDL_MapRGB(imageFont->format,0,0,255));
    imageCoeur = IMG_Load("data/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur,SDL_TRUE,SDL_MapRGB(imageCoeur->format,0,0,255));
}

Texte::~Texte() {
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);
}

void Texte::chercheText() {
    ostringstream os;
    int tmp;
    switch (id) {
        case 3  : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = "Has encontrado un cuarto de coraz�n !!!";
            if (tmp<4) buffer = "Con "+os.str()+" mas obtendras un coraz�n adicional !!!";
            else buffer = "Tu numero de coraz�nes acaba de aumentar !!!";
            break;
        case 5 : texte = "Cueva del portal sellado.**Entrada prohibida."; break;
        case 6 : texte = "Templo de Farone**Salve los �rboles, coma castor!!!"; break;
        case 7 : texte = "Has encontrado las botas Pegasus !!! *Manten Shift o pulsa Capslock para correr."; break;
        case 8 : texte = "N : Finca Este"; break;
        case 9 : texte = "O : Lago de Lanayru"; break;
        case 10 : texte = "S : Bosque Prohibido"; break;
        case 11 : texte = "S : Lago de Lanayru"; break;
        case 12 : texte = "N : Hasta el Templo Latoan"; break;
        case 13 : texte = "N : Pueblo de Ruto"; break;
        case 14 : texte = "-Servicio Anti Monstruos hUra�os y Salvajes- (S.A.M.U.S.)**Entrad si no os gustan los monstruos."; break;
        case 15 : texte = "O : Ciudad de Rauru"; break;
        case 16 : texte = "No has aprendido ning�n tema.";
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=17; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=26; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=28; chercheText();break;}
            break;
        case 17 : texte = "- CANCION DE VUELO*- No tocar";
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=19; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=30; chercheText();break;}
            break;
        case 18 : texte = "- Canci�n de Vuelo*- NO TOCAR"; break;
        case 19 : texte = "- CANCION DE VUELO*- Eleg�a al Vac�o*- No tocar";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=22; chercheText();break;}
            break;
        case 20 : texte = "- Canci�n de Vuelo*- ELEGIA AL VACIO*- No tocar"; break;
        case 21 : texte = "- Canci�n de Vuelo*- Eleg�a al Vac�o*- NO TOCAR"; break;
        case 22 : texte = "- CANCION DE VUELO*- Eleg�a al Vac�o*- Canci�n del Esp�ritu*- No tocar"; break;
        case 23 : texte = "- Canci�n de Vuelo*- ELEGIA AL VACIO*- Canci�n del Esp�ritu*- No tocar"; break;
        case 24 : texte = "- Canci�n de Vuelo*- Eleg�a al Vac�o*- CANCION DEL ESPIRITU*- No tocar"; break;
        case 25 : texte = "- Canci�n de Vuelo*- Eleg�a al Vac�o*- Canci�n del Esp�ritu*- NO TOCAR"; break;
        case 26 : texte = "- ELEGIA AL VACIO*- No tocar";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=33; chercheText();break;}
            break;
        case 27 : texte = "- Eleg�a al Vac�o*- NO TOCAR"; break;
        case 28 : texte = "- CANCION DEL ESPIRITU*- No tocar"; break;
        case 29 : texte = "- Canci�n del Esp�ritu*- NO TOCAR"; break;
        case 30 : texte = "- CANCION DE VUELO*- Canci�n del Esp�ritu*- No tocar"; break;
        case 31 : texte = "- Canci�n de Vuelo*- CANCION DEL ESPIRITU*- No tocar"; break;
        case 32 : texte = "- Canci�n de Vuelo*- Canci�n del Esp�ritu*- NO TOCAR"; break;
        case 33 : texte = "- ELEGIA AL VACIO*- Canci�n del Esp�ritu*- No tocar"; break;
        case 34 : texte = "- Eleg�a al Vac�o*- CANCION DEL ESPIRITU*- No tocar"; break;
        case 35 : texte = "- Eleg�a al Vac�o*- Canci�n del Esp�ritu*- NO TOCAR"; break;
        case 36 : texte = "N : Pueblo de Ruto*S : Finca Este"; break;
        case 37 : texte = "S : Pueblo de Ruto*E : Hasta el desierto"; break;
        case 38 : texte = "Entrada de la mina"; break;
        case 39 : texte = "O : Hasta el Templo Latoan*E : Pueblo de Ruto"; break;
        case 40 : texte = "Lo siento, ten�a solo una botella."; break;
        case 41 : texte = "Vendo una botella por 100 rupias, quieres?*               SI ?            no  "; 
            if (gpJeu->getJoueur()->hasBouteille(0)) {id=40; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) idsuiv=44;
            else idsuiv=45;
            break;
        case 42 : texte = "Vendo una botella por 100 rupias, quieres?*               si              NO ?"; idsuiv=43; break;
        case 43 : texte = "Vuelve si cambias de opini�n."; break;
        case 44 : texte = "No tienes bastante!"; break;
        case 45 : texte = "Gracias!"; break;
        case 46 : texte = "Has encontrado una botella vac�a !!!**Podr�s utilizarla para almacenar p�cimas."; break;
        case 47 : texte = "Hay un paso secreto al Oeste del pueblo que lleva al Templo Latoan, pero necesitar�s bombas para cogerlo."; break;
        case 49 :
            if (gpJeu->getJoueur()->getAvancement()>3 && !gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) 
                texte = "Si buscas un balso de bombas, deber�as ir a ver el hombre quien trabaja en la mina, utiliza un mot�n.";
            else texte = "Fuera de aqu� !"; break;
        case 50 : 
            if (gpJeu->getJoueur()->getAvancement()==5 || gpJeu->getJoueur()->getAvancement()==6)
                texte = "El alcalde prohib� el acceso a la mina desde que monstruos salgan de aqu�.";
            else if (gpJeu->getJoueur()->getAvancement()==7)
                texte = "Dices que quiz�s alguien esta bloqueado en la mina? Y que?";
            else if (gpJeu->getJoueur()->getAvancement()==8 || gpJeu->getJoueur()->getAvancement()==9)
                texte = "El alcalde te autoriz� a pasar? Entonces ap�rtate!";
            else texte = "..."; break;
        case 54 : texte = "Bienvenido al pueblo de Ruto.**Y que queda entre nosotros, desconf�a de todo el mundo por aqu�..."; break;
        case 55 : texte = "Este pueblo de fachada pr�spera es en realidad lo m�s pobre de Termina...*Y no podemos contar con el alcalde para que cambia eso..."; break;
        case 56 : texte = "Las turistas que vienen en este pueblo son o perdidos, o totalmente locos.**En lo que me concierne siempre tengo una mapa conmigo."; break;
        case 57 : texte = "S : Hasta la Finca Este*O : Hasta el Templo Latoan*E : Pueblo de Ruto"; break;
        case 58 : texte = "S : Finca Este"; break;
        case 59 : texte = "Templo Latoan"; break;
        case 60 : texte = "E : Tierras olvidadas"; break;
        case 61 : texte = "S : Pueblo de Ruto*O : Muerta segura"; break;
        case 62 : texte = "Oasis m�gico"; break;
        case 63 : texte = "Cueva de la Hada"; break;
        case 64 : texte = "Templo de Din**El poder de las hadas recompensar� a los valientes !"; break;
        case 65 : texte = "                     ???"; break;
        case 66 : texte = "Templo de Lanayru"; break;
        case 67 : texte = "O : Pantano de la bruja"; break;
        case 68 : texte = "E : Bosque prohibido"; break;
        case 69 : texte = "N : Finca Este*O : Hasta la ciudad de Rauru"; break;
        case 70 : texte = "N : Ciudad de Rauru"; break;
        case 71 : texte = "O : Finca Oeste"; break;
        case 72 : texte = "N : Tierras olvidadas*S : Ciudad de Rauru"; break;
        case 73 : texte = "N : Ciudad de Rauru*S : Lago de Lanayru*O : Finca Oeste*E : Finca Este"; break;
        case 74 : texte = "E : Finca Este"; break;
        case 75 : texte = "Lo siento, no tengo nada m�s en dep�sito."; break;
        case 76 : texte = "Vendo un mejor escudo por 250 rupias, quieres ?*               SI ?            no  "; 
            if (gpJeu->getJoueur()->getBouclier()>1) {id=75; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<250) idsuiv=44;
            else idsuiv=45;
            break;
        case 77 : texte = "Vendo un mejor escudo por 250 rupias, quieres ?*               si              NO ?"; idsuiv=43; break;
        case 78 : texte = "Has encontrado un nuevo escudo !!!**Tu defensa aumenta de un punto, resistes mejor a los ataques enemigos !!!"; break;
        case 79 : texte = "Porque soy otra vez yo quien tengo que cuidar estas gallinas ???"; break;
        case 80 : texte = "Me gusta barrer !"; break;
        case 81 : texte = "Rauru es la ciudad la m�s graciosa del pa�s, muchos visitantes llegan cada d�a para admirarla."; break;
        case 82 : texte = "Se dice que un instrumento m�gico se encuentra en alg�n sitio de las tierras de Termina. *Me pregunto si lo ver� un d�a..."; break;
        case 83 : texte = "Has encontrado el instrumento m�gico ???**Esperaba que ser�a un saxo..."; break;
        case 84 : texte = "Mis padres se han perdido."; break;
        case 85 : texte = "Me gusta pasear !"; break;
        case 86 : texte = "S : Ciudad de Rauru*E : Casa encantada"; break;
        case 87 : texte = "Casa encantada**Vengan a enriquecer nuestra colecci�n de almas !"; break;
        case 88 : texte = "E : Hasta el Templo Latoan"; break;
        case 89 : texte = "Templo de Farore**El poder de las hadas recompensar� a los valientes !"; break;
        case 90 : texte = "O : Pueblo de Mido"; break;
        case 91 : texte = "N : Monta�as del destino"; break;
        case 92 : texte = "Templo de Zelda"; break;
        case 93 : texte = "O : Cementerio"; break;
        case 94 : texte = "Secreto del desierto :*Levanta las piedras del p�jaro en el sentido de las agujas del reloj acabando por el ojo para abrir el camino."; break;
        case 95 : texte = "S : Pantano de la bruja"; break;
        case 96 : texte = "E : Ciudad de Rauru"; break;
        case 97 : texte = "N : Finca Oeste*S : Choza de la bruja"; break;
        case 98 : texte = "O : Pueblo de Kasuto*E : Choza de la bruja"; break;
        case 99 : texte = "Choza de las p�cimas**Venid cambiar vuestras rupias por las p�cimas las m�s poderosas del pa�s !!!"; break;
        case 100 : texte = "E : Lago de Lanayru"; break;
        case 101 : texte = "N : Cementerio*S : Pueblo de Kasuto"; break;
        case 102 : texte = "Pueblo de Kasuto**   -- Prihibido a los humanos (vivos) --"; break;
        case 103 : texte = "Truco : Manten Ctrl para mirar alrededor con las flechas del teclado."; break;
        case 104 : texte = "N : Pueblo de Kasuto*E : Pantano de la bruja"; break;
        case 105 : texte = "Coliseo de los monstruos**Venid numerosos !"; break;
        case 106 : texte = "Pareces bastante fuerte, deber�as ir entrenarte en la arena al Sur del pueblo. Dicen que hay un objeto muy �til escondido dentro..."; break;
        case 107 : texte = "Vaya.*Una nueva especie ?**Sabes hablar ?"; break;
        case 108 : texte = "Este pueblo es el ultimo amparo contra la humanidad."; break;
        case 109 : texte = "Hola, soy un monstruo d�bil."; break;
        case 110 : texte = "Atorado ?***Sin embargo la soluci�n no est� tan lejos."; break;
        case 111 : texte = "S : Pueblo de Kasuto"; break;
        case 112 : texte = "Templo de Xanto**Los muertos no hablan..."; break;
        case 113 : texte = "Han probado ya ustedes el martillo sobre los cr�neos?"; break;
        case 114 : texte = "E : Finca Oeste"; break;
        case 115 : texte = "Pueblo de Mido"; break;
        case 116 : texte = "Tienen todos los j�venes de tu edad tan mal gusto para la ropa?"; break;
        case 117 : texte = "Bienvenido al pueblo de Mido, pero no te sientas obligado de quedarte."; break;
        case 118 : texte = "Grrr... pensaba estar por fin en paz aqu�..."; break;
        case 119 : texte = "Solo el vac�o total podr� quitar la piedra."; break;
        case 120 : texte = "Templo de Nayru**El poder de las hadas recompensar� a los valientes !"; break;
        case 121 : texte = "Pesa del destino**Solo el aliado del bueno y del malo atravesar� esta cueva."; break;
        case 122 : texte = "S : Pueblo de Mido"; break;
        case 123 : texte = "Templo de Eldin"; break;
        case 124 : texte = "S : Finca Oeste"; break;
        case 125 : texte = "La fuerza de los titanes recaer� sobre el h�roe legendario..."; break;
        case 126 : texte = "Torre del Destino**H�roe de Hyrule ten cuidado, aqu� reina ahora el vil Ganon, aqu� se jugar� el porvenir del mundo."; break;
        case 127 : texte = "Felicitaciones !**Has conseguido alcanzar la cumbre del monte Planito !"; break;
        case 128 : texte = "No puedes transformarte aqu� !!!"; break;
        case 129 : texte = "No puedes entrar en un pueblo con esta apariencia !!!"; break;
        case 130 : texte = "Link, soy Pit. Te hablo por telepat�a. No debes en ning�n caso transformarte en un pueblo !*Te teletransporto fuera."; break;
        case 131 : texte = "Has encontrado una espada !!!**Pulsa W para atacar o mantiene W para cargar un ataque genial."; break;
        case 132 : texte = "Has encontrado el mapa !!!**Pulsa P para ver el mapa del calabozo."; break;
        case 133 : texte = "Has encontrado la br�jula !!!**Las arcas y el jefe del calabozo se ven ahora sobre el mapa."; break;
        case 134 : texte = "Has encontrado la llave del jefe !!!**Util�zala para llevar a su antro."; break;
        case 135 : texte = "Has encontrado una llave peque�a.**Util�zala para abrir una puerta."; break;
        case 136 : texte = "Has encontrado un nuevo coraz�n !!!**Tu vida m�xima aumenta de un coraz�n !!!"; break;
        case 137 : texte = "Has encontrado un Graal !!!"; break;
        case 138 : texte = "Vine para salvarme ?*Muchas gracias !"; 
            if (gpJeu->getMonde()->regionValue(0)==160*16) {
                if (gpJeu->getJoueur()->getCoffre(1,25)) {id=50; chercheText();break;}
                else idsuiv = 139;}
            if (gpJeu->getMonde()->regionValue(0)==180*16 
                && gpJeu->getMonde()->regionValue(1)==15*16) {
                if (gpJeu->getJoueur()->getCoffre(1,26)) {id=50; chercheText();break;}
                else idsuiv = 140;}
            if (gpJeu->getMonde()->regionValue(0)==180*16 
                && gpJeu->getMonde()->regionValue(1)==45*16) {
                if (gpJeu->getJoueur()->getCoffre(1,27)) {id=50; chercheText();break;}
                else idsuiv = 141;}
            break;
        case 139 : texte = "Cavando galer�as descubrimos esto antro de monstruos..."; idsuiv=142; break;
        case 140 : texte = "Fuimos capturados todos por los monstruos viviendo en estas cavernas."; idsuiv=142; break;
        case 141 : texte = "Nuestro jefe est� abajo, ve a salvarle de prisa!"; idsuiv=142; break;
        case 142 : texte = "Encontr� esto en la mina, toma, podr�a ayudarte!"; break;
        case 143 : 
            if (gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=50; chercheText();break;}
            texte = "Venciste el monstruo de la mina ???*Felicitaciones!!!"; idsuiv=144; break;
        case 144 : texte = "Soy el jefe de los obreros, dices que estabas busc�ndome?"; idsuiv=145; break;
        case 145 : texte = "Toma esta bolsa llena de bombas, deber�a ayudarte."; break;
        case 146 : texte = "Has encontrado la Bolsa de Bombas !!!*Y esta llena !!!*Pulsa ENTER para equiparlas, y despu�s X para poner una."; break;
        case 147 : texte = "Has encontrado los Guantes !!!**Ahora puedes levantar las piedras ligeras pulsando C."; break;
        case 148 : 
            if (gpJeu->getJoueur()->hasObjet(O_ARC)) {id=50; chercheText();break;}
            texte = "Soy el brazo derecho del alcalde, me mand� salvar a su hija...*Pero no pude hacer nada, estos fantasmas son invencibles..."; idsuiv=149; break;
        case 149 : texte = "No te quedes aqu�, no podr�s hacer nada con tus armas actuales..."; idsuiv=150; break;
        case 150 : texte = "Para continuar tu b�squeda, sigue el camino al Oeste de la ciudad. Con este arco podr�s alcanzar la esfera y abrir el camino..."; break;
        case 151 : texte = "Has encontrado el Arco !!!*Ahora puedes atacar a distancia y alcanzar objetos alejados !!!"; break;
        case 152 : 
            if (gpJeu->getJoueur()->getAvancement()>64) {id=153; chercheText();break;}
            texte = "Venciste el vampiro y viniste para salvarme? Muchas gracias! Mi padre es el alcalde de la ciudad, ve a verlo, estoy segura que te recompensar�."; break;
        case 153 : texte = "No te preocupes por mi, puedo volver a casa sin ayuda ahora que el vampiro esta vencido."; break;
        case 154 : 
            if (gpJeu->getJoueur()->getAvancement()==13)
                texte = "Has recibido la autorizaci�n del alcalde ?*Se prudente, los que se aventuran por ah� nunca vuelven...";
            else if (gpJeu->getJoueur()->getAvancement()<13)
                texte = "Orden del alcalde : el acceso a esta regi�n est� prohibido.";
            else texte = "..."; break;
        case 155 : texte = "No puedes huir ahora!"; break;
        case 156 : texte = "Has encontrado el martillo !!!**Ahora puedes aplastar los obst�culos molestos !!!"; break;
        case 157 : texte = "Has encontrado el lanzagarfios !!!**Ahora puedes atravesar los precipicios !!!"; break;
        case 158 : texte = "Hall del Coliseo"; break;
        case 159 : texte = "Arena 1"; break;
        case 160 : texte = "Arena 2"; break;
        case 161 : texte = "Arena 3"; break;
        case 162 : texte = "Arena 4"; break;
        case 163 : texte = "Entrega de premios"; break;
        case 164 : texte = "Arena especial**Venid a probar el premio especial !!!"; break;
        case 165 : texte = "Has encontrado las Aletas !!!**Ahora puedes nadar y atravesar superficies de agua !!!"; break;
        case 166 : texte = "Has encontrado una Loriga !!!**Tu defensa aumenta de un punto !!!"; break;
        case 167 : texte = "Has encontrado una mejor Loriga !!!   *Tu defensa aumenta de un punto !!!"; break;
        case 168 : texte = "Jijijijiji !!!*Felicitaciones Link ! Has conseguido deshacerte de la maldici�n. Y al mismo tiempo me has liberado !!!"; idsuiv=169; break;
        case 169 : texte = "Para recompensarte de tus esfuerzos no te matar� hoy, tengo una misi�n m�s importante."; idsuiv=170; break;
        case 170 : texte = "Si quieres pararme, une te a mi en el templo de los muertos si tienes la valor de hacerlo.*Adi�s ! Jijijijiji !!!"; break;
        case 171 : texte = "Link, soy Zelda, te hablo por telepat�a. Estoy con Pit, �nete a nosotros de prisa, tenemos un gran problema."; break;
        case 172 : texte = "Buenos d�as Link, te esperaba.**Me llamo Pit, fui encargado de la vigilancia de esta cueva por la princesa Zelda."; idsuiv=173; break;
        case 173 : texte = "Me avis� de tu llegada y me pidi� que te ayude.*Mi casa est� justo aqu�, estaremos mejor para hablar, s�gueme."; break;
        case 174 : texte = "Pit te pidi� que no salgas del bosque."; break;
        case 175 : texte = "Has encontrado la Varilla de Fuego !!!**Ahora puedes lanzar potentes bolas de fuego !!!"; break;
        case 176 : 
            if ((gpJeu->getZone() == 23 && gpJeu->getJoueur()->getCoffre(8,19))
            || (gpJeu->getZone() == 24 && gpJeu->getJoueur()->getCoffre(9,24))
            || (gpJeu->getZone() == 25 && gpJeu->getJoueur()->getCoffre(10,21))) {
                id=50; chercheText();break;}
            texte = "Te esperaba Link.*Transmito la potencia de la diosa a tu espada para restituir el poder de la Espada Maestra."; break;
        case 177 : 
            if (gpJeu->getJoueur()->getEpee()==5) {id=178; chercheText();break;}
            texte = "La potencia de la Espada Maestra aumenta ! **Ve de prisa al pr�ximo templo !"; break;
        case 178 : texte = "La Espada Maestra ha alcanzado su potencia m�xima !!!  *Incluso Oni-Link no deber�a resistir a su hoja !!!"; break;
        case 179 : texte = "Has encontrado la Varilla de Hielo !!!**Ahora puedes helar lo que quieras !!!"; break;
        case 180 : texte = "Has encontrado un nuevo escudo !!!**Tu defensa aumenta, resistes ahora mejor a los ataques !!!"; break;
        case 181 : texte = "Link, soy Zelda, te hablo por telepat�a. No entres en este calabozo si no estas perfectamente preparado, es sin duda una trampa de Oni-Link."; break;
        case 182 : texte = "As� has venido ?*Quiz�s quieres morir, va a ser un placer ayudarte.*Jijijijiji !!!"; break;
        case 183 : texte = "La esencia de Oni-Link fue encerrada en la M�scara del Esp�ritu !!!*Lo has hecho !!!"; break;
        case 184 : texte = "Grrrr !!! No lo puedo creer, has vencido a Oni-Link ??? Impresionante...*Me imagino que no contabas con verme, sin embargo estamos en el mundo de los muertos."; idsuiv=185; break;
        case 185 : texte = "Oni-Link me ha dado la energ�a que necesitaba para resucitarme, entonces estoy de vuelta m�s pronto que lo pensaba.*Gwajajajajaja !!!"; idsuiv=186; break;
        case 186 : texte = "A prop�sito, quiz�s te preguntas de donde viene Oni-Link ? Es muy simple, la ultima vez quer�a estar seguro que nunca m�s vendr�as a molestar mis planos, entonces utilic�"; idsuiv=187; break;
        case 187 : texte = "la Trifuerza para cambiarte en un monstruo de los m�os. Pero no hab�a bastantes tinieblas en tu coraz�n, y esta transformaci�n no fue fulgurante..."; idsuiv=188; break;
        case 188 : texte = "Basta ya, tengo muchos proyectos...*Ser�a un gran placer acabar contigo, pero no veo la utilidad..."; idsuiv=189; break;
        case 189 : texte = "Para que lo sepas : solo las criaturas de las tinieblas pueden escaparse de aqu�.*Entonces adi�s! Gwajajajajaja !!!"; break;
        case 190 : 
            if (!gpJeu->getJoueur()->getOni()) {id=184; chercheText();break;}
            texte = "Onilito ? Cuando viene este caf� ???*Que ??? Eres tu Link ???"; idsuiv=184; break;
        case 191 : texte = "                Mundo de los Muertos"; break;
        case 192 : texte = "Link, soy Zelda, te hablo por telepat�a. Es horrible, Ganon esta de vuelta !!!"; idsuiv=193; break;
        case 193 : texte = "Ha restaurado su ej�rcito, que se esta preparando a atacar Rauru!*Todav�a puedes pararlos, corre a interceptarlos en la finca Oeste!"; break;
        case 194 : texte = "Has encontrado el gran Arco de las Hadas !!!**Ahora tiras flechas de una potencia extraordinaria !!!"; break;
        case 195 : texte = "Has encontrado la Trifuerza !!!"; break;
        
        case 197 : texte = "Tutorial : pulsa ESPACIO para hablar, leer o abrir una arca, y ENTER para pasar los textos en la pantalla."; break;
        case 198 : texte = "Pulsa C para levantar un objeto ligero."; break;
        case 199 : texte = "Quieres gravar tu juego ?**                     ? SI ?*                      no  "; break;
        case 200 : texte = "Quieres gravar tu juego ?**                       si  *                    ? NO ?"; break;
        case 201 : texte = "                    Nivel 1 :                                                                                 Templo de Farone"; break;
        case 202 : texte = "                    Nivel 2 :                                                                                   Mina de Ruto"; break;
        case 203 : texte = "                    Nivel 3 :                                                                                 Templo de Latoan"; break;
        case 204 : 
            if (gpJeu->getJoueur()->getEpee()>=2) 
                texte = "                    Nivel 9 :                                                                                  Casa embrujada";
            else texte = "                    Nivel 4 :                                                                                  Casa embrujada"; break;
        case 205 : texte = "                    Nivel 5 :                                                                                 Templo de Eldin"; break;
        case 206 : texte = "                    Nivel 6 :                                                                             Coliseo de los Monstruos"; break;
        case 207 : texte = "                    Nivel 7 :                                                                                Templo de Lanayru"; break;
        case 208 : texte = "                    Nivel 8 :                                                                                 Templo de Zelda"; break;
        case 209 : texte = "                   Nivel 10 :                                                                                 Templo de Din"; break;
        case 210 : texte = "                   Nivel 11 :                                                                                 Templo de Nayru"; break;
        case 211 : texte = "                   Nivel 12 :                                                                                 Templo de Farore"; break;
        case 212 : 
            if (gpJeu->getJoueur()->getX()>14*320) {id=191; chercheText();break;}
            texte = "                   Nivel 13 :                                                                                 Templo de Xanto"; break;
        case 213 : texte = "                   Nivel ? :                                                                                  Templo secreto"; break;
        case 214 : texte = "                 Nivel Final :                                                                                Torre del Destino"; break;
        case 215 :texte = "               Ya estas cansado ?               ?                   SEGUIR                  ?                  Grabar y dejar                                Dejar sin grabar              "; break;
        case 216 :texte = "               Ya estas cansado ?                                   Seguir                     ?               GRABAR Y DEJAR              ?                 Dejar sin grabar              "; break;
        case 217 :texte = "               Ya estas cansado ?                                   Seguir                                     Grabar y dejar                 ?              DEJAR SIN GRABAR             ?"; break;
        case 218 : texte = "Despu�s de la derrota de Ganon y la desaparici�n de la Trifuerza, la leyenda deja creer que la paz dur�... *Pero cada leyenda oculta una oscura realidad..."; idsuiv=402; break;
        case 220 : texte = "Si... Es por ah�... *Casi estamos..."; idsuiv=221; break;
        case 221 : texte = "Lo siento mucho que no puedas llevar armas... Pero entiendes... Corres peligro de transformarte en cada momento...*Seria demasiado peligroso..."; idsuiv=222; break;
        case 222 : texte = "Ya estamos! Es aqu�!*No te muevas, activo el portal...**Estas listo ?"; break;
        case 223 : texte = "Liberado de la maldici�n de Ganon, Link pudo volver a Hyrule sin riesgo.**La Trifuerza, la Espada Maestra, as� como el Ocarina fueron entregados a la familia real de Hyrule, mientras que la M�scara de Oni-Link fue confiada a las hadas para ser escondida m�s all� del tiempo y del espacio...**El portal que conduc�a a Termina fue sellado por la princesa Zelda y por Pit, para nunca m�s ser abierto, y este horrible cap�tulo fue borrado de la leyenda..."; idsuiv=224; break;
        case 224 : texte = "El pueblo de Hyrule nunca supo lo que ocurro en las misteriosas comarcas de Termina, tampoco que el temible Ganon ya preparaba su regreso...**Pero lo que nadie ignoraba, fue el regreso en Hyrule de su h�roe, qui�n estar�a siempre all� para defender el Reino frente a la tinieblas."; break;
        case 225 : texte = "Has encontrado un escudo !!!**Tu defensa aumenta de un punto, te resistes mejor a los ataques enemigos !!!"; break;
        case 226 : texte = "Pit est� esper�ndote en la casa aqu� al lado."; break;
        case 227 : 
            if (gpJeu->getJoueur()->getMagieMax()>32) texte = "...";
            else texte = "Felicitaciones Link, has conseguido encontrarme. Para recompensarte, voy a doblar la capacidad de tu reserva de magia."; break;
        case 228 : texte = "La capacidad de tu reserva de magia ha doblado !!!"; break;
        case 229 : texte = "Has encontrado el Ocarina del Tiempo !!!**Su potencia es tal que para el tiempo cuando soplas dentro !"; break;
        case 230 : texte = "Has encontrado la L�mpara !!!**Ahora puedes hacer surgir llamas!!!"; break;
        case 231 : texte = "Has encontrado la M�scara del Esp�ritu !!!**Una extra�a aura se desprende de el..."; break;
        case 232 : 
            if (gpJeu->getJoueur()->getTutoriel()==3) {id=233; chercheText();break;}
            gpJeu->getJoueur()->setTutoriel(3);
            texte = "Felicitaciones, me has encontrado !!!**Soy la gorda hada del desierto, organizo colectas de rupias !"; idsuiv=233; break;
        case 233 : texte = "Dame 100 rupias ahora !!!**               SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) {idsuiv=236; break;}
            if (gpJeu->getJoueur()->getFlecheMax()==70 && gpJeu->getJoueur()->getBombeMax()==30) {idsuiv=239; break;}
            if (gpJeu->getJoueur()->getFlecheMax()==70) {idsuiv=237; break;}
            if (gpJeu->getJoueur()->getBombeMax()==30) {idsuiv=238; break;}
            idsuiv = 237 + (rand()%2); break;
        case 234 : texte = "Dame 100 rupias ahora !!!**               si              NO ?"; idsuiv=235; break;
        case 235 : texte = "Me haces perder el tiempo, fuera !"; break;
        case 236 : texte = "No tienes bastante!!!*Me haces perder el tiempo, fuera !"; break;
        case 237 : texte = "Aumento la cantidad m�xima de bombas que puedes transportar, gracias a qui�n ???"; break;
        case 238 : texte = "Aumento la cantidad m�xima de flechas que puedes transportar, gracias a qui�n ???"; break;
        case 239 : texte = "Tengo bastante rupias, desaparece !"; break;
        case 240 : texte = "Has encontrado los Guantes de Oro !!!**Ahora puedes levantar las piedras pesadas pulsando C."; break;
        case 241 : texte = "Solo dejar� pasar a las criaturas mal�ficas."; 
            if (gpJeu->getJoueur()->getOni()) idsuiv=243; break;
        case 242 : texte = "Solo dejar� pasar a las criaturas beneficiosas."; 
            if (!gpJeu->getJoueur()->getOni()) idsuiv=244; break;
        case 243 : texte = "Pareces mal�fico...*Vale puedes pasar!"; break;
        case 244 : texte = "Pareces beneficioso...*Vale puedes pasar!"; break;
        case 245 : 
            if (gpJeu->getJoueur()->getAvancement()==2) {id=250; chercheText();break;}
            texte = "Debe de preguntarte donde estas.*Aqu� est� Termina, y no necesitas saber m�s al respecto..."; idsuiv=246; break;
        case 246 : texte = "Es una tierra secreta que habr�a tenido que quedarlo, la princesa Zelda nunca habr�a tenido que enviarte aqu�..."; idsuiv=247;  break;
        case 247 : texte = "M�s precisamente estas en el bosque de Termina. En este bosque hay un templo, y en este templo hay un objeto sagrado capaz de conjurar cualquier maleficio..."; idsuiv=248; break;
        case 248 : texte = "Encuentra este objeto, luego vuelve a verme.*Abrir� el portal una ultima vez para tu regreso."; idsuiv=249; break;
        case 249 : texte = "Ultima cosa, no salgas del bosque para nada del mundo ! Tu presencia aqu� es secreta, adem�s, en tu estado eres una amenaza para todos los que te cruzas con..."; idsuiv=250; break;
        case 250 : texte = "Buena suerte Link!"; break;
        case 251 : 
            if (gpJeu->getJoueur()->getAvancement()==3) {id=250; chercheText();break;}
            texte = "Que ??? El graal no ha conseguido librarte de la maldici�n ??? Es... impensable..."; idsuiv=252; break;
        case 252 : texte = "Esta maldici�n debe de ser poderos�sima... Pero si miras bien queda esperanza..."; idsuiv=253; break;
        case 253 : texte = "El graal te surti� efecto, lo has notado.*De ahora en adelante tardas m�s para transformarte."; idsuiv=254; break;
        case 254 : texte = "Pero es de doble filo... Porque cuando estas transformado, lo quedas m�s tiempo..."; idsuiv=255; break;
        case 255 : texte = "Esc�chame Link, quedan aun 4 otros graals en los templos de Termina...*Se dice que los 5 juntos tienen tanto poder como la Trifuerza ella misma."; idsuiv=256; break;
        case 256 : texte = "Gracias al graal que has encontrado, eres ya un poco menos peligroso, entonces te autorizo a explorar Termina libremente."; idsuiv=257; break;
        case 257 : texte = "Avent�rate fuera del bosque, busca y encuentra los graals, y ser�s salvado.*Pero no deber�s en ning�n caso ir en un pueblo si estas transformado."; idsuiv=258; break;
        case 258 : texte = "Toma esta mapa, seguro que te ayudar�...*Buena suerte!"; break;
        case 259 : 
            if (gpJeu->getJoueur()->getEpee()>=2) {id=271; chercheText();break;}
            texte = "Encantada de verte sano y salvo Link ! Ahora que no corres el riesgo de transformarte, pens� que apreciar�as de tener esto..."; break;
        case 260 : texte = "Has encontrado la Espada Maestra!!!**Su incre�ble potencia parece palpable !!!"; break;
        case 261 : texte = "Por desgracia la necesitar�s...*Oni-Link fue liberado...*Lo pod�amos ver antes..."; idsuiv=262; break;
        case 262 : texte = "Por cada nuevo graal encontrado, la frecuencia de tus transformaciones disminu�a, pero la duraci�n de vida de Oni-Link aumentaba..."; idsuiv=263; break;
        case 263 : texte = "Adem�s, el comportamiento de Oni-Link me extra�a...*Con su naturaleza destructiva hubiera tenido que atacar un pueblo..."; idsuiv=264; break;
        case 264 : texte = "Deber�a alegrarme, pero tengo miedo de saber que el tiene intereses m�s importantes no es por nada una buena noticia..."; idsuiv=265; break;
        case 265 : texte = "Sin embargo, hemos establecido un plan de acci�n para vencerlo. Esc�chame con mucha atenci�n..."; idsuiv=266; break;
        case 266 : texte = "La Espada Maestra es una arma temible, pero no ser� suficiente contra Oni-Link...*...de momento..."; idsuiv=267; break;
        case 267 : texte = "Hay 3 templos secretos escondidos en Termina. En estos templos se encuentran hadas cuyos poderes aumentaran el poder de tu espada. Encu�ntralas todas."; idsuiv=268; break;
        case 268 : texte = "Entonces estar�s en pie de igualdad con Oni-Link.*Sin embargo, Oni-Link es solo energ�a y no puede ser vencido..."; idsuiv=269; break;
        case 269 : texte = "La M�scara del Esp�ritu te permitir� de encerarlo para siempre. Para eso, tendr�s que encontrar esta m�scara, encontrar el Ocarina m�gico y encontrar la melod�a que lo enfermar�..."; idsuiv=270; break;
        case 270 : texte = "Tu b�squeda solo empieza..."; break;
        case 271 : texte = "Encuentra las 3 hadas, la m�scara, el Ocarina, y la canci�n del esp�ritu, y luego ve a enfrentarte a Oni-Link!"; break;
        case 272 : 
            if (gpJeu->getJoueur()->getEpee()<2) {id=50; chercheText();break;}
            texte = "Como lo sabes, la Espada Maestra puede vencer a los fantasmas, reflejar los ataques m�gicos, y destruir las barreras m�gicas...*Util�zala bien..."; break;
        case 273 : texte = "No hay tiempo que perder!*Ve ahora mismo a la finca Oeste para interceptar el ej�rcito de Ganon!"; break;
        case 274 : texte = "Date prisa Link, que esperas ?*Navidad ???"; idsuiv=275; break;
        case 275 : texte = "Eh... Porque me hablas de mi ?*Estoy... pues... protegiendo a la princesa, esto!*Gracias a quien te crees que no fue raptada esta vez ? D�melo ?"; break;
        case 276 : 
            if (gpJeu->getJoueur()->getAvancement()==69) {id=282; chercheText();break;}
            texte = "Link... hay una cosa que tendr�a que decirte desde el principio...*Este mundo, Termina..."; idsuiv=277; break;
        case 277 : texte = "Este mundo es muy reciente, fue fabricado en su totalidad por la Trifuerza y por un deseo... La gente, sus recuerdos y sus historias as� fueron fabricados..."; idsuiv=278; break;
        case 278 : texte = "Si... Lo adivin�, soy yo quien ped� a la Trifuerza crear este mundo... Es un mundo pensado para contener todo lo que podr�amos necesitar."; idsuiv=279; break;
        case 279 : texte = "Encontraste los graals, Oni-Link encontr� su amo, y Ganon encontr�...*...la Trifuerza..."; idsuiv=280; break;
        case 280 : texte = "Cre� este mundo para servir de escondite para la Trifuerza, pero Ganon la encontr� una vez m�s..."; idsuiv=281; break;
        case 281 : texte = "Link! Ese pa�s y esa gente fueron creados, pero ahora son reales de verdad! Si no hacemos nada, este mundo se parecer� pronto al ex-mundo de las tinieblas!"; idsuiv=282; break;
        case 282 : texte = "Lo dejo por tu cuenta una vez m�s, Link, salva este mundo!"; break;
        case 283 : 
            texte = "Bienvenida en la casa de estudio de monstruos de todo estilo!"; 
            if (gpJeu->getJoueur()->getOni()) {idsuiv=290; break;}
            if (gpJeu->getJoueur()->hasObjet(O_ENCYCL)) {
                if (gpJeu->getJoueur()->getEpee()>1 
                && gpJeu->getJoueur()->hasObjet(O_ENCYCL)==1) {
                    gpJeu->getJoueur()->trouveObjet(O_ENCYCL,2);
                    idsuiv=294; break;
                }
                if (gpJeu->getJoueur()->getEnnemi(19)
                && gpJeu->getJoueur()->getEnnemi(24)
                && gpJeu->getJoueur()->getEnnemi(35)
                && gpJeu->getJoueur()->hasObjet(O_ENCYCL)!=3) {
                    gpJeu->getJoueur()->trouveObjet(O_ENCYCL,3);
                    idsuiv=296; break;
                }
                if (gpJeu->getJoueur()->nbEnnemis()==62) {idsuiv=297; break;}
                if (gpJeu->getJoueur()->getSolde()>0) {idsuiv=291; break;}
            }
            else {idsuiv=284; gpJeu->getJoueur()->trouveObjet(O_ENCYCL);}
            break;
        case 284 : texte = "Te acuerdas de mi ? Me ayudaste un mont�n en Hyrule.*Eh... Te preguntas como he llegado a Termina ? Eh... no importa!"; idsuiv=285; break;
        case 285 : texte = "Este inmenso mundo est� lleno de monstruos, no pod�a perderme el viaje!"; idsuiv=286; break;
        case 286 : texte = "Entonces voy a catalogar cada monstruo en una nueva enciclopedia!**Con tu ayuda, por supuesto."; idsuiv=287; break;
        case 287 : texte = "No tengo m�s cuartos de coraz�n, ahora el dinero es mi moneda m�s cotizada.*Te pagar� un buen precio por cada nuevo monstruo a�adido en la enciclopedia."; idsuiv=288; break;
        case 288 : texte = "Pasa a verme cuando quieras para recibir tus beneficios. Si no puedes transportar todo, conservar� el excedente para ti."; idsuiv=289; break;
        case 289 : texte = "Basta con matar a los monstruos para que sean a�adidos.*Puedes consultar la enciclopedia pulsando M!"; break;
        case 290 : 
            texte = "Vaya... que raro eres...";
            if (gpJeu->getJoueur()->getEnnemi(75) 
            || !gpJeu->getJoueur()->hasObjet(O_ENCYCL)) break;
            texte += "*Te a�ado en la enciclopedia!!!"; break;
        case 291 : 
            os << gpJeu->getJoueur()->getSolde();
            texte = "Te debo " + os.str() + " rupias.";
            idsuiv=292; break;
        case 292 : texte = "Quieres tu dinero ahora ?**              SI ?            no  "; break;
        case 293 : texte = "Quieres tu dinero ahora ?**              si              NO ?"; break;
        case 294 : texte = "Tengo una noticia para ti ! Parece que los monstruos que hab�as vencido en Hyrule han sido misteriosamente resucitados ! Se dice que pasean en las comarcas de Termina..."; idsuiv=295; break;
        case 295 : texte = "Son 3.*Si los matas, te ofrecer� un precio... especial..."; break;
        case 296 : texte = "Has vencido a los 3 monstruos raros ???*...*Tu recompensa te espera abajo..."; break;
        case 297 : texte = "Has vencido todos los monstruos...*Es incre�ble..."; break;
        case 298 : texte = "Hola Link, como est�n tus bombas ?"; break;
        case 299 : texte = "No tengo m�s precio que poner en juego, lo siento."; break;
        case 300 : texte = "Una de estas arcas contiene un cuarto de coraz�n, quieres probar tu fortuna por 10 rupias ?*Podr�s abrir solo uno, vale ?*              SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; break;
        case 301 : texte = "Una de estas arcas contiene un cuarto de coraz�n, quieres probar tu fortuna por 10 rupias ?*Podr�s abrir solo uno, vale ?*              si              NO ?"; break;
        case 302 : texte = "Elige un arca."; break;
        case 303 : texte = "Hey! Hay que pagar para abrir una de mis arcas!!!"; break;
        case 304 : texte = "Has perdido! Este arca esta vac�a."; break;
        case 305 : 
            if (gpJeu->getJoueur()->getAsile()==2) {id=342; chercheText(); break;}
            texte = "Que quiere de beber ?"; break;
        case 306 : texte = "Estas buscando al hombre que trabaja en la mina ? Nadie le ha visto desde que han cerrado la mina... Quiz�s todav�a esta dentro..."; break;
        case 307 : texte = "Este saloon era muy frecuentado...*...anta�o..."; break;
        case 308 : texte = "YO soy el alcalde de este pueblo y NO quiero hablar contigo!"; break;
        case 309 : texte = "Dices que quiz�s alguien esta encerrado en la mina ?**... ... ..."; 
            if (gpJeu->getJoueur()->getAvancement()==8) {id=308; chercheText();} 
            else idsuiv=310; break;
        case 310 : texte = "Vale, dame 10 rupias y te autorizo el acceso a la mina. Ok ?*              SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; 
            else idsuiv=312; break;
        case 311 : texte = "Vale, dame 10 rupias y te autorizo el acceso a la mina. Ok ?*              si              NO ?"; break;
        case 312 : texte = "Trato hecho, ve a hablar al guardia, te dejar� pasar..."; break;
        case 313 : texte = "Un coraz�n por 5 rupias, vale ?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getVie() == gpJeu->getJoueur()->getVieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=44; break;
        case 314 : texte = "Un coraz�n por 5 rupias, vale ?**             si              NO ?"; break;
        case 315 : texte = "No necesitas esto ahora."; break;
        case 316 : texte = "Un peque�o frasco de magia por 15 rupias, vale ?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=44; break;
        case 317 : texte = "Un peque�o frasco de magia por 15 rupias, vale ?**              si              NO ?"; break;
        case 318 : texte = "Un grande frasco de magia por 25 rupias, vale ?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<25) idsuiv=44; break;
        case 319 : texte = "Un grande frasco de magia por 25 rupias, vale ?**              si              NO ?"; break;
        case 320 : texte = "Elige lo que quieras.*"; break;
        case 321 : texte = "10 flechas por 20 rupias, vale ?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()
            || !gpJeu->getJoueur()->hasObjet(O_ARC)) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=44; break;
        case 322 : texte = "10 flechas por 20 rupias, vale ?**              si             NO ?"; break;
        case 323 : texte = "5 bombas por 30 rupias, vale ?**              SI ?            no  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=325; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=44; break;
        case 324 : texte = "5 bombas por 30 rupias, vale ?**              si              NO ?"; break;
        case 325 : texte = "Necesitas un bolso de bombas para comprar esto."; break;
        case 326 : texte = "Vuelve cuando tengas una botella vac�a  y te vender� p�cimas."; break;
        case 327 : texte = "Las p�cimas rojas devuelven energ�a mientras que las p�cimas verdes rellenan magia."; 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=326; chercheText(); break;}
            idsuiv=328; break;
        case 328 : texte = "Que quieres ?*                ? p�cima ROJA ?*                ? p�cima verde ?*                ?     nada     ?"; idsuiv=331; break;
        case 329 : texte = "Que quieres ?*                ? p�cima roja ?*                ? p�cima VERDE ?*                ?     nada     ?"; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=315;
            idsuiv=333; break;
        case 330 : texte = "Que quieres ?*                ? p�cima roja ?*                ? p�cima verde ?*                ?     NADA     ?"; break;
        case 331 : texte = "Una p�cima roja por 60 rubis ?**              SI ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=44; break;
        case 332 : texte = "Una p�cima roja por 60 rubis ?**              si              NO ?"; break;
        case 333 : texte = "Una p�cima verde por 40 rubis ?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=44; break;
        case 334 : texte = "Una p�cima verde por 40 rubis ?**              si              NO ?"; break;
        case 335 : texte = "Has encontrado una p�cima roja !!!**B�bela para restaurar toda tu energ�a !!!"; break;
        case 336 : texte = "Has encontrado una p�cima verde !!!**B�bela para restaurar toda tu magia!!!"; break;
        case 337 : texte = "Has encontrado una p�cima azul !!!**B�bela para restaurar tu energ�a y tu magia!!!"; break;
        case 338 : texte = "ME ACOJO ENSAGRADO !!!!!!!!"; break;
        case 339 : texte = "Ah tu tambi�n... las gallinas ? Hic!*Terribles estos bichos verdad ?... Hic!"; break;
        case 340 : 
            if (gpJeu->getJoueur()->getAsile()==2) {id=339; chercheText(); break;}
            if (gpJeu->getJoueur()->hasCristal(3)) {id=341; chercheText(); break;}
            texte = "Era pescador hace tiempo... Hic!*Pero desde que LO vi... Hic!*Este terrible monstruo... Hic!*En el lago... Hic!"; break;
        case 341 : texte = "Has vencido el monstruo del lago ???*... ... ...*De todos modos temo el agua... Hic!*(prefiero el vino) Hic!"; break;
        case 342 : texte = "Ja! Ja! Ja!"; break;
        case 343 : 
            if (gpJeu->getJoueur()->getAvancement()==11) {id=344; chercheText(); break;}
            if (gpJeu->getJoueur()->getAsile()==3) {id=347; chercheText(); break;}
            if (gpJeu->getJoueur()->getRaplaplat()) {id=348; chercheText(); break;}
            texte = "Hola! Yo s� todo sobre lo que se dice en la ciudad, ven a verme si necesitas informaciones."; break;
        case 344 : 
            if (gpJeu->getJoueur()->getAvancement()!=11) {id=343; chercheText(); break;}
            texte = "Quieres saber porque el alcalde es tan silencioso ?*Vale, pero no te he dicho nada, ok ?"; idsuiv=345; break;
        case 345 : texte = "Este ciudad tiene un horrible secreto...*Cada noche, chicas son raptadas, y nunca les vemos de nuevo. Ni siquiera me atrevo a ir a pasear..."; idsuiv=346; break;
        case 346 : texte = "La noche pasada, seg�n los rumores, ser�a la hija del alcalde quien habr�a desaparecido..."; break;
        case 347 : 
            if (gpJeu->getJoueur()->getRaplaplat()) idsuiv=348;
            texte = "Hola, Se�or-que-teme-las-gallinas!*Ji! Ji! Ji!"; break;
        case 348 : texte = "Se dice que habr�as escalado el monte Planito ? Felicitaciones! Ji! Ji! Ji!"; break;
        case 349 : 
            if (gpJeu->getJoueur()->getAvancement()==13) {id=50; chercheText(); break;}
            texte = "Es... estas al corriente por mi hija ?*Es horrible... Mi querida hija..."; idsuiv=350;break;
        case 350 : texte = "Seg�n la investigaci�n que llevo desde el principio de estos acontecimientos, las chicas raptadas son llevadas en la casa antigua al Norte de la ciudad..."; idsuiv=351; break;
        case 351 : texte = "Ya he mandado la guardia ah�, pero nadie volvi�..."; idsuiv=352; break;
        case 352 : texte = "Entonces esta ma�ana, cuando descubr� que mi hija ya no estaba aqu�, supliqu� mi secuaz de ir a buscarla... Es un combatiente excepcional, pero es anormalmente lento..."; idsuiv=353; break;
        case 353 : texte = "Pareces un combatiente tambi�n, puedes ir a ver lo qu� ocurre ah� ?*Ser�s muy bien recompensado si salvas a mi hija."; idsuiv=354; break;
        case 354 : texte = "Vete al guardia al Noroeste de la ciudad, te dejar� pasar."; break;
        case 355 : 
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=358; chercheText(); break;}
            texte = "Mi hija me ha contado todo, te debo much�simo!!!"; idsuiv=356; break;
        case 356 : texte = "Esc�chame atentamente, voy a aprenderte un canto que se transmite en mi familia de generaci�n en generaci�n :*La Eleg�a al Vac�o"; break;
        case 357 : texte = "Has aprendido la Eleg�a al Vac�o!!!**Utiliza el Ocarina para tocarla !"; break;
        case 358 : texte = "La Eleg�a al Vac�o tiene misteriosos poderes...*...Creo."; break;
        case 359 : texte = "Buenos d�as se�or-mi-salvador!"; break;
        case 360 : 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=326; chercheText(); break;}
            texte = "Una p�cima azul por 160 rupias ?*No te decepcionar�...*              SI ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=44; break;
        case 361 : texte = "Una p�cima azul por 160 rupias ?*No te decepcionar�...*              si              NO ?"; break;
        case 362 : 
            if (gpJeu->getJoueur()->hasObjet(O_GRAPPIN)) {id=364; chercheText(); break;}
            texte = "Hola, no solemos ver a un monstruo tan poderoso en el pueblo, es un gran honor..."; idsuiv=363; break;
        case 363 : texte = "Deber�as ir a divertirte en el coliseo al suroeste del pueblo, hay un precio interesante que ganar..."; break;
        case 364 : texte = "Has ganado el precio del Coliseo ?*Impresionante..."; break;
        case 365 : texte = "Si crees que eres el monstruo el m�s aterrador de Termina, es que tomas tus sue�os por la realidad pobre amigo m�o..."; idsuiv=366; break;
        case 366 : texte = "Palabra de honor, el monstruo del lago es con diferencia el m�s terror�fico de los monstruos, sobre todo te aconsejo que no procures enfrentarte a el."; break;
        case 367 : texte = "El coliseo al sur de aqu� es el principal divertimiento del pueblo.*El objetivo es de ir lo m�s lejos que puedes antes de ser matado."; idsuiv=368; break;
        case 368 : texte = "Pero es siempre muy dif�cil de encontrar a voluntarios, entonces el jefe fue obligado de poner dentro un objeto de gran valor."; break;
        case 369 : 
            texte = "Quieres escuchar mi historia por 10 rupias ?**              SI ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; break;
        case 370 : texte = "Quieres escuchar mi historia por 10 rupias ?**              si              NO ?"; break;
        case 371 : texte = "Seg�n el jefe, al Norte de aqu� est� el templo de Xanto, tambi�n conocido bajo el nombre del templo de los muertos..."; idsuiv=372; break;
        case 372 : texte = "Este templo seria un paso del mundo de los vivos hasta el mundo de los muertos... Pero para ir al mundo de los muertos, hay que atravesar un laberinto infranqueable..."; idsuiv=373; break;
        case 373 : texte = "P�game otra vez si quieres que repita."; break;
        case 374 : 
            if (gpJeu->getJoueur()->hasObjet(O_MASQUE)==1) {id=376; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_MASQUE)==2) {id=380; chercheText(); break;}
            texte = "Estas buscando la M�scara del Esp�ritu ?*... F�jate..."; idsuiv=375; break;
        case 375 : texte = "No, no s� donde esta, pero s� como utilizarla.*Vuelve a verme si lo encuentras y podr� ayudarte."; break;
        case 376 : 
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=379; chercheText(); break;}
            texte = "Has encontrado la M�scara del Esp�ritu ??? *...*Entonces esc�chame bien, voy a aprenderte como utilizarla."; idsuiv=377; break;
        case 377 : texte = "En presencia de un esp�ritu debilitado, tendr�s que tocar la Canci�n del Esp�ritu con tu ocarina.*Escucha la Canci�n del Esp�ritu!"; break;
        case 378 : texte = "Has aprendido la Canci�n del Esp�ritu!!!**Utiliza el Ocarina para tocarla!"; break;
        case 379 : texte = "La M�scara del Esp�ritu solo puede servir una vez, util�zalo adecuadamente..."; break;
        case 380 : texte = "Has encerrado un esp�ritu terriblemente poderoso...*Cuidado que no caiga en malas manos..."; break;
        case 381 : texte = "Nuestro pueblo alberga pocas veces visitantes...*A lo mejor es porque bloqueamos la entrada..."; break;
        case 382 : 
            if (gpJeu->getJoueur()->hasObjet(O_BFEU)) {id=386; chercheText(); break;}
            if (gpJeu->getJoueur()->getAvancement()==66) {id=385; chercheText(); break;}
            texte = "Eres el �nico visitante que he tenido desde que vivo aqu�...*Soy un ex aventurero, era muy listo como buscador de tesoro..."; idsuiv=383;break;
        case 383 : texte = "Un d�a o� la historia del tesoro de la pir�mide, un objeto m�gico...*Pero este desierto caus� mi ruina, nunca pude atravesarlo, es demasiado peligroso..."; idsuiv=384; break;
        case 384 : texte = "Pareces tan decidido como yo en mi juventud... Te propongo un trato..."; idsuiv=385; break;
        case 385 : texte = "Tr�eme el tesoro de la pir�mide, y te ofrecer� mi tesoro el m�s precioso."; break;
        case 386 : 
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=389; chercheText(); break;}
            texte = "Has encontrado el tesoro ???*Una varilla de fuego ?*...*..."; idsuiv=387; break;
        case 387 : texte = "Vale... Esta varilla te ser� mucho m�s �til que a mi...*Puedes conservarla...*"; idsuiv=388; break;
        case 388 : texte = "Acepta esta recompensa por haber ense�ado a un hombre viejo el tesoro que busc� toda su vida...*La Canci�n de Vuelo!!!"; break;
        case 389 : texte = "Tocada con un instrumento m�gico, esta canci�n te teletransporta. Esperaba que me permitir�a atravesar el desierto, pero nunca encontr� el instrumento adecuado..."; break;
        case 390 : texte = "Has aprendido la Canci�n de Vuelo!!!**Utiliza el Ocarina para tocarla!"; break;
        case 391 : texte = "Link! Soy Pit!!!*Que estas haciendo ???*Date prisa de ir a la finca oeste !!!"; break;
        case 392 : texte = "Link, soy Zelda, felicitaciones!!!*Rauru est� en seguridad, por un rato...*Va a la Torre del Destino  en la cumbre de la monta�a y para a Ganon!"; break;
        case 393 : texte = "Tutorial : cuando el indicador de nivel de ira est� lleno, te transformas en Oni-Link.*Tu alcance y tu fuerza aumentan mientras que tu defensa disminuye."; idsuiv=394; break;
        case 394 : texte = "En Oni-Link, no puedes utilizar los objetos equipables, pero puedes teletransportarte en la entrada cuando estas en un calabozo pulsando T."; idsuiv=395; break;
        case 395 : texte = "Por cada enemigo vencido por Oni-Link, tu indicador de nivel disminuye. Cuando esta vac�o, Link recupera su forma inicial."; break;
        case 396 : texte = "Jefe de proyecto, dise�ador y programador :                                                                  Vincent Jouillat"; break;
        case 397 : texte = "Guionista y traductora :                                                                                                      Lobal�z"; break;
        case 398 : texte = "Ayuda con los Grafismos :                                                                                           Harvestland"; break;
        case 399 : texte = "Ayuda con los Grafismos :                                                                                         Sol�ne Jouillat"; break;
        case 400 : texte = "Ilustrador :                                                                                                    Raiden"; break;
        case 401 : texte = "Has encontrado el mapa de Termina !!!**Pulsa P cuando estas fuera para mirarlo."; break;
        case 402 : texte = "La leyenda olvida que despu�s de estos acontecimientos su h�roe fue presa de una terrible maldici�n..."; idsuiv=403; break;
        case 403 : texte = "D�a a d�a, Link se transformaba en un monstruo con un poder destructor incontrolable nombrado Oni-Link..."; idsuiv=404; break;
        case 404 : texte = "Exiliado de Hyrule, Link pidi� consejo a la Princesa Zelda."; idsuiv=405; break;
        case 405 : texte = "Ella le indic� su ultima esperanza : un portal hasta un mondo secreto..."; break;
        case 406 : texte = "Juego gravado."; break;
        case 407 : texte = "No necesitas beber esta p�cima ahora."; break;
        case 408 : texte = "AYUDA : Pulsa F1 para consultar la ayuda."; break;
        case 409 : texte = "Grrrr... Como has podido escaparte del mundo de los muertos y llegar aqu� ???"; idsuiv=410; break;
        case 410 : texte = "Porque te empe�as en venir a enfrentarme ? *Aunque me venzas siempre resucitar�."; idsuiv=411; break;
        case 411 : texte = "Tu b�squeda es vana, abandona toda esperanza! **Let's rock, baby!"; break;
    }
    
    
}

void Texte::affiche(SDL_Surface* gpScreen, std::string s, int a, int b) {
    for (int i = 0; i < (int)s.length(); i++) {
        afficheLettre(gpScreen, s.at(i),a,b);
        a+=6;
    }
}

void Texte::draw(SDL_Surface* gpScreen) {
    
    if (cadre) drawCadre(gpScreen);
    
    if (id==3 && texte == "Has encontrado un cuarto de coraz�n !!!") {
        SDL_Rect src; SDL_Rect dst;
        src.x=16*(gpJeu->getJoueur()->nbQuarts()%4);
        if(src.x==0)src.x=16*4;
        src.y=0; src.w=16; src.h=16; dst.x=160-8; dst.y=120-8+16*5;
        SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
    }
    
    int a = x+8; int b = y+8;
    for (int i = 0; i < av; i++) {
        afficheLettre(gpScreen, texte.at(i),a,b);
        a+=6;
        if (a > x+w-16) {a=x+8; b+=16;}
    }
    
    if(SDL_GetTicks() > lastAnimTime + vitesse && def && av < (int)texte.length()) {
        lastAnimTime = SDL_GetTicks();
        do av++;
        while (av < (int)texte.length() && texte.at(av-1) == ' ');
        if (texte.at(av-1) != ' ') gpJeu->getAudio()->playSound(0,1);
    }
}

bool Texte::isFinished() {return (av==(int)texte.length());}

int Texte::getId() {return id;}

void Texte::changeId(int i) {
    id=i; idsuiv=0; buffer="";
    chercheText();
    decoupeText();
    if (av>(int)texte.length()) av=(int)texte.length();
}

void Texte::drawCadre(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=8; src.h=8; src.x = 103; src.y = 100; dst.x = x; dst.y = y;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.y = 109; src.w=8;
    for (int j = 8; j < h-8; j+=16) {
        dst.y = y + j;
        src.x = 103; dst.x = x; src.h=16;
        while (dst.y + src.h > y+h && src.h>0) src.h--;
        if (src.h>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
        src.x = 129; dst.x = x+w-8;
        if (src.h>0)SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.h=8; src.x = 103; src.y = 126; dst.x = x; dst.y = y+h-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

void Texte::setTexte(int idTxt, int vx, int vy, int vw, int vh, bool cadr, bool defil, int vit) {
    if (idTxt == 0) return;
    id = idTxt; 
    idsuiv = 0;
    buffer = "";
    chercheText();
    
    x = vx; y = vy; w = vw; h = vh;
    decoupeText();
        
    def=defil;
    if (def) av = 0;
    else av = texte.length();
    
    cadre = cadr;
    
    vitesse = vit;
}

void Texte::decoupeText() {
    //compte le nombre de caract�res possibles et largeur et en hauteur
    int nbcol = (w-16)/6 -1;
    int nblig = (h-16)/16;
    int tailleMax = nbcol * nblig;
    int taille;
    
    //parcours du texte � afficher; � chaque d�but de mot, 
    //v�rifie que le mot peut tenir sur la ligne
    for (int i = 0; i < (int)texte.length(); i++) {
        
        //supprime les espaces isol�s en d�but de ligne
        if (texte.at(i)==' ' && texte.at(i+1)!=' ' && i%nbcol == 0) texte.erase(i,1);
        //recherche du d�but du prochain mot
        while(texte.at(i)==' ' && i < (int)texte.length()-1) i++;
        
        //saute une ligne si trouve une �toile
        if (texte.at(i)=='*') {
            texte.erase(i,1);//replace(i, 1, " ");
            int nb = (nbcol)-(i%(nbcol));
            for (int j = 0; j < nb; j++) texte.insert(i," ");
            continue;
        }
        
        //si le mot d�passe
        taille = tailleMot(i);
        if ((i%nbcol)+taille>nbcol) {
            if  (i < tailleMax) {
                //si le mot ne tient pas sur une ligne, on le coupe avec des tirets
                if (taille>nbcol) {
                    texte.insert(((i/nbcol)+1)*nbcol-1,"--");
                    i = 1+((i/nbcol)+1)*nbcol;
                }
                //sinon, on ajoute des espaces pour faire commencer le mot � la ligne
                else while((i%nbcol) != 0) {texte.insert(i," "); i++;}
            }
        }
        
    }
    
    // si le texte est trop grand, on le coupe en deux
    if ((int)texte.length() > tailleMax) {
        buffer = texte.substr(tailleMax);
        texte = texte.substr(0, tailleMax);
    }
}

int Texte::tailleMot(int deb) {
    int i = deb;
    int total = 0;
    while (texte.at(i)!=' ') {total++; i++; if (i >= (int)texte.length()) return total;}
    return total;
}

void Texte::afficheLettre(SDL_Surface* gpScreen, char c, int vx, int vy) {
    SDL_Rect src;
    SDL_Rect dst;
    
    int val = (int)c;
    
    dst.x=vx; dst.y=vy;
    src.h=16;src.w=8;
    
    if(val==32) return;
    
    // es
    // �
    if(val==-15) {src.x=164;src.y=68;}
    // �
    if(val==-13) {src.x=164;src.y=103;}
    // �
    if(val==-19) {src.x=164;src.y=52;}
    // �
    if(val==-31) {src.x=164;src.y=84;}
    // �
    if(val==-6) {src.x=164;src.y=151;}
    
    
    // /
    if(val==47) {src.x=52;src.y=151;}
    
    // @ hylien
    if(val==64) {src.x=4;src.y=151;}
            
    // + hylien
    if(val==43) {src.x=20;src.y=151;}
            
    // = hylien
    if(val==61) {src.x=36;src.y=151;}
            
    //minuscules a-z
    if(val>=97 && val<=122) {src.x=4+16*((val-97)%10); src.y=52+16*((val-97)/10);}
            
    //majuscules A-Z
    if(val>=65 && val<=90) {src.x=6+16*((val-65)%10); src.y=2+16*((val-65)/10);}   
    // �
    if(val==-25) {src.x=148;src.y=34;}
    // �
    if(val==-23) {src.x=100;src.y=84;}
    // �
    if(val==-22) {src.x=116;src.y=84;}
    // �
    if(val==-24) {src.x=132;src.y=84;}
    // �
    if(val==-21) {src.x=132;src.y=151;}
    // �
    if(val==-32) {src.x=148;src.y=84;}
    // �
    if(val==-30) {src.x=148;src.y=103;}
    // �
    if(val==-28) {src.x=148;src.y=135;}
    // �
    if(val==-18) {src.x=84;src.y=119;}
    // �
    if(val==-17) {src.x=116;src.y=151;}
    // �
    if(val==-5) {src.x=84;src.y=103;}
    // �
    if(val==-7) {src.x=148;src.y=151;}
    // �
    if(val==-4) {src.x=116;src.y=135;}
    // �
    if(val==-10) {src.x=132;src.y=135;}
    // �
    if(val==-12) {src.x=148;src.y=119;}
            
    //ponctuation
    // -
    if(val==45) {src.x=102;src.y=34;}
    // .
    if(val==46) {src.x=118;src.y=34;}
    // ,
    if(val==44) {src.x=134;src.y=34;}
    // !
    if(val==33) {src.x=3;src.y=135;}
    // ?
    if(val==63) {src.x=19;src.y=135;}
    // (
    if(val==40) {src.x=35;src.y=135;}
    // )
    if(val==41) {src.x=51;src.y=135;}            
    // ' ( avec @ )
    if(val==39) {src.x=67;src.y=135;}
    // :
    if(val==58) {src.x=83;src.y=135;}
    // ... ( avec % )
    if(val==37) {src.x=101;src.y=135;}
    // >
    if(val==62) {src.x=100;src.y=151;}
    // <
    if(val==60) {src.x=84;src.y=151;}
            
    //chiffres            
    if(val>=48 && val<=57) {src.x=3+16*((val-48)%5); src.y=103+16*((val-48)/5);}
    
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

bool Texte::hasNext() {
    return (buffer != "" || idsuiv > 0);
}

bool Texte::suite() {
    if (av < (int)texte.length()) {
        av = texte.length();
        return true;
    }
    if (!hasNext()) {
        gpJeu->getAudio()->playSound(18);
        return gpJeu->finTexte(id);
    }
    if (buffer != "") {
        texte = buffer;
        buffer = "";
    }
    else {
        id = idsuiv;
        idsuiv = 0;
        chercheText();
    }
    decoupeText();
    if (def) av = 0;
    else av = texte.length();
    gpJeu->getAudio()->playSound(17);
    return true;
}
