#pragma once
#include <QCoreApplication>
#include <QVariant>
#include <QSize>
#include <QPoint>
#include <QColor>
#include <QFont>
#include "config.h"
#include "fontFormater.h"

class settings
{
public:
	static void openSettingsfile();

	static void saveSettings();

	static void loadSettings();

	static QString serverName();

	static QString salutation();

	static font defaultText();

	static font userText();

private:

	static QString serverName_;
	static QString salutation_;
	static font _defaultText;
	static font _userText;

};
