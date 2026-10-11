
// kursovaya_detmashDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "kursovaya_detmash.h"
#include "kursovaya_detmashDlg.h"
#include "CKompas.h"
#include "afxdialogex.h"

#include <atlimage.h>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	UINT g_layoutDpi = 96;
	HFONT g_layoutFont = nullptr;
	int g_layoutOffsetY = 0;
	std::vector<HWND>* g_createdControls = nullptr;

	int ScaleLayout(int value)
	{
		return ::MulDiv(value, static_cast<int>(g_layoutDpi), 96);
	}

	HWND CreateControl(HWND parent, DWORD exStyle, LPCWSTR className, LPCWSTR text,
		DWORD style, int x, int y, int width, int height, int id)
	{
		HWND control = ::CreateWindowExW(
			exStyle, className, text, WS_CHILD | WS_VISIBLE | style,
			ScaleLayout(x), ScaleLayout(y + g_layoutOffsetY),
			ScaleLayout(width), ScaleLayout(height), parent,
			reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
			AfxGetInstanceHandle(), nullptr);
		if (control != nullptr)
		{
			::SendMessage(control, WM_SETFONT,
				reinterpret_cast<WPARAM>(g_layoutFont != nullptr
					? g_layoutFont
					: ::GetStockObject(DEFAULT_GUI_FONT)), TRUE);
			if (g_createdControls != nullptr)
				g_createdControls->push_back(control);
		}
		return control;
	}

	void CreateLabel(HWND parent, LPCWSTR text, int x, int y, int width, int height = 18)
	{
		CreateControl(parent, 0, L"STATIC", text, SS_LEFT, x, y, width, height, -1);
	}

	void CreateReadOnlyEdit(HWND parent, int id, int x, int y, int width)
	{
		CreateControl(parent, WS_EX_CLIENTEDGE, L"EDIT", L"",
			ES_AUTOHSCROLL | ES_READONLY, x, y, width, 22, id);
	}

	CString FormatNumber(double value)
	{
		CString text;
		if (std::abs(value - std::round(value)) < 1e-7)
			text.Format(L"%.0f", value);
		else
		{
			text.Format(L"%.2f", value);
			text.TrimRight(L'0');
			text.TrimRight(L'.');
		}
		return text;
	}
}


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

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

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CkursovayadetmashDlg



CkursovayadetmashDlg::CkursovayadetmashDlg(CKompas& kompas, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_KURSOVAYA_DETMASH_DIALOG, pParent)
	, m_kompas(kompas)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CkursovayadetmashDlg::~CkursovayadetmashDlg()
{
	for (HBITMAP bitmap : m_drawingBitmaps)
	{
		if (bitmap != nullptr)
			::DeleteObject(bitmap);
	}
}

void CkursovayadetmashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CkursovayadetmashDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_RADIO_OVERLAY, &CkursovayadetmashDlg::OnParametersChanged)
	ON_BN_CLICKED(IDC_RADIO_INSET, &CkursovayadetmashDlg::OnParametersChanged)
	ON_BN_CLICKED(IDC_CHECK_SEAL, &CkursovayadetmashDlg::OnSealExecutionChanged)
	ON_BN_CLICKED(IDC_RADIO_SEAL_TYPE1, &CkursovayadetmashDlg::OnSealTypeChanged)
	ON_BN_CLICKED(IDC_RADIO_SEAL_TYPE2, &CkursovayadetmashDlg::OnSealTypeChanged)
	ON_EN_CHANGE(IDC_EDIT_D, &CkursovayadetmashDlg::OnParametersChanged)
	ON_EN_CHANGE(IDC_EDIT_H, &CkursovayadetmashDlg::OnParametersChanged)
	ON_CBN_SELCHANGE(IDC_COMBO_SHAFT_D, &CkursovayadetmashDlg::OnSealDiameterChanged)
	ON_BN_CLICKED(IDC_BUTTON_BUILD, &CkursovayadetmashDlg::OnBuildModel)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CkursovayadetmashDlg::OnResetParameters)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CkursovayadetmashDlg::OnTabSelectionChanged)
END_MESSAGE_MAP()


// Обработчики сообщений CkursovayadetmashDlg

