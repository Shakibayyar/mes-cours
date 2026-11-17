Mois = input("Saissez le nom d'un mois dans l'année!")
match Mois:
    case "Janvier"|"Mars"|"Mai"|"Juillet"|"Août"|"Octubtr"|"Décembre":
       print(f"Le mois de {Mois} a 31 jours")
    case "Avril"|"Juin"|"Septembre"|"Novembre":
        print(f"Le mois de {Mois} a 30 jours")
    case "Février":
        print(f"Le mois de {Mois} a 28 ou 29 jours")
    case _:
        print("Saisie incorrecte")