Pensez � ajouter "HTTP", "Json", "JsonUtilities" dans PublicDependencyModuleNames dans le fichier <nom du projet>.Build.cs

Faire h�riter votre class custom de GameInstance avec DeltaDNAGameInstance
NB: Si votre class custom de GameInstance override la methode Init() de GameInstance, pensez � appeler Super::Init(); au d�but.

Pour cr�er un event custom, cr�ez une class qui h�rite de DeltaDNAEvent, et remplir la variable eventParams (h�rit�e de DeltaDNAEvent) avec les m�thodes de FJsonObject