BOOL CkursovayadetmashDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	g_layoutDpi = ::GetDpiForWindow(GetSafeHwnd());
	if (g_layoutDpi == 0)
		g_layoutDpi = 96;
	LOGFONT uiFont{};
	uiFont.lfHeight = -::MulDiv(9, static_cast<int>(g_layoutDpi), 72);
	uiFont.lfWeight = FW_NORMAL;
	uiFont.lfCharSet = DEFAULT_CHARSET;
	wcscpy_s(uiFont.lfFaceName, L"Segoe UI");
	m_uiFont.CreateFontIndirect(&uiFont);
	g_layoutFont = static_cast<HFONT>(m_uiFont.GetSafeHandle());
	SetFont(&m_uiFont);

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	SetWindowText(L"Построение крышки подшипника редуктора");
	ModifyStyle(WS_THICKFRAME | WS_MAXIMIZEBOX, 0, SWP_FRAMECHANGED);
	SetWindowPos(nullptr, 0, 0, ScaleLayout(880), ScaleLayout(610),
		SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
	CRect fixedWindowRect;
	GetWindowRect(&fixedWindowRect);
	m_fixedWindowSize = fixedWindowRect.Size();
	if (CMenu* systemMenu = GetSystemMenu(FALSE))
	{
		systemMenu->RemoveMenu(SC_SIZE, MF_BYCOMMAND);
		systemMenu->RemoveMenu(SC_MAXIMIZE, MF_BYCOMMAND);
		DrawMenuBar();
	}
	CenterWindow();

	if (CWnd* okButton = GetDlgItem(IDOK))
		okButton->ShowWindow(SW_HIDE);
	if (CWnd* placeholder = GetDlgItem(IDC_STATIC))
		placeholder->ShowWindow(SW_HIDE);

	CreateMainTabs();
	g_layoutOffsetY = 34;
	g_createdControls = &m_parameterControls;
	CreateParameterControls();
	g_createdControls = nullptr;
	g_layoutOffsetY = 0;
	CreateDrawingControls();
	LoadProjectDrawings();
	ShowSelectedTab();
	SetDefID(IDC_BUTTON_BUILD);
	ResetParameters();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CkursovayadetmashDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CkursovayadetmashDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CkursovayadetmashDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CkursovayadetmashDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CDialog::OnGetMinMaxInfo(lpMMI);
	if (m_fixedWindowSize.cx <= 0 || m_fixedWindowSize.cy <= 0)
		return;
	lpMMI->ptMinTrackSize.x = m_fixedWindowSize.cx;
	lpMMI->ptMinTrackSize.y = m_fixedWindowSize.cy;
	lpMMI->ptMaxTrackSize.x = m_fixedWindowSize.cx;
	lpMMI->ptMaxTrackSize.y = m_fixedWindowSize.cy;
}

void CkursovayadetmashDlg::CreateMainTabs()
{
	HWND tab = ::CreateControl(
		GetSafeHwnd(), 0, WC_TABCONTROLW, L"",
		TCS_BUTTONS | TCS_FLATBUTTONS | TCS_FIXEDWIDTH | WS_TABSTOP,
		10, 6, 820, 30, IDC_TAB_MAIN);
	if (tab == nullptr)
		return;

	::SendMessage(tab, TCM_SETITEMSIZE, 0,
		MAKELPARAM(ScaleLayout(195), ScaleLayout(24)));
	const wchar_t* titles[] =
	{
		L"Параметры",
		L"Накладная крышка",
		L"Закладная крышка",
		L"Манжеты"
	};
	for (int index = 0; index < 4; ++index)
	{
		TCITEM item{};
		item.mask = TCIF_TEXT;
		item.pszText = const_cast<LPWSTR>(titles[index]);
		::SendMessage(tab, TCM_INSERTITEM, index,
			reinterpret_cast<LPARAM>(&item));
	}
	::SendMessage(tab, TCM_SETCURSEL, 0, 0);
}

void CkursovayadetmashDlg::CreateDrawingControls()
{
	const wchar_t* hints[] =
	{
		L"Чертёж накладной крышки ещё не выбран",
		L"Чертёж закладной крышки ещё не выбран",
		L"Чертёж манжет ещё не выбран"
	};
	const int previewIds[] =
	{
		IDC_STATIC_DRAWING_OVERLAY,
		IDC_STATIC_DRAWING_INSET,
		IDC_STATIC_DRAWING_SEALS
	};
	const int hintIds[] =
	{
		IDC_STATIC_DRAWING_OVERLAY_HINT,
		IDC_STATIC_DRAWING_INSET_HINT,
		IDC_STATIC_DRAWING_SEALS_HINT
	};
	const wchar_t* sourceNames[] = { L"overlay", L"inset", L"seals" };

	for (int index = 0; index < 3; ++index)
	{
		g_createdControls = &m_drawingPageControls[index];
		m_drawingPreviews[index] = ::CreateControl(
			GetSafeHwnd(), WS_EX_CLIENTEDGE, L"STATIC", L"",
			SS_BITMAP | SS_CENTERIMAGE | SS_SUNKEN,
			24, 48, 812, 450, previewIds[index]);
		m_drawingHints[index] = ::CreateControl(
			GetSafeHwnd(), 0, L"STATIC", hints[index],
			SS_CENTER | SS_CENTERIMAGE,
			40, 64, 780, 418, hintIds[index]);
		CString sourceLabel;
		sourceLabel.Format(
			L"Файл: drawings\\%s.png (также поддерживаются .jpg, .jpeg и .bmp)",
			sourceNames[index]);
		::CreateControl(
			GetSafeHwnd(), 0, L"STATIC", sourceLabel,
			SS_LEFT, 24, 505, 620, 20, -1);
	}
	g_createdControls = nullptr;
}

