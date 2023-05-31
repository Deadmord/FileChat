#include "file_watcher.h"

#include <QCoreApplication>  
#include <QFile>  
#include <QDir>  
#include <QDirIterator>  
#include <QFileInfo>  
#include <QFileSystemWatcher>  
#include <QDebug>
#include <ranges>

const auto print_info = [](const QString& path)
{
    const QFileInfo file_info(path);
    if (file_info.isFile())
    {
        qDebug() << "\tFile size:" << file_info.size();
        qDebug() << "\tFile path:" << file_info.absoluteFilePath();
    }
    else
    {
        qDebug() << "Directory path:" << file_info.absoluteFilePath();
    }
};

file_watcher::file_watcher(QObject *parent)
	: QObject(parent)
{
}

file_watcher::~file_watcher()
{}

void file_watcher::print_info(const QStringList& path_list)
{
	for (const auto& path : path_list)
	{
		print_info(path);
	}
}

void file_watcher::print_info(const QString& path)
{
    const QFileInfo file_info(path);
    if (file_info.isFile())
    {
        qDebug() << "\t|- File path:" << file_info.absoluteFilePath();
        qDebug() << "\t|---- Size:" << file_info.size();
        qDebug() << "\t|---- Time:" << file_info.birthTime().toString();
    }
    else
    {
        qDebug() << "Directory path:" << file_info.absoluteFilePath();
    }
}

QStringList file_watcher::find_all_file_1(const QString& root_path, const QString& ext)
{
    QStringList out;
    QDirIterator it(root_path, QStringList() << ext, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
	while (it.hasNext())
	{
        out << it.next();
	}
    return out;
}

QStringList file_watcher::find_all_file_2(const QString& root_path, const QString& ext)
{
    QStringList out;
	QDir dir(root_path);
    dir.setNameFilters(QStringList{}  << ext );
    
    QStringList entries = dir.entryList( QDir::Files | QDir::AllDirs | QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QString& entry : entries)
    {
        auto const path = dir.absoluteFilePath(entry);
        out << path;
	    if (QFileInfo file_info(path); file_info.isDir())
        {
            out << find_all_file_2(file_info.absoluteFilePath(), ext);
        }
    }
    return out;
}

QStringList file_watcher::find_all_folders(const QString& root_path)
{
    QStringList out;
	QDirIterator it(root_path, QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
	while (it.hasNext())
	{
		out << it.next();
	}
	return out;
}

void file_watcher::start_folder_watcher(const QString& folder_path)
{
    auto file_system_event = [this](const QString& path)
    {
        auto const& info = QFileInfo(path);
        if (info.isFile())
        {
            if (watcher.files().contains(path))
            {
                emit file_changed(path, FILE_CHANGED);
            }
            else
            {
                emit file_changed(path, FILE_DELETED);
            }
        }
        else
        {
            if (!watcher.files().contains(path))
            {
                emit file_changed(path, FILE_ADDED);
            }
        }
    };

    auto const& watched_list = find_all_file_2(folder_path, "*.*");
    watcher.addPaths(watched_list);
	
    connect(&watcher, &QFileSystemWatcher::fileChanged, [this](const QString& path)
        {
            if (watcher.files().contains(path))
            {
                emit file_changed(path, FILE_CHANGED);
            }
            else
            {
                emit file_changed(path, FILE_DELETED);
            }
        }
    );

    connect(&watcher, &QFileSystemWatcher::directoryChanged, [this](const QString& path)
        {
            if (watcher.files().contains(path))
            {
                emit file_changed(path, FOLDER_CHANGED);
            }
            else
            {
                emit file_changed(path, FILE_DELETED);
            }
        }
    );
}
