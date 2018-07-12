#pragma once


// IDD_MARK_PAGE 对话框

class IDD_MARK_PAGE : public CPropertyPage
{
	DECLARE_DYNAMIC(IDD_MARK_PAGE)

public:
	IDD_MARK_PAGE();
	virtual ~IDD_MARK_PAGE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MARK_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