void CkursovayadetmashDlg::ShowSelectedTab()
{
	CWnd* tabWindow = GetDlgItem(IDC_TAB_MAIN);
	const int selection = tabWindow == nullptr
		? 0
		: static_cast<int>(tabWindow->SendMessage(TCM_GETCURSEL));

	for (HWND control : m_parameterControls)
		::ShowWindow(control, selection == 0 ? SW_SHOW : SW_HIDE);
	for (int page = 0; page < 3; ++page)
	{
		const bool visible = selection == page + 1;
		for (HWND control : m_drawingPageControls[page])
			::ShowWindow(control, visible ? SW_SHOW : SW_HIDE);
		if (visible && m_drawingBitmaps[page] != nullptr)
			::ShowWindow(m_drawingHints[page], SW_HIDE);
	}

	SetDefID(selection == 0
		? IDC_BUTTON_BUILD
		: IDCANCEL);
	Invalidate(FALSE);
}

void CkursovayadetmashDlg::OnTabSelectionChanged(NMHDR*, LRESULT* pResult)
{
	ShowSelectedTab();
	*pResult = 0;
}

bool CkursovayadetmashDlg::LoadDrawing(
	int index,
	const CString& path,
	bool showError)
{
	if (index < 0 || index >= 3 || m_drawingPreviews[index] == nullptr)
		return false;

	CImage source;
	const HRESULT loadResult = source.Load(path);
	if (FAILED(loadResult) || source.GetWidth() <= 0 || source.GetHeight() <= 0)
	{
		if (showError)
			AfxMessageBox(L"Не удалось открыть выбранное изображение.", MB_ICONERROR);
		return false;
	}

	CRect previewRect;
	::GetClientRect(m_drawingPreviews[index], &previewRect);
	const int canvasWidth = previewRect.Width();
	const int canvasHeight = previewRect.Height();
	if (canvasWidth <= 0 || canvasHeight <= 0)
		return false;

	CImage canvas;
	if (!canvas.Create(canvasWidth, canvasHeight, 32))
		return false;
	HDC canvasDc = canvas.GetDC();
	RECT background{ 0, 0, canvasWidth, canvasHeight };
	::FillRect(canvasDc, &background,
		static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH)));
	::SetStretchBltMode(canvasDc, HALFTONE);

	const int padding = ScaleLayout(12);
	const double widthScale = static_cast<double>(canvasWidth - 2 * padding) / source.GetWidth();
	const double heightScale = static_cast<double>(canvasHeight - 2 * padding) / source.GetHeight();
	const double scale = (std::min)(widthScale, heightScale);
	const int drawingWidth = (std::max)(1, static_cast<int>(std::lround(source.GetWidth() * scale)));
	const int drawingHeight = (std::max)(1, static_cast<int>(std::lround(source.GetHeight() * scale)));
	const int drawingX = (canvasWidth - drawingWidth) / 2;
	const int drawingY = (canvasHeight - drawingHeight) / 2;
	source.Draw(canvasDc, drawingX, drawingY, drawingWidth, drawingHeight);
	canvas.ReleaseDC();

	HBITMAP newBitmap = canvas.Detach();
	::SendMessage(m_drawingPreviews[index], STM_SETIMAGE,
		IMAGE_BITMAP, reinterpret_cast<LPARAM>(newBitmap));
	if (m_drawingBitmaps[index] != nullptr)
		::DeleteObject(m_drawingBitmaps[index]);
	m_drawingBitmaps[index] = newBitmap;
	::ShowWindow(m_drawingHints[index], SW_HIDE);
	::InvalidateRect(m_drawingPreviews[index], nullptr, TRUE);
	return true;
}

