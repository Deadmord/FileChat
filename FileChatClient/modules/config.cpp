#include "config.h"
#include <QDebug>
#include <QCoreApplication>  
#include <QSettings>
#include <QSize>
#include <QPoint>
#include <QColor>
#include <QFont>

config::config(QObject *parent)
	: QObject(parent)
{}

config::~config()
{}



QString config::saveSettings(const QString& organization, const QString& application, bool useIniFile)
{
    QSettings::Format format = useIniFile ? QSettings::IniFormat : QSettings::NativeFormat;

    QSettings settings(format, QSettings::UserScope, organization, application);

    settings.beginGroup("MainWindow");
    settings.setValue("size", QSize(800, 600));
    settings.setValue("position", QPoint(100, 100));
    settings.endGroup();

    settings.beginGroup("TextEditor");
    settings.setValue("font", QFont("Arial", 12));
    settings.setValue("color", QColor(Qt::black));
    settings.endGroup();
    return settings.fileName();
}

void config::loadSettings(const QString& organization, const QString& application, bool useIniFile)
{
    QSettings::Format format = useIniFile ? QSettings::IniFormat : QSettings::NativeFormat;

    QSettings settings(format, QSettings::UserScope, organization, application);

    settings.beginGroup("MainWindow");
    QSize size = settings.value("size", QSize(800, 600)).toSize();
    QPoint position = settings.value("position", QPoint(100, 100)).toPoint();
    settings.endGroup();

    settings.beginGroup("TextEditor");
    QFont font = settings.value("font", QFont("Arial", 12)).value<QFont>();
    QColor color = settings.value("color", QColor(Qt::black)).value<QColor>();
    settings.endGroup();

    qDebug() << "MainWindow size:" << size << "position:" << position;
    qDebug() << "TextEditor font:" << font << "color:" << color;
}