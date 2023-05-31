#pragma once
#include <QObject>
#include <QFile>
#include <QDir>
#include <QProcess>

class config  : public QObject
{
	Q_OBJECT

public:
	config(QObject *parent);
	~config() override;

	static void openSettingsfile(const QString& organization, const QString& application, const QString& directory );
	static void loadSettings(const QString& organization, const QString& application, QMap<QString, QVariant>& parameters, const QString& directory, bool useIniFile = false);
	static QString saveSettings(const QString& organization, const QString& application, const QMap<QString, QVariant>& parameters, const QString& directory, bool useIniFile = false);

};
