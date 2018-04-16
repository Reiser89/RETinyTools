#include "AddrConv.h"

namespace RETT {
	bool AddrConv::checkHexFormatOnChangeFast(String^ input)
	{
		return System::Text::RegularExpressions::Regex::IsMatch(input, "\\A\\b(0[xX])?[0-9a-fA-F]*\\b\\Z");
	}

	bool AddrConv::checkHexFormatOnChangeUsable(String^ input)
	{
		return System::Text::RegularExpressions::Regex::IsMatch(input, "\\A\\b(0[xX])?[0-9a-fA-F]+\\b\\Z");
	}

	bool AddrConv::validateOnLeaveHexTextField(String^ &input)
	{
		if (AddrConv::checkHexFormatOnChangeUsable(input)) // Check if input is valid hex
		{
			if (!System::Text::RegularExpressions::Regex::IsMatch(input, "\\A\\b(0[xX]){1}[0-9a-fA-F]+\\b\\Z"))
			{ // Add 0x if not already present
				input = "0x" + input;
			}
			return true;
		}
		else
		{	// If not call parse-function
			// call parse function
			// call this function again here to revalidate (carefull danger-loop)
			input = "fail";
		}

		return false;
	}

	bool AddrConv::textFieldHexLeave(System::Windows::Forms::TextBox ^textBox)
	{
		String^ item = textBox->Text;
		if (AddrConv::validateOnLeaveHexTextField(item))
		{
			textBox->Text = item;
			return true;
		}
		else
		{
			textBox->Text = "";
			return false;
		}
	}

	bool AddrConv::textFieldHexTextChanged(System::Windows::Forms::TextBox ^textBox)
	{
		int reduced = 0; // Reduced chars (for setting the selection on the correct position

		if (!AddrConv::checkHexFormatOnChangeFast(textBox->Text)) // Basic RegEx check
		{ // If Regex fails check in detail and remove unwanted chars
			String^ item = textBox->Text;
			String^ newitem = L"";
			int pos = textBox->SelectionStart;
			wchar_t c;

			for (int i = 0; i < item->Length; i++)
			{
				if (((i - reduced) == 1 && (item[i] == 'x' || item[i] == 'X')) ||
					AddrConv::checkHexFormatOnChangeUsable(newitem + item[i]))
				{
					newitem += item[i];
				}
				else
				{
					reduced++;
				}
			}
			textBox->Text = newitem;
			pos -= reduced;
			textBox->SelectionStart = pos < 0 ? 0 : pos;

			return reduced > 0; // return true, if something has changed
		}
		return false;
	}

	std::vector<Byte> getHexFromString(String^ input)
	{
		std::vector<Byte> hex;

		if (input->Length < 3)
			return hex;

		input = input->Substring(2); // Cut off 0x

		size_t len = input->Length;
		len = len / 2 + (1 * len % 2); // add 1 more element if odd
		hex.resize(len);

		Char c;
		int pos;
		Byte tmp;
		short odd = input->Length % 2; // Importaint on odd hex-values like: 0x123 (to not get 0x1230)
									   //for (int i = input->Length, n = 0; i >= 0; i--, n++) // i counts down to select char in input, n counts up for pos-index
		for (int i = 0; i < input->Length; i++)
		{
			c = input[input->Length - i - 1]; // get char of input in reversed order

			pos = i; // Store 2 converted chars in one byte, adds 1 if odd strlen
			pos -= pos % 2; // -1 if odd
			pos /= 2;

			// From ascii-able:
			// 0 - 9 = 48...57  -> -48
			// A - F = 65...70  -> -54
			// a - f = 97...102 -> -86
			tmp = c;
			tmp -= c > 96 ? 86 : (c > 64 ? 54 : 48);
			//hex[pos] = (i + odd) % 2 ? hex[pos] : tmp;
			//hex[pos] += (i + odd) % 2 ? 0x10 * tmp : 0;
			hex[pos] = (i) % 2 ? hex[pos] : tmp;
			hex[pos] += (i) % 2 ? 0x10 * tmp : 0;
			//retval += String::Format("{0:X}", input[i]);
		}

		return hex;
	}

	String^ getStringFromHex(std::vector<Byte> input)
	{
		String^ retval = nullptr;

		Char c;
		int pos;
		Byte hx;
		bool first = true;
		//for each (Byte hx in input) {
		for (int i = 0; i < input.size(); i++)
		{
			hx = input[input.size() - i - 1];  // Get hex numbers in reverse order
			for (int pos = 0; pos < 2; pos++)
			{
				c = pos == 1 ? (hx & 0x0F) : ((hx & 0xF0) / 0x10);
				//std::cout << (int)hx << " ";
				// From ascii-able:
				// 0 - 9 = 48...57  -> +48
				// A - F = 65...70  -> +54
				c += c > 9 ? 54 : 48;

				// Do not add leading zero:
				retval += (!first || c != 48) ? String::Format("{0}", c) : "";
				first = false;
			}
		}

		return "0x" + retval;
	}

	String^ AddrConv::convRVA(String^ input)
	{
		//String^ retval = nullptr;
		//for each (Char ch in input) {
		//	array<Byte>^ bytes = BitConverter::GetBytes(ch);
		//	//array<Byte>^ bytes = BitConverter::GetBytes;
		//	//retval += String::Format("{0:X2} {1:X2} ", bytes[1], bytes[0]);
		//	retval += String::Format("{1:X2}", bytes[0]);
		//}
		//return retval;


		//double hex;
		String^ input2 = input;

		String^ retval = nullptr;
		for each (Char ch in input) {
			array<Byte>^ bytes = BitConverter::GetBytes(ch);
			//	retval += String::Format("{0:X}", ch);
		}
		//textBoxVA->Text = retval;

		//array<Byte>^ bytes = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf };
		//array<Byte>^ bytes = { 0x11,0x22,0x33,0x44 };
		//for each (Char ch in bytes) {
		//for (int i = 0; (Char ch in hexFrom) {
		//retval += String::Format("{0:X}", ch);
		//retval += String::Format("{0}", ch);
		//}

		//std::vector<Byte> hex; // Technically we only use 4 bit

		//for (int i = 0; i < input->Length; i++)
		//{
		//	retval += String::Format("{0:X}", input[i]);
		//}
		//for each (Char ch in input) {

		//	//retval += String::Format("{0:X}", ch);
		//	//retval += String::Format("{0}", ch);
		//}

		std::vector<Byte> hex = getHexFromString(input);
		retval = getStringFromHex(hex);

		//wchar_t buf[19];
		//swprintf_s(buf, 19, L"0x%16llx", hex[0]);
		//MessageBox(0, buf, L"Wrapper", 0);


		return retval;
	}

	String^ AddrConv::convVA(String^ input)
	{
		return "";
	}
}
