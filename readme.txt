installer pip: sudo apt install python3-pip
installer python-dev: sudo apt-get install python-dev sudo apt-get install python3.10-dev
installer matplolib:  pip install matplotlib
installer mysql-connector: pip install mysql-connector-python

recréer la base de données pour l'adapter au projet grâce à even.sql

pour exécuter le code: gcc *.c -I/usr/include/python3.10 `mysql_config --cflags --libs` -lpython3.10 -o main 

puis ./main 
