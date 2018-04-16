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
			// A - F = 65...70  -> -55
			// a - f = 97...102 -> -87
			tmp = c;
			tmp -= c > 96 ? 87 : (c > 64 ? 55 : 48);
			hex[pos] = (i) % 2 ? hex[pos] : tmp;
			hex[pos] += (i) % 2 ? 0x10 * tmp : 0;
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
				// From ascii-able:
				// 0 - 9 = 48...57  -> +48
				// A - F = 65...70  -> +55
				c += c > 9 ? 55 : 48;

				// Do not add leading zero:
				retval += (!first || c != 48) ? String::Format("{0}", c) : "";
				first = false;
			}
		}

		return "0x" + retval;
	}

	std::vector<Byte> additionHex(std::vector<Byte> term0, std::vector<Byte> term1)
	{
		std::vector<Byte> res;
		int8_t carry = 0;
		size_t size0 = term0.size(), size1 = term1.size();
		size_t max_size = size0 > size1 ? size0 : size1;
		res.resize(max_size);

		// Byte-array's are little endian:
		for (int i = 0; i < max_size; i++)
		{
			res[i] = res[i] > 0 ? res[i] : 0x00; // Preset result (to prevent losing carry)
			res[i] += size0 > i ? (size1 > i ? (term0[i] + term1[i]) : term0[i]) : (size1 > i ? term1[i] : 0x0);
			carry = size0 > i && size1 > i ? ((int16_t)(term0[i] + term1[i] + carry) > 0xff ? 1 : 0) : 0;

			// Take carry from last operation
			if (carry)
			{
				if ((i + 1) < max_size)
				{
					res[i + 1] = 0x01;
				}
				else
				{
					res.push_back(0x01); // Add a new value with the carry (if byte-array is not big enought).
				}
			}
		}

		return res;
	}

	std::vector<Byte> subtractionHex(std::vector<Byte> minuend, std::vector<Byte> subtrahend)
	{
		std::vector<Byte> res;
		int8_t carry = 0;
		Byte result, subtract;
		bool negative = false;
		size_t size0 = minuend.size(), size1 = subtrahend.size();
		size_t max_size = size0 > size1 ? size0 : size1;

		// Byte-array's are little endian:
		for (int i = 0; i < max_size; i++)
		{
			result = size0 > i ? minuend[i] : 0x00; // temporary result value
			subtract = size1 > i ? subtrahend[i] + carry : carry; // value to subtract if exists
																  //negative = result < (subtract + carry) ? true : false;
			carry = (result < subtract) || (carry && subtract == 0x00) ? 1 : 0;
			result -= carry ? -0x100 + subtract : subtract; // Calculate

			if (size0 <= i && carry) // Check if result will get negative due to smaller minuend than subtrahend.
			{
				res.resize(1);
				res[0] = 0x00;
				return res;
			}

			res.push_back(result);
		}

		if (carry) // Positive carry would mean, there is a residual value => result is negative.
		{
			res.resize(1);
			res[0] = 0x00;
			return res;
		}

		// clean leading zeros:
		for (int i = res.size() - 1; i >= 0; i--)
		{
			if (res[i] == 0x00)
				res.pop_back();
			else
				break;
		}

		return res;
	}

	String^ AddrConv::convRVA(String^ inputVA, String^ inputBaseAddr)
	{
		std::vector<Byte> hexVA = getHexFromString(inputVA);
		std::vector<Byte> hexBaseAddr = getHexFromString(inputBaseAddr);

		// RVA = VA - ImageBase
		std::vector<Byte> hexResult = subtractionHex(hexVA, hexBaseAddr);

		String^ retval = getStringFromHex(hexResult);

		return retval;
	}

	String^ AddrConv::convVA(String^ inputRVA, String^ inputBaseAddr)
	{
		std::vector<Byte> hexRVA = getHexFromString(inputRVA);
		std::vector<Byte> hexBaseAddr = getHexFromString(inputBaseAddr);

		// VA = RVA + ImageBase
		std::vector<Byte> hexResult = additionHex(hexRVA, hexBaseAddr);

		String^ retval = getStringFromHex(hexResult);

		return retval;
	}
}
