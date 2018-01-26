#include "GUIControls.h"

GUIClass::GUIClass(int w, int h)
{
	m_pFonts = NULL;
	m_pControls = NULL;
	m_pVertexBuffer = NULL;

	m_nTotalFontNum = m_nTotalControlNum = m_nTotalBufferNum = 0;
	m_nWindowWidth = m_nWindowHeight = 0;
	m_bIsBackgroundUsed = false;

	m_nWindowWidth = w; 
	m_nWindowHeight = h;
	m_bIsLoading = true;
	lastTime = curTime = 0;
	memset(&m_Background, 0, sizeof(GUICONTROL));
}

//void GUIClass::Render()
//{
//	//���Ʊ���
//	GUICONTROL *Background = GetBackground();
//	if (IsBackgroundUsed() && Background)
//	{
//		m_pSprite->Draw(Background->m_Background, NULL,
//			&D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(Background->m_xPos,
//				Background->m_yPos, 0), D3DCOLOR_XRGB(255, 255, 255));
//	}
//
//	LPD3DXFONT pFont = NULL;
//	RECT fontPosition = { 0,0,(long)GetWindowWidth(),(long)GetWindowHeight() };
//
//	int status = BUTTON_UP;
//	for (int i = 0; i < GetTotalControlNum(); i++)
//	{
//		GUICONTROL *pControl =GetGUIControl(i);
//		if (!pControl) continue;
//
//		switch (pControl->m_type)
//		{
//		case GUI_STATICTEXT:
//			pFont = GetFont(pControl->m_listID);
//			if (!pFont) continue;
//			fontPosition.left = pControl->m_xPos;
//			fontPosition.top = pControl->m_yPos;
//			pFont->DrawText(NULL, pControl->m_text, -1, &fontPosition,
//				DT_LEFT, pControl->m_color);
//			break;
//		case GUI_BUTTON:
//			status = BUTTON_UP;
//			if (mouseX > pControl->m_xPos && mouseX < pControl->m_xPos + pControl->m_width &&
//				mouseY > pControl->m_yPos && mouseY < pControl->m_yPos + pControl->m_height)
//			{
//				if (LMBDown)
//					status = BUTTON_DOWN;
//				else
//					status = BUTTON_OVER;
//			}
//
//			if (status == BUTTON_UP) texture = pControl->m_upTex;
//			if (status == BUTTON_DOWN) texture = pControl->m_downTex;
//			if (status == BUTTON_OVER)
//				if (pControl->m_overTex)
//					texture = pControl->m_overTex;
//				else
//					texture = pControl->m_downTex;
//
//			sprite->Draw(texture, NULL,
//				&D3DXVECTOR3(0, 0, 0),
//				&D3DXVECTOR3(pControl->m_xPos, pControl->m_yPos, 0),
//				D3DCOLOR_XRGB(255, 255, 255));
//			break;
//		default:
//			break;
//		}
//		if (funcPtr) funcPtr(pControl->m_id, status);
//	}
//}

GUICONTROL * GUIClass::GetBackground(int curBg)
{
	m_Background.m_Background = m_pBGs[curBg];
	if (!m_Background.m_Background)
		MessageBox(NULL, L"asdf", L"asdf111", NULL);
	m_Background.m_type = GUI_BACKGROUND;
	return &m_Background;
}

//��������
bool GUIClass::CreateTextFont(wchar_t * fontName, int size, int * fontID)
{
	if (!m_pFonts)
	{
		m_pFonts = new LPD3DXFONT[1];
		if (!m_pFonts)return false;
	}
	else
	{
		LPD3DXFONT *temp;
		temp = new LPD3DXFONT[m_nTotalFontNum + 1];
		if (!temp)return false;
		memcpy(temp, m_pFonts, sizeof(LPD3DXFONT)*m_nTotalFontNum);
		delete[] m_pFonts;
		m_pFonts = temp;
	}

	D3DXCreateFont(g_pDevice, size, 0, 0, 1000, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY
		, 0, fontName, &m_pFonts[m_nTotalFontNum]);
	if (!m_pFonts[m_nTotalFontNum])return false;

	if (fontID)*fontID = m_nTotalFontNum;
	m_nTotalFontNum++;

	return true;
}


