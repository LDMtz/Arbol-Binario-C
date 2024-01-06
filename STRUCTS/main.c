#include <stdio.h> // Para la consola
#include <windows.h>

#include "Identificadores.h"
#include "Estructuras.h"

#include "FuncionesArbol.h"
#include "FuncionesVentana.h"


errno_t freopen_s(FILE** streamptr, const char *filename, const char *mode, FILE *stream); // Para evitar el warning de funcion no declarada en consola

/* Eventos de la ventana */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	static HINSTANCE Instance;
	
	switch(Message) {
		case WM_CREATE:
			Instance= ((LPCREATESTRUCT)lParam) -> hInstance;
        	break;
		case WM_DESTROY: /*Para detener el programa*/
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case ID_SALIR:
					SendMessage(hwnd, WM_DESTROY, 0,0);
					break;
				case ID_AGREGAR:
					DialogBox(Instance, "ModalAgregarNodo", hwnd, (DLGPROC)DlgAgregarNodoProc);
					break;
				case ID_ELIMINAR:
					break;
			}
			break;
		default: /* Cualquier otro mensaje */
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

//Eventos de la modal AgregarNodo
BOOL CALLBACK DlgAgregarNodoProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	PAINTSTRUCT ps;
	static HDC hdcVent;
	static HBRUSH Pincel;
	//static FILE* Archivo; 
	
	switch(message){
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case ID_BTN_AGREGAR_NODO: {
					
				    int numeroTemp;
				    char nombreTemp[31];
				    char messageTemp[80];
				    BOOL success;
				    
				    GetDlgItemText(hwnd, EDT_NOMBRE, nombreTemp, sizeof(nombreTemp));
					numeroTemp = GetDlgItemInt(hwnd, EDT_NUMERO, &success, TRUE);
					
					if (success) {
						
						RECT rect;
						GetClientRect(hwndPrincipal, &rect);
					    int centerX = (rect.right - rect.left) / 2;
					    int centerY = 10;
					    
					    CalculatePositionLabelNode(AlumnRoot,hwndPrincipal,nombreTemp,numeroTemp,centerX, centerY);
					    AddAlumn(AlumnRoot, numeroTemp, nombreTemp);
						
						
    					sprintf(messageTemp,"El alumno %s fue agregado con el número %d", nombreTemp, numeroTemp);
				    	MessageBox(hwnd, messageTemp, "Ejemplo", MB_OK|MB_ICONINFORMATION);
					}else {
						strcpy(messageTemp, "Hubo un error en la conversion del número");
					    MessageBox(hwnd, messageTemp, "Ejemplo", MB_OK|MB_ICONINFORMATION);
					}
					
				    
				    break;
				}
				case IDCANCEL:
					EndDialog(hwnd, TRUE);
					break;
			}
			return TRUE;
		
		case WM_INITDIALOG:
			/*
			if((Archivo = fopen("Registro.txt","ab"))==NULL){ //Para abrir el archivo
				MessageBox(hwnd, "Fallo al abrir el archivo", "Error", MB_OK|MB_ICONERROR);
				EndDialog(hwnd,TRUE);
			}*/
			if(GetDlgCtrlID((HWND)wParam) != EDT_NUMERO){ //Para el foco al abrir la modal
				SetFocus(GetDlgItem(hwnd,EDT_NUMERO));
				return FALSE;
			}

			return TRUE;
			
		case WM_PAINT:
			hdcVent = BeginPaint(hwnd, &ps);
			if(hdcVent != NULL){
				FillRect(hdcVent,&ps.rcPaint, CreateSolidBrush(RGB(82,82,82)));
				EndPaint(hwnd,&ps);
			}
			break;
			
		case WM_CTLCOLORSTATIC:
			SetTextColor((HDC)wParam, RGB(255, 255, 255)); //Para la letra
			Pincel = CreateSolidBrush(RGB(82,82,82));
			SetBkColor((HDC) wParam,RGB(82,82,82)); //Para el fondo del label
			return (INT_PTR)Pincel;
			
		case WM_CLOSE:
			DeleteObject(Pincel);
			EndDialog(hwnd, TRUE);
			return TRUE;
	}
	return FALSE;
}

/* La función 'WinMain' de programas GUI Win32: aquí es donde comienza la ejecución */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	//Consola
	AllocConsole();
    FILE* consoleOut;
    FILE* consoleInt;
    freopen_s(&consoleOut, "CONOUT$", "w", stdout);
	freopen_s(&consoleInt, "CONIN$", "r", stdin);
	
    //Ventana
	WNDCLASSEX wc; /* Una struct de propiedades de nuestra ventana */
	HWND hwnd; /* Un 'HANDLE', por lo tanto, la 'H', o un puntero a nuestra ventana */
	MSG msg; /* Un lugar temporal para todos los mensajes */

	/* Ponemos a cero la struct y configuramos lo que queremos modificar */
	memset(&wc, 0, sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* Aquí es donde enviaremos los mensajes */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* Blanco, COLOR_WINDOW es simplemente un #define para un color del sistema, prueba Ctrl+Clic en él */
	wc.hbrBackground = CreateSolidBrush(RGB(38,38,38)); //55,55,55 <- Para el menu
	wc.lpszClassName = "WindowClass";
	wc.lpszMenuName = "MenuPrincipal";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Cargamos un ícono estándar */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* usamos el nombre "A" para usar el ícono del proyecto */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "¡Error al registrar la ventana!", "¡Error!", MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwndPrincipal = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Arbol Binario - Structs", WS_VISIBLE | WS_OVERLAPPEDWINDOW |WS_VSCROLL,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* ancho */
		480, /* alto */
		NULL, NULL, hInstance, NULL);
	
	if(hwndPrincipal == NULL) {
		MessageBox(NULL, "¡Error al crear la ventana!", "¡Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
	//---------------------------------------------------//
	ShowWindow(hwndPrincipal, SW_MAXIMIZE);
	//---------------------------------------------------//

	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* Si no se recibe ningún error... */
		TranslateMessage(&msg); /* Traducir códigos de teclas a caracteres si están presentes */
		DispatchMessage(&msg); /* Envíalo a WndProc */
	}
	
	// Cerrar la consola al salir
    FreeConsole();
    
	return msg.wParam;
}



