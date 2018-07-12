#pragma once


// IDD_CAPSULE_PAGE 对话框

class IDD_CAPSULE_PAGE : public CPropertyPage
{
	DECLARE_DYNAMIC(IDD_CAPSULE_PAGE)

public:
	IDD_CAPSULE_PAGE();
	virtual ~IDD_CAPSULE_PAGE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAPSULE_PAGR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
