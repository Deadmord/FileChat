#include <QtCore/QCoreApplication>
#include <QTimer> 
#include "modules/arg_parser.h"
#include "modules/fontFormater.h"
#include "ChatDirController.h"

#if defined (Q_OS_WIN)
#include "async_console_win.h"
#else

#endif

int gl_exit_timeout = 3000; // 3 sec
QString gl_serverName = "Default global name";
QString gl_salutation = "Hello World";
QString gl_arg_check_error = "";
ChatDirController chatDirController;

static void shutdown_routine()
{
    qDebug() << "AddPostRoutine : Application is finished. Have a nice day!..";
}

static void startup_routine()
{
    // set up some application settings
    qApp->setOrganizationName("C++ QT Course"); // through macro
    QCoreApplication::instance()->setOrganizationDomain("zionet.com"); // through member function of instance
    QCoreApplication::setApplicationName("FileChat server"); // through static function

    // add QT post exit rotine
    qAddPostRoutine(shutdown_routine);

    // add a routine to be executed just before application exits through signal
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, []()
        {
            qDebug() << "AboutToQuit : Application is finished. Have a nice day!..";;
        }
    );

    // check command line arguments
    auto const success = argParser::instance().parse(qApp->arguments(), gl_arg_check_error);
    if (!success)
    {
        qDebug() << gl_arg_check_error;
        argParser::show_help();
        QTimer::singleShot(gl_exit_timeout, qApp, &QCoreApplication::quit);
        return;
    }
    gl_exit_timeout = argParser::instance().exit_timeout();
    gl_salutation = argParser::instance().salutation();



    // register some meta types
    qRegisterMetaType<ChatDirController>();

    fontFormater::setFormat({ "blink_on", "white", "green" });
    qDebug() << "----------------------------------------------------";
    qDebug() << qApp->organizationName() << "                                    ";
    qDebug() << "FileChat server starting..." << "                        ";
    qDebug() << "Salutation : " << gl_salutation << "                  "; // this salutation we get from command line
    qDebug() << "----------------------------------------------------";
    fontFormater::clear();

#if defined (Q_OS_WIN)
    (void)new asyncConsoleWin(qApp);
#else
    new ConsoleAppMac(qApp);
#endif

    QTimer::singleShot(0, [&]()
        {
            chatDirController.initDir();        // Initialize and start server

            fontFormater::setFormat({ "bold_on", "light_green", "default" });
            qDebug() << "----------------------------------------------------";
            gl_serverName = settings::serverName();
            gl_salutation = settings::salutation();
            qDebug() << "ServerName : " << gl_serverName;
            qDebug() << "Salutation : " << gl_salutation;
            qDebug() << "----------------------------------------------------";
            fontFormater::setFormat(settings::defaultText());

            QTimer::singleShot(100, []() { qDebug() << "Enter text or command, type command \"/quit\" to quit..."; });
        });
}
Q_COREAPP_STARTUP_FUNCTION(startup_routine)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
