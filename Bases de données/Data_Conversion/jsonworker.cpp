#include "jsonworker.h"

/*
 *  Constructeur générique des workers. Il va en particulier vérifier que
 *  les fichiers de sortie et d'entrée existent.
 *
 */
JsonWorker::JsonWorker(QString inputPath, QString outputPath, QString bddName_){
    // Création du fichier de sortie s'il n'existe pas
    if(this->fileExists(outputPath)){
        cout << "WARNING : Un fichier de sortie existe deja. Voullez-vous le supprimer ou arreter le traitement." << endl;
        cout << "          [N] pour stopper le traitement ; [O] pour continuer.";
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
    this->loadFile(inputPath);
    this->bddName = bddName_;
}

/*
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

/*
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

/*
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

    if (this->inputFile->open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(this->inputFile);
        this->outputFile->open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(this->outputFile);
        out << "Comment\t RatingDegrad\t Rating\t TextType\t BDDName" << endl;

        while(!in.atEnd()){
            QString line = in.readLine();
            QString newLine = QString::fromStdString(this->parseData(line));
            out << newLine << endl;
        }
    }
    cout << "INFO    : Worker termine pour " << this->bddName.toStdString() << "." << endl;
    return true;
}

/*
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
