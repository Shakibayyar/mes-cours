#!/bin/bash
read -p "Température en Celsius ? " CELSIUS
let FAHRENHEIT=9*CELSIUS/5+32
echo "Une température de ${CELSIUS} °C est équivalente à ${FAHRENHEIT}°F"
