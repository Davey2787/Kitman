#pragma once

namespace Calculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button_1;
	protected: 

	private: System::Windows::Forms::Button^  button_2;
	protected: 

	private: System::Windows::Forms::Button^  button_3;
	private: System::Windows::Forms::Button^  button_4;
	private: System::Windows::Forms::Button^  button_5;



	private: System::Windows::Forms::Button^  button_6;
	private: System::Windows::Forms::Button^  button_7;
	private: System::Windows::Forms::Button^  button_8;



	private: System::Windows::Forms::Button^  button_9;

	private: System::Windows::Forms::Button^  button_plus;

	private: System::Windows::Forms::Button^  button_minus;

	private: System::Windows::Forms::Button^  button_multiple;

	private: System::Windows::Forms::Button^  button_divide;

	private: System::Windows::Forms::Button^  button_equals;
	private: System::Windows::Forms::Button^  button_0;


	private: System::Windows::Forms::Button^  button_des_point;

	private: System::Windows::Forms::Button^  button_delete;

	private: System::Windows::Forms::Button^  button_clear;
	private: System::Windows::Forms::Label^  display;






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
			this->button_1 = (gcnew System::Windows::Forms::Button());
			this->button_2 = (gcnew System::Windows::Forms::Button());
			this->button_3 = (gcnew System::Windows::Forms::Button());
			this->button_4 = (gcnew System::Windows::Forms::Button());
			this->button_5 = (gcnew System::Windows::Forms::Button());
			this->button_6 = (gcnew System::Windows::Forms::Button());
			this->button_7 = (gcnew System::Windows::Forms::Button());
			this->button_8 = (gcnew System::Windows::Forms::Button());
			this->button_9 = (gcnew System::Windows::Forms::Button());
			this->button_plus = (gcnew System::Windows::Forms::Button());
			this->button_minus = (gcnew System::Windows::Forms::Button());
			this->button_multiple = (gcnew System::Windows::Forms::Button());
			this->button_divide = (gcnew System::Windows::Forms::Button());
			this->button_equals = (gcnew System::Windows::Forms::Button());
			this->button_0 = (gcnew System::Windows::Forms::Button());
			this->button_des_point = (gcnew System::Windows::Forms::Button());
			this->button_delete = (gcnew System::Windows::Forms::Button());
			this->button_clear = (gcnew System::Windows::Forms::Button());
			this->display = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button_1
			// 
			this->button_1->Location = System::Drawing::Point(7, 206);
			this->button_1->Name = L"button_1";
			this->button_1->Size = System::Drawing::Size(48, 45);
			this->button_1->TabIndex = 0;
			this->button_1->Text = L"1";
			this->button_1->UseVisualStyleBackColor = true;
			this->button_1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button_2
			// 
			this->button_2->Location = System::Drawing::Point(61, 205);
			this->button_2->Name = L"button_2";
			this->button_2->Size = System::Drawing::Size(48, 45);
			this->button_2->TabIndex = 1;
			this->button_2->Text = L"2";
			this->button_2->UseVisualStyleBackColor = true;
			this->button_2->Click += gcnew System::EventHandler(this, &Form1::button_2_Click);
			// 
			// button_3
			// 
			this->button_3->Location = System::Drawing::Point(115, 203);
			this->button_3->Name = L"button_3";
			this->button_3->Size = System::Drawing::Size(48, 48);
			this->button_3->TabIndex = 2;
			this->button_3->Text = L"3";
			this->button_3->UseVisualStyleBackColor = true;
			this->button_3->Click += gcnew System::EventHandler(this, &Form1::button_3_Click);
			// 
			// button_4
			// 
			this->button_4->Location = System::Drawing::Point(7, 151);
			this->button_4->Name = L"button_4";
			this->button_4->Size = System::Drawing::Size(48, 48);
			this->button_4->TabIndex = 3;
			this->button_4->Text = L"4";
			this->button_4->UseVisualStyleBackColor = true;
			this->button_4->Click += gcnew System::EventHandler(this, &Form1::button_4_Click);
			// 
			// button_5
			// 
			this->button_5->Location = System::Drawing::Point(61, 151);
			this->button_5->Name = L"button_5";
			this->button_5->Size = System::Drawing::Size(48, 48);
			this->button_5->TabIndex = 4;
			this->button_5->Text = L"5";
			this->button_5->UseVisualStyleBackColor = true;
			this->button_5->Click += gcnew System::EventHandler(this, &Form1::button_5_Click);
			// 
			// button_6
			// 
			this->button_6->Location = System::Drawing::Point(115, 149);
			this->button_6->Name = L"button_6";
			this->button_6->Size = System::Drawing::Size(48, 48);
			this->button_6->TabIndex = 5;
			this->button_6->Text = L"6";
			this->button_6->UseVisualStyleBackColor = true;
			this->button_6->Click += gcnew System::EventHandler(this, &Form1::button_6_Click);
			// 
			// button_7
			// 
			this->button_7->Location = System::Drawing::Point(7, 97);
			this->button_7->Name = L"button_7";
			this->button_7->Size = System::Drawing::Size(48, 48);
			this->button_7->TabIndex = 6;
			this->button_7->Text = L"7";
			this->button_7->UseVisualStyleBackColor = true;
			this->button_7->Click += gcnew System::EventHandler(this, &Form1::button_7_Click);
			// 
			// button_8
			// 
			this->button_8->Location = System::Drawing::Point(61, 97);
			this->button_8->Name = L"button_8";
			this->button_8->Size = System::Drawing::Size(48, 48);
			this->button_8->TabIndex = 7;
			this->button_8->Text = L"8";
			this->button_8->UseVisualStyleBackColor = true;
			this->button_8->Click += gcnew System::EventHandler(this, &Form1::button_8_Click);
			// 
			// button_9
			// 
			this->button_9->Location = System::Drawing::Point(115, 97);
			this->button_9->Name = L"button_9";
			this->button_9->Size = System::Drawing::Size(48, 48);
			this->button_9->TabIndex = 8;
			this->button_9->Text = L"9";
			this->button_9->UseVisualStyleBackColor = true;
			this->button_9->Click += gcnew System::EventHandler(this, &Form1::button_9_Click);
			// 
			// button_plus
			// 
			this->button_plus->Location = System::Drawing::Point(169, 256);
			this->button_plus->Name = L"button_plus";
			this->button_plus->Size = System::Drawing::Size(48, 49);
			this->button_plus->TabIndex = 9;
			this->button_plus->Text = L"+";
			this->button_plus->UseVisualStyleBackColor = true;
			this->button_plus->Click += gcnew System::EventHandler(this, &Form1::button_plus_Click);
			// 
			// button_minus
			// 
			this->button_minus->Location = System::Drawing::Point(169, 202);
			this->button_minus->Name = L"button_minus";
			this->button_minus->Size = System::Drawing::Size(48, 48);
			this->button_minus->TabIndex = 10;
			this->button_minus->Text = L"-";
			this->button_minus->UseVisualStyleBackColor = true;
			this->button_minus->Click += gcnew System::EventHandler(this, &Form1::button_minus_Click);
			// 
			// button_multiple
			// 
			this->button_multiple->Location = System::Drawing::Point(169, 151);
			this->button_multiple->Name = L"button_multiple";
			this->button_multiple->Size = System::Drawing::Size(48, 48);
			this->button_multiple->TabIndex = 11;
			this->button_multiple->Text = L"x";
			this->button_multiple->UseVisualStyleBackColor = true;
			this->button_multiple->Click += gcnew System::EventHandler(this, &Form1::button_multiple_Click);
			// 
			// button_divide
			// 
			this->button_divide->Location = System::Drawing::Point(169, 97);
			this->button_divide->Name = L"button_divide";
			this->button_divide->Size = System::Drawing::Size(48, 48);
			this->button_divide->TabIndex = 12;
			this->button_divide->Text = L"/";
			this->button_divide->UseVisualStyleBackColor = true;
			this->button_divide->Click += gcnew System::EventHandler(this, &Form1::button13_Click);
			// 
			// button_equals
			// 
			this->button_equals->Location = System::Drawing::Point(223, 202);
			this->button_equals->Name = L"button_equals";
			this->button_equals->Size = System::Drawing::Size(48, 102);
			this->button_equals->TabIndex = 13;
			this->button_equals->Text = L"=";
			this->button_equals->UseVisualStyleBackColor = true;
			this->button_equals->Click += gcnew System::EventHandler(this, &Form1::button14_Click);
			// 
			// button_0
			// 
			this->button_0->Location = System::Drawing::Point(7, 257);
			this->button_0->Name = L"button_0";
			this->button_0->Size = System::Drawing::Size(102, 48);
			this->button_0->TabIndex = 14;
			this->button_0->Text = L"0";
			this->button_0->UseVisualStyleBackColor = true;
			this->button_0->Click += gcnew System::EventHandler(this, &Form1::button_0_Click);
			// 
			// button_des_point
			// 
			this->button_des_point->Location = System::Drawing::Point(115, 257);
			this->button_des_point->Name = L"button_des_point";
			this->button_des_point->Size = System::Drawing::Size(48, 48);
			this->button_des_point->TabIndex = 15;
			this->button_des_point->Text = L".";
			this->button_des_point->UseVisualStyleBackColor = true;
			this->button_des_point->Click += gcnew System::EventHandler(this, &Form1::button_des_point_Click);
			// 
			// button_delete
			// 
			this->button_delete->Location = System::Drawing::Point(223, 151);
			this->button_delete->Name = L"button_delete";
			this->button_delete->Size = System::Drawing::Size(48, 48);
			this->button_delete->TabIndex = 16;
			this->button_delete->Text = L"Del";
			this->button_delete->UseVisualStyleBackColor = true;
			this->button_delete->Click += gcnew System::EventHandler(this, &Form1::button17_Click);
			// 
			// button_clear
			// 
			this->button_clear->Location = System::Drawing::Point(224, 97);
			this->button_clear->Name = L"button_clear";
			this->button_clear->Size = System::Drawing::Size(48, 48);
			this->button_clear->TabIndex = 17;
			this->button_clear->Text = L"C";
			this->button_clear->UseVisualStyleBackColor = true;
			this->button_clear->Click += gcnew System::EventHandler(this, &Form1::Clear_Click);
			// 
			// display
			// 
			this->display->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->display->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->display->Location = System::Drawing::Point(4, 18);
			this->display->Name = L"display";
			this->display->Size = System::Drawing::Size(213, 49);
			this->display->TabIndex = 18;
			this->display->Text = L"0";
			this->display->Click += gcnew System::EventHandler(this, &Form1::display_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 316);
			this->Controls->Add(this->display);
			this->Controls->Add(this->button_clear);
			this->Controls->Add(this->button_delete);
			this->Controls->Add(this->button_des_point);
			this->Controls->Add(this->button_0);
			this->Controls->Add(this->button_equals);
			this->Controls->Add(this->button_divide);
			this->Controls->Add(this->button_multiple);
			this->Controls->Add(this->button_minus);
			this->Controls->Add(this->button_plus);
			this->Controls->Add(this->button_9);
			this->Controls->Add(this->button_8);
			this->Controls->Add(this->button_7);
			this->Controls->Add(this->button_6);
			this->Controls->Add(this->button_5);
			this->Controls->Add(this->button_4);
			this->Controls->Add(this->button_3);
			this->Controls->Add(this->button_2);
			this->Controls->Add(this->button_1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);

		}
