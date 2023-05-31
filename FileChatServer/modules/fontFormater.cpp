#include "fontFormater.h"

void fontFormater::setFormat(const font& font)
{
    QString format;

    if (textAttributes.contains(font.textAttribut))
        format += textAttributes.value(font.textAttribut);

    if (textColors.contains(font.textColor))
        format += textColors.value(font.textColor);

    if (backgroundColors.contains(font.bgColor))
        format += backgroundColors.value(font.bgColor);

    qDebug().noquote() << format;
}

void fontFormater::clear()
{
    qDebug().noquote() << textAttributes.value("off");
}

QMap<QString, QString> fontFormater::textAttributes = {
    { "off", "\x1b[0m" },
    { "bold_on", "\x1b[1m" },
    { "dim_on", "\x1b[2m" },
    { "italic_on", "\x1b[3m" },
    { "underline_on", "\x1b[4m" },
    { "blink_on", "\x1b[5m" },
    { "bold_off", "\x1b[21m" },
    { "dim_off", "\x1b[22m" },
    { "italic_off", "\x1b[23m" },
    { "underline_off", "\x1b[24m" },
    { "blink_off", "\x1b[25m" }
};

QMap<QString, QString> fontFormater::textColors = {
    { "black", "\x1b[30m" },
    { "red", "\x1b[31m" },
    { "green", "\x1b[32m" },
    { "yellow", "\x1b[33m" },
    { "blue", "\x1b[34m" },
    { "magenta", "\x1b[35m" },
    { "cyan", "\x1b[36m" },
    { "white", "\x1b[37m" },
    { "default", "\x1b[39m" },
    { "light_gray", "\x1b[90m" },
    { "light_red", "\x1b[91m" },
    { "light_green", "\x1b[92m" },
    { "light_yellow", "\x1b[93m" },
    { "light_blue", "\x1b[94m" },
    { "light_magenta", "\x1b[95m" },
    { "light_cyan", "\x1b[96m" },
    { "light_white", "\x1b[97m" }
};

QMap<QString, QString> fontFormater::backgroundColors = {
    { "black", "\x1b[40m" },
    { "red", "\x1b[41m" },
    { "green", "\x1b[42m" },
    { "yellow", "\x1b[43m" },
    { "blue", "\x1b[44m" },
    { "magenta", "\x1b[45m" },
    { "cyan", "\x1b[46m" },
    { "white", "\x1b[47m" },
    { "default", "\x1b[49m" },
    { "light_gray", "\x1b[100m" },
    { "light_red", "\x1b[101m" },
    { "light_green", "\x1b[102m" },
    { "light_yellow", "\x1b[103m" },
    { "light_blue", "\x1b[104m" },
    { "light_magenta", "\x1b[105m" },
    { "light_cyan", "\x1b[106m" },
    { "light_white", "\x1b[107m" }
};
