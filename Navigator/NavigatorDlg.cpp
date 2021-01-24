
// NavigatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Navigator.h"
#include "NavigatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CNavigatorDlg 对话框



CNavigatorDlg::CNavigatorDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_NAVIGATOR_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNavigatorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNavigatorDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_NAVI, &CNavigatorDlg::OnBnClickedNavi)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONUP()
    ON_BN_CLICKED(IDC_BUTTON1, &CNavigatorDlg::OnBnClickedButton1)
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDBLCLK()
    ON_CBN_EDITCHANGE(IDC_SOURCE_COMBOBOX, &CNavigatorDlg::OnCbnEditchangeSourceCombobox)
    ON_CBN_EDITCHANGE(IDC_DESTINATION_COMBOBOX, &CNavigatorDlg::OnCbnEditchangeDestinationCombobox)
END_MESSAGE_MAP()


// CNavigatorDlg 消息处理程序

BOOL CNavigatorDlg::OnInitDialog()
{

    CDialogEx::OnInitDialog();

    InitRoadsMap();
    InitPainter();
    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
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

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    //ShowWindow(SW_MAXIMIZE);

    //ShowWindow(SW_MINIMIZE);
    this->SetWindowPos(0, 200, 100, dialogWidth, dialogHeight, SWP_NOZORDER);
    GetClientRect(&m_client);
    // TODO: 在此添加额外的初始化代码

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNavigatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CNavigatorDlg::InitPainter() {
    GetDlgItem(IDC_DETAIL)->ShowWindow(FALSE);
    bgMapImg.Load(L"Data\\mapBackground.bmp");
    dialogWidth = bgMapImg.GetWidth();
    dialogHeight = bgMapImg.GetHeight() + 40;
}
void CNavigatorDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        dc.DrawIcon(x, y, m_hIcon);
        // 绘制图标
    }
    else
    {
        CDialogEx::OnPaint();   
    }
    CDC* pDC;
    pDC = this->GetDC();
    DrawOnBuffer(pDC);
}
void CNavigatorDlg::DrawOnBuffer(CDC* dc)
{
    CRgn rgn;
    rgn.CreateRectRgn(0, 40, dialogWidth, dialogHeight);
    dc->SelectClipRgn(&rgn);

    dc_mem.CreateCompatibleDC(dc);
    bitmapBuffer.CreateCompatibleBitmap(dc, dialogWidth, dialogHeight);
    dc_mem.SelectObject(&bitmapBuffer);
    dc_mem.FillSolidRect(0, 40, dialogWidth, dialogHeight, dc->GetBkColor());

    dc_mem.SetStretchBltMode(HALFTONE);

    //bitmapBuffer.Draw(dc_mem.m_hDC, rect);
    bgMapImg.Draw(dc_mem, 0, 40, dialogWidth, dialogHeight);
    for (auto i = locationIcons.begin(); i != locationIcons.end(); i++) {
        (*i)->Paint(dc_mem);
    }
    dc->BitBlt(0, 0, dialogWidth, dialogHeight, &dc_mem, 0, 0, SRCCOPY);
    int n = path.size();
    POINT* points = new POINT[n];
    for (auto i = 0; i < n; i++) {
        points[i].x = locationIcons[path[i]]->right-8;
        points[i].y = locationIcons[path[i]]->bottom-8;
    }
    CPen pen(PS_SOLID, 3, RGB(255, 0, 255));//创建画笔对象
    dc->SelectObject(&pen);
    dc->Polyline(points, n);
    delete[] points;
    /**将所有的点绘制到dc_mem上*/

    dc->SelectClipRgn(NULL);
    dc_mem.DeleteDC();
    bitmapBuffer.DeleteObject();
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNavigatorDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CNavigatorDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
}


void CNavigatorDlg::OnBnClickedNavi() {
    // TODO: 在此添加控件通知处理程序代码
    
    CString strSrc, strDst;
    GetDlgItemText(IDC_SOURCE_COMBOBOX, strSrc);
    GetDlgItemText(IDC_DESTINATION_COMBOBOX, strDst);
    int src=-1, dst=-1;
    for (auto i = organizations.begin(); i < organizations.end(); i++) {
        if ((*i).name == strSrc) {
            src = (*i).locationID;
        }
        if ((*i).name == strDst) {
            dst = (*i).locationID;
        }
    }
    if (src < 0 || dst < 0) {
        MessageBox(L"你是在我逗我吗?地址都不填");
        return;
    }
    if (src == dst) {
        MessageBox(L"拿着手机找手机?");
        return;
    }
    GetPath(src, dst);
    OnPaint();
}


