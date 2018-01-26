#include "Town.h"
#include "Door.h"

Door *door = NULL;

Town::Town()
{
	m_pMap = new Map();
	m_pAniMgr = new AnimationMgr();
	m_pDoorMgr = new DoorMgr();
	m_pNpcMgr = new NpcMgr();
	m_nMapCount = 0;
}

Town::Town(LPCTSTR mapName, LPCTSTR bgName)
{
	string fileName = "data\\aierwen.xml";
	xmlData=ReadXmlFile(fileName);
	m_pMap = new Map();
	m_pAniMgr = new AnimationMgr();
	m_pDoorMgr = new DoorMgr();
	m_sMapBg = mapName;
	m_sMapPros = bgName;
}

bool Town::Init(string dataFile)
{
	m_bIsLoad = true;
	mEndTime = 0;
	xmlData = ReadXmlFile(dataFile);
	int count,w,h;
	roleInst->IsRender(true);

	//场景类型为选择地下城时的初始化
	if (lstrcmp(xmlData["scenetype"],L"choose") ==0)
	{
		roleInst->IsRender(false);
		m_pTexLoad = CreateTexture(xmlData["bgload"], w, h);
		m_nMapType = MAP_TYPE_DUNGEON;
		guiInst->AddBackground(xmlData["bgpath"], xmlData["bgload"]);
		count = stoi(xmlData["dgcount"]);
		for (int i = 1; i <= count; i++)
		{
			string str = to_string(i);
			LPCWSTR up = xmlData["dg" + str + "up"];
			LPCWSTR over = xmlData["dg" + str + "over"];
			float xpos = stoi(xmlData["dg" + str + "xPos"]);
			float ypos = stoi(xmlData["dg" + str + "yPos"]);
			int width = stoi(xmlData["dg" + str + "width"]);
			int hight = stoi(xmlData["dg" + str + "hight"]);
			LPCWSTR xml = xmlData["dg" + str + "info"];
			guiInst->AddButton(i + 2, xpos, ypos, width, hight, up, over,over,xml);
		}
		return true;
	}
	m_pTexLoad = CreateTexture(xmlData["mapload"], w, h);
	//场景类型为地下城时的初始化
	if (lstrcmp(xmlData["scenetype"], L"dungeon") == 0)
	{
		m_nMapType = MAP_TYPE_DUNGEON;
		count = stoi(xmlData["doorcount"]);
		for (int i = 1; i <= count; i++)
		{
			DoorInfo doorInfo;
			string str = to_string(i);
			float xpos = stof(xmlData["door" + str + "xPos"]);
			float ypos = stof(xmlData["door" + str + "yPos"]);
			LPCWSTR info = xmlData["door" + str + "Info"];
			doorInfo.path = xmlData["door" + str + "path"];
			doorInfo.closeTex = xmlData["door" + str + "close"];
			doorInfo.rolePosX = stof(xmlData["door" + str + "rolex"]);
			doorInfo.rolePosY = stof(xmlData["door" + str + "roley"]);
			doorInfo.mapx = stof(xmlData["door" + str + "mapx"]);
			doorInfo.xml = WCharToString(info);
			m_pDoorMgr->AddDoor(new Door(doorInfo, xpos, ypos));
		}
		//结算界面初始化
		m_pGuiOption = new GUIClass(800, 600);
		m_pGuiOption->AddBackground(L"image//result.png", NULL);
		m_pGuiOption->AddButton(BUTTON_ID_2, 700, 80, L"image//gui//4.png", L"image//gui//12.png", L"image//gui//17.png");
		m_pGuiOption->AddButton(BUTTON_ID_1, 700, 50, L"image//gui//3.png", L"image//gui//11.png", L"image//gui//16.png");
		if(!IsInited(stoi(xmlData["mapid"])))
			monsterInst->AddMonster(stoi(xmlData["monstercount"]));
		m_pMap->AddMap(xmlData["mapname"], xmlData["mapproc"]);
		m_pMap->Init();
		initedMap[m_nMapCount] = stoi(xmlData["mapid"]);
		m_nMapCount++;
		return true;
	}
	//场景类型为城镇时的初始化

	m_nMapType = MAP_TYPE_TOWN;
#pragma region
	mapPosX = stof(xmlData["mapxPos"]);
	mapPosY = stof(xmlData["mapyPos"]);
	rolePosX = stof(xmlData["rolexPos"]);
	rolePosY = stof(xmlData["roleyPos"]);
	m_pMap->AddMap(xmlData["mapname"],NULL);
	m_pMap->Init();
	//初始化npc
	count = stoi(xmlData["npccount"]);
	for (int i=1;i<=count;i++)
	{
		string str = to_string(i);
		LPCWSTR filename = xmlData["npc"+str+"path"];
		int filecount = stoi(xmlData["npc" + str + "count"]);
		float xpos = stof(xmlData["npc" + str + "xPos"]);
		float ypos = stof(xmlData["npc" + str + "yPos"]);
		LPCWSTR name = xmlData["npc" + str + "name"];
		m_pNpcMgr->AddNpc(new NPC(filename,L"png",filecount,xpos,ypos,name));
	}
	//初始化门
	count = stoi(xmlData["doorcount"]);
	for (int i = 1; i <= count; i++)
	{
		DoorInfo doorInfo;
		string str = to_string(i);
		float xpos = stof(xmlData["door" + str + "xPos"]);
		float ypos = stof(xmlData["door" + str + "yPos"]);
		LPCWSTR info = xmlData["door" + str + "Info"];
		doorInfo.path = xmlData["door" + str + "path"];
		doorInfo.closeTex = xmlData["door" + str + "close"];
		doorInfo.rolePosX=stof(xmlData["door" + str + "rolex"]);
		doorInfo.rolePosY=stof(xmlData["door" + str + "roley"]);
		doorInfo.mapx= stof(xmlData["door" + str + "mapx"]);
		doorInfo.xml =WCharToString(info);
		m_pDoorMgr->AddDoor(new Door(doorInfo, xpos, ypos));
	}
	//初始化动画
	count = stoi(xmlData["animationcount"]);
	for (int i = 1; i <= count; i++)
	{
		string str = to_string(i);
		LPCWSTR filename = xmlData["animation" + str + "path"];
		int filecount = stoi(xmlData["animation" + str + "count"]);
		int speed = stoi(xmlData["animation" + str + "speed"]);
		float xpos = stof(xmlData["animation" + str + "xPos"]);
		float ypos = stof(xmlData["animation" + str + "yPos"]);
		LPCWSTR name = xmlData["animation" + str + "name"];
		float scaling= stof(xmlData["animation" + str + "scaling"]);
		m_pAniMgr->AddAnimation(new Animation(filename, filecount, xpos, ypos,speed,D3DXVECTOR2(scaling,scaling)));
	}

#pragma endregion
	return true;
}

