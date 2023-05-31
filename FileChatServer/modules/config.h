#pragma once
#include <QObject>
#include <QFile>
#include <QProcess>

class config  : public QObject
{
	Q_OBJECT

public:
	config(QObject *parent);
	~config() override;

	static void openSettingsfile(const QString& organization, const QString& application);
	static void loadSettings(const QString& organization, const QString& application, QMap<QString, QVariant>& parameters, bool useIniFile = false);
	static QString saveSettings(const QString& organization, const QString& application, const QMap<QString, QVariant>& parameters, bool useIniFile = false);

};
