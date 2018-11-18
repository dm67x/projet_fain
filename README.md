# Projet Fondements et Algorithmique de l'Imagerie Num�rique

## Comment compiler le projet

Pour compiler le projet il faut avoir au sein de son syst�me CMake d'install�. Apr�s lancer la commande dans le repertoire du projet : `cmake-gui .` pour lancer la fen�tre CMake.
Puis de cliquer sur le bouton "Configurer" et enfin choisir le compilateur voulu (bien s�r il faut �galement avoir les librairies freeglut et opengl dans le syst�me cible avec le compilateur cible).
Sur Linux choisir "Unix Makefiles". Enfin, il suffit de cliquer sur g�n�rer pour que CMake g�n�re le Makefile associ�, qui sera dans le repertoire sp�cifi� pour la "build".
Maintenant il suffit de faire un `make` pour que le projet soit compil�. 

## Exemples

Lancer le programme g�n�rer sans arguments (par d�faut fen�tre de 800 * 800 pixels).

![](images/exemple.gif)

### Insertion de sommets

Appuyer sur "i" pour passer en mode insertion.

![](images/insertion_sommet.gif)

### Selection d'un sommet

Appuyer sur "v" pour passer en mode sommet (vertex). Puis selectionner avec la souris le sommet voulu.

![](images/selection_sommet.gif)

### Suppression d'un sommet

Appuyer sur "v" pour passer en mode sommet (vertex). Puis selectionner avec la souris le sommet voulu. Et enfin appuyer sur "Del" ("Suppr") pour supprimer le sommet.

![](images/suppression_sommet.gif)

### Bouger un sommet

Appuyer sur "v" pour passer en mode sommet (vertex). Puis selectionner avec la souris le sommet voulu. Et enfin utiliser les touches haut, bas, gauche, droite du clavier pour bouger le sommet.

![](images/bouger_sommet.gif)

### Fermer le polygone

Appuyer sur "c" pour ouvrir/fermer le polygone. Le nombre de sommet doit �tre sup�rieur � 2.

![](images/fermer_ouvrir_polygone.gif)

### Remplissage

Appuyer sur "f" pour remplir le polygone (ferm�).

![](images/remplissage.gif)

### Selection de l'ar�te

Appuyer sur "e" pour passer en mode ar�te (edge). Puis utiliser les touches "PageUp" et "PageDown" pour selectionner une ar�te.

![](images/selection_arete.gif)

### Division de l'ar�te

Appuyer sur "e" pour passer en mode ar�te (edge). Puis selectionner une ar�te et enfin appuyer sur le bouton du milieu de la souris pour subdiviser l'ar�te.

![](images/division_arete.gif)

## Ce qui a �t� fait

- [x] Afficher une ligne bris�e (bresenham)
- [x] Dessin � la souris
- [x] Remplissage scan-line
- [x] Ins�rer et supprimer des sommets
- [x] S�lection par clavier
- [ ] S�lection par souris
	* [x] S�lection du sommet le plus proche
	* [ ] S�lection de l'ar�te la plus proche