#include "config.h"
#include <QDebug>
#include <QCoreApplication>  
#include <QSettings>

config::config(QObject *parent)
	: QObject(parent)
{}

config::~config()
{}

void config::openSettingsfile(const QString& organization, const QString& application)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, organization, application);
    const QString p = settings.fileName();
    QProcess::startDetached("notepad.exe", QStringList() << settings.fileName());

}

QString config::saveSettings(const QString& organization, const QString& application, const QMap<QString, QVariant>& parameters, bool useIniFile)
{
    QSettings::Format format = useIniFile ? QSettings::IniFormat : QSettings::NativeFormat;
    QSettings settings(format, QSettings::UserScope, organization, application);

    QMapIterator<QString, QVariant> it(parameters);
    while (it.hasNext()) 
    {
        it.next();
        const QString& paramName = it.key();
        const QVariant& paramValue = it.value();

        // Split to groupe and name of parameters
        QStringList nameParts = paramName.split('.');
        if (nameParts.size() != 2) 
        {
            qDebug() << "wrong format nameline: " << paramName;
            continue;
        }

        const QString& group = nameParts.at(0);
        const QString& name = nameParts.at(1);

        settings.beginGroup(group);
        settings.setValue(name, paramValue);
        settings.endGroup();
    }

    return settings.fileName();
}

void config::loadSettings(const QString& organization, const QString& application, QMap<QString, QVariant>& parameters, bool useIniFile)
{
    QSettings::Format format = useIniFile ? QSettings::IniFormat : QSettings::NativeFormat;
    QSettings settings(format, QSettings::UserScope, organization, application);

    QStringList groups = settings.childGroups();
    foreach(const QString & group, groups) 
    {
        settings.beginGroup(group);
        QStringList keys = settings.childKeys();

        foreach(const QString & key, keys) {
            // get name at format "group.name"
            QString paramName = group + "." + key;
            QVariant paramValue = settings.value(key);
            parameters[paramName] = paramValue;
        }

        settings.endGroup();
    }
}