#pragma endregion
		static char currentop;
		static char previousOp ='+';
		static float running_tot = 0;
		static char begin = 1;
		static float newnum;
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 if((display->Text == "0")||(begin==1))
				 {
					 display->Text = "1";
					 begin=0;
				 }
				 else
				 {
					 display->Text += "1";
				 }
			 }
private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Clear_Click(System::Object^  sender, System::EventArgs^  e) {

			 	 display->Text = "0";
				 running_tot = 0;
				 previousOp='+';
				 begin=1;
		 }
private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
			currentop= '=';
			 newnum = Convert::ToSingle(display->Text);
			 switch(previousOp){
				case '+':
					running_tot += newnum;
					break;
				case '-':
					running_tot -= newnum;
					break;
				case 'x':
					running_tot *= newnum;
					break;
				case '/':
					running_tot /= newnum;
					break;
			 }
			 display->Text = System::Convert::ToString(running_tot);
			 previousOp = currentop;
			 begin = 1;
		 }
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
			
			 currentop= '/';
			 newnum = Convert::ToSingle(display->Text);
			 switch(previousOp){
				case '+':
					running_tot += newnum;
					break;
				case '-':
					running_tot -= newnum;
					break;
				case 'x':
					running_tot *= newnum;
					break;
				case '/':
					running_tot /= newnum;
					break;
			 }
			 display->Text = System::Convert::ToString(running_tot);
			 previousOp = currentop;
			 begin = 1;
		 }
