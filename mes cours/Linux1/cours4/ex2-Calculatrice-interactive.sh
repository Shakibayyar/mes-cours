#!/bin/bash


nombre1=$1
operation=$2
Deuxieme2=$3

if [ "$operation" = "+" ]; then
    resultat=$((nombre1 + Deuxieme2))
elif [ "$operation" = "-" ]; then
      resultat=$((nombre1 - Deuxieme2))
elif [ "$operation" = "x" ]; then
      resultat=$((nombre1 * Deuxieme2))
elif [ "$operation" = "/" ]; then
    if [ "$Deuxième2" -eq 0 ]; then
       echo "Erreur : Division par zéro impossible."
    exit 1
fi 
    resultat=$((nombre1 / Deuxieme2))
else 
    echo "Opération non reconnue."
    exit 1 
fi
    echo "$nombre1 $operation $Deuxieme2 = $resultat"