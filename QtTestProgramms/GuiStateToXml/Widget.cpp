/*
 *demonstration only - XML Implementation is missing
 *QSettings might also be an option to save state of GUI elements...
*/

#include "Widget.h"
#include "ui_Widget.h"

#include <QDebug>

Widget::Widget(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);

  // steps to follow
  // --------------------------------------------------------------------------------
  // look if dynamic property "saveStateToXml" is set
  // get object name
  // search in xml file for child node where name = objectName()
  // read value from xml file
  // find out the type of object (i. e. QSpinBox, QCheckBox)
  // set value of GUI element
}

Widget::~Widget()
{
  // iterate over all widgets and "save" state
  for (int i = 0; i < children().size(); i++)
  {
    if (children().at(i)->property("saveStateToXml").toBool())
    {
      qDebug() << children().at(i)->objectName();

      QPlainTextEdit* plainTextEdit = qobject_cast<QPlainTextEdit*>(children().at(i));
      QLineEdit* lineEdit = qobject_cast<QLineEdit*>(children().at(i));
      QCheckBox* checkBox = qobject_cast<QCheckBox*>(children().at(i));
      QSpinBox*  spinBox  = qobject_cast<QSpinBox*>(children().at(i));

      if (plainTextEdit)
      {
        qDebug() << "save plainTextEdit content";
      }
      else if (lineEdit)
      {
        qDebug() << "save lineEdit content";
      }
      else if (checkBox)
      {
        qDebug() << "save checkBox content";
      }
      else if (spinBox)
      {
        qDebug() << "save spinBox content";
      }
      else
      {
        // nothing to do?
      }
    }
  }

  delete ui;
}
