vitesse_max = int(input("Donne la vitesse maximale"))
vitesse = int(input("Donne la vitesse autorisée."))
ecart =  vitesse_max - vitesse
if ecart <= 0:
    print("pas d'amende.")
elif ecart < 5:
    print("Amande : 20 CHF")
elif ecart < 10:
    print("Amende : 60 CHF")
elif ecart < 15:
    print("Amende : 120 CHF")
elif ecart < 20:
    print("Amende : 180 CHF")
elif ecart < 25:
    print ("Amende : 260 CHF")
else:
    print ("Juje")
