#include <iostream>
#include <fstream>
#include <string>
#include <QString>

using namespace std;

#include "jsonworker.h"
#include "amazonworker.h"

int main()
{
    string amazonInputPath = "../BDD Brutes/Amazon Product Data/";
    string amazonOutputPath = "../BDD Remaniées/";
//    AmazonWorker ACellPhoneWorker(QString::fromStdString(amazonInputPath + "Amanzon_Cell_Phones_and_Accessories.json"), QString::fromStdString(amazonOutputPath + "Amanzon_Cell_Phones_and_Accessories.csv"), "Amanzon_Cell_Phones_and_Accessories");
//    AmazonWorker AAndroidWorker(QString::fromStdString(amazonInputPath + "Amazon_Apps_for_Android.json"), QString::fromStdString(amazonOutputPath + "Amazon_Apps_for_Android.csv"), "Amazon_Apps_for_Android");
//    AmazonWorker AAutomotiveWorker(QString::fromStdString(amazonInputPath + "Amazon_Automotive.json"), QString::fromStdString(amazonOutputPath + "Amazon_Automotive.csv"), "Amazon_Automotive");
//    AmazonWorker ABabyWorker(QString::fromStdString(amazonInputPath + "Amazon_Baby.json"), QString::fromStdString(amazonOutputPath + "Amazon_Baby.csv"), "Amazon_Baby");
//    AmazonWorker ABeautyWorker(QString::fromStdString(amazonInputPath + "Amazon_Beauty.json"), QString::fromStdString(amazonOutputPath + "Amazon_Beauty.csv"), "Amazon_Beauty");
    AmazonWorker ACDsWorker(QString::fromStdString(amazonInputPath + "Amazon_CDs_and_Vinyl.json"), QString::fromStdString(amazonOutputPath + "Amazon_CDs_and_Vinyl.csv"), "Amazon_CDs_and_Vinyl");
//    AmazonWorker AClothingWorker(QString::fromStdString(amazonInputPath + "Amazon_Clothing_Shoes_and_Jewelry.json"), QString::fromStdString(amazonOutputPath + "Amazon_Clothing_Shoes_and_Jewelry.csv"), "Amazon_Clothing_Shoes_and_Jewelry");
//    AmazonWorker AMusicWorker(QString::fromStdString(amazonInputPath + "Amazon_Digital_Music.json"), QString::fromStdString(amazonOutputPath + "Amazon_Digital_Music.csv"), "Amazon_Digital_Music");
//    AmazonWorker AGroceryWorker(QString::fromStdString(amazonInputPath + "Amazon_Grocery_and_Gourmet_Food.json"), QString::fromStdString(amazonOutputPath + "Amazon_Grocery_and_Gourmet_Food.csv"), "Amazon_Grocery_and_Gourmet_Food");
//    AmazonWorker AHealthWorker(QString::fromStdString(amazonInputPath + "Amazon_Health_and_Personal_Care.json"), QString::fromStdString(amazonOutputPath + "Amazon_Health_and_Personal_Care.csv"), "Amazon_Health_and_Personal_Care");
    AmazonWorker AHomeWorker(QString::fromStdString(amazonInputPath + "Amazon_Home_and_Kitchen.json"), QString::fromStdString(amazonOutputPath + "Amazon_Home_and_Kitchen.csv"), "Amazon_Home_and_Kitchen");
    AmazonWorker AVideoWorker(QString::fromStdString(amazonInputPath + "Amazon_Instant_Video.json"), QString::fromStdString(amazonOutputPath + "Amazon_Instant_Video.csv"), "Amazon_Instant_Video");
    AmazonWorker AKindleWorker(QString::fromStdString(amazonInputPath + "Amazon_Kindle_Store.json"), QString::fromStdString(amazonOutputPath + "Amazon_Kindle_Store.csv"), "Amazon_Kindle_Store");
//    AmazonWorker AMusicInstrWorker(QString::fromStdString(amazonInputPath + "Amazon_Musical_Instruments.json"), QString::fromStdString(amazonOutputPath + "Amazon_Musical_Instruments.csv"), "Amazon_Musical_Instruments");
    AmazonWorker AOfficeWorker(QString::fromStdString(amazonInputPath + "Amazon_Office_Products.json"), QString::fromStdString(amazonOutputPath + "Amazon_Office_Products.csv"), "Amazon_Office_Products");
    AmazonWorker AGardenWorker(QString::fromStdString(amazonInputPath + "Amazon_Patio_Lawn_and_Garden.json"), QString::fromStdString(amazonOutputPath + "Amazon_Patio_Lawn_and_Garden.csv"), "Amazon_Patio_Lawn_and_Garden");
    AmazonWorker APetWorker(QString::fromStdString(amazonInputPath + "Amazon_Pet_Supplies.json"), QString::fromStdString(amazonOutputPath + "Amazon_Pet_Supplies.csv"), "Amazon_Pet_Supplies");
    AmazonWorker ASportsWorker(QString::fromStdString(amazonInputPath + "Amazon_Sports_and_Outdoors.json"), QString::fromStdString(amazonOutputPath + "Amazon_Sports_and_Outdoors.csv"), "Amazon_Sports_and_Outdoors");
    AmazonWorker AToolsHomeWorker(QString::fromStdString(amazonInputPath + "Amazon_Tools_and_Home_Improvement.json"), QString::fromStdString(amazonOutputPath + "Amazon_Tools_and_Home_Improvement.csv"), "Amazon_Tools_and_Home_Improvement");
    AmazonWorker AToysWorker(QString::fromStdString(amazonInputPath + "Amazon_Toys_and_Games.json"), QString::fromStdString(amazonOutputPath + "Amazon_Toys_and_Games.csv"), "Amazon_Toys_and_Games");
    AmazonWorker AVideoGamesWorker(QString::fromStdString(amazonInputPath + "Amazon_Video_Games.json"), QString::fromStdString(amazonOutputPath + "Amazon_Video_Games.csv"), "Amazon_Video_Games");

//    ACellPhoneWorker.launchWorker();
//    AAndroidWorker.launchWorker();
//    AAutomotiveWorker.launchWorker();
//    ABabyWorker.launchWorker();
//    ABeautyWorker.launchWorker();
//    AClothingWorker.launchWorker();
//    AMusicWorker.launchWorker();
//    AGroceryWorker.launchWorker();
//    AHealthWorker.launchWorker();
//    AMusicInstrWorker.launchWorker();

    ACDsWorker.launchWorker();
    AHomeWorker.launchWorker();
    AVideoWorker.launchWorker();
    AKindleWorker.launchWorker();
    AOfficeWorker.launchWorker();
    AGardenWorker.launchWorker();
    APetWorker.launchWorker();
    ASportsWorker.launchWorker();
    AToolsHomeWorker.launchWorker();
    AToysWorker.launchWorker();
    AVideoGamesWorker.launchWorker();

    return 0;
}