void CkursovayadetmashDlg::LoadProjectDrawings()
{
	wchar_t modulePath[MAX_PATH]{};
	if (::GetModuleFileNameW(nullptr, modulePath, _countof(modulePath)) == 0)
		return;
	CString executableDirectory(modulePath);
	const int lastSlash = executableDirectory.ReverseFind(L'\\');
	if (lastSlash < 0)
		return;
	executableDirectory = executableDirectory.Left(lastSlash);

	const wchar_t* baseNames[] = { L"overlay", L"inset", L"seals" };
	const wchar_t* extensions[] = { L".png", L".jpg", L".jpeg", L".bmp" };
	CString projectDrawingDirectory;
	projectDrawingDirectory.Format(L"%s\\..\\..\\drawings",
		executableDirectory.GetString());
	const CString drawingDirectories[] =
	{
		projectDrawingDirectory,
		executableDirectory + L"\\drawings"
	};
	for (int index = 0; index < 3; ++index)
	{
		bool loaded = false;
		for (const CString& drawingDirectory : drawingDirectories)
		{
			for (const wchar_t* extension : extensions)
			{
				CString path;
				path.Format(L"%s\\%s%s",
					drawingDirectory.GetString(), baseNames[index], extension);
				const DWORD attributes = ::GetFileAttributesW(path);
				if (attributes == INVALID_FILE_ATTRIBUTES ||
					(attributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
					continue;
				if (LoadDrawing(index, path, false))
				{
					loaded = true;
					break;
				}
			}
			if (loaded)
				break;
		}
	}
}

#define CreateControl(...) ::CreateControl(__VA_ARGS__)
void CkursovayadetmashDlg::CreateParameterControls()
{
	const HWND parent = GetSafeHwnd();

	CreateControl(parent, 0, L"BUTTON", L"Тип крышки", BS_GROUPBOX, 10, 8, 390, 54, -1);
	CreateControl(parent, 0, L"BUTTON", L"Накладная", BS_AUTORADIOBUTTON | WS_GROUP | WS_TABSTOP,
		24, 29, 130, 20, IDC_RADIO_OVERLAY);
	CreateControl(parent, 0, L"BUTTON", L"Закладная", BS_AUTORADIOBUTTON | WS_TABSTOP,
		190, 29, 130, 20, IDC_RADIO_INSET);

	CreateControl(parent, 0, L"BUTTON", L"Основные параметры, мм", BS_GROUPBOX, 10, 68, 390, 118, -1);
	CreateLabel(parent, L"Исходный диаметр D:", 24, 92, 155);
	CreateControl(parent, WS_EX_CLIENTEDGE, L"EDIT", L"", ES_AUTOHSCROLL | WS_TABSTOP,
		185, 88, 75, 23, IDC_EDIT_D);
	CreateLabel(parent, L"Размер крышки h:", 24, 124, 155);
	CreateControl(parent, WS_EX_CLIENTEDGE, L"EDIT", L"", ES_AUTOHSCROLL | WS_TABSTOP,
		185, 120, 75, 23, IDC_EDIT_H);
	CreateControl(parent, 0, L"STATIC", L"Введите D", SS_LEFT,
		270, 124, 116, 18, IDC_STATIC_H_RANGE);
	CreateControl(parent, 0, L"BUTTON", L"Исполнение с манжетой", BS_AUTOCHECKBOX | WS_TABSTOP,
		24, 154, 210, 20, IDC_CHECK_SEAL);

	CreateControl(parent, 0, L"BUTTON", L"Манжета по ГОСТ 8752-79", BS_GROUPBOX, 10, 192, 390, 142, -1);
	CreateControl(parent, 0, L"BUTTON", L"Тип 1 — без пыльника",
		BS_AUTORADIOBUTTON | WS_GROUP | WS_TABSTOP, 24, 216, 170, 20, IDC_RADIO_SEAL_TYPE1);
	CreateControl(parent, 0, L"BUTTON", L"Тип 2 — с пыльником",
		BS_AUTORADIOBUTTON | WS_TABSTOP, 205, 216, 175, 20, IDC_RADIO_SEAL_TYPE2);
	CreateLabel(parent, L"Диаметр вала d*:", 24, 250, 145);
	CreateControl(parent, WS_EX_CLIENTEDGE, L"COMBOBOX", L"",
		CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, 185, 245, 75, 190, IDC_COMBO_SHAFT_D);
	CreateLabel(parent, L"Посадочный D*:", 24, 282, 125);
	CreateReadOnlyEdit(parent, IDC_EDIT_SEAL_D_RESULT, 150, 278, 75);
	CreateLabel(parent, L"Ширина h*:", 238, 282, 75);
	CreateReadOnlyEdit(parent, IDC_EDIT_SEAL_H_RESULT, 310, 278, 65);
	CreateLabel(parent, L"Проходное отверстие равно d* + 1 мм", 24, 309, 320);

	CreateControl(parent, 0, L"BUTTON", L"Рассчитанные параметры, мм", BS_GROUPBOX,
		410, 8, 420, 326, -1);
	CreateLabel(parent, L"D1", 430, 36, 25);
	CreateReadOnlyEdit(parent, IDC_EDIT_D1_RESULT, 458, 31, 70);
	CreateLabel(parent, L"D2", 550, 36, 25);
	CreateReadOnlyEdit(parent, IDC_EDIT_D2_RESULT, 578, 31, 70);
	CreateLabel(parent, L"D3", 670, 36, 25);
	CreateReadOnlyEdit(parent, IDC_EDIT_D3_RESULT, 698, 31, 70);

	CreateLabel(parent, L"H", 430, 70, 25);
	CreateReadOnlyEdit(parent, IDC_EDIT_H_RESULT, 458, 65, 70);
	CreateLabel(parent, L"h", 550, 70, 25);
	CreateReadOnlyEdit(parent, IDC_EDIT_H_SMALL_RESULT, 578, 65, 70);
	CreateLabel(parent, L"s", 670, 70, 25);
	CreateReadOnlyEdit(parent, IDC_EDIT_S_RESULT, 698, 65, 70);

	CreateLabel(parent, L"b", 430, 104, 25);
	CreateReadOnlyEdit(parent, IDC_EDIT_B_RESULT, 458, 99, 70);
	CreateLabel(parent, L"R внутр.", 550, 104, 68);
	CreateReadOnlyEdit(parent, IDC_EDIT_FILLET_RESULT, 620, 99, 48);
	CreateLabel(parent, L"R нар.", 680, 104, 56);
	CreateReadOnlyEdit(parent, IDC_EDIT_OUTER_FILLET_RESULT, 738, 99, 52);

	CreateControl(parent, 0, L"BUTTON", L"Крепёж накладной крышки", BS_GROUPBOX,
		424, 134, 390, 86, -1);
	CreateLabel(parent, L"d отверстия:", 440, 158, 88);
	CreateReadOnlyEdit(parent, IDC_EDIT_HOLE_D_RESULT, 530, 153, 58);
	CreateLabel(parent, L"d1 цековки:", 602, 158, 85);
	CreateReadOnlyEdit(parent, IDC_EDIT_COUNTERBORE_RESULT, 690, 153, 58);
	CreateLabel(parent, L"Резьба:", 440, 190, 55);
	CreateReadOnlyEdit(parent, IDC_EDIT_THREAD_RESULT, 500, 185, 58);
	CreateLabel(parent, L"Количество n:", 602, 190, 88);
	CreateReadOnlyEdit(parent, IDC_EDIT_HOLE_COUNT_RESULT, 690, 185, 58);

	CreateControl(parent, 0, L"BUTTON", L"Посадочное место манжеты", BS_GROUPBOX,
		424, 226, 390, 92, -1);
	CreateLabel(parent, L"Отверстие d*+1:", 440, 252, 112);
	CreateReadOnlyEdit(parent, IDC_EDIT_CLEARANCE_RESULT, 554, 247, 65);
	CreateLabel(parent, L"Фаска:", 642, 252, 54);
	HWND chamfer = CreateControl(parent, WS_EX_CLIENTEDGE, L"EDIT", L"2x15°",
		ES_AUTOHSCROLL | ES_READONLY, 698, 247, 80, 22, -1);
	if (chamfer != nullptr)
		::SetWindowTextW(chamfer, L"2x15°");
	CreateLabel(parent, L"Входная фаска 2x15°, задняя стенка 5 мм", 440, 286, 320);

	CreateControl(parent, 0, L"BUTTON", L"Порядок работы", BS_GROUPBOX, 10, 342, 820, 104, -1);
	CreateLabel(parent, L"1. Выберите тип крышки и введите D.", 24, 366, 380);
	CreateLabel(parent, L"2. Для накладной крышки задайте h в показанном диапазоне.", 24, 389, 390);
	CreateLabel(parent, L"3. При необходимости включите манжету и задайте её параметры.", 420, 366, 390);
	CreateLabel(parent, L"4. Нажмите «Построить модель». Будет создана новая деталь.", 420, 389, 390);
	CreateLabel(parent, L"Материал детали не назначается. Модель остаётся несохранённой в КОМПАС-3D.", 24, 416, 760);

	CreateControl(parent, 0, L"STATIC", L"Введите исходные параметры.", SS_CENTER,
		10, 454, 820, 22, IDC_STATIC_STATUS);
	CreateControl(parent, 0, L"BUTTON", L"Построить модель", BS_DEFPUSHBUTTON | WS_TABSTOP,
		420, 490, 132, 30, IDC_BUTTON_BUILD);
	CreateControl(parent, 0, L"BUTTON", L"Сбросить параметры", BS_PUSHBUTTON | WS_TABSTOP,
		560, 490, 142, 30, IDC_BUTTON_RESET);

	if (CWnd* closeButton = GetDlgItem(IDCANCEL))
	{
		closeButton->SetWindowText(L"Закрыть");
		closeButton->SetFont(&m_uiFont);
		closeButton->MoveWindow(
			ScaleLayout(710), ScaleLayout(524),
			ScaleLayout(120), ScaleLayout(30));
		closeButton->ShowWindow(SW_SHOW);
	}
}
#undef CreateControl

void CkursovayadetmashDlg::ResetParameters()
{
	m_updatingUi = true;
	CheckRadioButton(IDC_RADIO_OVERLAY, IDC_RADIO_INSET, IDC_RADIO_OVERLAY);
	CheckDlgButton(IDC_CHECK_SEAL, BST_UNCHECKED);
	CheckRadioButton(IDC_RADIO_SEAL_TYPE1, IDC_RADIO_SEAL_TYPE2, IDC_RADIO_SEAL_TYPE1);
	SetDlgItemText(IDC_EDIT_D, L"40");
	SetDlgItemText(IDC_EDIT_H, L"5");
	m_updatingUi = false;
	PopulateSealDiameters();
	UpdateInterface();
}

void CkursovayadetmashDlg::OnResetParameters()
{
	ResetParameters();
}

void CkursovayadetmashDlg::OnParametersChanged()
{
	if (m_updatingUi)
		return;
	PopulateSealDiameters();
	if (IsDlgButtonChecked(IDC_CHECK_SEAL) == BST_CHECKED)
	{
		CoverInput baseInput;
		if (TryReadBaseInput(baseInput))
		{
			const SealType type = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
				? SealType::Type2
				: SealType::Type1;
			SelectCompatibleSeal(baseInput, type);
		}
	}
	UpdateInterface();
}

void CkursovayadetmashDlg::OnSealExecutionChanged()
{
	if (m_updatingUi)
		return;

	if (IsDlgButtonChecked(IDC_CHECK_SEAL) != BST_CHECKED)
	{
		PopulateSealDiameters();
		UpdateInterface();
		return;
	}

	CoverInput baseInput;
	if (!TryReadBaseInput(baseInput))
	{
		PopulateSealDiameters();
		UpdateInterface();
		return;
	}

	const bool hasType1 = HasCompatibleSeal(baseInput, SealType::Type1);
	const bool hasType2 = HasCompatibleSeal(baseInput, SealType::Type2);
	if (!hasType1 && !hasType2)
	{
		AfxMessageBox(
			L"Для текущих размеров крышки не помещается ни одна манжета.\n"
			L"Измените D или h, затем снова включите исполнение с манжетой.",
			MB_ICONWARNING);
		CheckDlgButton(IDC_CHECK_SEAL, BST_UNCHECKED);
		PopulateSealDiameters();
		UpdateInterface();
		return;
	}

	SealType type = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
		? SealType::Type2
		: SealType::Type1;
	if ((type == SealType::Type1 && !hasType1) ||
		(type == SealType::Type2 && !hasType2))
	{
		type = hasType1 ? SealType::Type1 : SealType::Type2;
		CheckRadioButton(
			IDC_RADIO_SEAL_TYPE1,
			IDC_RADIO_SEAL_TYPE2,
			type == SealType::Type1 ? IDC_RADIO_SEAL_TYPE1 : IDC_RADIO_SEAL_TYPE2);
	}
	PopulateSealDiameters();
	SelectCompatibleSeal(baseInput, type);
	UpdateInterface();
}

void CkursovayadetmashDlg::OnSealTypeChanged()
{
	if (m_updatingUi)
		return;

	const SealType selectedType = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
		? SealType::Type2
		: SealType::Type1;
	PopulateSealDiameters();
	if (IsDlgButtonChecked(IDC_CHECK_SEAL) != BST_CHECKED)
	{
		UpdateInterface();
		return;
	}

	CoverInput baseInput;
	if (!TryReadBaseInput(baseInput))
	{
		UpdateInterface();
		return;
	}

	if (!HasCompatibleSeal(baseInput, selectedType))
	{
		const CString typeName = selectedType == SealType::Type1 ? L"1" : L"2";
		CString message;
		message.Format(
			L"Манжеты типа %s не помещаются в крышку с текущими размерами.\n"
			L"Измените D или h либо выберите другой тип манжеты.",
			typeName.GetString());
		AfxMessageBox(message, MB_ICONWARNING);

		const SealType otherType = selectedType == SealType::Type1
			? SealType::Type2
			: SealType::Type1;
		if (HasCompatibleSeal(baseInput, otherType))
		{
			CheckRadioButton(
				IDC_RADIO_SEAL_TYPE1,
				IDC_RADIO_SEAL_TYPE2,
				otherType == SealType::Type1 ? IDC_RADIO_SEAL_TYPE1 : IDC_RADIO_SEAL_TYPE2);
			PopulateSealDiameters();
			SelectCompatibleSeal(baseInput, otherType);
		}
		else
		{
			CheckDlgButton(IDC_CHECK_SEAL, BST_UNCHECKED);
		}
	}
	else
	{
		SelectCompatibleSeal(baseInput, selectedType);
	}
	UpdateInterface();
}

void CkursovayadetmashDlg::OnSealDiameterChanged()
{
	if (m_updatingUi)
		return;

	CoverInput baseInput;
	if (IsDlgButtonChecked(IDC_CHECK_SEAL) != BST_CHECKED ||
		!TryReadBaseInput(baseInput))
	{
		UpdateInterface();
		return;
	}

	CComboBox* combo = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SHAFT_D));
	const int selection = combo == nullptr ? CB_ERR : combo->GetCurSel();
	if (selection != CB_ERR)
	{
		CoverInput trial = baseInput;
		trial.withSeal = true;
		trial.sealType = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
			? SealType::Type2
			: SealType::Type1;
		trial.shaftDiameter = static_cast<double>(combo->GetItemData(selection));
		CoverParameters parameters;
		std::wstring error;
		if (!CalculateCoverParameters(trial, parameters, error))
		{
			AfxMessageBox(CString(error.c_str()), MB_ICONWARNING);
			SelectCompatibleSeal(baseInput, trial.sealType);
		}
	}
	UpdateInterface();
}

