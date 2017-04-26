#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include <QWidget>

namespace Ui {
class Permutations;
}

class Permutations : public QWidget
{
    Q_OBJECT
    
public:
    explicit Permutations(QWidget *parent = 0);
    ~Permutations();
    
private:
    Ui::Permutations *ui;
    QList<QStringList> listOfParameters;
};

#endif // PERMUTATIONS_H
