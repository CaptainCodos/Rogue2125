#include "cmp_tilemap.h"
#include "system_physics.h"
#include <fstream>
#include <string>
#include <iostream>
//#include "maths.h"

using namespace std;
using namespace sf;

TileMapComponent::TileMapComponent(Entity* p, TextureMgr* txrMgr, int currMap)
	: Component(p)
{
	m_txrMgr = txrMgr;

	m_width = 40 + ((currMap) * 3);
	m_height = 40 + ((currMap) * 3);

	stringstream str;
	str << "map" << currMap;
	m_ID = str.str();
	m_IntID = currMap;

	m_roomIDs = RandomInt(1, 5);
	m_corridorIDs = RandomInt(1, 5);

	m_roomColor = Color(RandomInt(210, 256), RandomInt(210, 256), RandomInt(210, 256), 255);
	m_corridorColor = Color(RandomInt(180, 256), RandomInt(180, 256), RandomInt(180, 256), 255);

	m_chanceOfLiquid = RandomFloat(0.2f, 0.5f);

	while (m_corridorIDs == m_roomIDs)
	{
		m_corridorIDs = RandomInt(1, 5);
	}
	

	m_tileEnts = vector<vector<shared_ptr<Entity>>>();
	m_tileCmps = vector<vector<shared_ptr<TileComponent>>>();
	m_visibleTiles = vector<vector<shared_ptr<TileComponent>>>();

	m_rooms = vector<IntRect>();

	m_corridorDirs = vector<int>();
	m_corridors = vector<vector<shared_ptr<TileComponent>>>();
	//LoadMap();
	bool b = true;

	if (!LoadMap())
	{
		for (int y = 0; y < m_height; y++)
		{
			m_tileEnts.push_back(vector<shared_ptr<Entity>>());
			m_tileCmps.push_back(vector<shared_ptr<TileComponent>>());
		}

		for (int y = 0; y < m_tileEnts.size(); y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				shared_ptr<Entity> ent = make_shared<Entity>(nullptr);
				ent->setPosition(Vector2f(16.0f + (32.0f * x), 16.0f + (32.0f * y)));

				shared_ptr<TileComponent> cmpT = ent->addComponent<TileComponent>(txrMgr, x, y);
				cmpT->SetTileID(m_roomIDs + 5);
				cmpT->SetColor(m_roomColor);
				cmpT->update(1.0f);

				m_tileEnts[y].push_back(ent);
				m_tileCmps[y].push_back(cmpT);
			}
		}

		GenerateMap();

		SaveMap();

		m_visibleTiles = GetTiles(IntRect(0, 0, m_width, m_height));
	}
}

void TileMapComponent::update(double dt)
{

}

void TileMapComponent::render()
{
	for (int y = 0; y < m_visibleTiles.size(); y++)
	{
		for (int x = 0; x < m_visibleTiles[y].size(); x++)
		{
			m_visibleTiles[y][x]->render();
		}
	}
}

string TileMapComponent::GetID() { return m_ID; }
int TileMapComponent::GetIntID() { return m_IntID; }

shared_ptr<TileComponent> TileMapComponent::GetTile(int x, int y)
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		return m_tileCmps[y][x];
	}
	else
	{
		return nullptr;
	}
}

shared_ptr<Entity> TileMapComponent::GetEnt(int x, int y)
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		return m_tileEnts[y][x];
	}
	else
	{
		return nullptr;
	}
}