bool CkursovayadetmashDlg::ReadInput(
	CoverInput& input,
	CString& error,
	bool requireSealSelection) const
{
	auto readNumber = [this](int id, double& value) -> bool
	{
		CString text;
		GetDlgItemText(id, text);
		text.Trim();
		text.Replace(L',', L'.');
		if (text.IsEmpty())
			return false;
		wchar_t* end = nullptr;
		value = std::wcstod(text.GetString(), &end);
		return end != text.GetString() && end != nullptr && *end == L'\0' && std::isfinite(value);
	};

	input.coverType = IsDlgButtonChecked(IDC_RADIO_INSET) == BST_CHECKED
		? CoverType::Inset
		: CoverType::Overlay;
	if (!readNumber(IDC_EDIT_D, input.D))
	{
		error = L"Введите числовое значение D.";
		return false;
	}

	if (input.coverType == CoverType::Overlay)
	{
		if (!readNumber(IDC_EDIT_H, input.h))
		{
			error = L"Введите числовое значение h.";
			return false;
		}
	}
	else
	{
		input.h = 5;
	}

	input.withSeal = IsDlgButtonChecked(IDC_CHECK_SEAL) == BST_CHECKED;
	input.sealType = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
		? SealType::Type2
		: SealType::Type1;

	if (input.withSeal)
	{
		const CComboBox* combo = reinterpret_cast<const CComboBox*>(GetDlgItem(IDC_COMBO_SHAFT_D));
		const int selection = combo == nullptr ? CB_ERR : combo->GetCurSel();
		if (selection == CB_ERR)
		{
			if (!requireSealSelection)
			{
				input.withSeal = false;
				return true;
			}
			error = L"Выберите диаметр вала для манжеты.";
			return false;
		}
		input.shaftDiameter = static_cast<double>(combo->GetItemData(selection));
	}
	return true;
}

