#!/bin/bash

read -p "Premier nombre ? " NOMBRE1
read -p "Opération (+,-,*,/ ) ? " OPERATION
read -p "Deuxième nombre ? " NOMBRE2

case  "$OPERATION" in 
+) let "RESULTAT = NOMBRE1 + NOMBRE2" ;;
-) let "RESULTAT = NOMBRE1 - NOMBRE2" ;;
\*) let "RESULTAT = NOMBRE1 * NOMBRE2" ;;
/) let "RESULTAT = NOMBRE1 / NOMBRE2" ;;
*) echo "Opération invalide"; exit 1 ;; 

esac 
echo "Résultat : $RESULTAT"
