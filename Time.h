#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "time.h"
#include <string>
#include <chrono>
#include <ctime>  
#include <iostream>

#include <cstdlib>
using namespace std;
class Time
{
	string week[7] = { "ом", "бр", "яп", "вр", "ор", "яа", "бя" };



public:
	string DateRet(int n);
	string ConvTime(time_t t);
};

