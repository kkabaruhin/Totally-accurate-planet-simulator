#pragma once
//#include "imagineGenerator.h"
#include "lithospheric_plates.h"
#include <chrono>
#include <thread>
#include <windows.h>

geomap* my_geomap;
HANDLE runningThread;
volatile bool is_running = false;
bool is_free;
int years_to_skip;

DWORD WINAPI thread_func(LPVOID lpParameter) {
	while (is_running) {
		if (years_to_skip <= 0)
			break;
		if (!is_free) {
			Sleep(9);
			continue;
		}
		is_free = false;
		my_geomap->do_one_step();
		years_to_skip -= 1;
		
		is_free = true;
	}
	is_running = false;
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
	private: System::Windows::Forms::PictureBox^ map_box;
	protected:



	private: System::Windows::Forms::Button^ GenerateButton;
	private: System::Windows::Forms::Button^ OneStepButton;
	private: System::Windows::Forms::Button^ SkipButton;

	private: System::Windows::Forms::Button^ StopButton;
	private: System::Windows::Forms::Button^ redraw_button;
	private: System::Windows::Forms::GroupBox^ groupBoxOfTypeOfImage;
	private: System::Windows::Forms::RadioButton^ altitudeRadioButton;
	private: System::Windows::Forms::RadioButton^ platesRadioButton;
	private: System::Windows::Forms::Label^ count_of_years_label;

	private:


	private:


	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ countYearsSkipBox1;

	private: System::Windows::Forms::Label^ label2;




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
			this->map_box = (gcnew System::Windows::Forms::PictureBox());
			this->GenerateButton = (gcnew System::Windows::Forms::Button());
			this->OneStepButton = (gcnew System::Windows::Forms::Button());
			this->SkipButton = (gcnew System::Windows::Forms::Button());
			this->StopButton = (gcnew System::Windows::Forms::Button());
			this->redraw_button = (gcnew System::Windows::Forms::Button());
			this->groupBoxOfTypeOfImage = (gcnew System::Windows::Forms::GroupBox());
			this->altitudeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->platesRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->count_of_years_label = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->countYearsSkipBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->map_box))->BeginInit();
			this->groupBoxOfTypeOfImage->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// map_box
			// 
			this->map_box->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->map_box->Location = System::Drawing::Point(10, 138);
			this->map_box->Name = L"map_box";
			this->map_box->Size = System::Drawing::Size(800, 600);
			this->map_box->TabIndex = 2;
			this->map_box->TabStop = false;
			this->map_box->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::map_box_MouseDown);
			this->map_box->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::map_box_MouseMove);
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
			this->OneStepButton->Text = L"Skip 1 year";
			this->OneStepButton->UseVisualStyleBackColor = true;
			this->OneStepButton->Click += gcnew System::EventHandler(this, &MyForm::One_step_click);
			// 
			// SkipButton
			// 
			this->SkipButton->Location = System::Drawing::Point(1035, 38);
			this->SkipButton->Name = L"SkipButton";
			this->SkipButton->Size = System::Drawing::Size(125, 23);
			this->SkipButton->TabIndex = 5;
			this->SkipButton->Text = L"Skip 1 year";
			this->SkipButton->UseVisualStyleBackColor = true;
			this->SkipButton->Click += gcnew System::EventHandler(this, &MyForm::skip_Button_Click);
			// 
			// StopButton
			// 
			this->StopButton->Location = System::Drawing::Point(1035, 90);
			this->StopButton->Name = L"StopButton";
			this->StopButton->Size = System::Drawing::Size(75, 23);
			this->StopButton->TabIndex = 6;
			this->StopButton->Text = L"Stop";
			this->StopButton->UseVisualStyleBackColor = true;
			this->StopButton->Click += gcnew System::EventHandler(this, &MyForm::StopButton_Click);
			// 
			// redraw_button
			// 
			this->redraw_button->Location = System::Drawing::Point(1035, 138);
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
			this->count_of_years_label->Location = System::Drawing::Point(1032, 9);
			this->count_of_years_label->Name = L"count_of_years_label";
			this->count_of_years_label->Size = System::Drawing::Size(58, 13);
			this->count_of_years_label->TabIndex = 9;
			this->count_of_years_label->Text = L"0 years left";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(837, 188);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(56, 19);
			this->button1->TabIndex = 11;
			this->button1->Text = L"Create";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->BackColor = System::Drawing::Color::White;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Location = System::Drawing::Point(837, 240);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(314, 466);
			this->panel1->TabIndex = 12;
			// 
			// trackBar1
			// 
			this->trackBar1->LargeChange = 1;
			this->trackBar1->Location = System::Drawing::Point(949, 188);
			this->trackBar1->Maximum = 100;
			this->trackBar1->Minimum = 1;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(173, 45);
			this->trackBar1->TabIndex = 13;
			this->trackBar1->Value = 20;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(978, 172);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(122, 13);
			this->label1->TabIndex = 14;
			this->label1->Text = L"size of the selected area";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(837, 209);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 15;
			this->button2->Text = L"Clear";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// countYearsSkipBox1
			// 
			this->countYearsSkipBox1->Location = System::Drawing::Point(886, 38);
			this->countYearsSkipBox1->Name = L"countYearsSkipBox1";
			this->countYearsSkipBox1->Size = System::Drawing::Size(100, 20);
			this->countYearsSkipBox1->TabIndex = 16;
			this->countYearsSkipBox1->Text = L"1";
			this->countYearsSkipBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::countYearsSkipBox1_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(901, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(68, 13);
			this->label2->TabIndex = 17;
			this->label2->Text = L"Years to skip";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1172, 764);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->countYearsSkipBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->count_of_years_label);
			this->Controls->Add(this->groupBoxOfTypeOfImage);
			this->Controls->Add(this->redraw_button);
			this->Controls->Add(this->StopButton);
			this->Controls->Add(this->SkipButton);
			this->Controls->Add(this->OneStepButton);
			this->Controls->Add(this->GenerateButton);
			this->Controls->Add(this->map_box);
			this->Name = L"MyForm";
			this->Text = L"Main window";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->map_box))->EndInit();
			this->groupBoxOfTypeOfImage->ResumeLayout(false);
			this->groupBoxOfTypeOfImage->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		Bitmap^ bitmap_of_plates;
		Bitmap^ bitmap_of_height;
		Bitmap^ current_bitmap;
		int size_of_area;
		int x1, y1, x2, y2; //left top and right lower corners of selected area

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		is_free = true;
		is_running = false;
		size_of_area = 20;
		x1 = 0;
		y1 = 0;
		x2 = map_box->Width -1;
		y2 = map_box->Height -1;
		years_to_skip = 10;
	}

	public: System::Void draw_image() {
		
		if (my_geomap == nullptr)
			return;

		while (!is_free) {
			Sleep(1);
		}
		is_free = false;

		delete map_box->Image;
		if (platesRadioButton->Checked) {
			if (bitmap_of_plates != nullptr)
				delete bitmap_of_plates;
			bitmap_of_plates = my_geomap->create_bitmap_of_plates();
			if (current_bitmap != nullptr)
				delete current_bitmap;
			current_bitmap = gcnew Bitmap(bitmap_of_plates);
		}
		if (altitudeRadioButton->Checked) {
			if (bitmap_of_plates != nullptr)
				delete bitmap_of_height;
			bitmap_of_height = my_geomap->create_bitmap_of_height();
			if (current_bitmap != nullptr)
				delete current_bitmap;
			current_bitmap = gcnew Bitmap(bitmap_of_height);
		}
		map_box->Image = current_bitmap;
		count_of_years_label->Text = my_geomap->get_years().ToString() + " years left";
		is_free = true;
	}

	private: System::Void clear_panel() {
		panel1->Controls->Clear();
		SolidBrush^ solidBrush = gcnew SolidBrush(
			Color::FromArgb(255, 255, 255, 255));
		Graphics^ g = panel1->CreateGraphics();
		g->FillRectangle(solidBrush, 1, 1, panel1->Width, panel1->Height);
		delete solidBrush, g;
	}

	private: System::Void create_record(int number, double min, double max, double local_min, double local_max) {
		Graphics^ g = panel1->CreateGraphics();
		int size_of_grad = 70;

		LinearGradientBrush^ lgb = gcnew LinearGradientBrush(
			Point(10, 0),
			Point(10 + size_of_grad, 0),
			my_geomap->get_altitude_color(local_min),
			my_geomap->get_altitude_color(local_max)
		);
		
		Label^ lb = gcnew Label();
		lb->Text = "[" + local_min.ToString() + "; " + local_max.ToString() + "]";
		lb->AutoSize = true;
		if (number < 5) {
			g->FillRectangle(lgb, 10, 10 + number * (size_of_grad + 10), size_of_grad, size_of_grad);
			lb->Location = Point(size_of_grad + 20, 30 + number * (size_of_grad + 10));
		}
		else {
			delete lgb;
			lgb = gcnew LinearGradientBrush(
				Point(size_of_grad + 100, 0),
				Point(2 * size_of_grad + 100, 0),
				my_geomap->get_altitude_color(local_min),
				my_geomap->get_altitude_color(local_max)
			);
			g->FillRectangle(lgb, size_of_grad + 100, 10 + (number - 5) * (size_of_grad + 10), size_of_grad, size_of_grad);
			lb->Location = Point(2 * size_of_grad + 110, 30 + (number - 5) * (size_of_grad + 10));
		}
		
		panel1->Controls->Add(lb);
		delete g, lgb;
	}

	private: System::Void show_info() {
		int map_width, map_height;
		map_width = my_geomap->get_width();
		map_height = my_geomap->get_height();
		double** altitude_map = my_geomap->get_copy_altitude_map();
		int arr_size = (x2 - x1 + 1) * (y2 - y1 + 1);
		double* list_of_altitude = new double[arr_size];

		for (int i = x1; i <= x2; i++)
			for (int j = y1; j <= y2; j++) {
				list_of_altitude[(i - x1) * (y2 - y1 + 1) + (j - y1)] = altitude_map[i][j];
			}

		for (int i = 0; i < arr_size - 1; i++)
			for (int j = 0; j < arr_size - i - 1; j++)
				if (list_of_altitude[j] > list_of_altitude[j + 1]) {
					double x = list_of_altitude[j];
					list_of_altitude[j] = list_of_altitude[j + 1];
					list_of_altitude[j + 1] = x;
				}
		double k = 0;
		for (int i = 0; i < 10; i++) {
			double min = list_of_altitude[(int)k];
			double max = list_of_altitude[(int)(k + arr_size / 10.0) - 1];

			k += arr_size / 10.0;
			create_record(i, my_geomap->get_min_altitude(), my_geomap->get_max_altitude(), min, max);
		}
		

		for (int i = 0; i < map_width; i++)
			delete[] altitude_map[i];
		delete[] altitude_map;
		delete[] list_of_altitude;
	}

	private: System::Void GenerateButton_Click(System::Object^ sender, System::EventArgs^ e) {
		
		if (is_running) return;
		int new_count_of_plates = 10;
		int new_width = map_box->Size.Width;
		int new_height = map_box->Size.Height;

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
	   
	/*private: System::Void StartButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (my_geomap == nullptr || is_running) return;
		is_running = true;
		is_free = true;
		runningThread = CreateThread(NULL, 0, thread_func, NULL, 0, NULL);
	}*/

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

	private: System::Void map_box_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (map_box->Image == nullptr) return;

		Bitmap^ new_bitmap = gcnew Bitmap(current_bitmap);
		
		int mouse_x = e->X;
		int mouse_y = e->Y;

		if (map_box->Image != current_bitmap)
			delete map_box->Image;
		for (int i = mouse_x - size_of_area / 2; i < mouse_x + size_of_area / 2; i++) {
			int j = mouse_y - size_of_area / 2;
			if (i > 0 && j > 0 && i < map_box->Width && j < map_box->Height)
				new_bitmap->SetPixel(i, j, Color::Black);
		}
		for (int i = mouse_x - size_of_area / 2; i < mouse_x + size_of_area / 2; i++) {
			int j = mouse_y + size_of_area / 2;
			if (i > 0 && j > 0 && i < map_box->Width && j < map_box->Height)
				new_bitmap->SetPixel(i, j, Color::Black);
		}
		for (int j = mouse_y - size_of_area / 2; j < mouse_y + size_of_area / 2; j++) {
			int i = mouse_x - size_of_area / 2;
			if (i > 0 && j > 0 && i < map_box->Width && j < map_box->Height)
				new_bitmap->SetPixel(i, j, Color::Black);
		}
		for (int j = mouse_y - size_of_area / 2; j < mouse_y + size_of_area / 2; j++) {
			int i = mouse_x + size_of_area / 2;
			if (i > 0 && j > 0 && i < map_box->Width && j < map_box->Height)
				new_bitmap->SetPixel(i, j, Color::Black);
		}
	
		map_box->Image = new_bitmap;
		
}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		clear_panel();
		//show_info();
		LinearGradientBrush^ lgb = gcnew LinearGradientBrush(
			Point(10, 0),
			Point(60, 0),
			Color::FromArgb(255, 0, 0),
			Color::FromArgb(0, 0, 255)
		);
		Graphics^ g = panel1->CreateGraphics();

		for (int i = 0; i < 7; i++) 
			g->FillRectangle(lgb, 10, 10 + i * 60, 50, 50);

		delete g, lgb;
		/*for (int i = 0; i < 7; i++) {
			Label^ lb = gcnew Label();
			lb->Text = i.ToString();
			lb->Location = Point(80, 30 + i * 60);
			panel1->Controls->Add(lb);
		}*/
	}

	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
		size_of_area = trackBar1->Value;
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		clear_panel();
	}

	private: System::Void map_box_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (map_box->Image == nullptr) return;
		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			draw_image();
			clear_panel();
			return;
		}
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			draw_image();

			int mouse_x = e->X;
			int mouse_y = e->Y;

			x1 = mouse_x - size_of_area / 2;
			y1 = mouse_y - size_of_area / 2;
			x2 = mouse_x + size_of_area / 2;
			y2 = mouse_y + size_of_area / 2;

			if (x1 < 1) x1 = 1;
			if (y1 < 1) y1 = 1;
			if (x2 >= map_box->Width) x2 = map_box->Width - 1;
			if (y2 >= map_box->Height) y2 = map_box->Height - 1;

			for (int i = mouse_x - size_of_area / 2; i < mouse_x + size_of_area / 2; i++) {
				int j = mouse_y - size_of_area / 2;
				if (i > 0 && j > 0 && i < map_box->Width && j < map_box->Height)
					current_bitmap->SetPixel(i, j, Color::Black);
			}
			for (int i = mouse_x - size_of_area / 2; i < mouse_x + size_of_area / 2; i++) {
				int j = mouse_y + size_of_area / 2;
				if (i > 0 && j > 0 && i < map_box->Width && j < map_box->Height)
					current_bitmap->SetPixel(i, j, Color::Black);
			}
			for (int j = mouse_y - size_of_area / 2; j < mouse_y + size_of_area / 2; j++) {
				int i = mouse_x - size_of_area / 2;
				if (i > 0 && j > 0 && i < map_box->Width && j < map_box->Height)
					current_bitmap->SetPixel(i, j, Color::Black);
			}
			for (int j = mouse_y - size_of_area / 2; j < mouse_y + size_of_area / 2; j++) {
				int i = mouse_x + size_of_area / 2;
				if (i > 0 && j > 0 && i < map_box->Width && j < map_box->Height)
					current_bitmap->SetPixel(i, j, Color::Black);
			}

			map_box->Image = current_bitmap;
			clear_panel();
			show_info();
		}
		
	}
	
	private: System::Void skip_Button_Click(System::Object^ sender, System::EventArgs^ e) {
		if (my_geomap == nullptr || is_running) return;
		String^ str = countYearsSkipBox1->Text;
		bool is_int = true;
		for (int i = 0; i < str->Length; i++) {
			if (str[i] < '0' || str[i] > '9')
				is_int = false;
		}
		if (is_int && str->Length < 9)
		{
			years_to_skip = Convert::ToInt32(str);
			is_running = true;
			is_free = true;
			runningThread = CreateThread(NULL, 0, thread_func, NULL, 0, NULL);
			draw_image();
		}

	}

	private: System::Void countYearsSkipBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		String^ str = countYearsSkipBox1->Text;
		bool is_int = true;
		for (int i = 0; i < str->Length; i++) {
			if (str[i] < '0' || str[i] > '9')
				is_int = false;
		}
		if (is_int && str->Length < 9)
			SkipButton->Text = "Skip " + str + " years";
	}
};
}
