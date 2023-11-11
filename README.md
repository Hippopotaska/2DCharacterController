# Suomeksi
## 2DCharacterController
2D character controller on projekti joka tehtiin opinnäytetyötä varten, "2D-tasohyppelypelien erilaiset mekaniikat ja käytänteet". Projekti on 2D-tasohyppelypeli, joka ohjelmoitiin C++-ohjelmointikielellä ja renderöimiseen hyödynnettiin OpenGLää. Moottori käyttää peliobjekti komponentti systeemiä. Projektin pääaihe
on pelaajan liikkuminen, johon implementoitu muutamia tasohyppely mekaniikkoja, kuten hallittava hyppykorkeus ja kojoottiaika.

## Kuinka asentaa
Projekti hyödyntää CMakea projektin tiedostojen buildaamiseen. Projektin CMake lista löytyy "project" nimisestä kansiosta. Build kansio tulisi tehdä kyseisen kansion sisälle, jossa CMake lista on.

## Kuinka käyttää
Projekti hyödyntää ImGuia kääyttöliittymän luomiseen. Käyttöliittymässä voidaan muokata pelaajan liikkumisarvoja, kuten liikkumisnopeutta ja hyppykorkeutta. Kättöliittymässä näkee myös muuta informaatiota, kuten pelin kuvataajuuden ja mittayksiköt. Viimeisenä käyttöliittymästä löytyy kaksi nappia; "Controls"
josta aukeaa pieni menu jossa näkee kontrollit ja "Reset Player" joka siirtää pelaajan aloituspisteeseen ja palauttaa liikkumisarvot lähtöarvoihin.

# 
# 
# 

# In English
## 2DCharacterController
2D character controller is a project made along side my thesis project, "Different mechanics and practices of 2D platformers". Project is a 2D platformer game created in C++ and uses OpenGL for rendering. The engine uses a game object component system as a base. The main focus of the project
is the character movement, which features a couple of platformer mechanics, such as variable jump height and coyote time. 

## How to setup project
Project uses CMake to build the project files, as there is no executable file. CMake list can be found inside the folder named "project". Build folder should be created withing the same folder.

## How to use
Project uses ImGui to create an UI from which players attributes, such as movement speed and jump height can be modified. The UI also provides info, such as the framerate and measurement information. Finally the UI has two buttons; "Controls" button opens a menu which shows the controls and "Reset Player" moves player
back to the start and resets the player attributes.
