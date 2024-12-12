#include "MyForm.h"
using namespace System;

using namespace System::Windows::Forms;
using namespace PlanetSimulator;

//[STAThread]

System::Void draw_func(MyForm^ form) {
	form->draw_image();
}

DWORD WINAPI drawing_thread_func(LPVOID lpParameter) {
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


void main(array<String^>^ args)

{
    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

	MyForm form;

    Application::Run(% form);
    
}