//������̬����

//���������ؼ�
bool GUIClass::AddBackground(LPCTSTR filename,LPCTSTR loadImageName)
{
	//CREATE_TEXTURE(L"image//startmenu//light.png", &m_Background.m_Background);

	if(CREATE_TEXTURE(filename, &m_Background.m_Background))
		MessageBox(NULL, L"asd", L"asdff", NULL);

	if(loadImageName)
		CREATE_TEXTURE(loadImageName, &m_pTex);

	m_Background.m_type = GUI_BACKGROUND;

	// ��ȡ���ڿ�Ⱥ͸߶�
	float w = (float)m_nWindowWidth;
	float h = (float)m_nWindowHeight;
	m_bIsBackgroundUsed = true;
	return true;
}

bool GUIClass::AddBackground(LPCTSTR fileName, int count,LPCTSTR fileType, LPCTSTR loadImageName)
{
	static TCHAR strFileName[100];
	m_pBGs = new LPDIRECT3DTEXTURE9[count];
	m_nBgCount = count;
	for (int i = 0; i < count; i++)
	{
		swprintf_s(strFileName, L"%s%d.%s",fileName,i,fileType);
		CREATE_TEXTURE(strFileName, &m_pBGs[i]);
	}
	if (!m_pBGs)
		MessageBox(NULL, L"asdf", L"asdf", NULL);

	m_Background.m_Background = m_pBGs[0];

	if (loadImageName)
		if(CREATE_TEXTURE(loadImageName, &m_pTex)) return false;
	if (!m_Background.m_Background)
		MessageBox(NULL, L"asdf", L"asdf", NULL);
	m_Background.m_type = GUI_BACKGROUND;

	// ��ȡ���ڿ�Ⱥ͸߶�
	float w = (float)m_nWindowWidth;
	float h = (float)m_nWindowHeight;
	m_bIsBackgroundUsed = true;
	return true;
}


//������̬�ı��ؼ�
bool GUIClass::AddStaticText(int id, wchar_t * text, float x, float y, unsigned long color, int fontID)
{
	if (!text || fontID < 0 || fontID >= m_nTotalFontNum) return false;
	if (!m_pControls)
	{
		m_pControls = new GUICONTROL[1];
		if (!m_pControls) return false;
		memset(&m_pControls[0], 0, sizeof(GUICONTROL));
	}
	else
	{
		GUICONTROL *temp;
		temp = new GUICONTROL[m_nTotalControlNum + 1];
		if (!temp) return false;
		memset(temp, 0, sizeof(GUICONTROL)*(m_nTotalControlNum + 1));
		memcpy(temp, m_pControls, sizeof(GUICONTROL)*m_nTotalControlNum);
		delete[] m_pControls;
		m_pControls = temp;
	}

	m_pControls[m_nTotalControlNum].m_type = GUI_STATICTEXT;
	m_pControls[m_nTotalControlNum].m_id = id;
	m_pControls[m_nTotalControlNum].m_color = color;
	m_pControls[m_nTotalControlNum].m_xPos = x;
	m_pControls[m_nTotalControlNum].m_yPos = y;
	m_pControls[m_nTotalControlNum].m_listID = fontID;
	
	int len = wcslen(text);
	m_pControls[m_nTotalControlNum].m_text = new wchar_t[len + 1];
	if (!m_pControls[m_nTotalControlNum].m_text) return false;
	wcscpy(m_pControls[m_nTotalControlNum].m_text, text);

	m_nTotalControlNum++;
	return true;
}