void CNavigatorDlg::OnMouseMove(UINT nFlags, CPoint point) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    bool flag = false;
    int x = 0, y = 0;
    FZJ::LocationSprite* selectedLocation = nullptr;
    for (auto i = locationIcons.begin(); i != locationIcons.end(); i++) {
        if ((*i)->OnMouseMove(point.x, point.y)) {
            flag = true;
            selectedLocation = *i;
            x = selectedLocation->right + 5;
            y = selectedLocation->bottom + 5;
            break;
        }
    }
    GetDlgItem(IDC_DETAIL)->ShowWindow(flag);
    if (flag) {
        GetDlgItem(IDC_DETAIL)->SetWindowPos(0, x, y, 0, 0, SWP_NOSIZE);
        CString tmp;
        if (selectedLocation) {
            for (auto i = selectedLocation->organizations.begin(); i != selectedLocation->organizations.end(); i++) {
                tmp += (*i)->name;
                tmp += L"\n";
            }
        }
        tmp = tmp.Trim();
        GetDlgItem(IDC_DETAIL)->SetWindowText(tmp);
    }

    CDialogEx::OnMouseMove(nFlags, point);
}


void CNavigatorDlg::OnLButtonUp(UINT nFlags, CPoint point) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    bool flag = false;
    int x = 0, y = 0;
    FZJ::LocationSprite* selectedLocation = nullptr;
    for (auto i = locationIcons.begin(); i != locationIcons.end(); i++) {
        if ((*i)->OnMouseLButtonUp(point.x, point.y)) {
            flag = true;
            selectedLocation = *i;
            x = selectedLocation->right + 5;
            y = selectedLocation->bottom + 5;
            break;
        }
    }
    if (flag && selectedLocation) {
        SetDlgItemText(IDC_SOURCE_COMBOBOX, selectedLocation->organizations[0]->name);
    }
    CDialogEx::OnLButtonUp(nFlags, point);
}


void CNavigatorDlg::OnRButtonUp(UINT nFlags, CPoint point) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    bool flag = false;
    int x = 0, y = 0;
    FZJ::LocationSprite* selectedLocation = nullptr;
    for (auto i = locationIcons.begin(); i != locationIcons.end(); i++) {
        if ((*i)->OnMouseRButtonUp(point.x, point.y)) {
            flag = true;
            selectedLocation = *i;
            x = selectedLocation->right + 5;
            y = selectedLocation->bottom + 5;
            break;
        }
    }
    if (flag && selectedLocation) {
        SetDlgItemText(IDC_DESTINATION_COMBOBOX, selectedLocation->organizations[0]->name);
    }
    CDialogEx::OnRButtonUp(nFlags, point);
}

