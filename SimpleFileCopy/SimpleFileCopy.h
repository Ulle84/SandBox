#ifndef SIMPLEFILECOPY_H
#define SIMPLEFILECOPY_H

#include <QDialog>

namespace Ui {
class SimpleFileCopy;
}

class SimpleFileCopy : public QDialog
{
    Q_OBJECT
    
public:
    explicit SimpleFileCopy(QWidget *parent = 0);
    ~SimpleFileCopy();

private slots:
    void on_pushButtonCopy_clicked();

    void on_pushButtonSelectSource_clicked();

    void on_pushButtonSelectDestination_clicked();

private:
    Ui::SimpleFileCopy *ui;
    void setTimeOnStatusBar();
    void setNewTextAtStatusBar(const QString &newText);
};

#endif // SIMPLEFILECOPY_H