//��Ӱ�ť�ؼ�
bool GUIClass::AddButton(int id, float x, float y, wchar_t * up,wchar_t *over,wchar_t * down)
{
	//if (!up || !down) return false;
	if (!m_pControls)
	{
		m_pControls = new GUICONTROL[1];
		if (!m_pControls) return false;
		memset(&m_pControls[0], 0, sizeof(GUICONTROL));
	}
	else
	{
		GUICONTROL *temp;
		temp = new GUICONTROL[m_nTotalControlNum + 1];
		if (!temp) return false;
		memset(temp, 0, sizeof(GUICONTROL)*(m_nTotalControlNum + 1));
		memcpy(temp, m_pControls, sizeof(GUICONTROL)*m_nTotalControlNum);
		delete[] m_pControls;
		m_pControls = temp;
	}

	m_pControls[m_nTotalControlNum].m_type = GUI_BUTTON;
	m_pControls[m_nTotalControlNum].m_id = id;
	m_pControls[m_nTotalControlNum].m_xPos = x;
	m_pControls[m_nTotalControlNum].m_yPos = y;
	m_pControls[m_nTotalControlNum].m_listID = m_nTotalBufferNum;
	if (up)
		CREATE_TEXTURE_IMAGEINFO(up, &m_ImageInfo, &m_pControls[m_nTotalControlNum].m_upTex);
		CREATE_TEXTURE_IMAGEINFO(down, &m_ImageInfo, &m_pControls[m_nTotalControlNum].m_downTex);
	if (over)
		CREATE_TEXTURE_IMAGEINFO(over, &m_ImageInfo, &m_pControls[m_nTotalControlNum].m_overTex);
	m_pControls[m_nTotalControlNum].m_width = m_ImageInfo.Width;
	m_pControls[m_nTotalControlNum].m_height = m_ImageInfo.Height;

	m_nTotalControlNum++;
	return true;
}

bool GUIClass::AddButton(int id, float x, float y, int w, int h, LPCWSTR up, LPCWSTR over, LPCWSTR down)
{
	if (!m_pControls)
	{
		m_pControls = new GUICONTROL[1];
		if (!m_pControls) return false;
		memset(&m_pControls[0], 0, sizeof(GUICONTROL));
	}
	else
	{
		GUICONTROL *temp;
		temp = new GUICONTROL[m_nTotalControlNum + 1];
		if (!temp) return false;
		memset(temp, 0, sizeof(GUICONTROL)*(m_nTotalControlNum + 1));
		memcpy(temp, m_pControls, sizeof(GUICONTROL)*m_nTotalControlNum);
		delete[] m_pControls;
		m_pControls = temp;
	}

	m_pControls[m_nTotalControlNum].m_type = GUI_BUTTON;
	m_pControls[m_nTotalControlNum].m_id = id;
	m_pControls[m_nTotalControlNum].m_xPos = x;
	m_pControls[m_nTotalControlNum].m_yPos = y;
	m_pControls[m_nTotalControlNum].m_listID = m_nTotalBufferNum;

	if (up)
	{
		CREATE_TEXTURE_IMAGEINFO(up, &m_ImageInfo, &m_pControls[m_nTotalControlNum].m_upTex);
	}

	CREATE_TEXTUREWH(down, w,h, &m_pControls[m_nTotalControlNum].m_downTex);

	if (over)
	{
		CREATE_TEXTURE_IMAGEINFO(over, &m_ImageInfo, &m_pControls[m_nTotalControlNum].m_overTex);
	}

	/*if (!m_pControls[m_nTotalControlNum].m_upTex || !m_pControls[m_nTotalControlNum].m_downTex)
	{
		MessageBox(NULL, L"SDF", L"asdf", NULL);
	}*/
	/*if (D3DXCreateTextureFromFile(m_pD3dDevice, up, &m_pControls[m_nTotalControlNum].m_upTex) != D3D_OK)
	return false;
	if (D3DXCreateTextureFromFile(m_pD3dDevice, down, &m_pControls[m_nTotalControlNum].m_downTex) != D3D_OK)
	return false;*/
	//unsigned long white = D3DCOLOR_XRGB(255, 255, 255);

	/*D3DSURFACE_DESC desc;
	m_pControls[m_nTotalControlNum].m_upTex->GetLevelDesc(0, &desc);

	float w = (float)desc.Width;
	float h = (float)desc.Height;*/

	m_pControls[m_nTotalControlNum].m_width = w;
	m_pControls[m_nTotalControlNum].m_height = h;

	m_nTotalControlNum++;
	return true;
}