void CkursovayadetmashDlg::PopulateSealDiameters()
{
	CComboBox* combo = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SHAFT_D));
	if (combo == nullptr)
		return;

	int previousValue = -1;
	const int oldSelection = combo->GetCurSel();
	if (oldSelection != CB_ERR)
		previousValue = static_cast<int>(combo->GetItemData(oldSelection));

	m_updatingUi = true;
	combo->ResetContent();
	const SealType type = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
		? SealType::Type2
		: SealType::Type1;

	for (double shaftDiameter : GetSealShaftDiameters(type))
	{
		const CString value = FormatNumber(shaftDiameter);
		const int index = combo->AddString(value);
		combo->SetItemData(index, static_cast<DWORD_PTR>(std::lround(shaftDiameter)));
		if (static_cast<int>(std::lround(shaftDiameter)) == previousValue)
			combo->SetCurSel(index);
	}
	if (combo->GetCurSel() == CB_ERR && combo->GetCount() > 0)
		combo->SetCurSel(0);
	m_updatingUi = false;
}

bool CkursovayadetmashDlg::TryReadBaseInput(CoverInput& input) const
{
	CString inputError;
	if (!ReadInput(input, inputError, false))
		return false;
	input.withSeal = false;
	CoverParameters parameters;
	std::wstring calculationError;
	return CalculateCoverParameters(input, parameters, calculationError);
}