vector<vector<shared_ptr<TileComponent>>> TileMapComponent::GetTiles(IntRect area)
{
	vector<vector<shared_ptr<TileComponent>>> tilegrid = vector<vector<shared_ptr<TileComponent>>>();

	for (int i = 0; i < area.height; i++)
	{
		tilegrid.push_back(vector<shared_ptr<TileComponent>>());
	}

	bool areaValid = (area.left >= 0 && area.left + area.width - 1 < m_width) && (area.top >= 0 && area.top + area.height - 1 < m_height);

	if (areaValid)
	{
		int sX = area.left;
		int sY = area.top;

		for (int y = 0; y < area.height; y++)
		{
			for (int x = 0; x < area.width; x++)
			{
				int cX = sX + x;
				int cY = sY + y;

				tilegrid[y].push_back(GetTile(cX, cY));
			}
		}

		return tilegrid;
	}
	else
	{
		return tilegrid;
	}
}
vector<vector<shared_ptr<TileComponent>>> TileMapComponent::GetNeighbourTiles(int x, int y)
{
	vector<vector<shared_ptr<TileComponent>>> tilegrid = vector<vector<shared_ptr<TileComponent>>>();

	for (int i = 0; i < 2; i++)
	{
		tilegrid.push_back(vector<shared_ptr<TileComponent>>());
	}

	if (y - 1 >= 0)
		tilegrid[0].push_back(GetTile(x, y - 1));
	else
		tilegrid[0].push_back(nullptr);

	if (y + 1 < m_height)
		tilegrid[0].push_back(GetTile(x, y + 1));
	else
		tilegrid[0].push_back(nullptr);

	if (x - 1 >= 0)
		tilegrid[1].push_back(GetTile(x - 1, y));
	else
		tilegrid[1].push_back(nullptr);

	if (x + 1 < m_width)
		tilegrid[1].push_back(GetTile(x + 1, y));
	else
		tilegrid[1].push_back(nullptr);

	return tilegrid;
}

vector<vector<shared_ptr<Entity>>> TileMapComponent::GetNeightbourEnts(int X, int Y)
{
	vector<vector<shared_ptr<Entity>>> tilegrid = vector<vector<shared_ptr<Entity>>>();

	for (int i = 0; i < 3; i++)
	{
		tilegrid.push_back(vector<shared_ptr<Entity>>());
	}

	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			int cX = X + x;
			int cY = Y + y;
			int vY = y + 1;

			tilegrid[vY].push_back(GetEnt(cX, cY));
		}
	}

	return tilegrid;
}

vector<vector<shared_ptr<TileComponent>>> TileMapComponent::GetAllNeighbourTiles(int X, int Y)
{
	vector<vector<shared_ptr<TileComponent>>> tilegrid = vector<vector<shared_ptr<TileComponent>>>();

	for (int i = 0; i < 3; i++)
	{
		tilegrid.push_back(vector<shared_ptr<TileComponent>>());
	}

	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			int cX = X + x;
			int cY = Y + y;
			int vY = y + 1;

			tilegrid[vY].push_back(GetTile(cX, cY));
		}
	}

	return tilegrid;
}

char TileMapComponent::ConvertFromInt(int n)
{
	assert(n >= 0 && n < 26);
	return "abcdefghijklmnopqrstuvwxyz"[n];
}
int TileMapComponent::ConvertFromChar(char c)
{
	assert(c >= 'a' && c <= 'z');
	return int(c) - 97;
}

