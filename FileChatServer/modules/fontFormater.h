#pragma once
#include <QString>
#include <QMap>
#include <QDebug>

struct font 
{
    QString textAttribut;
    QString textColor; 
    QString bgColor;
};

class fontFormater
{
public:
    static void setFormat(const font& font);
    static void clear();

private:
    static QMap<QString, QString> textAttributes;
    static QMap<QString, QString> textColors;
    static QMap<QString, QString> backgroundColors;
};

