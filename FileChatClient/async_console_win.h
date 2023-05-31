#pragma once

#include <QCoreApplication>
#include <QObject>
#include <iostream>
#include <QTextStream>
#include <QDebug>
#include <QTimer>
#include "modules/config.h"

#if defined (Q_OS_WIN)
#   include <windows.h>  
#   include <QWinEventNotifier>

class asyncConsoleWin  : public QObject
{
	Q_OBJECT

public:
	asyncConsoleWin(QObject *parent);
	~asyncConsoleWin() override = default;

public Q_SLOTS :

	void handleInput(HANDLE h);

private :
	void processInput(const QString& input);

	HANDLE inputHandle;
	QWinEventNotifier* notifier;
	QString lineBuffer;
};
#endif	