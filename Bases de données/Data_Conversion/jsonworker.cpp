#include "jsonworker.h"

/**
 *  Constructeur générique des workers. Il va en particulier vérifier que
 *  les fichiers de sortie et d'entrée existent.
 *
 *  Params :
 *      - inputPath : chemin vers le fichier original à traiter.
 *                    S'il vaut "", il ne sera pas chargé.
 *      - outputPath : chemin vers le fichier de sortie de la BDD remaniée.
 *      - bddName_ : nom de la BDD étudiée.
 */
JsonWorker::JsonWorker(QString inputPath, QString outputPath, QString bddName_){
    cout << "INFO    : Construction d'un worker pour la BDD " << this->bddName.toStdString() << "." << endl;

    // Création du fichier de sortie s'il n'existe pas
    if(this->fileExists(outputPath)){
        cout << "WARNING : Un fichier de sortie existe deja. Voullez-vous le supprimer ou arreter le traitement." << endl;
        cout << "          [N] pour stopper le traitement ; [O] pour continuer.";
        cout << "        : Votre choix : ";
        string answer;
        getline(cin, answer);
        if(answer == "o" || answer == "O"){
            QFile::remove(outputPath);
            this->createOutputFile(outputPath);
            cout << "INFO    : Creation du fichier de sortie " << outputPath.toStdString() << "." << endl;
        } else {
            this->outputFile = new QFile(outputPath);
        }
    } else {
        this->createOutputFile(outputPath);
        cout << "INFO    : Creation du fichier de sortie " << outputPath.toStdString() << "." << endl;
    }
    if(inputPath != ""){
        this->loadFile(inputPath);
    }
    this->bddName = bddName_;
}

/**
 *  Méthode pour ouvrir le fichier d'entrée ce Worker.
 *
 *  Params :
 *      - path : le chemin du fichier à lire.
 *
 *  Return :
 *      - Rien, mais initialise la variable inputFile pour la lecture.
 *
 */
void JsonWorker::loadFile(QString path){
    this->inputFile = new QFile(path);
}

/**
 *  Méthode pour créer le fichier de sortie pour ce Worker.
 *
 *  Params :
 *      - path : le chemin du fichier à créer.
 *
 *  Return :
 *      - Rien, mais initialise la variable outputFile pour l'écriture.
 *
 */
void JsonWorker::createOutputFile(QString path){
    this->outputFile = new QFile(path);
    this->outputFile->open(QIODevice::WriteOnly | QIODevice::Text);
    this->outputFile->close();
}

/**
 *  Lancement du job pour faire le traitement des données en entrées.
 *  Cette méthode va appeler les worker associés nécessaires par héritage.
 *
 *  Params :
 *      - Aucun.
 *
 *  Return :
 *      - True si le traitement s'est bien déroulé, false sinon.
 *
 */
bool JsonWorker::launchWorker(){
    // Vérification de l'existence des fichiers d'entrée et de sortie.
    QString inputPath = this->inputFile->fileName();
    QString outputPath = this->outputFile->fileName();
    // On vérifie que le fichier à parser et le fichier de sortie existent bien.
    if(!(this->fileExists(inputPath) && this->fileExists(outputPath))){
        if(!this->fileExists(inputPath)){
            cout << "ERREUR  : Le chemin du fichier a charger n'existe pas ou est un repertoire..." << endl;
        } else if (!this->fileExists(outputPath)){
            cout << "ERREUR  : Le chemin du fichier de sortie n'existe pas ou est un repertoire..." << endl;
        } else {
            cout << "ERREUR  : Un des flux de lecture ou ecriture n'a pas pu etre lance convenablement..." << endl;
        }
        cout << "INFO    : Ce traitement est interrompu. Veuillez verifier les configurations avant de relancer les conversions." << endl;
        return false;
    }

    // Lecture du fichier ligne par ligne.
    if (this->inputFile->open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(this->inputFile);
        this->outputFile->open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(this->outputFile);
        out << "Comment\t RatingDegrad\t Rating\t TextType\t BDDName" << endl;

        while(!in.atEnd()){
            QString line = in.readLine();
            QString newLine = QString::fromStdString(this->parseData(line));
            if(!newLine.trimmed().isEmpty()){
                out << newLine << endl;
            }
        }
    }
    cout << "INFO    : Worker termine pour " << this->bddName.toStdString() << "." << endl;

    // Nettoyage espace de travail.
    this->outputFile->close();
    this->inputFile->close();
    return true;
}

/**
 *  Méthode pour vérifier l'existence d'un fichier donné. La méthode vérifie que le
 *  chemin fournit existe et qu'il s'agit bien d'un fichier et non d'un répertoire.
 *
 *  Params :
 *      - path : un QString contenant l'emplacement à tester.
 *
 *  Return :
 *      - bool : true si le fichier existe ; false sinon.
 *
 */
bool JsonWorker::fileExists(QString path) {
    QFileInfo check_file(path);
    return (check_file.exists() && check_file.isFile());
}

/**
 *  Méthode utilitaire pour retirer des substring d'une chaîne de caractère.
 *  Toutes les occurences seront retirées.
 *
 *  Params :
 *      - s : la string a modifier.
 *      - p : la substring à supprimer de s.
 *
 *  Return :
 *      - La string modifiée.
 */
string JsonWorker::removeSubstrs(string s, string p) {
    string::size_type n = p.length();
    for (string::size_type i = s.find(p); i != string::npos; i = s.find(p)){
        s.erase(i, n);
    }
    return s;
}
