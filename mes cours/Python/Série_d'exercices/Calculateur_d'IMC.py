poids = float(input("entrez votre poids en Kg :"))
taille = float(input("Entrez votre taille en cm :"))
taille_m = taille / 100
imc = poids / (taille_m * taille_m)
print ("Votre IMC est :", imc)