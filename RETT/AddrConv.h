#pragma once
#include <vector>
#include <array>

namespace RETT {
	using namespace System;

	public class AddrConv
	{

	public:
		static bool checkHexFormatOnChangeFast(String^ input); // Checks for correct hex-syntax on typing ("0x" accepted)
		static bool checkHexFormatOnChangeUsable(String^ input); // Checks for correct hex-syntax after finishing typing (0x0, 0x1234, 5ABC for example, but not 0x)
		static bool validateOnLeaveHexTextField(String^ &input); // Will be called on leaving the TextField to final check the correct hex-format (it will add 0x if not exists on beginning)
		static bool textFieldHexLeave(System::Windows::Forms::TextBox ^textBox); // Handles Hex-TextBox on leave
		static bool textFieldHexTextChanged(System::Windows::Forms::TextBox ^textBox); // Handles Hex-TextBox on TextChange
		static String^ convRVA(String^ input); // Converts hex in form of a String from VA+BaseAddr to RVA
		static String^ convVA(String^ input); // Converts hex in form of a String from RVA+BaseAddr to VA
	//private:
	};
}

