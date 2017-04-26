#ifndef TEXTCOMPLETER_H
#define TEXTCOMPLETER_H

#include <QWidget>

namespace Ui {
class TextCompleter;
}

class TextCompleter : public QWidget
{
  Q_OBJECT
  
public:
  explicit TextCompleter(QWidget *parent = 0);
  ~TextCompleter();
  
private:
  Ui::TextCompleter *ui;
};

#endif // TEXTCOMPLETER_H