bool GUIClass::AddButton(int id, float x, float y, int w, int h, LPCWSTR up, LPCWSTR over, LPCWSTR down, LPCWSTR xml)
{
	if (!m_pControls)
	{
		m_pControls = new GUICONTROL[1];
		if (!m_pControls) return false;
		memset(&m_pControls[0], 0, sizeof(GUICONTROL));
	}
	else
	{
		GUICONTROL *temp;
		temp = new GUICONTROL[m_nTotalControlNum + 1];
		if (!temp) return false;
		memset(temp, 0, sizeof(GUICONTROL)*(m_nTotalControlNum + 1));
		memcpy(temp, m_pControls, sizeof(GUICONTROL)*m_nTotalControlNum);
		delete[] m_pControls;
		m_pControls = temp;
	}

	m_pControls[m_nTotalControlNum].m_type = GUI_BUTTON;
	m_pControls[m_nTotalControlNum].m_id = id;
	m_pControls[m_nTotalControlNum].m_xPos = x;
	m_pControls[m_nTotalControlNum].m_yPos = y;
	m_pControls[m_nTotalControlNum].m_listID = m_nTotalBufferNum;

	if (up)
	{
		CREATE_TEXTURE_IMAGEINFO(up, &m_ImageInfo, &m_pControls[m_nTotalControlNum].m_upTex);
	}

	CREATE_TEXTUREWH(down, w, h, &m_pControls[m_nTotalControlNum].m_downTex);

	if (over)
	{
		CREATE_TEXTURE_IMAGEINFO(over, &m_ImageInfo, &m_pControls[m_nTotalControlNum].m_overTex);
	}


	m_pControls[m_nTotalControlNum].m_width = w;
	m_pControls[m_nTotalControlNum].m_height = h;
	m_pControls[m_nTotalControlNum].xml = xml;
	m_nTotalControlNum++;
	return true;
}

//������Դ
void GUIClass::ClearUp()
{
	if (m_bIsBackgroundUsed)
	{
		if (m_Background.m_Background)
			m_Background.m_Background->Release();
		/*if (m_BackgroundBuffer)
			m_BackgroundBuffer->Release();*/
	}

	m_Background.m_Background = NULL;
	//m_BackgroundBuffer = NULL;

	for (int i = 0; i < m_nTotalFontNum; i++)
	{
		if (m_pFonts[i])
		{
			m_pFonts[i]->Release();
			m_pFonts[i] = NULL;
		}
	}

	if (m_pFonts) delete[] m_pFonts;
	m_pFonts = NULL;
	m_nTotalFontNum = 0;

	for (int i = 0; i < m_nTotalBufferNum; i++)
	{
		if (m_pVertexBuffer[i])
		{
			m_pVertexBuffer[i]->Release();
			m_pVertexBuffer[i] = NULL;
		}
	}

	if (m_pVertexBuffer) delete[] m_pVertexBuffer;
	m_pVertexBuffer = NULL;
	m_nTotalBufferNum = 0;

	for (int i = 0; i < m_nTotalControlNum; i++)
	{
		if (m_pControls[i].m_Background)
		{
			m_pControls[i].m_Background->Release();
			m_pControls[i].m_Background = NULL;
		}

		if (m_pControls[i].m_upTex)
		{
			m_pControls[i].m_upTex->Release();
			m_pControls[i].m_upTex = NULL;
		}

		if (m_pControls[i].m_downTex)
		{
			m_pControls[i].m_downTex->Release();
			m_pControls[i].m_downTex = NULL;
		}

		if (m_pControls[i].m_overTex)
		{
			m_pControls[i].m_overTex->Release();
			m_pControls[i].m_overTex = NULL;
		}

		if (m_pControls[i].m_text)
		{
			delete[] m_pControls[i].m_text;
			m_pControls[i].m_text = NULL;
		}
	}
	if (m_pBGs)
	for (int i=0;i<m_nBgCount;i++)
	{
		m_pBGs[i]->Release();
		m_pBGs[i] = NULL;
	}
	if (m_pBGs)
	{
		delete[] m_pBGs;
		m_pBGs = NULL;
	}
	if (m_pTex)
	{
		m_pTex->Release(); m_pTex = NULL;
	}
	//if (m_pControls) 
	//		delete[] m_pControls;
		
	m_pControls = NULL;
	m_nTotalControlNum = 0;

}

