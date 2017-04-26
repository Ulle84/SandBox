#include <qmath.h>

#include <QList>
#include <QDateTime>
#include <QMessageBox>

#include "CowsBullsUBE.h"
#include "ui_CowsBullsUBE.h"

CowsBullsUBE::CowsBullsUBE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CowsBullsUBE)
{
    ui->setupUi(this);

    doFirstGuess();
}

CowsBullsUBE::~CowsBullsUBE()
{
    delete ui;
}

void CowsBullsUBE::on_pushButtonSubmitAnswer_clicked()
{
    m_currentGuess.bulls = ui->spinBoxBulls->value();
    m_currentGuess.cows = ui->spinBoxCows->value();

    m_guesses.append(m_currentGuess);

    if (ui->spinBoxBulls->value() == 4 && ui->spinBoxCows->value() == 4)
    {
        QMessageBox::information(this, tr("Success"), tr("I needed %1 guesses.").arg(m_guesses.count()));
        return;
    }

    calculateNextGuess();
}

void CowsBullsUBE::calculateNextGuess()
{
    // bulls -> matching digits, which are in their right positions
    // cows  -> matching digits
    // bull < cow

    // cows = 0 -> delete all digits

    // cows = 1 ... 3 -> ???

    // cows = 4 -> only shuffle

    // TODO -> analyse m_guesses and make next guess

    //

    showCurrentGuess();
}

void CowsBullsUBE::doFirstGuess()
{
    qsrand(QDateTime::currentDateTime().toTime_t());

    QList<int> firstGuess;

    firstGuess.append((qrand() % 9) + 1);

    while (firstGuess.length() < 4)
    {
        int randomNumber = qrand() % 10;
        if (!firstGuess.contains(randomNumber))
        {
            firstGuess.append(randomNumber);
        }
    }

    m_currentGuess.m_numbers = firstGuess;

    showCurrentGuess();
}

void CowsBullsUBE::showCurrentGuess()
{
    ui->lineEditGuess->setText(listToString(m_currentGuess.m_numbers));
}

QString CowsBullsUBE::listToString(const QList<int> &list)
{
    QString string;

    for (int i = 0; i < list.length(); i++)
    {
        string.append(QString::number(list.at(i)));
    }

    return string;
}
