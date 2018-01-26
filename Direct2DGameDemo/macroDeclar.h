#pragma once
//��ͼ����
extern float mapPosX;
extern float mapPosY;
//��ͼ���
extern float mapWidth;
extern float mapHight;
//��ɫ��������������
#define MIN_POS_Y 300
#define MAX_POS_Y 480
#define MIN_POS_X 0
#define MAX_POS_X 640

//��ȡ���λ��
extern POINT gMousePosition;

//char*ת��Ϊlpcwstr

inline LPCWSTR CharToWchar(const char* str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);			// ��ȡ��ת�����UNICODE�ַ�������ĳ���
	wchar_t* buf1 = (wchar_t*)calloc(len, sizeof(wchar_t));				// ���仺����
	MultiByteToWideChar(CP_ACP, 0, str, -1, buf1, len);					// ��ʼת��
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

//��ȡ��ǰ����·��
inline char* GetAppPath()
{//��ȡӦ�ó����Ŀ¼  
	char modulePath[MAX_PATH];
	_getcwd(modulePath, MAX_PATH);
	return modulePath;
}

typedef map<string, LPCWSTR> XmlData;

//����xml�ļ�
inline XmlData ReadXmlFile(string& szFileName)
{
		//��ȡXml�ļ���������
		XmlData xmlData;
		char* appPath = GetAppPath();
		string seperator = "\\";
		string fullPath = appPath + seperator + szFileName;
		//����һ��XML���ĵ�����
		TiXmlDocument *myDocument = new TiXmlDocument(szFileName.c_str());
		myDocument->LoadFile();
		//��ø�Ԫ��
		TiXmlElement *RootElement = myDocument->RootElement();
		//����ӽڵ㡣
		for (TiXmlElement *element = RootElement->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
		{
			static TiXmlAttribute* countAttr;
			countAttr = element->FirstAttribute();
			xmlData[(string)element->Value() + countAttr->Name()] = CharToWchar(countAttr->Value());//����ӽڵ��count����ֵ
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

//sprite��ʼ����
extern D3DXMATRIX g_pMax;
extern ID3DXLine *g_pLine;