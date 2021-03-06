
// MFC_Lab2.cpp: определяет поведение классов для приложения.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFC_Lab2.h"
#include "MainFrm.h"
#include "BitMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCLab2App

BEGIN_MESSAGE_MAP(CMFCLab2App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMFCLab2App::OnAppAbout)
END_MESSAGE_MAP()

void CMFCLab2App::LoadImageBMP(CPoint point)
{
	CFileDialog fileDialog(true);				// объект класса выбора файла
	int result = fileDialog.DoModal();			// запустить диалоговое окно
	if (result == IDCANCEL) return;				// Если пользователь отказался от выбора
	CWnd *cwnd = AfxGetMainWnd();				// получить указатель на активное главное окно приложения
	hwnd = cwnd->GetSafeHwnd();					// Возвращает m_hWnd или NULL если указатель thisNULL.
	hBit = (HBITMAP)LoadImage(NULL, fileDialog.GetPathName().GetBuffer(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION); //загрузка изображения
	ShowBitMap(hwnd, hBit, point.x, point.y);	//вывод изображения - для точки
}

void CMFCLab2App::SaveArea()
{
	CFileDialog fileDialog((BOOL)FALSE, NULL, L"Save.bmp");	//объект класса выбора файла
	int result = fileDialog.DoModal();							//запустить диалоговое окно
	if (result == IDOK)	//если файл выбран
	{
		CWnd *cwnd = AfxGetMainWnd();
		HWND hwnd = cwnd->GetSafeHwnd();
		RECT r;  //r – область в окне, куда выводится изображение
		if (From.x < To.x)
		{
			r.left = From.x;
			r.right = To.x;
			r.top = From.y;
			r.bottom = To.y;
		}
		else
		{
			r.left = To.x;
			r.right = From.x;
			r.top = To.y;
			r.bottom = From.y;
		}
		ClientToBmp(hwnd, r, (char*)fileDialog.GetPathName().GetBuffer());
	}
}
// Создание CMFCLab2App

CMFCLab2App::CMFCLab2App() noexcept
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Если приложение построено с поддержкой среды Common Language Runtime (/clr):
	//     1) Этот дополнительный параметр требуется для правильной поддержки работы диспетчера перезагрузки.
	//   2) В своем проекте для сборки необходимо добавить ссылку на System.Windows.Forms.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: замените ниже строку идентификатора приложения строкой уникального идентификатора; рекомендуемый
	// формат для строки: ИмяКомпании.ИмяПродукта.СубПродукт.СведенияОВерсии
	SetAppID(_T("MFCLab2.AppID.NoVersion"));

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}

// Единственный объект CMFCLab2App

CMFCLab2App theApp;


// Инициализация CMFCLab2App

BOOL CMFCLab2App::InitInstance()
{
	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Инициализация библиотек OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// Для использования элемента управления RichEdit требуется метод AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующего
	// конкретные процедуры инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));


	// Чтобы создать главное окно, этот код создает новый объект окна
	// рамки, а затем задает его как объект основного окна приложения
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// создайте и загрузите рамку с его ресурсами
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);


	// Разрешить использование расширенных символов в горячих клавишах меню
	CMFCToolBar::m_bExtCharTranslation = TRUE;




	// Одно и только одно окно было инициализировано, поэтому отобразите и обновите его
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CMFCLab2App::ExitInstance()
{
	//TODO: обработайте дополнительные ресурсы, которые могли быть добавлены
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// Обработчики сообщений CMFCLab2App


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Команда приложения для запуска диалога
void CMFCLab2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Обработчики сообщений CMFCLab2App