bool CkursovayadetmashDlg::HasCompatibleSeal(
	const CoverInput& baseInput,
	SealType type) const
{
	for (double shaftDiameter : GetSealShaftDiameters(type))
	{
		CoverInput trial = baseInput;
		trial.withSeal = true;
		trial.sealType = type;
		trial.shaftDiameter = shaftDiameter;
		CoverParameters parameters;
		std::wstring error;
		if (CalculateCoverParameters(trial, parameters, error))
			return true;
	}
	return false;
}

bool CkursovayadetmashDlg::SelectCompatibleSeal(
	const CoverInput& baseInput,
	SealType type)
{
	CComboBox* combo = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SHAFT_D));
	if (combo == nullptr)
		return false;

	auto isCompatible = [&baseInput, type](double shaftDiameter) -> bool
	{
		CoverInput trial = baseInput;
		trial.withSeal = true;
		trial.sealType = type;
		trial.shaftDiameter = shaftDiameter;
		CoverParameters parameters;
		std::wstring error;
		return CalculateCoverParameters(trial, parameters, error);
	};

	const int currentSelection = combo->GetCurSel();
	if (currentSelection != CB_ERR &&
		isCompatible(static_cast<double>(combo->GetItemData(currentSelection))))
		return true;

	for (int index = 0; index < combo->GetCount(); ++index)
	{
		if (isCompatible(static_cast<double>(combo->GetItemData(index))))
		{
			combo->SetCurSel(index);
			return true;
		}
	}
	return false;
}

void CkursovayadetmashDlg::UpdateInterface()
{
	if (m_updatingUi)
		return;
	m_updatingUi = true;

	const bool overlay = IsDlgButtonChecked(IDC_RADIO_INSET) != BST_CHECKED;
	const bool withSeal = IsDlgButtonChecked(IDC_CHECK_SEAL) == BST_CHECKED;
	if (CWnd* hEdit = GetDlgItem(IDC_EDIT_H))
		hEdit->EnableWindow(overlay);
	for (const int id : { IDC_RADIO_SEAL_TYPE1, IDC_RADIO_SEAL_TYPE2, IDC_COMBO_SHAFT_D })
	{
		if (CWnd* control = GetDlgItem(id))
			control->EnableWindow(withSeal);
	}

	CoverInput input;
	CString inputError;
	if (!ReadInput(input, inputError))
	{
		ShowParameters(nullptr);
		SetStatus(inputError);
		m_updatingUi = false;
		return;
	}

	CoverInput baseInput = input;
	baseInput.withSeal = false;
	if (baseInput.coverType == CoverType::Overlay && baseInput.h <= 0)
		baseInput.h = 5;
	CoverParameters baseParameters;
	std::wstring baseError;
	if (CalculateCoverParameters(baseInput, baseParameters, baseError))
	{
		if (overlay)
		{
			CString range;
			range.Format(L"Допустимо: %.0f–%.0f", baseParameters.hMin, baseParameters.hMax);
			SetDlgItemText(IDC_STATIC_H_RANGE, range);
		}
		else
		{
			SetDlgItemText(IDC_EDIT_H, FormatNumber(baseParameters.h));
			SetDlgItemText(IDC_STATIC_H_RANGE, L"По таблице");
		}
	}
	else
	{
		SetDlgItemText(IDC_STATIC_H_RANGE, L"Проверьте D");
	}

	CoverParameters parameters;
	std::wstring calculationError;
	if (CalculateCoverParameters(input, parameters, calculationError))
	{
		ShowParameters(&parameters);
		SetStatus(L"Параметры корректны. Модель готова к построению.");
	}
	else
	{
		ShowParameters(baseError.empty() ? &baseParameters : nullptr);
		SetStatus(CString(calculationError.c_str()));
	}
	m_updatingUi = false;
}

