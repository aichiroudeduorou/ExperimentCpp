
// NavigatorDlg.h: 头文件
//

#pragma once
#include "models.h"
#include "sprites.h"
// CNavigatorDlg 对话框
class CNavigatorDlg : public CDialogEx
{
// 构造
public:
	CNavigatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAVIGATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg
	void InitPainter();
	void OnPaint();
	void DrawOnBuffer(CDC* dc);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedNavi();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
private:
	std::vector<FZJ::LocationSprite*> locationIcons;
	std::vector<std::vector<double>> roadsMap;
	std::vector<FZJ::Organization> organizations;
	std::vector<int> path;
	std::vector<std::vector<int>> *pathCahe;
	//std::vector<FZJ::LocationSprite*> locations;
	void InitRoadsMap();
	void Assistant(int a, int b);
	CImage bgMapImg;
	CDC dc_mem;   //缓冲DC
	CBitmap bitmapBuffer;//缓冲位图
	CRect m_client;
	int dialogWidth, dialogHeight;
	
public:
	afx_msg void OnBnClickedButton1();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void Floyd(std::vector<std::vector<double>>& map);
	void GetPath(int a, int b);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCbnEditchangeSourceCombobox();
	afx_msg void OnCbnEditchangeDestinationCombobox();
};
