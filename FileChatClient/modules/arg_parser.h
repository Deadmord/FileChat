#pragma once
#include <QString>

#include <QCommandLineParser>  
#include <QCommandLineOption> 

class argParser
{
public:
    argParser() = default;
    ~argParser() = default;

    static argParser& instance()
    {
        static argParser _instance;
        return _instance;
    }

    bool parse(const QStringList& command_line_args, QString& message)
    {
        auto parser = init();

    	// Process and check the provided command line arguments  
        parser->process(command_line_args);
        _gui = parser->isSet(_guiOption);
        bool b_valid = true;
        const int console_timeout = parser->isSet(_timeoutOption) ? parser->value(_timeoutOption).toInt(&b_valid) : 1000;
        if (!b_valid || console_timeout < 1000 || console_timeout > 10000)
        {
            message = "Argument parser error ! Incorrect argument \"timeout\"";
            _help_string = parser->helpText();
            return false;
        }

        _exit_timeout = console_timeout;

        if (parser->isSet(_saluteOption))
        {
            _salutation = parser->value(_saluteOption);
        }


        qDebug() << "Is GUI ?:" << _gui;
        qDebug() << "Exit timeout:" << _exit_timeout;
        qDebug() << "Salutation String:" << _salutation;
        return true;
    }

    static void show_help()
    {
        init()->showHelp();
    }

    [[nodiscard]] bool is_gui() const { return _gui; }
    [[nodiscard]] bool exit_timeout() const { return _exit_timeout; }
    [[nodiscard]] QString salutation() const { return _salutation; }
    [[nodiscard]] QString get_help() const { return _help_string; }

private:
    static QSharedPointer<QCommandLineParser> init()
    {
        QSharedPointer<QCommandLineParser> ret_val = QSharedPointer<QCommandLineParser>(new QCommandLineParser);
        ret_val->addHelpOption();
        ret_val->addVersionOption();
        ret_val->setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);

        ret_val->setApplicationDescription("Qt Examples Program");

        // Add two flags  
        ret_val->addOption(_guiOption);
    	ret_val->addOption(_timeoutOption);

        // Add an argument with a value  
        ret_val->addOption(_saluteOption);
        return ret_val;
    }

    bool _gui = true;
    int _exit_timeout = -1;
    QString _salutation = "Default Salutaton";
    QString _help_string;

    static inline const QCommandLineOption _guiOption = { QStringList{} << "gui" << "g", "Run GUI  version" };
    static inline const QCommandLineOption _timeoutOption = { QStringList {} << "timeout" << "t", "Console timeout ( should be in range 1000 - 10000 )", "timeout" };
    static inline const QCommandLineOption _saluteOption = { QStringList{} << "salutation" << "s", "First string", "salutation"
};
};
