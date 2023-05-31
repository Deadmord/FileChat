#include "ChatDirController.h"


ChatDirController::ChatDirController(QObject* parent)
	: QObject(parent)
	, _text("Default Text")
{
	connect(this, qOverload<int>(&ChatDirController::signal_1), this, qOverload<int>(&ChatDirController::on_signal_1));
	connect(this, qOverload<QString>(&ChatDirController::signal_1), this, qOverload<QString>(&ChatDirController::on_signal_1));
}

ChatDirController::ChatDirController(const ChatDirController& other)
{
	_text = other._text;
}

ChatDirController::~ChatDirController()
= default;

ChatDirController& ChatDirController::operator=(const ChatDirController& other)
{
	if (this != &other)
	{
		_text = other._text;
	}
	return *this;
}

void ChatDirController::initDir()
{
	//clear directory
		//-получить все файлы .txt
		//-удалить каждый фаил из списка полученных кроме фаила настроек
	//создать фаил настроек по умолчанию если его нет
	//создать фаил server_messages.txt
	//начать отслеживать эту директорию

	createMsgFile();
}

void ChatDirController::createMsgFile()
{
	writeToFile("Hello from server!");
	readFromFile("./server_messages.txt");
}

bool ChatDirController::writeToFile(const QString& msg)
{
	QByteArray buf;
	QFile file_out(qApp->applicationDirPath() + "/server_messages.txt");
	//QFile file_out("./server_messages.txt");
	auto res = file_out.open(QIODevice::WriteOnly | QIODevice::Append);
	if (!res)
	{
		qDebug() << "Error opening file for writing; error " << file_out.errorString();
		return res;
	}
	else
	{
		buf = msg.toUtf8();
		buf.append("\n");
		auto const bytes_written = file_out.write(buf);
		if (bytes_written == -1 || bytes_written < buf.size())
		{
			qDebug() << "Error writing to file; error " << file_out.errorString();
			return false;
		}
		else
		{
			qDebug() << "Wrote " << bytes_written << " bytes";
		}
		file_out.close();
	}
	return res;
}

QString ChatDirController::readFromFile(const QString& fileName)
{
	QByteArray buf;
	buf.clear();
	QFile file_in(qApp->applicationDirPath() + "/server_messages.txt");
	//QFile file_in("./server_messages.txt");
	auto res = file_in.open(QIODevice::ReadOnly);
	if (!res)
	{
		qDebug() << "Error opening file for reading; error " << file_in.errorString();
	}
	else
	{
		//buf = file_in.readAll();
		buf = file_in.readLine();
		qDebug() << "Read " << buf.size() << " bytes";
		qDebug() << "Content :  " << buf;
		qDebug() << buf;
	}
	return QString(buf);
}

//-----------slots------------
void ChatDirController::on_signal_1(int val)
{
	qDebug() << "MyClass1::on_signal_1: " << val;
}

void ChatDirController::on_signal_1(QString str)
{
	qDebug() << "MyClass1::on_signal_1: " << str;
}