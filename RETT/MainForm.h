#pragma once

#include "AddrConv.h"

namespace RETT {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
		public:
			MainForm(void)
			{
				InitializeComponent();
				//
				//TODO: Add the constructor code here
				//
			}

		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~MainForm()
			{
				if (components)
				{
					delete components;
				}
			}
		private: System::Windows::Forms::GroupBox^  groupBox1;
		protected:
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Button^  buttonConvRVA;
		private: System::Windows::Forms::Button^  buttonConvVA;

		private: System::Windows::Forms::TextBox^  textBoxImagebase;
		private: System::Windows::Forms::TextBox^  textBoxRVA;
		private: System::Windows::Forms::TextBox^  textBoxVA;
		private: System::Windows::Forms::Label^  label3;

		private:
			/// <summary>
			/// Required designer variable.
			/// </summary>
			System::ComponentModel::Container ^components;

	#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
			{
				System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
				this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				this->buttonConvRVA = (gcnew System::Windows::Forms::Button());
				this->buttonConvVA = (gcnew System::Windows::Forms::Button());
				this->textBoxImagebase = (gcnew System::Windows::Forms::TextBox());
				this->textBoxRVA = (gcnew System::Windows::Forms::TextBox());
				this->textBoxVA = (gcnew System::Windows::Forms::TextBox());
				this->label2 = (gcnew System::Windows::Forms::Label());
				this->label3 = (gcnew System::Windows::Forms::Label());
				this->label1 = (gcnew System::Windows::Forms::Label());
				this->groupBox1->SuspendLayout();
				this->SuspendLayout();
				// 
				// groupBox1
				// 
				this->groupBox1->Controls->Add(this->buttonConvRVA);
				this->groupBox1->Controls->Add(this->buttonConvVA);
				this->groupBox1->Controls->Add(this->textBoxImagebase);
				this->groupBox1->Controls->Add(this->textBoxRVA);
				this->groupBox1->Controls->Add(this->textBoxVA);
				this->groupBox1->Controls->Add(this->label2);
				this->groupBox1->Controls->Add(this->label3);
				this->groupBox1->Controls->Add(this->label1);
				this->groupBox1->Location = System::Drawing::Point(12, 12);
				this->groupBox1->Name = L"groupBox1";
				this->groupBox1->Size = System::Drawing::Size(390, 98);
				this->groupBox1->TabIndex = 0;
				this->groupBox1->TabStop = false;
				this->groupBox1->Text = L"Addresses";
				// 
				// buttonConvRVA
				// 
				this->buttonConvRVA->Enabled = false;
				this->buttonConvRVA->Location = System::Drawing::Point(329, 69);
				this->buttonConvRVA->Name = L"buttonConvRVA";
				this->buttonConvRVA->Size = System::Drawing::Size(55, 23);
				this->buttonConvRVA->TabIndex = 6;
				this->buttonConvRVA->Text = L"↑Conv";
				this->buttonConvRVA->UseVisualStyleBackColor = true;
				this->buttonConvRVA->Click += gcnew System::EventHandler(this, &MainForm::buttonConvRVA_Click);
				// 
				// buttonConvVA
				// 
				this->buttonConvVA->Enabled = false;
				this->buttonConvVA->Location = System::Drawing::Point(329, 43);
				this->buttonConvVA->Name = L"buttonConvVA";
				this->buttonConvVA->Size = System::Drawing::Size(55, 23);
				this->buttonConvVA->TabIndex = 5;
				this->buttonConvVA->Text = L"↓Conv";
				this->buttonConvVA->UseVisualStyleBackColor = true;
				this->buttonConvVA->Click += gcnew System::EventHandler(this, &MainForm::buttonConvVA_Click);
				// 
				// textBoxImagebase
				// 
				this->textBoxImagebase->Location = System::Drawing::Point(164, 19);
				this->textBoxImagebase->Name = L"textBoxImagebase";
				this->textBoxImagebase->Size = System::Drawing::Size(159, 20);
				this->textBoxImagebase->TabIndex = 1;
				this->textBoxImagebase->Text = L"0x400000";
				this->textBoxImagebase->Click += gcnew System::EventHandler(this, &MainForm::textBoxImagebase_Click);
				this->textBoxImagebase->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxImagebase_TextChanged);
				this->textBoxImagebase->Leave += gcnew System::EventHandler(this, &MainForm::textBoxImagebase_Leave);
				// 
				// textBoxRVA
				// 
				this->textBoxRVA->Location = System::Drawing::Point(164, 71);
				this->textBoxRVA->Name = L"textBoxRVA";
				this->textBoxRVA->Size = System::Drawing::Size(159, 20);
				this->textBoxRVA->TabIndex = 3;
				this->textBoxRVA->Click += gcnew System::EventHandler(this, &MainForm::textBoxRVA_Click);
				this->textBoxRVA->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxRVA_TextChanged);
				this->textBoxRVA->Leave += gcnew System::EventHandler(this, &MainForm::textBoxRVA_Leave);
				// 
				// textBoxVA
				// 
				this->textBoxVA->Location = System::Drawing::Point(164, 45);
				this->textBoxVA->Name = L"textBoxVA";
				this->textBoxVA->Size = System::Drawing::Size(159, 20);
				this->textBoxVA->TabIndex = 2;
				this->textBoxVA->Click += gcnew System::EventHandler(this, &MainForm::textBoxVA_Click);
				this->textBoxVA->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxVA_TextChanged);
				this->textBoxVA->Leave += gcnew System::EventHandler(this, &MainForm::textBoxVA_Leave);
				// 
				// label2
				// 
				this->label2->AutoSize = true;
				this->label2->Location = System::Drawing::Point(6, 48);
				this->label2->Name = L"label2";
				this->label2->Size = System::Drawing::Size(103, 13);
				this->label2->TabIndex = 0;
				this->label2->Text = L"VA (Virtual Address):";
				// 
				// label3
				// 
				this->label3->AutoSize = true;
				this->label3->Location = System::Drawing::Point(6, 22);
				this->label3->Name = L"label3";
				this->label3->Size = System::Drawing::Size(62, 13);
				this->label3->TabIndex = 0;
				this->label3->Text = L"Imagebase:";
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Location = System::Drawing::Point(6, 74);
				this->label1->Name = L"label1";
				this->label1->Size = System::Drawing::Size(153, 13);
				this->label1->TabIndex = 0;
				this->label1->Text = L"RVA (Relative Virtual Address):";
				// 
				// MainForm
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(414, 122);
				this->Controls->Add(this->groupBox1);
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				this->Name = L"MainForm";
				this->Text = L"RE Tiny Tools";
				this->groupBox1->ResumeLayout(false);
				this->groupBox1->PerformLayout();
				this->ResumeLayout(false);

			}
	#pragma endregion

		private: void enableAllCvtButtons(bool enable) // Enables/Disables all convert buttons
		{
			this->buttonConvRVA->Enabled = enable;
			this->buttonConvVA->Enabled = enable;
		}

		private: System::Void textBoxImagebase_TextChanged(System::Object^  sender, System::EventArgs^  e)
		{
			AddrConv::textFieldHexTextChanged(this->textBoxImagebase);

			// https://social.msdn.microsoft.com/Forums/windows/en-US/ec7b777d-deb1-45e1-b66e-e25daddf6497/text-box-which-accepts-only-hexadecimal-values?forum=winforms
			/*String^ item = this->textBoxImagebase->Text;
			int n = 0;
			if (!Int32::TryParse(item, System::Globalization::NumberStyles::HexNumber, System::Globalization::NumberFormatInfo::CurrentInfo, n) &&
			item->Empty) // item != String::Empty
			{
			this->textBoxImagebase->Text = item->Remove(item->Length - 1, 1);
			this->textBoxImagebase->SelectionStart = this->textBoxImagebase->Text->Length;
			}*/

			this->buttonConvVA->Enabled = AddrConv::checkHexFormatOnChangeUsable(this->textBoxImagebase->Text) &&
				AddrConv::checkHexFormatOnChangeUsable(this->textBoxVA->Text);
			this->buttonConvRVA->Enabled = AddrConv::checkHexFormatOnChangeUsable(this->textBoxImagebase->Text) &&
				AddrConv::checkHexFormatOnChangeUsable(this->textBoxRVA->Text);
		}
		private: System::Void textBoxVA_TextChanged(System::Object^  sender, System::EventArgs^  e)
		{
			AddrConv::textFieldHexTextChanged(this->textBoxVA);
			this->buttonConvVA->Enabled = AddrConv::checkHexFormatOnChangeUsable(this->textBoxVA->Text) &&
				AddrConv::checkHexFormatOnChangeUsable(this->textBoxImagebase->Text);
		}
		private: System::Void textBoxRVA_TextChanged(System::Object^  sender, System::EventArgs^  e)
		{
			AddrConv::textFieldHexTextChanged(this->textBoxRVA);
			this->buttonConvRVA->Enabled = AddrConv::checkHexFormatOnChangeUsable(this->textBoxRVA->Text) &&
				AddrConv::checkHexFormatOnChangeUsable(this->textBoxImagebase->Text);
		}
		private: System::Void textBoxImagebase_Leave(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonConvVA->Enabled = AddrConv::textFieldHexLeave(this->textBoxImagebase) &&
				AddrConv::checkHexFormatOnChangeUsable(this->textBoxVA->Text);
			this->buttonConvRVA->Enabled = AddrConv::textFieldHexLeave(this->textBoxImagebase) &&
				AddrConv::checkHexFormatOnChangeUsable(this->textBoxRVA->Text);
		}
		private: System::Void textBoxVA_Leave(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonConvVA->Enabled = AddrConv::textFieldHexLeave(this->textBoxVA) &&
				AddrConv::checkHexFormatOnChangeUsable(this->textBoxImagebase->Text);
		}
		private: System::Void textBoxRVA_Leave(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonConvRVA->Enabled = AddrConv::textFieldHexLeave(this->textBoxRVA) &&
				AddrConv::checkHexFormatOnChangeUsable(this->textBoxImagebase->Text);
		}
		private: System::Void textBoxImagebase_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->textBoxImagebase->SelectAll();
		}
		private: System::Void textBoxRVA_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->textBoxRVA->SelectAll();
		}
		private: System::Void textBoxVA_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->textBoxVA->SelectAll();
		}
		private: System::Void buttonConvVA_Click(System::Object^  sender, System::EventArgs^  e)
		{

		}
		private: System::Void buttonConvRVA_Click(System::Object^  sender, System::EventArgs^  e)
		{

		}
};
}
