# Mon projet C

## Description

Ce projet est une application C qui utilise Python pour générer des graphiques à partir de données stockées dans une base de données MySQL.

## Installation

1. Installer pip : `sudo apt install python3-pip`
2. Installer python-dev : `sudo apt-get install python-dev python3.10-dev`
3. Installer matplotlib : `pip install matplotlib`
4. Installer mysql-connector : `pip install mysql-connector-python`
5. Recréer la base de données pour l'adapter au projet grâce à `./event.sql`

## Exécution

1. Compiler le code : `gcc *.c -I/usr/include/python3.10 `\`mysql_config --cflags --libs\`` -lpython3.10 -o main`
2. Exécuter le programme : `./main`

Le programme va se connecter à la base de données MySQL, récupérer les données nécessaires, les traiter en utilisant Python pour générer les graphiques, et les afficher à l'utilisateur.

Assurez-vous que la base de données MySQL est en cours d'exécution avant d'exécuter le programme.
