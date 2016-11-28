# raspberry projet c++ [EPSI]

Ce répo est consituer de toute notre application QTCPServer
* Elle permet de créer le server TCP et prends en charge la gestion du socket
* Recevoir une photo et la décoder depuis la Base64
* Envoyer une socket comprenant la réponse du portier (Oui ou non)
* Une connection avec une base de donnée MYSQL

##Présentation
Un portier se retrouve devant une application qui permettera d'accepter ou non une personne ayant composé un code et pris une photo devant un portillon (simulé par une application sur un raspberry).
Le projet prends en compte deux application (répo disponible sur ce GitHub : raspberry & remote-app-on-raspberry)

##Architecture

Portier Raspberry | projectName = remote-app-on-raspberry | Caméra HD | Carte IO  
Réseau | QTCPServer | QTCPSocket | port 9999    
PC gardien | projectName = raspberry  
