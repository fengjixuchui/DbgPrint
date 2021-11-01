#include "pch.h"
#include "resource.h"
#include "PropertiesDlg.h"
#include "DebugOutputBase.h"
#include "ImageIconCache.h"
#include "ProcessManager.h"
#include "AppSettings.h"

CPropertiesDlg::CPropertiesDlg(DebugItem const& item) : m_Item(item) {
}

LRESULT CPropertiesDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL&) {
    InitDynamicLayout();
    AdjustOKCancelButtons();

    AppSettings::Get().LoadWindowPosition(m_hWnd, L"PropertiesDlg");

    CImageList images(ImageIconCache::Get().GetImageList());
    SetDialogIcon(images.GetIcon(m_Item.Image));

    SetDlgItemInt(IDC_PID, m_Item.Process.ProcessId, FALSE);
    SetDlgItemInt(IDC_INDEX, m_Item.Index, FALSE);
    SetDlgItemText(IDC_TIME, m_Item.LocalTimeAsString);
    SetDlgItemText(IDC_NAME, m_Item.ProcessName);
    SetDlgItemText(IDC_PATH, ProcessManager::Get().GetProcessInfo(m_Item.Process)->FullPath);
    SetDlgItemText(IDC_TEXT, m_Item.Text);
    SetDlgItemText(IDC_COMMENT, m_Item.Comment);

    return 0;
}

LRESULT CPropertiesDlg::OnCloseCmd(WORD, WORD wID, HWND, BOOL&) {
    AppSettings::Get().SaveWindowPosition(m_hWnd, L"PropertiesDlg");

    if (wID == IDOK) {
        GetDlgItemText(IDC_COMMENT, m_Comment);
        GetDlgItemText(IDC_TEXT, m_Text);
    }
    EndDialog(wID);
    return 0;
}
