#include <QApplication>
#include <QCoreApplication>
#include "mytimer.h"
#include "window.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;




    std::vector<std::string> MomentsStorage;
    std::string tempString;

    QFile inputFile("/home/jubaskete/ufba/poses.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd()) //each loop is one line
        {
            QString line = in.readLine();
            std::string linha = line.toStdString();

            for (uint k1 = 0; k1 <= linha.size(); ++k1) { // each loop is a caracter

                // verifica o tamanho da string
                // soh entra aqui se a string tiver simbolos

                if (k1!= linha.size() && linha.at(k1) != ',' ){
                    tempString.push_back(linha.at(k1));

                } else {
                    double number = std::stod("9,87");
                    std::cout << "this is already the float " << number << std::endl;

                    MomentsStorage.push_back(tempString);
                    tempString.clear();
                }
            }

        }
        inputFile.close();
    }


    for (uint i = 0; i < MomentsStorage.size() - 1; i = i + 6) {

        std::cout <<"x Position " << MomentsStorage.at(i) << std::endl;
        std::cout <<"y Position " << MomentsStorage.at(i + 1) << std::endl;
        std::cout <<"z Position " << MomentsStorage.at(i + 2) << std::endl;
        std::cout <<"roll " << MomentsStorage.at(i + 3) << std::endl;
        std::cout <<"pitch " << MomentsStorage.at(i + 4) << std::endl;
        std::cout <<"yaw " << MomentsStorage.at(i + 5) << std::endl << std::endl;

    }





    MyTimer timer;

    window.show();
    return app.exec();
}



