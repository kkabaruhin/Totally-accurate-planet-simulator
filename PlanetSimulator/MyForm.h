#pragma once
//#include "imagineGenerator.h"
#include "lithospheric_plates.h"
#include <chrono>
#include <thread>
#include <windows.h>

geomap* my_geomap;
HANDLE runningThread;
volatile bool is_running = true;
bool is_free;

DWORD WINAPI thread_func(LPVOID lpParameter) {
	while (is_running) {
		if (!is_free) {
			Sleep(9);
			continue;
		}
		is_free = false;
		my_geomap->do_one_step();
		is_free = true;
		Sleep(50);
	}
	ExitThread(0);
	return 0;
}



namespace PlanetSimulator {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Drawing::Imaging;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ GenerateButton;
	private: System::Windows::Forms::Button^ OneStepButton;
	private: System::Windows::Forms::Button^ StartButton;
	private: System::Windows::Forms::Button^ StopButton;
	private: System::Windows::Forms::Button^ redraw_button;
	private: System::Windows::Forms::GroupBox^ groupBoxOfTypeOfImage;
	private: System::Windows::Forms::RadioButton^ altitudeRadioButton;
	private: System::Windows::Forms::RadioButton^ platesRadioButton;
	private: System::Windows::Forms::Label^ count_of_years_label;









