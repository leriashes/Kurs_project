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
	static string RetDate(int n, int type);
	static string ConvTime(time_t t, int type);
	static string RetTime(int fun);

	static bool loadingComplete;
	static void PrintLoading();


};

