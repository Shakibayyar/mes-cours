
# Introduction au web

 A la fin de cette fiche, vous serez capable de créer votre première page web à l’aide
d’un éditeur de texte adapté à cet effet.

## 1.1 Les langages du web

Bien qu’il existe une grande quantité de langages de programmation utilisés sur l’internet,
nous n’en étudierons que deux :

**XHTML** :Le rôle du XHTML est de décrire la structure du texte. Il permet d’indiquer au navi-
gateur que cette partie est le titre d’un chapitre, celle-ci un paragraphe, une autre
un tableau, ...

**CSS** : Le CSS gère la présentation des différents éléments logiques. Les instructions CSS
permettent par exemple, de définir que les titres doivent être centrés sur la page et
écrit en rouge, les paragraphes doivent être ajusté et de couleur bleue, etc.

En séparant la présentation du contenu il est possible de répartir le travail de rédaction
et de mise en forme entre plusieurs personnes. Il est aussi possible d’adapter la présenta-
tion selon le mode d’affichage (écran, imprimante, SmartPhone) sans devoir toucher au
contenu.


## 1.2 Les éditeurs
La description des pages web se fait à l’aide de texte brut. N’importe quel éditeur adapté
à la programmation peut être utilisé pour coder une page web. Voici quelques exemples
d’éditeurs :
– Bloc note de Windows
– NotePad++ *(http ://notepad-plus-plus.org/fr/ )*
– Aptana *(http ://www.aptana.com/ )*
– NetBeans *(http ://fr.netbeans.org/ )*
Dans le cadre de ce cours, nous allons utiliser **NetBeans**


## 1.3 Les balises
Les balises sont des éléments de textes qui ne sont pas affichés mais qui indiquent aux
navigateurs comment ils doivent présenter le texte. Elles se repèrent facilement car elles
sont encadrées par des chevrons < et >.  
Les balises vont par paire pour encadrer un bloc de texte. pour différentier les balises ou-
vrantes et fermantes, le symbole divisé par est ajouté devant la balise fermante. Exemple 

 ```<html>
<title> Le titre de la page </title>
<P> La balise p encadre un paragraphe </p>
<body> Le corps de la page </body>
```

Certaines balises servent à insérer des éléments dans un document (sauts de lignes, images,
...). Pour simplifier l’écriture, XHTML permet de combiner les balises d’ouverture et de fer-
meture en 1 seule. Ce type de balise se reconnaît par le symbole "diviser par" placé après
le nom du marqueur. Par exemple, la balise pour forcer le retour à la ligne s’écrit <br />.
Il est parfaitement possible de placer des balises dans d’autres balises. L’image suivante
montre comment faire :




## 1.4 Les attributs
Les attributs sont des informations qui donnent des précisions sur une balise. Ils se placent
dans la balise ouvrante. La syntaxe correcte pour un attribut est : nom_attribut="valeur"
(la valeur est toujours placée entre guillemets). Les attributs sont séparés les uns des autres
par des espace.
1 ```<img src="logo.png"> alt= " pas_d'image??"/>
2 <table width= "66%"> cellspacing="0"> ...</table>```


## 1.5 Les commentaires
XHTML définit aussi une balise spéciale qui permet d’ajouter des commentaires à la page
. Ils sont utiles aux développeurs
1 ```<!--Ceci est un commentaire -->
2 <! Voicu zb cinnebtaure sur plusieurs lignes -->```

Faites attention à ne pas imbriquer plusieurs commentaires les uns dans les autres. Le ré-
sultats n’est pas toujours celui qu’on croit !

## 1.6 La page minimale
L’extrait de code suivant montere la page XHTML de base que vous allez utiliser tout au
long de ce cours
```<!DOCTYPE html PUBLIC "-//W3C//DTD_XHTML_1.1//EN""http://www..w3.org/TR/xhtml111/DTD/xhtml111.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">

<head>
<meta http-equiv="content-type" content=text/html;_charset=UTF-8" />
<title>Titre de la fenêtre<title>
</hedy>

<body>
Le texte qui sera affiché 
</body>

</html>
```

# Exercices

## 2.1 Utilisation de NetBeans

Si votre machine n’est pas équipée de NetBeans, téléchargez et installez la dernière ver-
sion sur votre disque dur externe (ou clé USB).

## 2.2 Créer une page XHTML

Créez votre première page XHTML à l’aide de NetBeans (projet PHP) et recopiez la struc-
ture qui vous est proposée dans la théorie de cette fiche.