//GUI����
void ProcessGUI(GUIClass * gui, int mouseX, int mouseY, void(*funcPtr)(int id, int status))
{
	if (!gui) return;
	LPDIRECT3DTEXTURE9 texture=NULL;
	//����ʱͼƬ
	if (gui->m_bIsLoading)
	{
		gui->curTime = GetTickCount();
		if (gui->lastTime == 0)
			 gui->lastTime= gui->curTime;

		if(gui->curTime-gui->lastTime<=1000)
			SPRITE_DRAW(gui->m_pTex, 0, 0);
		else
		{
			Safe_Release(gui->m_pTex);
			gui->lastTime = 0;
			gui->m_bIsLoading = false;
		}
		return;
	}
	else
	{
		//���Ʊ���
		GUICONTROL *Background = gui->GetBackground();
		if (gui->IsBackgroundUsed() && Background)
		{
			SPRITE_DRAW(Background->m_Background, Background->m_xPos,Background->m_yPos);
		}

		static bool keyFree = true;
		LPD3DXFONT pFont = NULL;
		RECT fontPosition = { 0,0,(long)gui->GetWindowWidth(),(long)gui->GetWindowHeight() };

		int status = BUTTON_UP;
		for (int i = 0; i < gui->GetTotalControlNum(); i++)
		{
			GUICONTROL *pControl = gui->GetGUIControl(i);
			if (!pControl) continue;

			switch (pControl->m_type)
			{
			case GUI_STATICTEXT:
				pFont = gui->GetFont(pControl->m_listID);
				if (!pFont) continue;
				fontPosition.left = pControl->m_xPos;
				fontPosition.top = pControl->m_yPos;
				pFont->DrawText(NULL, pControl->m_text, -1, &fontPosition,
					DT_LEFT, pControl->m_color);
				break;
			case GUI_BUTTON:
				status = BUTTON_UP;
				if (mouseX > pControl->m_xPos && mouseX < pControl->m_xPos + pControl->m_width &&
					mouseY > pControl->m_yPos && mouseY < pControl->m_yPos + pControl->m_height)
				{
					if (DIMOUSEDOWN(0))
					{
						status = BUTTON_DOWN; keyFree = false;
					}
					else
						status = BUTTON_OVER;
					if (!DIMOUSEDOWN(0) && !keyFree)
					{
						status = BUTTON_DOWNUP; keyFree = true;
					}
				}

				if (status == BUTTON_UP) texture = pControl->m_upTex;
				if (status == BUTTON_DOWN) texture = pControl->m_downTex;
				if (status == BUTTON_OVER)
					if (pControl->m_overTex)
						texture = pControl->m_overTex;
					else
						texture = pControl->m_downTex;
				SPRITE_DRAW(texture, pControl->m_xPos, pControl->m_yPos);
				break;
			default:
				break;
			}
			if (funcPtr) funcPtr(pControl->m_id, status);
		}
	}
}

