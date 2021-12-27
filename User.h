#pragma once
#include "Menu.h"

class User
{
private:
	static bool admin;
	static string password;
	static string parol;

public:
	static bool GetAdmin();
	static bool SignIn();
	static void AdminLogIn();
	static void AdminLogOut();
	static void Admin(Cinema& cinema, File_O& file_stream);
};