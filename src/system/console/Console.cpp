#include "Console.h"

#include <iostream>
#include <Windows.h>

void Console::Info(const char* message, const char* message_addition)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 3);
	std::cout << "Info:\t";
	SetConsoleTextAttribute(handle, 7);
	std::cout << message << std::endl;

	if (message_addition != nullptr) {
		const char* delimiter = "\n";
		const char* token = strtok(strdup(message_addition), delimiter);

		while (token != nullptr) {
			std::cout << "\t" << token << std::endl;
			token = strtok(nullptr, delimiter);
		}
	}
}

void Console::Warn(const char* message, const char* message_addition)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 6);
	std::cout << "Warn:\t";
	SetConsoleTextAttribute(handle, 7);
	std::cout << message << std::endl;

	if (message_addition != nullptr) {
		const char* delimiter = "\n";
		const char* token = strtok(strdup(message_addition), delimiter);

		while (token != nullptr) {
			std::cout << "\t" << token << std::endl;
			token = strtok(nullptr, delimiter);
		}
	}
}

void Console::Error(const char* message, const char* message_addition)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 4);
	std::cout << "Error:\t";
	SetConsoleTextAttribute(handle, 7);
	std::cout << message << std::endl;

	if (message_addition != nullptr) {
		const char* delimiter = "\n";
		const char* token = strtok(strdup(message_addition), delimiter);

		while (token != nullptr) {
			std::cout << "\t" << token << std::endl;
			token = strtok(nullptr, delimiter);
		}
	}
}