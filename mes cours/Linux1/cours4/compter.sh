#!/bin/bash
dossier=$1
nombre=$(ls -l"$dossier" | wc -l)
echo "Le dossier $dossier contient $nombre éléments"
