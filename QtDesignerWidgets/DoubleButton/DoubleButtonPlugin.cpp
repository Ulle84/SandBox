#include "DoubleButton.h"
#include "DoubleButtonPlugin.h"

#include <QtPlugin>
#include <QExtensionManager>
#include <QDesignerFormEditorInterface>

#include "DoubleButtonTaskMenu.h"

DoubleButtonPlugin::DoubleButtonPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void DoubleButtonPlugin::initialize(QDesignerFormEditorInterface* core)
{
  if (m_initialized)
    return;

  QExtensionManager *manager = core->extensionManager();
  Q_ASSERT(manager != 0);

  manager->registerExtensions(new DoubleButtonTaskMenuFactory(manager),
                              Q_TYPEID(QDesignerTaskMenuExtension));

  m_initialized = true;
}

bool DoubleButtonPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *DoubleButtonPlugin::createWidget(QWidget *parent)
{
  return new DoubleButton(parent);
}

QString DoubleButtonPlugin::name() const
{
  return QLatin1String("DoubleButton");
}

QString DoubleButtonPlugin::group() const
{
  return QLatin1String("Vitronic");
}

QIcon DoubleButtonPlugin::icon() const
{
  return QIcon();
}

QString DoubleButtonPlugin::toolTip() const
{
  return QLatin1String("Double button");
}

QString DoubleButtonPlugin::whatsThis() const
{
  return QLatin1String("Double button for testing the designer plugin mechanism");
}

bool DoubleButtonPlugin::isContainer() const
{
  return true;
}

QString DoubleButtonPlugin::domXml() const
{
  return QLatin1String("<widget class=\"DoubleButton\" name=\"doubleButton\"></widget>\n");
  //return QLatin1String("<widget class=\"DoubleButton\" name=\"doubleButton\">\n  <addpagemethod>addPage</addpagemethod>\n</widget>\n");
}

QString DoubleButtonPlugin::includeFile() const
{
  return QLatin1String("DoubleButton.h");
}

Q_EXPORT_PLUGIN2(doublebuttonplugin, DoubleButtonPlugin)
