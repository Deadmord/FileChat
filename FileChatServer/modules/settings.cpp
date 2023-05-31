#pragma once
#include "settings.h"

QString settings::serverName_;
QString settings::salutation_;
font settings::_defaultText;
font settings::_userText;

void settings::openSettingsfile()
{
    config::openSettingsfile(qApp->organizationName(), qApp->applicationName());
}

void settings::saveSettings()
{
    QMap<QString, QVariant> parameters;
    //parameters.insert("MainWindow.size", QSize(1024, 768));
    //parameters.insert("MainWindow.position", QPoint(200, 200));
    //parameters.insert("TextEditor.font", QFont("Helvetica", 14));
    //parameters.insert("TextEditor.color", QColor(Qt::blue));
    parameters.insert("DefaultText.textAttribute", QString("off"));
    parameters.insert("DefaultText.textColor", QString("light_blue"));
    parameters.insert("DefaultText.backgroundColor", QString("default"));
    parameters.insert("UsersText.textAttribute", QString("italic_on"));
    parameters.insert("UsersText.textColor", QString("light_cyan"));
    parameters.insert("UsersText.backgroundColor", QString("default"));
    parameters.insert("ServerSettings.name", QString("QT FileChat"));
    parameters.insert("ServerSettings.salutation", QString("Salutation from Settings"));

    auto ini_path = config::saveSettings(qApp->organizationName(), qApp->applicationName(), parameters, true); // Saves settings using INI files 
}

void settings::loadSettings()
{
    QMap<QString, QVariant> parameters;

    config::loadSettings(qApp->organizationName(), qApp->applicationName(), parameters, true); // Loads settings using INI files 

    QMapIterator<QString, QVariant> it(parameters);
    while (it.hasNext()) {
        it.next();
        qDebug() << it.key() << ": " << it.value();
    }
    
    //if (parameters.contains("DefaultText.textAttribute") && parameters.value("DefaultText.textAttribute").isValid())
    //    defaultText.textAttribut = parameters.value("DefaultText.textAttribute").toString();
    if (const QVariant v = parameters["DefaultText.textAttribute"]; v.isValid() && v.type() == QVariant::String)
        _defaultText.textAttribut = v.toString();
    if (const QVariant v = parameters["DefaultText.textColor"]; v.isValid() && v.type() == QVariant::String)
        _defaultText.textColor = v.toString();
    if (const QVariant v = parameters["DefaultText.backgroundColors"]; v.isValid() && v.type() == QVariant::String)
        _defaultText.bgColor = v.toString();
    if (const QVariant v = parameters["UsersText.textAttribute"]; v.isValid() && v.type() == QVariant::String)
        _userText.textAttribut = v.toString();
    if (const QVariant v = parameters["UsersText.textColor"]; v.isValid() && v.type() == QVariant::String)
        _userText.textColor = v.toString();
    if (const QVariant v = parameters["UsersText.backgroundColors"]; v.isValid() && v.type() == QVariant::String)
        _userText.bgColor = v.toString();

    if (const QVariant v = parameters["ServerSettings.name"]; v.isValid() && v.type() == QVariant::String)
        serverName_ = v.toString();
    if (const QVariant v = parameters["ServerSettings.salutation"]; v.isValid() && v.type() == QVariant::String)
        salutation_ = v.toString();
    qDebug() << "Settings loaded.";
    fontFormater::setFormat(_defaultText);
}

QString settings::serverName() { return serverName_; }

QString settings::salutation() { return salutation_; }

font settings::defaultText() { return _defaultText; }

font settings::userText() { return _userText; }
