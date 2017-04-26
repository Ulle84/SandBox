#ifndef COWSBULLSUBE_H
#define COWSBULLSUBE_H

#include <QWidget>
#include <QList>

#include "Guess.h"

namespace Ui {
class CowsBullsUBE;
}

class CowsBullsUBE : public QWidget
{
  Q_OBJECT

public:
  explicit CowsBullsUBE(QWidget *parent = 0);
  ~CowsBullsUBE();

private slots:
  void on_pushButtonSubmitAnswer_clicked();

private:
  void calculateNextGuess();
  void doFirstGuess();
  void showCurrentGuess();

  QString listToString(const QList<int>& list);

  Ui::CowsBullsUBE *ui;
  QList<Guess> m_guesses;
  Guess m_currentGuess;
};

#endif // COWSBULLSUBE_H
