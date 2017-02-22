Pensez à ajouter "HTTP", "Json", "JsonUtilities" dans PublicDependencyModuleNames dans le fichier <nom du projet>.Build.cs

Faire hériter votre class custom de GameInstance avec DeltaDNAGameInstance
NB: Si votre class custom de GameInstance override la methode Init() de GameInstance, pensez à appeler Super::Init(); au début.

Pour créer un event custom, créez une class qui hérite de DeltaDNAEvent, et remplir la variable eventParams (héritée de DeltaDNAEvent) avec les méthodes de FJsonObject
