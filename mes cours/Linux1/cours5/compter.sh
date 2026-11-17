#!/bin/bash
ls "$1" | grep .| wc -l 
echo "Le dossier $1 contient $1 $(ls "$1" | grep . | wc -l) éléments"

