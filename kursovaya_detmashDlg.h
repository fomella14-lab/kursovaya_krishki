
// kursovaya_detmashDlg.h: файл заголовка
//

#pragma once

#include "CoverParameters.h"

class CKompas;

// Диалоговое окно CkursovayadetmashDlg
class CkursovayadetmashDlg : public CDialog
{
// Создание
public:
	CkursovayadetmashDlg(CKompas& kompas, CWnd* pParent = nullptr);
	virtual ~CkursovayadetmashDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KURSOVAYA_DETMASH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnParametersChanged();
	afx_msg void OnSealExecutionChanged();
	afx_msg void OnSealTypeChanged();
	afx_msg void OnSealDiameterChanged();
	afx_msg void OnBuildModel();
	afx_msg void OnResetParameters();
	afx_msg void OnTabSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

private:
	CKompas& m_kompas;
	CFont m_uiFont;
	std::vector<HWND> m_parameterControls;
	std::vector<HWND> m_drawingPageControls[3];
	HWND m_drawingPreviews[3]{};
	HWND m_drawingHints[3]{};
	HBITMAP m_drawingBitmaps[3]{};
	CSize m_fixedWindowSize;
	bool m_updatingUi = false;

	void CreateMainTabs();
	void CreateParameterControls();
	void CreateDrawingControls();
	void ShowSelectedTab();
	bool LoadDrawing(int index, const CString& path, bool showError);
	void LoadProjectDrawings();
	void ResetParameters();
	void UpdateInterface();
	void PopulateSealDiameters();
	bool TryReadBaseInput(CoverInput& input) const;
	bool HasCompatibleSeal(const CoverInput& baseInput, SealType type) const;
	bool SelectCompatibleSeal(const CoverInput& baseInput, SealType type);
	bool ReadInput(CoverInput& input, CString& error, bool requireSealSelection = true) const;
	void ShowParameters(const CoverParameters* parameters);
	void SetStatus(const CString& text);
};