void CNavigatorDlg::InitRoadsMap()
{
    /// <summary>
    /// 分割输入
    /// </summary>
    auto split = [](CString source, CStringArray& dest, CString division)->void
    {
        dest.RemoveAll();
        int pos = 0;
        int pre_pos = 0;
        if (source.Find(division) == -1) {
            dest.Add(source);
            return;
        }
        while (-1 != pos) {
            pre_pos = pos;
            pos = source.Find(division, (pos + 1));
            if (pos == -1) {
                auto tmp = source.Mid(pre_pos + 1, source.GetLength() - pre_pos).Trim();
                if (tmp != L"") {
                    dest.Add(tmp);
                }
                return;
            }
            auto tmp = source.Mid(pre_pos, (pos - pre_pos)).Trim();
            if (tmp != L"") {
                dest.Add(tmp);
            }
#ifdef _DEBUG
            auto a = dest.GetCount();
#endif
        }
    };
    /*********************Organization******************************/
    CStdioFile file;
    if (!file.Open(L"Data\\Organization.txt", CFile::modeRead | CFile::typeBinary)) {
        MessageBox(L"Data\\Organization.txt not found!", 0, 0);
        HANDLE hself = GetCurrentProcess();
        TerminateProcess(hself, 0);
    }
    CString wholeFile;
    char* buffer;
    ULONGLONG length = file.GetLength();
    buffer = new char[length + 1];
    buffer[length] = 0;
    file.Read(buffer, length);
    int n = MultiByteToWideChar(CP_UTF8, 0, buffer, length + 1, NULL, 0);
    wchar_t* pWideChar = new wchar_t[n + 1];
    MultiByteToWideChar(CP_UTF8, 0, buffer, length + 1, pWideChar, n);
    wholeFile = CString(pWideChar).Trim();
    CStringArray strOrganizations;//org finished
    split(wholeFile, strOrganizations, L"\n");
    delete[] buffer;
    delete[] pWideChar;
    file.Close();

    /***********************Location****************************/
    if (!file.Open(L"Data\\Location.txt", CFile::modeRead | CFile::typeBinary)) {
        MessageBox(L"Data\\Location.txt not found!", 0, 0);
        HANDLE hself = GetCurrentProcess();
        TerminateProcess(hself, 0);
    }
    length = file.GetLength();
    buffer = new char[length + 1];
    buffer[length] = 0;
    file.Read(buffer, length);
    n = MultiByteToWideChar(CP_UTF8, 0, buffer, length + 1, NULL, 0);
    pWideChar = new wchar_t[n + 1];
    MultiByteToWideChar(CP_UTF8, 0, buffer, length + 1, pWideChar, n);
    wholeFile = CString(pWideChar).Trim();
    CStringArray strLocations;//org finished
    split(wholeFile, strLocations, L"\n");
    delete[] buffer;
    delete[] pWideChar;
    file.Close();
    /***********************Edge****************************/
    if (!file.Open(L"Data\\Edge.txt", CFile::modeRead | CFile::typeBinary)) {
        MessageBox(L"Data\\Edge.txt not found!", 0, 0);
        HANDLE hself = GetCurrentProcess();
        TerminateProcess(hself, 0);
    }
    length = file.GetLength();
    buffer = new char[length + 1];
    buffer[length] = 0;
    file.Read(buffer, length);
    n = MultiByteToWideChar(CP_UTF8, 0, buffer, length + 1, NULL, 0);
    pWideChar = new wchar_t[n + 1];
    MultiByteToWideChar(CP_UTF8, 0, buffer, length + 1, pWideChar, n);
    wholeFile = CString(pWideChar).Trim();
    CStringArray strEdges;//org finished
    split(wholeFile, strEdges, L"\n");
    delete[] buffer;
    delete[] pWideChar;
    file.Close();

    /***********************Locorg.txt****************************/
    if (!file.Open(L"Data\\Locorg.txt", CFile::modeRead | CFile::typeBinary)) {
        MessageBox(L"Data\\Locorg.txt not found!", 0, 0);
        HANDLE hself = GetCurrentProcess();
        TerminateProcess(hself, 0);
    }
    length = file.GetLength();
    buffer = new char[length + 1];
    buffer[length] = 0;
    file.Read(buffer, length);
    n = MultiByteToWideChar(CP_UTF8, 0, buffer, length + 1, NULL, 0);
    pWideChar = new wchar_t[n + 1];
    MultiByteToWideChar(CP_UTF8, 0, buffer, length + 1, pWideChar, n);
    wholeFile = CString(pWideChar).Trim();
    //auto tmp = wholeFile.Mid(0, 10);
    std::vector<std::vector<int>> orgsOfLocation;
    CStringArray orgsOfLocationLines;//org finished
    split(wholeFile, orgsOfLocationLines, L"\n");
    for (int i = 0; i < orgsOfLocationLines.GetCount(); i++) {
        CStringArray tmp;
        split(orgsOfLocationLines.GetAt(i), tmp, L",");
        orgsOfLocation.push_back(std::vector<int>());
        for (int j = 0; j < tmp.GetCount(); j++) {
            auto index = _ttoi(tmp.GetAt(j));
            orgsOfLocation[i].push_back(index);
        }
    }
    delete[] buffer;
    delete[] pWideChar;
    file.Close();
    /************************Read file end************************/
    /**********************Start init models************************/
    auto countOfLocations = strLocations.GetCount();
    for (int i = 0; i < countOfLocations; i++) {
        locationIcons.push_back(new FZJ::LocationSprite(strLocations.GetAt(i), i));
        roadsMap.push_back(std::vector<double>(countOfLocations, UINT_MAX));
        roadsMap[i][i] = 0;
        int countOfOrgs = orgsOfLocation[i].size();
        for (int j = 0; j < countOfOrgs; j++) {
            locationIcons[i]->organizations.push_back(new FZJ::Organization(strOrganizations.GetAt(orgsOfLocation[i][j])));
            organizations.push_back(FZJ::Organization(strOrganizations.GetAt(orgsOfLocation[i][j])));
            organizations.back().locationID = i;
        }
    }
    auto countOfEdges = strEdges.GetCount();
    for (int i = 0; i < countOfEdges; i++) {
        auto str = strEdges.GetAt(i);
        CString tmp(str);
        tmp.Trim();
        auto index = tmp.Find(L'，', 0);
        index = index > -1 ? index : tmp.Find(L',', 0);
        auto xstr = tmp.Mid(0, index);
        auto ystr = tmp.Mid(index + 1, tmp.GetLength() - index);
        auto x = _ttoi(xstr);
        auto y = _ttoi(ystr);
        roadsMap[x][y] = locationIcons[x]->distanceTo(locationIcons[y]);
        roadsMap[y][x] = roadsMap[x][y];
    }
    //做出pathCache
    Floyd(roadsMap);

    //std::string a;
    //for (int i = 0; i < roadsMap.size(); i++) {
    //    for (int j = 0; j < roadsMap[i].size(); j++) {
    //        a += std::to_string(roadsMap[i][j]);
    //        a += ' ';
    //    }
    //    a += '\n';
    //}
    //std::fstream out("1.txt", std::ios::in | std::ios::out|std::ios::app);
    //out << a;
    //int aa = 0;
}