bool TileMapComponent::LoadMap()
{
	//_tileSize = tileSize;
	//size_t w = 0, h = 0;
	//string buffer;

	//// Load in file to buffer
	//ifstream f("res/maze_2.txt");
	//if (f.good()) {
	//	f.seekg(0, std::ios::end);
	//	buffer.resize(f.tellg());
	//	f.seekg(0);
	//	f.read(&buffer[0], buffer.size());
	//	f.close();
	//}

	//for (int i = 0; i < buffer.size(); i++)
	//{
	//	cout << buffer[i];
	//}
	bool info = false;
	bool data = false;
	ifstream infoFile("res/" + m_ID + "Info.txt");
	if (infoFile.good())
	{
		Uint8 roomCs[3] = { 0, 0, 0 };
		Uint8 corrCs[3] = { 0, 0, 0 };
		char IDs[2] = { 'a', 'a' };

		for (int i = 0; i < 3; i++)
		{
			string l;
			getline(infoFile, l);

			roomCs[i] = l[0];
		}

		for (int i = 0; i < 3; i++)
		{
			string l;
			getline(infoFile, l);

			corrCs[i] = l[0];
		}

		for (int i = 0; i < 2; i++)
		{
			string l;
			getline(infoFile, l);

			IDs[i] = l[0];
		}

		m_roomColor = Color(roomCs[0], roomCs[1], roomCs[2], 255);
		m_corridorColor = Color(corrCs[0], corrCs[1], corrCs[2], 255);

		m_roomIDs = ConvertFromChar(IDs[0]);
		m_corridorIDs = ConvertFromChar(IDs[1]);

		info = true;
	}

	ifstream file("res/" + m_ID + ".txt");
	if (file.good())
	{
		
		for (int y = 0; y < m_height; y++)
		{
			m_tileEnts.push_back(vector<shared_ptr<Entity>>());
			m_tileCmps.push_back(vector<shared_ptr<TileComponent>>());
		}

		int y = 0;
		for (string line; getline(file, line); )
		{
			for (int x = 0; x < line.size(); x++)
			{
				shared_ptr<Entity> ent = make_shared<Entity>(nullptr);
				ent->setPosition(Vector2f(16.0f + (32.0f * x), 16.0f + (32.0f * y)));

				shared_ptr<TileComponent> cmpT = ent->addComponent<TileComponent>(m_txrMgr, x, y);
				cmpT->SetColor(m_roomColor);
				cmpT->SetTileID(ConvertFromChar(line[x]));

				if (cmpT->GetWalkable() && cmpT->GetID() == m_corridorIDs)
					cmpT->SetColor(m_corridorColor);

				/*if (cmpT->GetWalkable() && cmpT->GetID() == m_roomIDs)
					cmpT->SetColor(m_roomColor);*/

				cmpT->update(1.0f);

				m_tileEnts[y].push_back(ent);
				m_tileCmps[y].push_back(cmpT);
				
			}

			y++;
		}

		m_visibleTiles = GetTiles(IntRect(0, 0, m_width, m_height));
		IterateTiles();

		data = true;
	}

	return info && data;
}
void TileMapComponent::SaveMap()
{
	string dir = "res/" + m_ID + ".txt";
	string mapInfoDir = "res/" + m_ID + "Info.txt";

	ofstream out(dir);
	ofstream outInfo(mapInfoDir);
	//string str = "hahaha";

	if (outInfo.good())
	{
		string str;

		str += m_roomColor.r; outInfo << str << endl; str = "";
		str += m_roomColor.g; outInfo << str << endl; str = "";
		str += m_roomColor.b; outInfo << str << endl; str = "";

		str += m_corridorColor.r; outInfo << str << endl; str = "";
		str += m_corridorColor.g; outInfo << str << endl; str = "";
		str += m_corridorColor.b; outInfo << str << endl; str = "";

		str += ConvertFromInt(m_roomIDs); outInfo << str << endl; str = "";
		str += ConvertFromInt(m_corridorIDs); outInfo << str << endl; str = "";

		outInfo.close();
	}

	if (out.good())
	{
		for (int i = 0; i < m_tileCmps.size(); i++)
		{
			string str;

			for (int j = 0; j < m_tileCmps[i].size(); j++)
			{
				str += ConvertFromInt(m_tileCmps[i][j]->GetID());

				/*if (j >= m_tileCmps[i].size() - 1)
					str << '-';*/
			}

			out << str << endl;
		}

		out.close();
	}
	
	
}

