# OpenGL – Exploration du pipeline graphique 3D

**Apprentissage et exploration du pipeline graphique OpenGL pour la création et le rendu d'objets 3D** 

Ce projet a pour objectif de se familiariser avec les concepts fondamentaux d’OpenGL et le rendu 3D. Il permet de créer, manipuler et afficher différents objets 3D tout en appliquant des shaders, des textures et des modèles d’éclairage avancés.
Cette première expérience m’a permis de poser des bases solides pour mon expérience professionnelle chez **Thales**.

---

## Description du projet

Ce projet se compose de deux parties principales :

### OpenGL1
- Affichage de formes géométriques simples : cube et octaèdre.
- Couleurs appliquées par sommet ou par face.
- Rotation et zoom de la scène avec la souris et le clavier.
- Manipulation basique de la caméra avec glOrtho.
- Pas de shaders : rendu fixe via le pipeline OpenGL classique.

### OpenGL2
- Gestion de shaders : vertex et fragment shaders pour Phong, Gouraud, cel shading, textures dynamiques, etc.
- Objets 3D complexes : Suzanne (modèle OBJ) avec normals par vertex ou moyennées.
- Textures : textures statiques (BMP ou checkerboard) et textures dynamiques générées par shaders.
- Lumière et matériaux : contrôle des coefficients Ka, Kd, Ks et du shininess, changement du mode d'affichage et déplacement de la lumière.
- Framebuffers : rendu vers texture pour effets post-processing ou textures dynamiques.

## Concepts et techniques abordés

- Gestion des **sommets et indices** pour construire les objets 3D.
- Calcul des **normales** et des **matrices de transformation** (MVP, MV, NM).
- Utilisation des **shaders GLSL** pour :
  - Phong shading
  - Gouraud shading
  - Cell shading
  - Textures dynamiques
- Création de textures procédurales (checkerboard) et chargement de BMP.
- Rendu via **framebuffers** pour post-processing.
- Interaction utilisateur : rotation, zoom, changement de shader.

## Objectif pédagogique

- Comprendre le **pipeline graphique OpenGL**.
- Créer et manipuler des **objets 3D interactifs**.
- Expérimenter avec différents **shaders et effets visuels**.
- Acquérir les bases nécessaires pour des projets plus avancés comme **Physci Engine** ou d’autres moteurs 3D.

## Prérequis

- **Visual Studio 2022** (le projet a été initialement développé sous VS2019, mais fonctionne sous VS2022).  
- **Windows 10 ou 11**.  
- Bibliothèques incluses dans le dépôt :  
  - **FreeGLUT**  
  - **GLM**  
  - **GLEW** (si nécessaire)  
- Les fichiers DLL nécessaires doivent être placés dans **C:\Windows\System32** ou ajoutés au **PATH**.

## Installation

1. **Cloner le dépôt**  
   ```bash
   git clone <URL_DU_DEPOT>
   ```

2. **Ouvrir la solution dans Visual Studio**  
   - Double-cliquez sur `OpenGL.sln` pour ouvrir la solution dans Visual Studio 2022.

3. **Vérifier les dépendances**  
   - Les bibliothèques FreeGLUT, GLM et GLEW sont incluses dans le dossier `External Libraries/`, à extraire dans ce dossier.  
   - Dans Visual Studio, faites un clic droit sur le projet → **Propriétés** → **VC++ Directories** :  
     - **Include Directories** : pour chaque lib, ajoutez le chemin vers `External Libraries/include`.  
     - **Library Directories** : pour chaque lib, ajoutez le chemin vers `External Libraries/lib`.  
   - Dans **Linker → Input → Additional Dependencies**, ajoutez les fichiers `.lib` nécessaires dans la bonne configuration :  
     - `freeglut.lib`  
     - `glew32.lib`

4. **DLL**  
   - Copiez les fichiers `*.dll` requis dans :  
     - `C:\Windows\System32`  
     - **ou** dans le dossier contenant l’exécutable généré (`Debug/` ou `Release/`).  
   - Par exemple : `freeglut.dll`, `glew32.dll`.

5. **Compiler et exécuter**  
   - Sélectionnez **Debug** ou **Release** et compilez le projet.  
   - Exécutez `OpenGL1.exe` ou `OpenGL2.exe` depuis Visual Studio ou le dossier `Debug/` ou `Release/`.

## Guide des touches

### OpenGL1
| Touche | Action                                                  |
| ------ | ------------------------------------------------------- |
| `q`    | Quitter le programme                                    |
| `Esc`  | Quitter le programme                                    |
| `1`    | Passer en mode triangle                                 |
| `2`    | Passer en mode cube                                     |
| `3`    | Basculer entre projection orthographique et perspective |
| `4`    | Activer/désactiver le mode fil de fer (wireframe)       |
| `5`    | Activer/désactiver le mélange alpha (transparence)      |
| `6`    | Activer/désactiver le brouillard (fog)                  |

| Bouton      | Action                                     |
| ----------- | ------------------------------------------ |
| Clic gauche | Déplacer le sommet V1 du triangle (mode 1) |
| Clic milieu | Déplacer le sommet V2 du triangle (mode 1) |
| Clic droit  | Déplacer le sommet V3 du triangle (mode 1) |
| Glisser     | Rotation du cube (mode 2)                  |

### OpenGL2
| Touche              | Action                                                    |
| ------------------- | --------------------------------------------------------- |
| `0`                 | Affiche la texture dynamique sur le quad                  |
| `1`                 | Alterne cube standard / cube couleurs par face / octaèdre |
| `2`                 | Affiche Suzanne (normales par vertex)                     |
| `3`                 | Affiche Suzanne 2 (normales moyennées)                    |
| `4`                 | Affiche Suzanne avec cel shading                          |
| `5`                 | Affiche Suzanne avec texture dynamique                    |
| `8`                 | Post-processing (commenté)                                |
| `k`                 | Affiche Suzanne avec Gouraud (mode 2)                     |
| `l`                 | Affiche Suzanne 2 avec Gouraud                            |
| `m`                 | Affiche Suzanne 2 avec Phong                              |
| `t`                 | Bascule entre checker texture et BMP texture              |
| `i`                 | Vecteur lumière ADS → (1,0,0)                             |
| `o`                 | Vecteur lumière ADS → (0,1,0)                             |
| `p`                 | Vecteur lumière ADS → (0,0,1)                             |
| `z`                 | Diminue Ka.x (ambiance)                                   |
| `e`                 | Augmente Ka.x                                             |
| `s`                 | Diminue Kp.y (diffuse)                                    |
| `d`                 | Augmente Kp.y                                             |
| `x`                 | Diminue Ks.z (speculaire)                                 |
| `c`                 | Augmente Ks.z                                             |
| `7`                 | Diminue shininess                                         |
| `9`                 | Augmente shininess                                        |
| `a`                 | Zoom avant                                                |
| `w`                 | Zoom arrière                                              |
| `Souris` clic droit | Déplace la source de lumière                              |
| `Souris` glisser    | Modifie la rotation de la scène                           |
| `q` / `Q` / `ESC`   | Quitte le programme et libère les ressources              |


Les touches peuvent être modifiées dans les fichiers `keyboard()` de chaque projet.

---

## License
- Projet pedagogique – usage libre pour consultation, tests et apprentissage.