void CNavigatorDlg::OnBnClickedButton1()
{
    this->SendMessage(WM_CLOSE);
    // TODO: 在此添加控件通知处理程序代码
}


BOOL CNavigatorDlg::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    return CDialogEx::OnEraseBkgnd(pDC);
    //return true;
}

void CNavigatorDlg::Floyd(std::vector<std::vector<double>>& edges){
    pathCahe = new std::vector<std::vector<int>>(edges.size(), std::vector<int>(edges.size(), -1));//STL
    for (int k = 0; k < edges.size(); k++){
        for (int i = 0; i < edges.size(); i++) {
            for (int j = 0; j < edges.size(); j++) {
                if (edges[i][j] > edges[i][k] + edges[k][j]){//如果能够缩短就更新距离 
                    edges[i][j] = edges[i][k] + edges[k][j];
                    (*pathCahe)[i][j] = k;//记录能松弛的点 
                }
            }
        }
    }
}
//empty path before call GetPath
void CNavigatorDlg::GetPath(int a, int b) {
    path.clear();
    path.push_back(a);
    Assistant(a, b);
    path.push_back(b);
}
void CNavigatorDlg::Assistant(int a, int b) {
    if ((*pathCahe)[a][b] == -1) return;//因为开始初始化为-1，这里就可以避免相邻的再次输出 
    Assistant(a, (*pathCahe)[a][b]);//前半部 
    path.push_back((*pathCahe)[a][b]);
    Assistant((*pathCahe)[a][b], b);//后半部 
}

void CNavigatorDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    OnBnClickedNavi();
    CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CNavigatorDlg::OnCbnEditchangeSourceCombobox()
{
    CComboBox *m_cbb = (CComboBox *)GetDlgItem(IDC_SOURCE_COMBOBOX);
    CString strObj;
    m_cbb->GetWindowText(strObj);
    if (strObj.GetLength() == 0) {
        m_cbb->ShowDropDown(false);
        return;
    }
    m_cbb->ResetContent();
    for (auto i = organizations.begin(); i != organizations.end(); i++) {
        if((i)->longestSubstring(strObj) >=strObj.GetLength())
        {
            m_cbb->AddString(i->name);
        }
    }
    ::SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
    m_cbb->ShowDropDown();
    if (m_cbb->GetCount() == 1)
    {
        m_cbb->SetCurSel(0);
    }
    m_cbb->SetWindowText(strObj);
    m_cbb->SetEditSel(strObj.GetLength(), strObj.GetLength());
    // TODO: 在此添加控件通知处理程序代码
}


void CNavigatorDlg::OnCbnEditchangeDestinationCombobox()
{
    CComboBox* m_cbb = (CComboBox*)GetDlgItem(IDC_DESTINATION_COMBOBOX);
    CString strObj;
    m_cbb->GetWindowText(strObj);
    if (strObj.GetLength() == 0) {
        m_cbb->ShowDropDown(false);
        return;
    }
    m_cbb->ResetContent();
    for (auto i = organizations.begin(); i != organizations.end(); i++) {
        if ((i)->longestSubstring(strObj) >= strObj.GetLength())
        {
            m_cbb->AddString(i->name);
        }
    }
    ::SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
    m_cbb->ShowDropDown();
    if (m_cbb->GetCount() == 1)
    {
        m_cbb->SetCurSel(0);
    }
    m_cbb->SetWindowText(strObj);
    m_cbb->SetEditSel(strObj.GetLength(), strObj.GetLength());
    // TODO: 在此添加控件通知处理程序代码
}