void CallBackGui(int id,int state)
{
	if(state==BUTTON_DOWNUP)
	{
		townInst->CleanUp();
		townInst->Init(WCharToString(guiInst->GetGUIControl(id-3)->xml));
		roleInst->Position(0, 420);
		mapPosX = 0;
		guiInst->ClearUp();
	}
}

void CallBackResult(int id, int state)
{
	if (state == BUTTON_DOWNUP)
	{
		switch (id)
		{
		case BUTTON_ID_1:
			townInst->CleanUp();
			townInst->Init("data//aierwen.xml");
			roleInst->Position(600, 420);
			mapPosX = 3200;
			break;
		default:
			break;
		}
	}
}

bool Town::Render()
{
	//切换地图时加载图片
	if (m_bIsLoad&&m_pTexLoad)
	{
		mBeginTime = GetTickCount();
		if (mEndTime == 0)
			mEndTime = mBeginTime;
		if (mBeginTime - mEndTime <= 1000)
		{
			SPRITE_DRAW(m_pTexLoad, 0, 0);
			return false;
		}
		else
		{
			m_bIsLoad = false;
			Safe_Release(m_pTexLoad);
		}
	}

	m_pMap->Render(0,0);
	m_pDoorMgr->Render();
	m_pAniMgr->Render();
	m_pNpcMgr->Render();
	//角色与npc的碰撞并设置角色的碰撞属性
	roleInst->SetCollision(m_pNpcMgr->CollisionDetec(roleInst->GetRoleRange()));
	m_pDoorMgr->CollisionDetec(roleInst->GetRoleRange());
	monsterInst->CollisionDetec(roleInst->GetRoleRange());
	monsterInst->Render();
	ProcessGUI(guiInst,gMousePosition.x, gMousePosition.y,CallBackGui);
	if(m_nMapType==MAP_TYPE_DUNGEON)
	if (monsterInst->MonsterCount() == 0 && lstrcmp(xmlData["roomtype"], L"boss") == 0)
		ProcessGUI(m_pGuiOption, gMousePosition.x, gMousePosition.y, CallBackResult);
	return true;
}

void Town::RenderLine()
{
	m_pNpcMgr->RenderLine();
}

bool Town::CleanUp()
{
	m_pMap->CleanUp();
	m_pNpcMgr->CleanUp();
	m_pDoorMgr->CleanUp();
	m_pAniMgr->CleanUp();
	return true;
}

bool Town::IsInited(int id)
{
	for (int i=0;i<m_nMapCount;i++)
	{
		if (id == initedMap[i])
			return true;
	}
	return false;
}
