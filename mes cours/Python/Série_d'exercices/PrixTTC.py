prixHT = float(input("Entrez le prix HT !"))
tauxTVA= float(input("Entrez ke taux de TVA !"))
prix_ttc = prixHT * (1 + tauxTVA / 100)

print(f"Le prixTTC= {prix_ttc} !")