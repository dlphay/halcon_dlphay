#pragma once



// IDD_PROPERTY_SHEET

class IDD_PROPERTY_SHEET : public CPropertySheet
{
	DECLARE_DYNAMIC(IDD_PROPERTY_SHEET)

public:
	IDD_PROPERTY_SHEET(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	IDD_PROPERTY_SHEET(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~IDD_PROPERTY_SHEET();

protected:
	DECLARE_MESSAGE_MAP()
};


