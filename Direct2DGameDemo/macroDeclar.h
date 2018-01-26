#pragma once
//地图坐标
extern float mapPosX;
extern float mapPosY;
//地图宽高
extern float mapWidth;
extern float mapHight;
//角色、怪物行走限制
#define MIN_POS_Y 300
#define MAX_POS_Y 480
#define MIN_POS_X 0
#define MAX_POS_X 640

//获取鼠标位置
extern POINT gMousePosition;

//char*转换为lpcwstr

inline LPCWSTR CharToWchar(const char* str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);			// 先取得转换后的UNICODE字符串所需的长度
	wchar_t* buf1 = (wchar_t*)calloc(len, sizeof(wchar_t));				// 分配缓冲区
	MultiByteToWideChar(CP_ACP, 0, str, -1, buf1, len);					// 开始转换
	return buf1;
}

inline string WCharToString(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);

	if (nLen <= 0) return std::string("");

	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;

	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;
}

//获取当前程序路径
inline char* GetAppPath()
{//获取应用程序根目录  
	char modulePath[MAX_PATH];
	_getcwd(modulePath, MAX_PATH);
	return modulePath;
}

typedef map<string, LPCWSTR> XmlData;

//解析xml文件
inline XmlData ReadXmlFile(string& szFileName)
{
		//读取Xml文件，并遍历
		XmlData xmlData;
		char* appPath = GetAppPath();
		string seperator = "\\";
		string fullPath = appPath + seperator + szFileName;
		//创建一个XML的文档对象。
		TiXmlDocument *myDocument = new TiXmlDocument(szFileName.c_str());
		myDocument->LoadFile();
		//获得根元素
		TiXmlElement *RootElement = myDocument->RootElement();
		//获得子节点。
		for (TiXmlElement *element = RootElement->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
		{
			static TiXmlAttribute* countAttr;
			countAttr = element->FirstAttribute();
			xmlData[(string)element->Value() + countAttr->Name()] = CharToWchar(countAttr->Value());//获得子节点的count属性值
			for (TiXmlElement *elementnext = element->FirstChildElement(); elementnext != NULL; elementnext = elementnext->NextSiblingElement())
			{
				for (TiXmlElement *elementnextchild=elementnext->FirstChildElement();elementnextchild!=NULL;elementnextchild=elementnextchild->NextSiblingElement())
				{
					xmlData[(string)elementnext->Value() + elementnextchild->Value()] = CharToWchar(elementnextchild->GetText());
				}
			}
		}

		return xmlData;
}

//sprite初始矩阵
extern D3DXMATRIX g_pMax;
extern ID3DXLine *g_pLine;