void TileMapComponent::GenerateMap()
{
	int rRooms = sf::RandomInt(7 + (m_IntID / 2), 11 + (m_IntID / 2));
	IntRect prevRoom;
	IntRect currRoom;

	// Generate first room
	int rW = sf::RandomInt(3 + (m_IntID / 2), 8 + m_IntID);
	int rH = sf::RandomInt(3 + (m_IntID / 2), 8 + m_IntID);
	prevRoom = IntRect(sf::RandomInt(1, m_width - rW - 2), sf::RandomInt(1, m_height - rH - 2), rW, rH);

	m_rooms.push_back(prevRoom);

	for (int i = 0; i < rRooms; i++)
	{
		currRoom = GenerateRoom(prevRoom);
		m_rooms.push_back(currRoom);
		prevRoom = currRoom;
	}

	for (int i = 0; i < m_corridors.size(); i++)
	{
		AlterCorridorTiles(m_corridors[i], m_corridorIDs, m_corridorColor);
	}
	for (int i = 0; i < m_rooms.size(); i++)
	{
		AlterRoomTiles(m_rooms[i], m_roomIDs, m_roomColor, false);
	}
	int passes = 0;

	while (passes < 1)
	{
		IterateAcrossTileMap(passes);
		passes++;
	}
	
}

char TileMapComponent::CalculateTileIdx(vector<vector<shared_ptr<TileComponent>>> neighbours)
{
	char idx = 0;

	if (neighbours[0][0] != nullptr)
	{
		if (!neighbours[0][0]->GetWalkable() || neighbours[0][0]->GetDisguised())
		{
			idx += 1;
		}
	}
	else
	{
		idx += 1;
	}

	if (neighbours[0][1] != nullptr)
	{
		if (!neighbours[0][1]->GetWalkable() || neighbours[0][1]->GetDisguised())
		{
			idx += 4;
		}
	}
	else
	{
		idx += 4;
	}

	if (neighbours[1][0] != nullptr)
	{
		if (!neighbours[1][0]->GetWalkable() || neighbours[1][0]->GetDisguised())
		{
			idx += 8;
		}
	}
	else
	{
		idx += 8;
	}

	if (neighbours[1][1] != nullptr)
	{
		if (!neighbours[1][1]->GetWalkable() || neighbours[1][1]->GetDisguised())
		{
			idx += 2;
		}
	}
	else
	{
		idx += 2;
	}

	return idx;
}

char TileMapComponent::CalculateLiquidID(vector<vector<shared_ptr<TileComponent>>> neighbours, char currID)
{
	char idx = currID;

	for (int y = 0; y < neighbours.size(); y++)
	{
		for (int x = 0; x < neighbours[y].size(); x++)
		{
			if (neighbours[y][x] != nullptr)
			{
				char id = neighbours[y][x]->GetID();
				char lID = neighbours[y][x]->GetLiquidID();
				if (id > 14 && lID < idx)
					idx = lID;
			}
		}
	}

	return idx + 15;
}

bool TileMapComponent::CheckForRoughLiquid(vector<vector<shared_ptr<TileComponent>>> neighbours, char currID)
{
	char idx = currID;

	for (int y = 0; y < neighbours.size(); y++)
	{
		for (int x = 0; x < neighbours[y].size(); x++)
		{
			if (neighbours[y][x] != nullptr)
			{
				char id = neighbours[y][x]->GetID();
				char lID = neighbours[y][x]->GetLiquidID();
				if (id > 14 && lID > idx)
					return true;
			}
		}
	}

	return false;
}

