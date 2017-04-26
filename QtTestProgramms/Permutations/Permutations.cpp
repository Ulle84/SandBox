#include "Permutations.h"
#include "ui_Permutations.h"

Permutations::Permutations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Permutations)
{
    ui->setupUi(this);

    QStringList list1;
    list1.append("ViDiag.exe signiert");
    list1.append("ViDiag.exe unsigniert");

    QStringList list2;
    list2.append("ViDiag.dll signiert");
    list2.append("ViDiag.dll unsigniert");

    QStringList list3;
    list3.append("ViDiag.dll signiert");
    list3.append("ViDiag.dll unsigniert");
    list3.append("ViDiag.dll teilweise signiert");

    listOfParameters.append(list1);
    listOfParameters.append(list2);
    listOfParameters.append(list3);

    int permutationsCount = 1; //TODO Sonderfaelle bei leeren Listen
    for (int i = 0; i < listOfParameters.length(); i++)
    {
        permutationsCount *= listOfParameters.at(i).count();
    }

    for (int i = 0; i < permutationsCount; i++)
    {
        QString permutation;
        for (int j = 0; j < listOfParameters.length(); j++)
        {
            int divisor = 1;
            for (int k = j + 1; k < listOfParameters.length(); k++)
            {
                divisor *= listOfParameters.at(k).length();
            }
            //permutation.append(QString("%1 ").arg((i/divisor)%listOfParameters.at(j).length()));
            permutation.append(listOfParameters.at(j).at((i/divisor)%listOfParameters.at(j).length()));
            if (j != listOfParameters.length() - 1)
            {
                permutation.append(" - ");
            }
        }
        ui->plainTextEditResult->appendPlainText(permutation);
    }
}

Permutations::~Permutations()
{
    delete ui;
}
