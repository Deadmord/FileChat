#pragma once
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QTextStream>  
#include <ranges>

const char* esc_normal = "\033[0m";

const std::vector<const char*> colors_list =
{
    "\x1B[31m"
    ,"\x1B[32m"
    ,"\x1B[33m"
    ,"\x1B[34m"
    ,"\x1B[35m"
    ,"\x1B[36m"
    ,"\x1B[37m"
    ,"\x1B[93m"
    ,"\033[1;41;30m"
    ,"\033[2;41;30m"
    ,"\033[3;41;30m"
    ,"\033[3;42;30m"
    ,"\033[3;43;30m"
    ,"\033[3;44;30m"
    ,"\033[3;45;30m"
    ,"\033[3;46;30m"
    ,"\033[3;47;30m"
    ,"\033[3;50;30m"
};

void print_colors()
{
    qDebug() << "------  Color Table  ------";
    std::ranges::for_each(colors_list, [](auto const& f) { std::cout << f << "Colored Texting" << esc_normal << std::endl; });
    qDebug() << "----------------------------";
}