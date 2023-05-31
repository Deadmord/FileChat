#pragma once
#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include "modules/file_watcher.h"

static file_watcher* gl_file_watcher = nullptr;

class ChatDirController : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString	text MEMBER _text READ get_text WRITE set_text NOTIFY text_changed RESET reset_text)
public:

	explicit ChatDirController(QObject* parent = nullptr);
	ChatDirController(const ChatDirController& other);
	~ChatDirController() override;
	ChatDirController& operator = (const ChatDirController& other);

Q_SIGNALS:

	void signal_1(int val);
	void signal_1(QString str);
	void text_changed(const QString& newText);

public:
	void initDir();

	[[nodiscard]] QString get_text() const { return _text; }
	void set_text(const QString& val)
	{
		_text = val; emit text_changed(val);
	}
	void reset_text() { _text.clear(); }

public Q_SLOTS:

	void on_signal_1(int val);
	void on_signal_1(QString str);

private:
	void clearDir();
	void createMsgFile();
	bool writeToFile(const QString& msg);
	QString readFromFile(const QString& fileName);

private:
	QString _text;


};

Q_DECLARE_METATYPE(ChatDirController)