void TileMapComponent::SmoothLiquids(int bX, int bY)
{
	vector<shared_ptr<TileComponent>> openList = vector<shared_ptr<TileComponent>>();
	vector<shared_ptr<TileComponent>> closedList = vector<shared_ptr<TileComponent>>();

	Vector2i cC = Vector2i(bX, bY);
	shared_ptr<TileComponent> start = GetTile(bX, bY);
	openList.push_back(start);
	//TileComponent current = *start;

	while (openList.size() > 0)
	{
		TileComponent current = *GetTile(openList[0]->GetCoords().x, openList[0]->GetCoords().y);

		vector<vector<shared_ptr<TileComponent>>> Ns = GetNeighbourTiles(current.GetCoords().x, current.GetCoords().y);

		for (int y = 0; y < Ns.size(); y++)
		{
			for (int x = 0; x < Ns[y].size(); x++)
			{
				if (Ns[y][x] != nullptr)
				{
					bool found = find(openList.begin(), openList.end(), Ns[y][x]) != openList.end() 
						&& find(closedList.begin(), closedList.end(), Ns[y][x]) != closedList.end();

					if (!found)
					{
						char id = Ns[y][x]->GetID();
						char Lid = Ns[y][x]->GetLiquidID();
						if (id > 14 && Lid > current.GetLiquidID() && current.GetID() > 14)
						{
							Ns[y][x]->SetTileID(current.GetID());
							openList.push_back(Ns[y][x]);
						}
					}
				}
			}
		}

		closedList.push_back(GetTile(current.GetCoords().x, current.GetCoords().y));
		openList.erase(remove_if(begin(openList), end(openList), [&](shared_ptr<TileComponent> x) {return find(begin(closedList), end(closedList), x) != end(closedList); }), end(openList));
	}
}

bool TileMapComponent::ToggleTile(vector<vector<shared_ptr<TileComponent>>> tiles)
{
	for (int y = 0; y < tiles.size(); y++)
	{
		for (int x = 0; x < tiles[y].size(); x++)
		{
			if (tiles[y][x] != nullptr && tiles[y][x]->GetWalkable())
				return true;
		}
	}

	return false;
}

IntRect TileMapComponent::GenerateRoom(IntRect prev)
{


	int rW = sf::RandomInt(3 + (m_IntID / 2), 8 + m_IntID);
	int rH = sf::RandomInt(3 + (m_IntID / 2), 8 + m_IntID);

	IntRect newRoom;
	newRoom = IntRect(sf::RandomInt(1, m_width - rW - 2), sf::RandomInt(1, m_height - rH - 2), rW, rH);

	if (newRoom.left <= 0)
		newRoom.left = 1;
	else if (newRoom.left + newRoom.width >= m_width)
		newRoom.left = m_width - newRoom.width - 1;

	if (newRoom.top <= 0)
		newRoom.top = 1;
	else if (newRoom.top + newRoom.height >= m_height)
		newRoom.top = m_height - newRoom.height - 1;

	m_corridors.push_back(GenerateCorridor(prev, newRoom));

	return newRoom;
}

std::vector<std::shared_ptr<TileComponent>> TileMapComponent::GenerateCorridor(IntRect r1, IntRect r2)
{
	std::vector<std::shared_ptr<TileComponent>> corridor = std::vector<std::shared_ptr<TileComponent>>();

	// Get room centres.
	Vector2i r1C = Vector2i(r1.left + (r1.width / 2), r1.top + (r1.height / 2));
	Vector2i r2C = Vector2i(r2.left + (r2.width / 2), r2.top + (r2.height / 2));

	int curr[2];
	int gDirs[2] = { 0, 0 };

	curr[0] = r1C.x;
	curr[1] = r1C.y;

	bool flag = false;

	// Generate corridor via multiple "halls"
	while (curr[0] != r2C.x || curr[1] != r2C.y)
	{
		int dS[2] = { 0, 0 };
		dS[0] = r2C.x - curr[0];
		dS[1] = r2C.y - curr[1];

		if (dS[0] != 0)
			gDirs[0] = dS[0] / abs(dS[0]);
		else
			gDirs[0] = 0;

		if (dS[1] != 0)
			gDirs[1] = dS[1] / abs(dS[1]);
		else
			gDirs[1] = 0;

		int dir = RandomInt(0, 2);

		// Ensures that if the chosen direction cannot over shoot the target room centre.
		while (abs(dS[dir]) <= 0)
		{
			dir = RandomInt(0, 2);
		}

		// Ensures that length of next "hall" cannot over shoot target.
		int length = RandomInt(min(1, abs(dS[dir])), min(12, abs(dS[dir])));

		int dest = curr[dir] + (length * gDirs[dir]);

		// Create "hall"
		while (curr[dir] != dest)
		{
			corridor.push_back(GetTile(curr[0], curr[1]));
			curr[dir] += gDirs[dir];
		}
	}

	return corridor;
}

