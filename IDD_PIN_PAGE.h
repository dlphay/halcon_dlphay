#pragma once


// IDD_PIN_PAGE 对话框

class IDD_PIN_PAGE : public CPropertyPage
{
	DECLARE_DYNAMIC(IDD_PIN_PAGE)

public:
	IDD_PIN_PAGE();
	virtual ~IDD_PIN_PAGE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIN_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