	protected:

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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->GenerateButton = (gcnew System::Windows::Forms::Button());
			this->OneStepButton = (gcnew System::Windows::Forms::Button());
			this->StartButton = (gcnew System::Windows::Forms::Button());
			this->StopButton = (gcnew System::Windows::Forms::Button());
			this->redraw_button = (gcnew System::Windows::Forms::Button());
			this->groupBoxOfTypeOfImage = (gcnew System::Windows::Forms::GroupBox());
			this->altitudeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->platesRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->count_of_years_label = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBoxOfTypeOfImage->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(10, 138);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(800, 600);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// GenerateButton
			// 
			this->GenerateButton->Location = System::Drawing::Point(482, 54);
			this->GenerateButton->Name = L"GenerateButton";
			this->GenerateButton->Size = System::Drawing::Size(75, 23);
			this->GenerateButton->TabIndex = 3;
			this->GenerateButton->Text = L"Generate";
			this->GenerateButton->UseVisualStyleBackColor = true;
			this->GenerateButton->Click += gcnew System::EventHandler(this, &MyForm::GenerateButton_Click);
			// 
			// OneStepButton
			// 
			this->OneStepButton->Location = System::Drawing::Point(699, 53);
			this->OneStepButton->Name = L"OneStepButton";
			this->OneStepButton->Size = System::Drawing::Size(75, 23);
			this->OneStepButton->TabIndex = 4;
			this->OneStepButton->Text = L"1 Step";
			this->OneStepButton->UseVisualStyleBackColor = true;
			this->OneStepButton->Click += gcnew System::EventHandler(this, &MyForm::One_step_click);
			// 
			// StartButton
			// 
			this->StartButton->Location = System::Drawing::Point(973, 150);
			this->StartButton->Name = L"StartButton";
			this->StartButton->Size = System::Drawing::Size(75, 23);
			this->StartButton->TabIndex = 5;
			this->StartButton->Text = L"Start";
			this->StartButton->UseVisualStyleBackColor = true;
			this->StartButton->Click += gcnew System::EventHandler(this, &MyForm::StartButton_Click);
			// 
			// StopButton
			// 
			this->StopButton->Location = System::Drawing::Point(973, 235);
			this->StopButton->Name = L"StopButton";
			this->StopButton->Size = System::Drawing::Size(75, 23);
			this->StopButton->TabIndex = 6;
			this->StopButton->Text = L"Stop";
			this->StopButton->UseVisualStyleBackColor = true;
			this->StopButton->Click += gcnew System::EventHandler(this, &MyForm::StopButton_Click);
			// 
			// redraw_button
			// 
			this->redraw_button->Location = System::Drawing::Point(973, 326);
			this->redraw_button->Name = L"redraw_button";
			this->redraw_button->Size = System::Drawing::Size(75, 23);
			this->redraw_button->TabIndex = 7;
			this->redraw_button->Text = L"Redraw";
			this->redraw_button->UseVisualStyleBackColor = true;
			this->redraw_button->Click += gcnew System::EventHandler(this, &MyForm::redraw_button_Click);
			// 
			// groupBoxOfTypeOfImage
			// 
			this->groupBoxOfTypeOfImage->Controls->Add(this->altitudeRadioButton);
			this->groupBoxOfTypeOfImage->Controls->Add(this->platesRadioButton);
			this->groupBoxOfTypeOfImage->Location = System::Drawing::Point(67, 53);
			this->groupBoxOfTypeOfImage->Name = L"groupBoxOfTypeOfImage";
			this->groupBoxOfTypeOfImage->Size = System::Drawing::Size(190, 49);
			this->groupBoxOfTypeOfImage->TabIndex = 8;
			this->groupBoxOfTypeOfImage->TabStop = false;
			this->groupBoxOfTypeOfImage->Text = L"Type of image";
			// 
			// altitudeRadioButton
			// 
			this->altitudeRadioButton->AutoSize = true;
			this->altitudeRadioButton->Location = System::Drawing::Point(112, 19);
			this->altitudeRadioButton->Name = L"altitudeRadioButton";
			this->altitudeRadioButton->Size = System::Drawing::Size(60, 17);
			this->altitudeRadioButton->TabIndex = 1;
			this->altitudeRadioButton->Text = L"Altitude";
			this->altitudeRadioButton->UseVisualStyleBackColor = true;
			this->altitudeRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::altitudeRadioButton_CheckedChanged);
			// 
			// platesRadioButton
			// 
			this->platesRadioButton->AutoSize = true;
			this->platesRadioButton->Checked = true;
			this->platesRadioButton->Location = System::Drawing::Point(21, 20);
			this->platesRadioButton->Name = L"platesRadioButton";
			this->platesRadioButton->Size = System::Drawing::Size(54, 17);
			this->platesRadioButton->TabIndex = 0;
			this->platesRadioButton->TabStop = true;
			this->platesRadioButton->Text = L"Plates";
			this->platesRadioButton->UseVisualStyleBackColor = true;
			this->platesRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::platesRadioButton_CheckedChanged);
			// 
			// count_of_years_label
			// 
			this->count_of_years_label->AutoSize = true;
			this->count_of_years_label->Location = System::Drawing::Point(973, 63);
			this->count_of_years_label->Name = L"count_of_years_label";
			this->count_of_years_label->Size = System::Drawing::Size(58, 13);
			this->count_of_years_label->TabIndex = 9;
			this->count_of_years_label->Text = L"0 years left";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1163, 755);
			this->Controls->Add(this->count_of_years_label);
			this->Controls->Add(this->groupBoxOfTypeOfImage);
			this->Controls->Add(this->redraw_button);
			this->Controls->Add(this->StopButton);
			this->Controls->Add(this->StartButton);
			this->Controls->Add(this->OneStepButton);
			this->Controls->Add(this->GenerateButton);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"Main window";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBoxOfTypeOfImage->ResumeLayout(false);
			this->groupBoxOfTypeOfImage->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		is_free = true;
		is_running = false;
	}

	private: System::Void draw_image() {

		if (my_geomap == nullptr)
			return;
		
		while (!is_free) {
			Sleep(17);
		}
		is_free = false;
		Bitmap^ bmp;
		if (platesRadioButton->Checked) 
			bmp = my_geomap->create_bitmap_of_plates();
		if (altitudeRadioButton->Checked)
			bmp = my_geomap->create_bitmap_of_height();
		delete pictureBox1->Image;
		pictureBox1->Image = bmp;
		count_of_years_label->Text = my_geomap->get_years().ToString() + " years left";
		is_free = true;
	}

	private: System::Void GenerateButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (is_running) return;
		int new_count_of_plates = 10;
		int new_width = pictureBox1->Size.Width;
		int new_height = pictureBox1->Size.Height;

		if (my_geomap != nullptr)
			delete my_geomap;

		my_geomap = new geomap(new_width, new_height, new_count_of_plates, 0.3, 1);

		draw_image();
	}

	private: System::Void One_step_click(System::Object^ sender, System::EventArgs^ e) {
		if (my_geomap == nullptr || is_running) return;
		my_geomap->do_one_step();

		draw_image();
	}
	   
	private: System::Void StartButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (my_geomap == nullptr || is_running) return;
		is_running = true;
		is_free = true;
		runningThread = CreateThread(NULL, 0, thread_func, NULL, 0, NULL);
	}
	private: System::Void StopButton_Click(System::Object^ sender, System::EventArgs^ e) {
		is_running = false;
		CloseHandle(runningThread);
		is_free = true;
	}

	private: System::Void redraw_button_Click(System::Object^ sender, System::EventArgs^ e) {
		draw_image();
	}
private: System::Void platesRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	draw_image();
}
private: System::Void altitudeRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	draw_image();
}
};
}
