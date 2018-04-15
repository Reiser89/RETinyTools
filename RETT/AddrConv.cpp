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
}
