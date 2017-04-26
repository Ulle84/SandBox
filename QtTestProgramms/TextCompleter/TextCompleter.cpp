#include <QCompleter>

#include "TextCompleter.h"
#include "ui_TextCompleter.h"

TextCompleter::TextCompleter(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TextCompleter)
{
  ui->setupUi(this);
  QStringList stringList;
  stringList << "first" << "second" << "third";
  QCompleter* completer = new QCompleter(stringList);
  ui->lineEdit->setCompleter(completer);
}

TextCompleter::~TextCompleter()
{
  delete ui;
}
