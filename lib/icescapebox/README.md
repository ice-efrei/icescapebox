# ICEscapeBox Librairie

Utilisation :
- Appeler la fonction `begin()` une fois que l'Arduino est prêt à reçevoir la seed
- Appeler la fonction `won()` quand le jeu est gagné
- Appeler la fonction `lost()` quand le jeu a perdu une vie
- Appeler la fonction `update()` si le jeu prévoit de reçevoir des messages. La fonction renvoie le nombre de bytes lus depuis le master dans le buffer. **La taille maximale du buffer est de 16 bytes !!**
- Appeler la fonction `write()` pour envoyer un message au master
- Appeler la fonction `read()` pour lire les bytes dans le buffer. **La taille maximale du buffer est de 16 bytes !!**
