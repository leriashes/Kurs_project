#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "time.h"
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>  
#include <iostream>
#include <cstdlib>
#include <thread>
using namespace std;

class Time
{
public:
	static string RetDate(int n);
	static string ConvTime(time_t t);
	static string RetTime();

	static bool loadingComplete;
	static void PrintLoading();
};