void TileMapComponent::AlterRoomTiles(IntRect room, char ID, Color color, bool isLiquid)
{
	vector<vector<shared_ptr<TileComponent>>> tilegrid = GetTiles(room);

	float liquidVal = RandomFloat(0.0f, 1.0f);
	IntRect liquidCover;

	


	for (int y = 0; y < tilegrid.size(); y++)
	{
		for (int x = 0; x < tilegrid[y].size(); x++)
		{
			tilegrid[y][x]->SetColor(color);
			tilegrid[y][x]->SetTileID(ID);
		}
	}

	if (liquidVal <= m_chanceOfLiquid && !isLiquid)
	{
		int rW = RandomInt(2, min(room.width, 12));
		int rH = RandomInt(2, min(room.height, 12));

		liquidCover = IntRect(RandomInt(0, room.width - rW), RandomInt(0, room.height - rH), rW, rH);
		liquidCover.left += room.left;
		liquidCover.top += room.top;

		char id = RandomInt(15, 20);
		AlterRoomTiles(liquidCover, id, m_txrMgr->colors_LiquidTiles[id % 5], true);
	}
}

void TileMapComponent::AlterCorridorTiles(vector<shared_ptr<TileComponent>> corridor, char ID, Color color)
{
	int liquidIdx = RandomInt(0, 5);

	for (int i = 0; i < corridor.size(); i++)
	{
		float liquidVal = RandomFloat(0.0f, 1.0f);

		if (liquidVal < m_chanceOfLiquid)
		{
			corridor[i]->SetColor(m_txrMgr->colors_LiquidTiles[liquidIdx]);
			corridor[i]->SetTileID(liquidIdx + 15);
		}
		else
		{
			corridor[i]->SetColor(color);
			corridor[i]->SetTileID(ID);
		}
		
	}
}

void TileMapComponent::IterateAcrossTileMap(int pass)
{
	
	for (int y = 0; y < m_tileEnts.size(); y++)
	{
		for (int x = 0; x < m_tileEnts[y].size(); x++)
		{
			if (pass <= 0)
			{
				if (!m_tileCmps[y][x]->GetWalkable())
					m_tileCmps[y][x]->SetTileIdx(1 + CalculateTileIdx(GetNeighbourTiles(x, y)));

				bool vis = ToggleTile(GetAllNeighbourTiles(x, y));
				m_tileEnts[y][x]->setVisible(vis);
			}

			if (m_tileCmps[y][x]->GetID() > 14)
			{
				//m_tileCmps[y][x]->SetTileIdx(CalculateLiquidID(GetNeighbourTiles(x, y), m_tileCmps[y][x]->GetLiquidID()));
				if (CheckForRoughLiquid(GetNeighbourTiles(x, y), m_tileCmps[y][x]->GetLiquidID()))
				{
					SmoothLiquids(x, y);
				}
			}
		}
	}
}

void TileMapComponent::IterateTiles()
{

	for (int y = 0; y < m_tileEnts.size(); y++)
	{
		for (int x = 0; x < m_tileEnts[y].size(); x++)
		{
			if (!m_tileCmps[y][x]->GetWalkable())
				m_tileCmps[y][x]->SetTileIdx(1 + CalculateTileIdx(GetNeighbourTiles(x, y)));

			bool vis = ToggleTile(GetAllNeighbourTiles(x, y));
			m_tileEnts[y][x]->setVisible(vis);
		}
	}
}

bool TileMapComponent::ListContains(vector<shared_ptr<TileComponent>> list, shared_ptr<TileComponent> t)
{
	return find(list.begin(), list.end(), t) != list.end();
}