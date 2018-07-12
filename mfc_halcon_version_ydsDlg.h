
// mfc_halcon_version_ydsDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// Cmfc_halcon_version_ydsDlg 对话框
class Cmfc_halcon_version_ydsDlg : public CDialogEx
{
// 构造
public:
	Cmfc_halcon_version_ydsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_HALCON_VERSION_YDS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton4();
	CString Result_of_recognition;
	afx_msg void OnEnChangeEdit1();
	CEdit Result_pin_01_width;
	CString Result_pin_02_width;
	CString Result_pin01_width;
	CString Result_pin_03_width;
	CString Result_pin_04_width;
	CString Result_pin_05_width;
	CString Result_pin_06_width;
	CString Result_pin_07_width;
	CString Result_pin_08_width;
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnEnChangeEdit15();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnEnChangeEdit17();
	CString Result_gap_01_width;
	CString Result_gap_02_width;
	CString Result_gap_03_width;
	CString Result_gap_04_width;
	CString Result_gap_06_width;
	CString Result_gap_05_width;
	CString Result_pin_a_width;
	CString Result_gap_a_width;
	afx_msg void OnEnChangeEdit18();
	CString m_sSnapFilePath;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnEnChangeEdit19();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnStnClickedStaticPreview();
	CStatic m_cPreview;
	CString Result_of_ocr_recognition;
	CString Result_pin0n_width;
	CString Result_dis_01_yds_width;
	CString Result_dis_02_yds_width;
	CString Result_dis_03_yds_width;
	CString Result_dis_04_yds_width;
	CString Result_dis_05_yds_width;
	CString Result_dis_06_yds_width;
	afx_msg void OnEnChangeEdit57();
	afx_msg void OnEnChangeEdit61();
	afx_msg void OnEnChangeEdit58();
	afx_msg void OnEnChangeEdit59();
	afx_msg void OnEnChangeEdit60();
	afx_msg void OnEnChangeEdit56();
	CString Result_detection_00_00_yds;
	CString Result_detection_01_00_yds;
	CString Result_detection_02_00_yds;
	CString Result_detection_03_00_yds;
	CString Result_detection_04_00_yds;
	CString Result_detection_10_00_yds;
	CString Result_detection_11_00_yds;
	CString Result_detection_12_00_yds;
	CString Result_detection_13_00_yds;
	CString Result_detection_14_00_yds;
	CString Result_detection_15_00_yds;
	CString Result_detection_16_00_yds;
	CString Result_detection_17_00_yds;
	CString Result_detection_18_00_yds;
	CString Result_detection_19_00_yds;
	CString Result_detection_20_00_yds;
	CString Result_detection_25_00_yds;
	CString Result_detection_29_00_yds;
	CString Result_detection_21_00_yds;
	afx_msg void OnEnChangeEdit20();
	afx_msg void OnEnChangeEdit21();
	afx_msg void OnEnChangeEdit22();
	afx_msg void OnEnChangeEdit23();
	afx_msg void OnEnChangeEdit24();
	afx_msg void OnEnChangeEdit25();
	afx_msg void OnEnChangeEdit26();
	afx_msg void OnEnChangeEdit27();
	afx_msg void OnEnChangeEdit28();
	afx_msg void OnEnChangeEdit29();
	afx_msg void OnEnChangeEdit30();
	afx_msg void OnEnChangeEdit31();
	afx_msg void OnEnChangeEdit32();
	afx_msg void OnEnChangeEdit33();
	afx_msg void OnEnChangeEdit34();
	afx_msg void OnEnChangeEdit37();
	afx_msg void OnEnChangeEdit39();
	afx_msg void OnEnChangeEdit40();
	afx_msg void OnEnChangeEdit41();
	afx_msg void OnEnChangeEdit42();
	afx_msg void OnEnChangeEdit44();
	afx_msg void OnEnChangeEdit45();
	afx_msg void OnEnChangeEdit46();
	afx_msg void OnEnChangeEdit47();
	afx_msg void OnEnChangeEdit48();
	afx_msg void OnEnChangeEdit49();
	afx_msg void OnEnChangeEdit50();
	afx_msg void OnEnChangeEdit51();
	afx_msg void OnEnChangeEdit52();
	afx_msg void OnEnChangeEdit53();
	afx_msg void OnEnChangeEdit54();
	afx_msg void OnEnChangeEdit55();
	afx_msg void OnEnChangeEdit36();
	afx_msg void OnEnChangeEdit35();
	afx_msg void OnEnChangeEdit38();
	CString Result_detection_24_01_yds;
	CString Result_detection_24_02_yds;
	CString Result_detection_24_03_yds;
	CString Result_detection_24_04_yds;
	CString Result_detection_24_05_yds;
	CString Result_detection_24_06_yds;
	CString Result_detection_24_07_yds;
	CString Result_detection_24_08_yds;
	CString Result_detection_26_01_yds;
	CString Result_detection_26_02_yds;
	CString Result_detection_26_03_yds;
	CString Result_detection_26_04_yds;
	CString Result_detection_26_05_yds;
	CString Result_detection_26_06_yds;
	CString Result_detection_26_07_yds;
	CString Result_detection_26_08_yds;
	CString NCC_QUALITY_SCORE;
	CString OCV_QUALITY_SCORE_TRAIN;
	CString OCV_QUALITY_SCORE;
	afx_msg void OnEnChangeEdit43();
	afx_msg void OnEnChangeEdit62();
	afx_msg void OnEnChangeEdit63();
	CString OCV_QUALITY_SCORE_TRAIN_CAPSULE;
	CString OCV_QUALITY_SCORE_CAPSULE;
	afx_msg void OnEnChangeEdit64();
	afx_msg void OnEnChangeEdit65();
};
