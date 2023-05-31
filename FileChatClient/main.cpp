#include <QtCore/QCoreApplication>
#include <QVariant> 
#include <QTimer> 
#include "modules/arg_parser.h"

#if defined (Q_OS_WIN)
#include "async_console_win.h"
#else

#endif

int gl_exit_timeout = 3000; // 3 sec
QString gl_salutation = "Hello World";
QString gl_arg_check_error = "";

const char* esc_normal = "\033[0m";

static void shutdown_routine()
{
    qDebug() << "AddPostRoutine : Application is finished. Have a nice day!..";
}

static void startup_routine()
{
    // set up some application settings
    qApp->setOrganizationName("C++ QT Course"); // through macro
    QCoreApplication::instance()->setOrganizationDomain("zionet.com"); // through member function of instance
    QCoreApplication::setApplicationName("FileChat client"); // through static function

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
    //qRegisterMetaType<MyClasses::MyClass1>();

    qDebug() << "----------------------------------------------------";
    qDebug() << "FileChat client is started.";
    qDebug() << "Salutation : " << gl_salutation; // this salutation we get from command line
    qDebug() << "----------------------------------------------------";

#if defined (Q_OS_WIN)
    (void)new asyncConsoleWin(qApp);
#else
    new ConsoleAppMac(qApp);
#endif

    qDebug() << "Enter text, or type '/quit' to exit:";
    QTimer::singleShot(0, [&]()
        {
            //do_examples();
            QTimer::singleShot(100, []() { qDebug() << "Press command \"/quit\" to quit..."; });
        });
}
Q_COREAPP_STARTUP_FUNCTION(startup_routine)

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}

