#include "jsonworker.h"

JsonWorker::JsonWorker(QString inputPath, QString outputPath){
    // Création du fichier de sortie s'il n'existe pas
    if(this->fileExists(outputPath)){
        cout << "WARNING : Un fichier de sortie existe deja. Voullez-vous le supprimer ou arreter le traitement." << endl;
        cout << "          Pour arrete le traitement Ctrl+C, pour continuer Entree." << endl;
        system("pause");
        QFile::remove(outputPath);
    }
    cout << "INFO : Creation du fichier de sortie " << outputPath.toStdString() << "." << endl;
    this->createOutputFile(outputPath);
    this->loadFile(inputPath);

    // On vérifie que le fichier à parser et le fichier de sortie existent bien.
    if(!(this->fileExists(inputPath) && this->fileExists(outputPath))){
        if(!this->fileExists(inputPath)){
            cout << "ERREUR : Le chemin du fichier a charger n'existe pas ou est un repertoire..." << endl;
        } else if (!this->fileExists(outputPath)){
            cout << "ERREUR : Le chemin du fichier de sortie n'existe pas ou est un repertoire..." << endl;
        } else {
            cout << "ERREUR : Un des flux de lecture ou ecriture n'a pas pu etre lance convenablement..." << endl;
        }
        cout << "         Tous les traitements sont interrompus. Veuillez verifier les configurations avant de relancer les conversions." << endl;
        QCoreApplication::quit();
    }
}

/*
 *  Méthode pour ouvrir le fichier d'entrée ce Worker.
 *
 *  Params :
 *      - path : le chemin du fichier à lire.
 *
 *  Return :
 *      - Rien, mais initialise la variable inputStream pour la lecture.
 *
 */
void JsonWorker::loadFile(QString path){
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&inputFile);
        this->inputStream = &in;
    }
}

/*
 *  Méthode pour créer le fichier de sortie pour ce Worker.
 *
 *  Params :
 *      - path : le chemin du fichier à créer.
 *
 *  Return :
 *      - Rien, mais initialise la variable outputStream pour l'écriture.
 *
 */
void JsonWorker::createOutputFile(QString path){
    QFile outputFile(path);
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&outputFile);
        this->outputStream = &out;
    }
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