void ProcessGUI(GUIClass * gui, int mouseX, int mouseY, void(*funcPtr)(int id, int status), bool allBg) 
{
	if (!gui) return;
	LPDIRECT3DTEXTURE9 texture = NULL;
	if (gui->m_bIsLoading)
	{
		if (gui->m_pTex && !IntervalTimeBigger(loadTime))
		{
			SPRITE_DRAW(gui->m_pTex,0,0);
		}
		else
		{
			Safe_Release(gui->m_pTex);
			gui->m_bIsLoading = false;
		}
	}
	else {
		for (int i = 0; i < gui->m_nBgCount; i++)
		{
			SPRITE_DRAW(gui->m_pBGs[i], 0, 0);
		}

		LPD3DXFONT pFont = NULL;
		RECT fontPosition = { 0,0,(long)gui->GetWindowWidth(),(long)gui->GetWindowHeight() };
		static bool keyFree = true;
		int status = BUTTON_UP;
		for (int i = 0; i < gui->GetTotalControlNum(); i++)
		{
			GUICONTROL *pControl = gui->GetGUIControl(i);
			if (!pControl) continue;

			switch (pControl->m_type)
			{
			case GUI_STATICTEXT:
				pFont = gui->GetFont(pControl->m_listID);
				if (!pFont) continue;
				fontPosition.left = pControl->m_xPos;
				fontPosition.top = pControl->m_yPos;
				pFont->DrawText(NULL, pControl->m_text, -1, &fontPosition,
					DT_LEFT, pControl->m_color);
				break;
			case GUI_BUTTON:
				status = BUTTON_UP;
				if (mouseX > pControl->m_xPos && mouseX < pControl->m_xPos + pControl->m_width &&
					mouseY > pControl->m_yPos && mouseY < pControl->m_yPos + pControl->m_height)
				{
					if (DIMOUSEDOWN(0))
					{
						status = BUTTON_DOWN; keyFree = false;
					}
					else
						status = BUTTON_OVER;
					if (!DIMOUSEDOWN(0) && !keyFree)
					{
						status = BUTTON_DOWNUP; keyFree = true;
					}
				}

				if (status == BUTTON_UP) texture = pControl->m_upTex;
				if (status == BUTTON_DOWN) texture = pControl->m_downTex;
				if (status == BUTTON_OVER)
					if (pControl->m_overTex)
						texture = pControl->m_overTex;
					else
						texture = pControl->m_downTex;
				SPRITE_DRAW(texture, pControl->m_xPos, pControl->m_yPos);
				break;
			default:
				break;
			}
			if (funcPtr) funcPtr(pControl->m_id, status);
		}
	}
}

void ProcessGUI(GUIClass * gui, int mouseX, int mouseY, void(*funcPtr)(int id, int status), int curBg)
{
	
	if (!gui) return;
	LPDIRECT3DTEXTURE9 texture = NULL;
	if (gui->m_bIsLoading)
	{
		if (gui->m_pTex && !IntervalTimeBigger(loadTime))
		{
			SPRITE_DRAW(gui->m_pTex, 0, 0);
		}
		else
		{
			Safe_Release(gui->m_pTex);
			gui->m_bIsLoading = false;
		}
	}
	else {
		//���Ʊ���
		SPRITE_DRAW(gui->m_pBGs[curBg], 0, 0);
		static bool keyFree = true;
		LPD3DXFONT pFont = NULL;
		RECT fontPosition = { 0,0,(long)gui->GetWindowWidth(),(long)gui->GetWindowHeight() };

		int status = BUTTON_UP;
		for (int i = 0; i < gui->GetTotalControlNum(); i++)
		{
			GUICONTROL *pControl = gui->GetGUIControl(i);
			if (!pControl) continue;

			switch (pControl->m_type)
			{
			case GUI_STATICTEXT:
				fontPosition.left = pControl->m_xPos;
				fontPosition.top = pControl->m_yPos;
				pFont->DrawText(NULL, pControl->m_text, -1, &fontPosition,
					DT_LEFT, pControl->m_color);
				break;
			case GUI_BUTTON:
				status = BUTTON_UP;
				if (mouseX > pControl->m_xPos && mouseX < pControl->m_xPos + pControl->m_width &&
					mouseY > pControl->m_yPos && mouseY < pControl->m_yPos + pControl->m_height)
				{
					if (DIMOUSEDOWN(0))
					{
						status = BUTTON_DOWN; keyFree=false;
					}
					else
						status = BUTTON_OVER;
					if (!DIMOUSEDOWN(0) && !keyFree)
					{
						status = BUTTON_DOWNUP; keyFree = true;
					}
				}

				if (status == BUTTON_UP) texture = pControl->m_upTex;
				if (status == BUTTON_DOWN) texture = pControl->m_downTex;
				if (status == BUTTON_OVER) texture = pControl->m_overTex;
					/*if (pControl->m_overTex)
						texture = pControl->m_overTex;
					else
						texture = pControl->m_downTex;*/
				SPRITE_DRAW(texture, pControl->m_xPos, pControl->m_yPos);
				break;
			default:
				break;
			}
			if (funcPtr) funcPtr(pControl->m_id, status);
		}
	}
	//LMBDown = DIMOUSEDOWN(0);
}

