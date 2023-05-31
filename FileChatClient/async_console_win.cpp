#include "async_console_win.h"

extern int gl_exit_timeout;

#if defined (Q_OS_WIN)
asyncConsoleWin::asyncConsoleWin(QObject *parent)
	: QObject(parent)
{
    inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    notifier = new QWinEventNotifier(inputHandle, this);
    connect(notifier, &QWinEventNotifier::activated, this, &asyncConsoleWin::handleInput);
}


void asyncConsoleWin::handleInput(HANDLE h)
{
    INPUT_RECORD inputBuffer[128];
    DWORD numEventsRead;
    if (ReadConsoleInput(inputHandle, inputBuffer, 128, &numEventsRead)) {
        for (DWORD i = 0; i < numEventsRead; ++i) {
            if (inputBuffer[i].EventType == KEY_EVENT && inputBuffer[i].Event.KeyEvent.bKeyDown) {
                WCHAR ch = inputBuffer[i].Event.KeyEvent.uChar.UnicodeChar;
                if (ch != '\r' && ch != '\n')
                {
                    std::wcout << ch;
                    lineBuffer.append(ch);
                }
                else
                {
                    std::wcout << std::endl;
                    processInput(lineBuffer);
                    lineBuffer.clear();
                }
            }
        }
    }
}

void asyncConsoleWin::processInput(const QString& input)
{
    QTextStream qout(stdout);
    qDebug() << "You entered: " << input;

    // Exit the application if the user types "quit"  
    if (input == "quit")
    {
        qDebug() << "Command \"quit\" detected. Exiting in " << gl_exit_timeout << "ms...";
        QTimer::singleShot(gl_exit_timeout, qApp, &QCoreApplication::quit);
    }
    else
    {
        qDebug() << "Unknown command detected. You entered: " << input;
    }


}
#endif
