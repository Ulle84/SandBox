#include <QtDesigner>
 #include <QtGui>

 #include "DoubleButton.h"
 #include "DoubleButtonDialog.h"
 #include "DoubleButtonTaskMenu.h"

 DoubleButtonTaskMenu::DoubleButtonTaskMenu(DoubleButton* doubleButton, QObject *parent)
     : QObject(parent)
 {
     m_doubleButton = doubleButton;

     m_editStateAction = new QAction(tr("Edit labels..."), this);
     connect(m_editStateAction, SIGNAL(triggered()), this, SLOT(editLabels()));
 }

 void DoubleButtonTaskMenu::editLabels()
 {
     DoubleButtonDialog dialog(m_doubleButton);

     if (dialog.exec() == QDialog::Accepted)
     {
       m_doubleButton->setButtonText1(dialog.buttonText1());
       m_doubleButton->setButtonText2(dialog.buttonText2());
     }
 }

 QAction *DoubleButtonTaskMenu::preferredEditAction() const
 {
     return m_editStateAction;
 }

 QList<QAction *> DoubleButtonTaskMenu::taskActions() const
 {
     QList<QAction *> list;
     list.append(m_editStateAction);
     return list;
 }

 DoubleButtonTaskMenuFactory::DoubleButtonTaskMenuFactory(QExtensionManager *parent)
     : QExtensionFactory(parent)
 {
 }

 QObject *DoubleButtonTaskMenuFactory::createExtension(QObject *object,
                                                    const QString &iid,
                                                    QObject *parent) const
 {
     if (iid != Q_TYPEID(QDesignerTaskMenuExtension))
         return 0;

     if (DoubleButton *doubleButton = qobject_cast<DoubleButton*>(object))
         return new DoubleButtonTaskMenu(doubleButton, parent);

     return 0;
 }
