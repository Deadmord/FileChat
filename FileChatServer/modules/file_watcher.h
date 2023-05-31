	#pragma once

#include <QObject>
#include <QFileSystemWatcher>

enum FILE_CHANGE_TYPE { FILE_CHANGED, FILE_ADDED, FILE_DELETED, FOLDER_CHANGED };

class file_watcher  : public QObject
{
	Q_OBJECT

public:
	file_watcher(QObject *parent);
	~file_watcher();

	QStringList find_all_file_1(const QString& root_path, const QString& ext);
	QStringList find_all_file_2(const QString& root_path, const QString& ext);
	QStringList find_all_file_3(const QString& root_path, const QString& ext);
	QStringList find_all_folders(const QString& root_path);

	void start_folder_watcher(const QString& folder_path);

	void print_info(const QStringList& path_list);
	void print_info(const QString& path);
	void delete_files(const QStringList& path_list);
	void delete_file(const QString& path);

Q_SIGNALS:

	void file_changed(const QString&, int);

private:

	QFileSystemWatcher watcher;
};
