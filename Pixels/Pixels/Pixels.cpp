#include <windows.h>
#include <wchar.h>
#include <time.h>

//17. Заменить в рисунке красный цвет синим, а синий – красным (на рисунке должны быть и синий, и красный цвета)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawPixels(HWND hwnd);

int WINAPI wWinMain(
	HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	PWSTR       lpCmdLine,
	int         nCmdShow
) {

	MSG  msg;
	WNDCLASSW wc = { 0 };

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"Pixels";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	CreateWindowW(wc.lpszClassName, L"Pixels",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 300, 250, NULL, NULL, hInstance, NULL);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	srand(time(NULL));

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	switch (msg) {

	case WM_PAINT:

		DrawPixels(hwnd);
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void DrawPixels(HWND hwnd) {

	PAINTSTRUCT ps;
	RECT r;

	GetClientRect(hwnd, &r);

	if (r.bottom == 0) {

		return;
	}

	HDC hdc = BeginPaint(hwnd, &ps);

	for (int i = 0; i < 3000; i++) {

		int x = rand() % r.right;
		int y = rand() % r.bottom;
		SetPixel(hdc, x, y, RGB(255, 0, 0));
	}

	RECT blueRect;										//создаю прямоугольник
	blueRect.left = (r.right - r.left) / 2;				//левая его сторона начинается с центра текущего экрана
	blueRect.top = r.top;								//верх - такой же, как и у экрана
	blueRect.right = r.right;							//правая сторона - такая же, как и у экрана
	blueRect.bottom = r.bottom / 2;						//низ - до середины экрана

	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));	//задаю цвет - синий

	FillRect(hdc, &blueRect, brush);					//рисую закрашенный синий прямоугольник со значениями краёв, указанными выше

	EndPaint(hwnd, &ps);
}