bool EditBoxClass::CtrlRender(LONG mouseX,LONG monseY)
{
	if (!m_pEditBox) return false;
	for (int i = 0; i < m_nEditBoxCount; i++)
	{		
		if (m_pEditBox[i].m_pBackground)
		{
			m_pSprite->Draw(m_pEditBox[i].m_pBackground,
				NULL, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(m_pEditBox[i].m_xPos, m_pEditBox[i].m_yPos, 0),
				D3DCOLOR_XRGB(255, 255, 255));
			m_pLineArr[0].x = m_pEditBox[i].m_xPos + 12, m_pLineArr[0].y = m_pEditBox[i].m_yPos + 60;
			m_pLineArr[1].x = m_pEditBox[i].m_xPos + 12, m_pLineArr[1].y = m_pEditBox[i].m_yPos + m_pEditBox[i].m_height - 55;
		}
		

		else {
			m_pDevice->SetStreamSource(0, m_pEditBox[i].m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));//�Ѱ����ļ�������Ϣ�Ķ��㻺�����Ⱦ��ˮ�������
			m_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);//ָ������ʹ�õ������ʽ�ĺ�����
			m_pDevice->SetIndices(m_pEditBox[i].m_pIndexBuffer);//������������
			m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, 5, 0, 4);
			m_pLineArr[0].x = m_pEditBox[i].m_xPos + 4, m_pLineArr[0].y = m_pEditBox[i].m_yPos + 2;
			m_pLineArr[1].x = m_pEditBox[i].m_xPos + 4, m_pLineArr[1].y = m_pEditBox[i].m_yPos + m_pEditBox[i].m_height - 2;
		}

		

		//m_pLine->SetAntialias(TRUE);
		m_pLine->SetWidth(1.f);

		if (mouseX > m_pEditBox[i].m_xPos && mouseX < m_pEditBox[i].m_xPos + m_pEditBox[i].m_width &&
			monseY > m_pEditBox[i].m_yPos && monseY < m_pEditBox[i].m_yPos + m_pEditBox[i].m_height)
			m_pLine->Draw(m_pLineArr, 2, D3DCOLOR_XRGB(255, 255, 255));
	}
	return true;
}

EditBoxClass::EditBoxClass(LPDIRECT3DDEVICE9 device,LPD3DXSPRITE sprite)
{
	m_pSprite = sprite;
	m_pDevice = device;
	D3DXCreateLine(m_pDevice, &m_pLine);
	m_pLineArr = new D3DXVECTOR2[2];
}

bool EditBoxClass::AddEditBoxFromFile(int xPos, int yPos, wchar_t *fileName)
{
	if (!m_pEditBox)
	{
		m_pEditBox = new MFEditBox[1];
		if (!m_pEditBox) return false;
		memset(&m_pEditBox[0], 0, sizeof(MFEditBox));
	}
	else
	{
		MFEditBox *temp;
		temp = new MFEditBox[m_nEditBoxCount + 1];
		if (!temp) return false;
		memset(temp, 0, sizeof(MFEditBox)*(m_nEditBoxCount + 1));
		memcpy(temp, m_pEditBox, sizeof(MFEditBox)*m_nEditBoxCount);
		delete[] m_pEditBox;
		m_pEditBox = temp;
	}

	D3DXCreateTextureFromFileEx(
		m_pDevice,											//�豸ָ��
		fileName,											//ͼƬ·��
		D3DX_FROM_FILE,										//ͼƬ�Ŀ������ļ�
		D3DX_FROM_FILE,										//ͼƬ�ĸ������ļ�
		0,													//�༶��������ĵȼ�
		0,													//ͼƬ������
		D3DFMT_UNKNOWN,										//δ֪�����ʽ
		D3DPOOL_MANAGED,									//��ϵͳ����Ĵ洢�ռ�
		D3DX_FILTER_LINEAR,									//�����������
		D3DX_FILTER_LINEAR,									//�༶�����������
		D3DCOLOR_XRGB(255, 255, 255),						//�ؼ�ɫ͸��
		NULL,												//ͼƬ��Ϣ��Žṹ��
		NULL,												//��ɫ����Ϣ
		&m_pEditBox[m_nEditBoxCount].m_pBackground			//����ָ��
	);

	m_pEditBox[m_nEditBoxCount].m_xPos = xPos;
	m_pEditBox[m_nEditBoxCount].m_yPos = yPos;
	m_pEditBox[m_nEditBoxCount].m_width = 186;
	m_pEditBox[m_nEditBoxCount].m_height = 98;

	if (!m_pEditBox[m_nEditBoxCount].m_pBackground)
	{
		return false;
	}
	
	m_nEditBoxCount++;
	return true;
}