private: System::Void display_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button_2_Click(System::Object^  sender, System::EventArgs^  e) {

			 if((display->Text == "0")||(begin==1))
				 {
					 display->Text = "2";
					 begin=0;
				 }
			 else
				 {
					 display->Text += "2";
				 }
		 }
private: System::Void button_3_Click(System::Object^  sender, System::EventArgs^  e) {

			 if((display->Text == "0")||(begin==1))
				 {
					 display->Text = "3";
					 begin=0;
				 }
			 else
				 {
					 display->Text += "3";
				 }
		 }
private: System::Void button_4_Click(System::Object^  sender, System::EventArgs^  e) {

			 if((display->Text == "0")||(begin==1))
				 {
					 display->Text = "4";
				 }
			 else
				 {
					 display->Text += "4";
				 }
		 }
private: System::Void button_5_Click(System::Object^  sender, System::EventArgs^  e) {

			 if((display->Text == "0")||(begin==1))
				 {
					 display->Text = "5";
				 }
			 else
				 {
					 display->Text += "5";
				 }
		 }
private: System::Void button_6_Click(System::Object^  sender, System::EventArgs^  e) {

			 if((display->Text == "0")||(begin==1))
				 {
					 display->Text = "6";
				 }
			 else
				 {
					 display->Text += "6";
				 }
		 }