void CkursovayadetmashDlg::ShowParameters(const CoverParameters* p)
{
	const int resultIds[] =
	{
		IDC_EDIT_D1_RESULT, IDC_EDIT_D2_RESULT, IDC_EDIT_D3_RESULT,
		IDC_EDIT_H_RESULT, IDC_EDIT_H_SMALL_RESULT, IDC_EDIT_S_RESULT,
		IDC_EDIT_B_RESULT, IDC_EDIT_HOLE_D_RESULT, IDC_EDIT_COUNTERBORE_RESULT,
		IDC_EDIT_THREAD_RESULT, IDC_EDIT_HOLE_COUNT_RESULT,
		IDC_EDIT_SEAL_D_RESULT, IDC_EDIT_SEAL_H_RESULT,
		IDC_EDIT_CLEARANCE_RESULT, IDC_EDIT_FILLET_RESULT,
		IDC_EDIT_OUTER_FILLET_RESULT
	};
	for (int id : resultIds)
		SetDlgItemText(id, L"");
	if (p == nullptr)
		return;

	SetDlgItemText(IDC_EDIT_D1_RESULT, FormatNumber(p->D1));
	SetDlgItemText(IDC_EDIT_D2_RESULT, FormatNumber(p->D2));
	if (p->coverType == CoverType::Overlay)
		SetDlgItemText(IDC_EDIT_D3_RESULT, FormatNumber(p->D3));
	SetDlgItemText(IDC_EDIT_H_RESULT, FormatNumber(p->H));
	SetDlgItemText(IDC_EDIT_H_SMALL_RESULT, FormatNumber(p->h));
	SetDlgItemText(IDC_EDIT_S_RESULT, FormatNumber(p->s));
	if (p->coverType == CoverType::Inset)
		SetDlgItemText(IDC_EDIT_B_RESULT, FormatNumber(p->b));
	SetDlgItemText(IDC_EDIT_FILLET_RESULT, FormatNumber(p->filletRadius));
	if (p->coverType == CoverType::Overlay)
		SetDlgItemText(IDC_EDIT_OUTER_FILLET_RESULT, FormatNumber(p->outerFilletRadius));

	if (p->coverType == CoverType::Overlay)
	{
		SetDlgItemText(IDC_EDIT_HOLE_D_RESULT, FormatNumber(p->holeDiameter));
		SetDlgItemText(IDC_EDIT_COUNTERBORE_RESULT, FormatNumber(p->counterboreDiameter));
		SetDlgItemText(IDC_EDIT_THREAD_RESULT, CString(p->fastenerThread.c_str()));
		CString count;
		count.Format(L"%d", p->holeCount);
		SetDlgItemText(IDC_EDIT_HOLE_COUNT_RESULT, count);
	}

	if (p->withSeal)
	{
		SetDlgItemText(IDC_EDIT_SEAL_D_RESULT, FormatNumber(p->sealOuterDiameter));
		SetDlgItemText(IDC_EDIT_SEAL_H_RESULT, FormatNumber(p->sealWidth));
		SetDlgItemText(IDC_EDIT_CLEARANCE_RESULT, FormatNumber(p->shaftClearanceDiameter));
	}
}

void CkursovayadetmashDlg::SetStatus(const CString& text)
{
	SetDlgItemText(IDC_STATIC_STATUS, text);
}

void CkursovayadetmashDlg::OnBuildModel()
{
	CoverInput input;
	CString inputError;
	if (!ReadInput(input, inputError))
	{
		AfxMessageBox(inputError, MB_ICONWARNING);
		return;
	}

	CoverParameters parameters;
	std::wstring calculationError;
	if (!CalculateCoverParameters(input, parameters, calculationError))
	{
		AfxMessageBox(CString(calculationError.c_str()), MB_ICONWARNING);
		return;
	}

	SetStatus(L"Создание новой детали в КОМПАС-3D...");
	UpdateWindow();
	std::wstring buildError;
	if (!m_kompas.CreateCover(parameters, buildError))
	{
		const CString message = buildError.empty()
			? L"Не удалось построить модель крышки."
			: CString(buildError.c_str());
		SetStatus(message);
		AfxMessageBox(message, MB_ICONERROR);
		return;
	}
	SetStatus(L"Модель успешно построена в новой несохранённой детали.");
}

