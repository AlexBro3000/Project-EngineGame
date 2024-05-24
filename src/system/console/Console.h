#pragma once

class Console
{
public:
	/**
	 * @brief ������� �������������� ��������� � �������.
	 * @param message - ��������� ��� ������.
	 */
	static void Info(const char* message, const char* message_addition = nullptr);

	/**
	 * @brief ������� ��������������� ��������� � �������.
	 * @param message - ��������� ��� ������.
	 */
	static void Warn(const char* message, const char* message_addition = nullptr);

	/**
	 * @brief ������� ��������� �� ������ � �������.
	 * @param message - ��������� ��� ������.
	 */
	static void Error(const char* message, const char* message_addition = nullptr);

};