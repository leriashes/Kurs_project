#pragma once
#include "Menu.h"

class User
{
private:
	static bool admin;

public:
	static bool GetAdmin();
	static bool SignIn();
	static bool AdminLogIn();
	static void Admin(Cinema& cinema, File_O& file_stream);
};