#include "config.h"
#include <QDebug>
#include <QCoreApplication>  
#include <QSettings>

#define SETTINGS_FILE "config"

config::config(QObject *parent)
	: QObject(parent)
{}

config::~config()
{}

void config::openSettingsfile(const QString& organization, const QString& application, const QString& directory)
{
    QString filePath = QDir(directory).filePath(QString("%1.ini").arg(SETTINGS_FILE));
    QSettings settings(filePath, QSettings::IniFormat, new QObject());

    const QString p = settings.fileName();
    QProcess::startDetached("notepad.exe", QStringList() << settings.fileName());

}

QString config::saveSettings(const QString& organization, const QString& application, const QMap<QString, QVariant>& parameters, const QString& directory, bool useIniFile)
{
    QSettings::Format format = useIniFile ? QSettings::IniFormat : QSettings::NativeFormat;
    //QString filePath = QDir(directory).filePath(QString("%1.ini").arg(application));
    QString filePath = QDir(directory).filePath(QString("%1.ini").arg(SETTINGS_FILE));
    //QSettings settings(format, QSettings::UserScope, organization, application);
    //QSettings settings(format, QSettings::UserScope, organization, application, new QObject());
    //QSettings settings(QSettings::UserScope, new QObject());      //save in registr
    QSettings settings(filePath, QSettings::IniFormat, new QObject());
    //settings.setPath(QSettings::IniFormat, QSettings::UserScope, filePath);


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

void config::loadSettings(const QString& organization, const QString& application, QMap<QString, QVariant>& parameters, const QString& directory, bool useIniFile)
{
    QSettings::Format format = useIniFile ? QSettings::IniFormat : QSettings::NativeFormat;
    QString filePath = QDir(directory).filePath(QString("%1.ini").arg(SETTINGS_FILE));
    QSettings settings(filePath, QSettings::IniFormat, new QObject());

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