private: System::Void button_7_Click(System::Object^  sender, System::EventArgs^  e) {

			 if((display->Text == "0")||(begin==1))
				 {
					 display->Text = "7";
				 }
			 else
				 {
					 display->Text += "7";
				 }
		 }
private: System::Void button_8_Click(System::Object^  sender, System::EventArgs^  e) {

			 if((display->Text == "0")||(begin==1))
				 {
					 display->Text = "8";
				 }
			 else
				 {
					display->Text += "8";
				 }
		 }
private: System::Void button_9_Click(System::Object^  sender, System::EventArgs^  e) {

			 if((display->Text == "0")||(begin==1))
				 {
					 display->Text = "9";
				 }
			 else
				 {
					 display->Text += "9";
				 }
		 }
private: System::Void button_des_point_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			
					 display->Text += ".";
					 begin = 0;

		 }
private: System::Void button_0_Click(System::Object^  sender, System::EventArgs^  e) {
			
			 if((display->Text == "0")||(begin==1))
				 {
					 display->Text = "0";
				 }
			 else
				 {
					 display->Text += "0";
				 }
		 }
private: System::Void button_plus_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 currentop= '+';
			 newnum = Convert::ToSingle(display->Text);
			 switch(previousOp){
				case '+':
					running_tot += newnum;
					break;
				case '-':
					running_tot -= newnum;
					break;
				case 'x':
					running_tot *= newnum;
					break;
				case '/':
					running_tot /= newnum;
					break;
			 }
			 display->Text = System::Convert::ToString(running_tot);
			 previousOp = currentop;
			 begin = 1;


		 }
private: System::Void button_minus_Click(System::Object^  sender, System::EventArgs^  e) {

			currentop= '-';
			 newnum = Convert::ToSingle(display->Text);
			 switch(previousOp){
				case '+':
					running_tot += newnum;
					break;
				case '-':
					running_tot -= newnum;
					break;
				case 'x':
					running_tot *= newnum;
					break;
				case '/':
					running_tot /= newnum;
					break;
			 }
			 display->Text = System::Convert::ToString(running_tot);
			 previousOp = currentop;
			 begin = 1;
		 }
private: System::Void button_multiple_Click(System::Object^  sender, System::EventArgs^  e) {

			 currentop= 'x';
			 newnum = Convert::ToSingle(display->Text);
			 switch(previousOp){
				case '+':
					running_tot += newnum;
					break;
				case '-':
					running_tot -= newnum;
					break;
				case 'x':
					running_tot *= newnum;
					break;
				case '/':
					running_tot /= newnum;
					break;
			 }
			 display->Text = System::Convert::ToString(running_tot);
			 previousOp = currentop;
			 begin = 1;
		 }
};
}

