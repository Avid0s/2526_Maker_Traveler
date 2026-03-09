# 25-26_Maker_Traveler
Gabriel VIDON\
Projet d'option Maker à l'ENSEA.

# 1 Description du projet

## 1.1 Contexte

J'ai toujours été passioné par la robotique et les systèmes embarqués, c'est pour cela que dans le cadre d'un projet Maker qui devait regrouper le plus de technologies possibles pour apprendre leur fonctionnement. J'ai décidé de travailler sur un projet de voiture téléguidée par connection bluetooth. Pour éviter de devoir créer un système de rotation pour les roues de zero, j'ai décidé d'utiliser des roues holonomes.\ 
Ce système qui deverait toucher à toutes les technologies d'impression 3D, de découpe laser, routage pcb, et toutes les autres vues en cours de Maker.
Mes objectifs sont les suivants :
- Créer un chassis pouvant supporter l'ensemble du système
- Créer un PCB avec un ESP32 permettant de controler les moteurs
- Créer un programme permettant de communiquer en bluetooth avec l'ESP et de controler la voiture depuis un telephone puis une manette.

## 1.2 Retroplanning

| Séance | Objectif|
|--------|---------|
|TP1     |Définir les spécifications, choisir les composants, rédiger le cahier des charges et planifier les tâches.|
|TP2     |Modéliser le châssis en 3D, concevoir le schéma du PCB et préparer les fichiers pour la fabrication.|
|TP3     |Imprimer/découper le châssis, finaliser le PCB et préparer les outils pour la séance suivante.|
|TP4     |Souder les composants sur le PCB et écrire le code de base pour contrôler les moteurs.|
|TP5     |Développer la communication Bluetooth et tester les mouvements de la voiture.|
|TP6     |Assembler le châssis, tester l'ensemble (mouvements, Bluetooth) et finaliser le code.|
|TP7     |Valider les tests, rédiger le rapport technique et préparer la démonstration.|


# 2 Projet

## Séance 1

L'alimentation de la voiture sera fait grâce a une batterie 12v, cette tension sera convertie en 5v par un convertisseur DC-DC, qui alimentera toute la carte.\
Un esp32 recuperera les informations de mouvement depuis une connection bluetooth, enverra la PWM appropriée aux drivers, qui eux controleront les moteurs.\
Les moteurs seront eux alimentés par la batterie 12v, et leur valeur d'encodeur sera renvoyée à l'esp pour permettre un niveau de précision adéquat pour utiliser les roues omnidirectionelles.\
Une interface sera faite sur telephone avec l'application BT electronics, et si le temps le permets, le robot sera controlé par une manette de ps4

| Composant | Référence | Lien | Quantité |
|-----------|-----------|------|----------|
| Moteurs | RK370SD22140n9h | https://www.pololu.com/product/3240 | x4 |
| Drivers moteur | DRV8411APWPR | | x2 |
| ESP32 | | | x1 |
| Roues omnidirectionelles | FIT0779 | https://www.gotronic.fr/art-roue-omnidirectionnelle-droite-fit0780-34179.htm | x2L x2R |
| Convertisseur 12v-5v | 173950x78 | https://www.we-online.com/components/products/datasheet/173950378.pdf | x1 |
| Batterie 12v | fait in ensea |  | x1 |
