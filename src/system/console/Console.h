#pragma once

class Console
{
public:
	/**
	 * @brief Выводит информационное сообщение в консоль.
	 * @param message - Сообщение для вывода.
	 */
	static void Info(const char* message, const char* message_addition = nullptr);

	/**
	 * @brief Выводит предупреждающее сообщение в консоль.
	 * @param message - Сообщение для вывода.
	 */
	static void Warn(const char* message, const char* message_addition = nullptr);

	/**
	 * @brief Выводит сообщение об ошибке в консоль.
	 * @param message - Сообщение для вывода.
	 */
	static void Error(const char* message, const char* message_addition = nullptr);

};