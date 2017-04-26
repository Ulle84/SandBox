#ifndef DOUBLEBUTTONTASKMENU_H
#define DOUBLEBUTTONTASKMENU_H


#include <QDesignerTaskMenuExtension>
 #include <QExtensionFactory>

 class QAction;
 class QExtensionManager;

 class DoubleButton;

 class DoubleButtonTaskMenu : public QObject, public QDesignerTaskMenuExtension
 {
     Q_OBJECT
     Q_INTERFACES(QDesignerTaskMenuExtension)

 public:
     DoubleButtonTaskMenu(DoubleButton *doubleButton, QObject *parent);

     QAction *preferredEditAction() const;
     QList<QAction *> taskActions() const;

 private slots:
     void editLabels();

 private:
     QAction* m_editStateAction;
     DoubleButton* m_doubleButton;
 };

 class DoubleButtonTaskMenuFactory : public QExtensionFactory
 {
     Q_OBJECT

 public:
     DoubleButtonTaskMenuFactory(QExtensionManager *parent = 0);

 protected:
     QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
 };


#endif // DOUBLEBUTTONTASKMENU_H
