Pensez à ajouter "HTTP", "Json", "JsonUtilities" dans PublicDependencyModuleNames dans le fichier <nom du projet>.Build.cs

Faire hériter votre class custom de GameInstance avec DeltaDNAGameInstance

Pour créer un event custom, créez une class qui hérite de DeltaDNAEvent, et remplir la variable eventParams (héritée de DeltaDNAEvent) avec les méthodes de FJsonObject
