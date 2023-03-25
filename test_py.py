import matplotlib.pyplot as plt
import mysql.connector

# Connexion à la base de données
cnx = mysql.connector.connect(user='zeus', password='8716taho',
                              host='localhost',
                              database='event')
cursor = cnx.cursor()

# Exécution de la requête
query = ("SELECT plat.label, COUNT(reserver.use_id) AS nombre_commandes "
         "FROM plat "
         "LEFT JOIN reserver ON plat.id = reserver.plat_id "
         "GROUP BY plat.id "
         "ORDER BY nombre_commandes DESC")
cursor.execute(query)

# Récupération des résultats
noms_plats = []
nombre_commandes = []
couleurs = ['r', 'g', 'b', 'y', 'm', 'c']  # liste des couleurs
for i, (nom, nombre) in enumerate(cursor):
    noms_plats.append(nom)
    nombre_commandes.append(nombre)
    couleur = couleurs[i % len(couleurs)]  # récupère la couleur correspondante
    plt.bar(nom, nombre, color=couleur)

# Fermeture de la connexion à la base de données
cursor.close()
cnx.close()

# Affichage de l'histogramme
plt.xticks(rotation=90)
plt.show()
