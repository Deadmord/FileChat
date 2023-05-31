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
	gl_file_watcher = new file_watcher(nullptr);

	qDebug() << "\n------------ Initialize chat directory -------------";
	qDebug() << "\n----------- clear message history files ------------";
	clearDir();
	qDebug() << "\n------------------ load settings -------------------";
	initSettingsFile();
	qDebug() << "\n------------ create server_messages.txt ------------";
	createMsgFile();
	qDebug() << "\n-------------- start monitoring chat----------------";
	startWatcher();

	//вывести консольные команды


}

void ChatDirController::clearDir()
{
	qDebug() << " Find files : ";
	gl_file_watcher->delete_files(gl_file_watcher->find_all_file_1(qApp->applicationDirPath(), "*.txt"));
}

void ChatDirController::initSettingsFile()
{
	if (!gl_file_watcher->find_all_file_1(qApp->applicationDirPath(), "config.ini").size())
	{
		qDebug() << "config file not found. Create default config: ";
	}
	qDebug() << "Load settings: ";
	settings::loadSettings();
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
void ChatDirController::startWatcher()
{
	gl_file_watcher = new file_watcher(nullptr);

	gl_file_watcher->start_folder_watcher(qApp->applicationDirPath());
	QObject::connect(gl_file_watcher, &file_watcher::file_changed, [](QString const& file_name, int change_type)
		{
			switch (const auto ctype = static_cast<FILE_CHANGE_TYPE>(change_type))
			{
			case FILE_ADDED: qDebug() << "--- File watcher : File created: " << file_name; break;
			case FILE_CHANGED:  qDebug() << "--- File watcher : File changed: " << file_name; break;
			case FILE_DELETED:  qDebug() << "--- File watcher : File deleted: " << file_name; break;
			case FOLDER_CHANGED: qDebug() << "--- File watcher : Folder changed: " << file_name; break;
			}
		}
	);
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