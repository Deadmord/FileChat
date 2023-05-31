#pragma once
#include <QObject>

class config  : public QObject
{
	Q_OBJECT

public:
	config(QObject *parent);
	~config() override;

	static void loadSettings(const QString& organization, const QString& application, bool useIniFile = false);
	static QString saveSettings(const QString& organization, const QString& application, bool useIniFile = false);

};
