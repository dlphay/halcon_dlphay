// IDD_PROPERTY_SHEET.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_halcon_version_yds.h"
#include "IDD_PROPERTY_SHEET.h"


// IDD_PROPERTY_SHEET

IMPLEMENT_DYNAMIC(IDD_PROPERTY_SHEET, CPropertySheet)

IDD_PROPERTY_SHEET::IDD_PROPERTY_SHEET(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

IDD_PROPERTY_SHEET::IDD_PROPERTY_SHEET(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

IDD_PROPERTY_SHEET::~IDD_PROPERTY_SHEET()
{
}


BEGIN_MESSAGE_MAP(IDD_PROPERTY_SHEET, CPropertySheet)
END_MESSAGE_MAP()


// IDD_PROPERTY_SHEET 消息处理程序
