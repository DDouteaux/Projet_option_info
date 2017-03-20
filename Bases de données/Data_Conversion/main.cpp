#include <iostream>
#include <fstream>
#include <string>
#include <QString>

using namespace std;

#include "jsonworker.h"
#include "amazonworker.h"
#include "largemovieworker.h"

int main()
{
    /**
     *  Définir quels traitements sont à lancer.
     *  Pour les chemins vers les BDD, voir les différentes parties associées à chaque BDD.
     */
    bool launchLMRD = false;            // Toute la base Large Movie DataBase.
    bool launchAmazonAll = false;       // Toute la base d'Amazon.
    bool launchAmazonInf100 = false;    // Les éléments d'Amazon de taille < 100Mo.
    bool launchAmazon100500 = false;    // Les éléments d'Amazon où 100Mo < taille < 500Mo.
    bool launchAmazonSup500 = false;    // Les éléments d'Amazon où taill > 500Mo.

    /**
     *  Lancement du worker pour la base de données Large Movie Dataset.
     *  Renseignez les valeurs attendues pour les chemins relatifs vers
     *  la base de données en fonction de votre implémentation.
     *
     *  Temps d'exécution < 5 minutes.
     *
     **/
    if(launchLMRD){
        QString lmrdPath = "../BDD Brutes/Large Movie Review Dataset/";
        QString testPath = "test/";
        QString trainPath = "train/";
        QString negPath = "neg/";
        QString posPath = "pos/";
        LargeMovieWorker largeMovieWorker("", "../BDD Remaniées/Large_Movie_Dataset.csv", "Large Movie DB", lmrdPath, testPath, trainPath, negPath, posPath);
        largeMovieWorker.launchWorker();
    }

    /**
     *  Lancement des workers sur la base de données d'Amazon.
     *  Renseignez les valeurs attendues pour les chemins relatifs vers
     *  la base de données en fonction de votre implémentation.
     *
     *  30 minutes < Temps d'exécution < 1h
     *
     *  /!\ Les données de Kindle et CD/Vinyl représentent un peu plus de
     *      1/3 de la BDD, les retirer peut donc considérablement réduire
     *      le temps de traitement...
     *
     */
    if(launchAmazonAll || launchAmazon100500 || launchAmazonInf100 || launchAmazonSup500){
        string amazonInputPath = "../BDD Brutes/Amazon Product Data/";
        string amazonOutputPath = "../BDD Remaniées/";

        if(launchAmazonAll || launchAmazonSup500){
            AmazonWorker ACDsWorker(QString::fromStdString(amazonInputPath + "Amazon_CDs_and_Vinyl.json"), QString::fromStdString(amazonOutputPath + "Amazon_CDs_and_Vinyl.csv"), "Amazon_CDs_and_Vinyl");
            ACDsWorker.launchWorker();
            AmazonWorker AKindleWorker(QString::fromStdString(amazonInputPath + "Amazon_Kindle_Store.json"), QString::fromStdString(amazonOutputPath + "Amazon_Kindle_Store.csv"), "Amazon_Kindle_Store");
            AKindleWorker.launchWorker();
        }

        if(launchAmazonAll || launchAmazon100500){
            AmazonWorker ACellPhoneWorker(QString::fromStdString(amazonInputPath + "Amanzon_Cell_Phones_and_Accessories.json"), QString::fromStdString(amazonOutputPath + "Amanzon_Cell_Phones_and_Accessories.csv"), "Amanzon_Cell_Phones_and_Accessories");
            ACellPhoneWorker.launchWorker();
            AmazonWorker AAndroidWorker(QString::fromStdString(amazonInputPath + "Amazon_Apps_for_Android.json"), QString::fromStdString(amazonOutputPath + "Amazon_Apps_for_Android.csv"), "Amazon_Apps_for_Android");
            AAndroidWorker.launchWorker();
            AmazonWorker AClothingWorker(QString::fromStdString(amazonInputPath + "Amazon_Clothing_Shoes_and_Jewelry.json"), QString::fromStdString(amazonOutputPath + "Amazon_Clothing_Shoes_and_Jewelry.csv"), "Amazon_Clothing_Shoes_and_Jewelry");
            AClothingWorker.launchWorker();
            AmazonWorker AHealthWorker(QString::fromStdString(amazonInputPath + "Amazon_Health_and_Personal_Care.json"), QString::fromStdString(amazonOutputPath + "Amazon_Health_and_Personal_Care.csv"), "Amazon_Health_and_Personal_Care");
            AHealthWorker.launchWorker();
            AmazonWorker AVideoGamesWorker(QString::fromStdString(amazonInputPath + "Amazon_Video_Games.json"), QString::fromStdString(amazonOutputPath + "Amazon_Video_Games.csv"), "Amazon_Video_Games");
            AVideoGamesWorker.launchWorker();
            AmazonWorker ASportsWorker(QString::fromStdString(amazonInputPath + "Amazon_Sports_and_Outdoors.json"), QString::fromStdString(amazonOutputPath + "Amazon_Sports_and_Outdoors.csv"), "Amazon_Sports_and_Outdoors");
            ASportsWorker.launchWorker();
            AmazonWorker AHomeWorker(QString::fromStdString(amazonInputPath + "Amazon_Home_and_Kitchen.json"), QString::fromStdString(amazonOutputPath + "Amazon_Home_and_Kitchen.csv"), "Amazon_Home_and_Kitchen");
            AHomeWorker.launchWorker();
        }

        if(launchAmazonAll || launchAmazonInf100){
            AmazonWorker ABeautyWorker(QString::fromStdString(amazonInputPath + "Amazon_Beauty.json"), QString::fromStdString(amazonOutputPath + "Amazon_Beauty.csv"), "Amazon_Beauty");
            ABeautyWorker.launchWorker();
            AmazonWorker AToysWorker(QString::fromStdString(amazonInputPath + "Amazon_Toys_and_Games.json"), QString::fromStdString(amazonOutputPath + "Amazon_Toys_and_Games.csv"), "Amazon_Toys_and_Games");
            AToysWorker.launchWorker();
            AmazonWorker ABabyWorker(QString::fromStdString(amazonInputPath + "Amazon_Baby.json"), QString::fromStdString(amazonOutputPath + "Amazon_Baby.csv"), "Amazon_Baby");
            ABabyWorker.launchWorker();
            AmazonWorker AToolsHomeWorker(QString::fromStdString(amazonInputPath + "Amazon_Tools_and_Home_Improvement.json"), QString::fromStdString(amazonOutputPath + "Amazon_Tools_and_Home_Improvement.csv"), "Amazon_Tools_and_Home_Improvement");
            AToolsHomeWorker.launchWorker();
            AmazonWorker AGroceryWorker(QString::fromStdString(amazonInputPath + "Amazon_Grocery_and_Gourmet_Food.json"), QString::fromStdString(amazonOutputPath + "Amazon_Grocery_and_Gourmet_Food.csv"), "Amazon_Grocery_and_Gourmet_Food");
            AGroceryWorker.launchWorker();
            AmazonWorker APetWorker(QString::fromStdString(amazonInputPath + "Amazon_Pet_Supplies.json"), QString::fromStdString(amazonOutputPath + "Amazon_Pet_Supplies.csv"), "Amazon_Pet_Supplies");
            APetWorker.launchWorker();
            AmazonWorker AMusicWorker(QString::fromStdString(amazonInputPath + "Amazon_Digital_Music.json"), QString::fromStdString(amazonOutputPath + "Amazon_Digital_Music.csv"), "Amazon_Digital_Music");
            AMusicWorker.launchWorker();
            AmazonWorker AOfficeWorker(QString::fromStdString(amazonInputPath + "Amazon_Office_Products.json"), QString::fromStdString(amazonOutputPath + "Amazon_Office_Products.csv"), "Amazon_Office_Products");
            AOfficeWorker.launchWorker();
            AmazonWorker AVideoWorker(QString::fromStdString(amazonInputPath + "Amazon_Instant_Video.json"), QString::fromStdString(amazonOutputPath + "Amazon_Instant_Video.csv"), "Amazon_Instant_Video");
            AVideoWorker.launchWorker();
            AmazonWorker AGardenWorker(QString::fromStdString(amazonInputPath + "Amazon_Patio_Lawn_and_Garden.json"), QString::fromStdString(amazonOutputPath + "Amazon_Patio_Lawn_and_Garden.csv"), "Amazon_Patio_Lawn_and_Garden");
            AGardenWorker.launchWorker();
            AmazonWorker AAutomotiveWorker(QString::fromStdString(amazonInputPath + "Amazon_Automotive.json"), QString::fromStdString(amazonOutputPath + "Amazon_Automotive.csv"), "Amazon_Automotive");
            AAutomotiveWorker.launchWorker();
            AmazonWorker AMusicInstrWorker(QString::fromStdString(amazonInputPath + "Amazon_Musical_Instruments.json"), QString::fromStdString(amazonOutputPath + "Amazon_Musical_Instruments.csv"), "Amazon_Musical_Instruments");
            AMusicInstrWorker.launchWorker();
        }
    }

    return 0;
}