bool EditBoxClass::AddEditBox(int x, int y, int w, int h)
{
	if (!m_pEditBox)
	{
		m_pEditBox = new MFEditBox[1];
		if (!m_pEditBox) return false;
		memset(&m_pEditBox[0], 0, sizeof(MFEditBox));
	}
	else
	{
		MFEditBox *temp;
		temp = new MFEditBox[m_nEditBoxCount + 1];
		if (!temp) return false;
		memset(temp, 0, sizeof(MFEditBox)*(m_nEditBoxCount + 1));
		memcpy(temp, m_pEditBox, sizeof(MFEditBox)*m_nEditBoxCount);
		delete[] m_pEditBox;
		m_pEditBox = temp;
	}
	m_pEditBox[m_nEditBoxCount].m_xPos = x;
	m_pEditBox[m_nEditBoxCount].m_yPos = y;
	m_pEditBox[m_nEditBoxCount].m_width = w;
	m_pEditBox[m_nEditBoxCount].m_height = h;
	m_pEditBox[m_nEditBoxCount].m_pBackground = NULL;
	if (!m_pDevice) return false;
	
	m_pDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pEditBox[m_nEditBoxCount].m_pVertexBuffer, NULL);
	m_pDevice->CreateIndexBuffer(4 * sizeof(WORD), 0,
		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pEditBox[m_nEditBoxCount].m_pIndexBuffer, NULL);
	CUSTOMVERTEX Vertices[4];
	Vertices[0].x = x;
	Vertices[0].y = y;
	Vertices[0].z = 0.0f;
	Vertices[0].rhw = 1.0f;
	//Vertices[0].color = D3DCOLOR_XRGB(0,0,0);
	Vertices[1].x = x + w;
	Vertices[1].y = y;
	Vertices[1].z = 0.0f;
	Vertices[1].rhw = 1.0f;
	//Vertices[1].color = D3DCOLOR_XRGB(0, 0, 0);
	Vertices[2].x = x;
	Vertices[2].y = x + h;
	Vertices[2].z = 0.0f;
	Vertices[2].rhw = 1.0f;
	//Vertices[2].color = D3DCOLOR_XRGB(0, 0, 0);
	Vertices[3].x = x + w;
	Vertices[3].y = x + h;
	Vertices[3].z = 0.0f;
	Vertices[3].rhw = 1.0f;
	//Vertices[3].color = D3DCOLOR_XRGB(0, 0, 0);
	VOID* pVertices;
	m_pEditBox[m_nEditBoxCount].m_pVertexBuffer->Lock(0, sizeof(Vertices), (void**)&pVertices, 0);
	memcpy(pVertices, Vertices, sizeof(Vertices));
	m_pEditBox[m_nEditBoxCount].m_pVertexBuffer->Unlock();

	WORD Indices[] = { 0,1,3,2,0 };

	// �����������
	WORD *pIndices = NULL;
	m_pEditBox[m_nEditBoxCount].m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	memcpy(pIndices, Indices, sizeof(Indices));
	m_pEditBox[m_nEditBoxCount].m_pIndexBuffer->Unlock();

	m_nEditBoxCount++;
	return true;
}

bool EditBoxClass::ShowControl()
{
	return false;
}

wchar_t * EditBoxClass::GetText()
{
	return nullptr;
}

bool EditBoxClass::SetText()
{
	return true;
}

void EditBoxClass::CleanUp()
{
}
