#include "TestScene.h"
#include "Entity.h"
#include <AllMgrs.h>
#include "Tile.h"
#include "Tilemap.h"

using namespace std;
using namespace sf;

void TestScene::UpdateScene(double dt)
{
	m_entMgr.UpdateEnts(dt);
}

void TestScene::DrawScene()
{
	m_entMgr.DrawEnts();
	Renderer::getWindow().clear();
	Renderer::Draw();
	Renderer::getWindow().display();
}

void TestScene::LoadScene()
{
	m_entMgr = EntityMgr();

	static TextureMgr* txrM = TextureMgr::GetInstance();
	static FontMgr* fM = FontMgr::GetInstance();

	// Setup two animating tiles and some text.

	shared_ptr<Entity> ent = make_shared<Entity>();
	ent->SetPos(Vector2f(500.0f, 500.0f));
	ent->SetScale(10.0f);
	ent->SetRot(0.0f);
	auto sC = ent->AddComponent<Tile>();
	sC->SetAnimates(true, false);
	sC->SetSpriteTex(txrM->m_tileSheets[3], 32, 1);
	sC->SetOrigin(Vector2f(0.5f, 0.5f));
	sC->SetColor(Color(255, 255, 255, 255));

	shared_ptr<Entity> tm = make_shared<Entity>();
	tm->SetPos(Vector2f(0.0f, 0.0f));
	auto map = tm->AddComponent<TileMap>(12, 12, vector<char>{1});
	std::vector<std::shared_ptr<Entity>> allT = map->GetAllTileEntities();

	shared_ptr<Entity> msg = make_shared<Entity>();
	msg->SetPos(Vector2f(500.0f, 200.0f));
	msg->SetScale(1.0f);
	msg->SetRot(0.0f);
	auto msgC = msg->AddComponent<FontComponent>();
	msgC->SetText(String("Watch the tile go through the bitmasking"), fM->m_fonts[0], 40);
	msgC->SetOrigin(Vector2f(0.5f, 0.5f));

	shared_ptr<Entity> str1 = make_shared<Entity>();
	str1->SetPos(Vector2f(500.0f, 280.0f));
	str1->SetScale(1.0f);
	str1->SetRot(0.0f);
	auto strC1 = str1->AddComponent<FontComponent>();
	strC1->SetText(String("1"), fM->m_fonts[0], 40);
	strC1->SetOrigin(Vector2f(0.5f, 0.5f));

	shared_ptr<Entity> str2 = make_shared<Entity>();
	str2->SetPos(Vector2f(700.0f, 500.0f));
	str2->SetScale(1.0f);
	str2->SetRot(0.0f);
	auto strC2 = str2->AddComponent<FontComponent>();
	strC2->SetText(String("2"), fM->m_fonts[0], 40);
	strC2->SetOrigin(Vector2f(0.5f, 0.5f));

	shared_ptr<Entity> str3 = make_shared<Entity>();
	str3->SetPos(Vector2f(500.0f, 680.0f));
	str3->SetScale(1.0f);
	str3->SetRot(0.0f);
	auto strC3 = str3->AddComponent<FontComponent>();
	strC3->SetText(String("4"), fM->m_fonts[0], 40);
	strC3->SetOrigin(Vector2f(0.5f, 0.5f));

	shared_ptr<Entity> str4 = make_shared<Entity>();
	str4->SetPos(Vector2f(300.0f, 500.0f));
	str4->SetScale(1.0f);
	str4->SetRot(0.0f);
	auto strC4 = str4->AddComponent<FontComponent>();
	strC4->SetText(String("8"), fM->m_fonts[0], 40);
	strC4->SetOrigin(Vector2f(0.5f, 0.5f));

	shared_ptr<Entity> e = make_shared<Entity>();
	e->SetPos(Vector2f(1500.0f, 500.0f));
	e->SetScale(10.0f);
	e->SetRot(45.0f);
	auto sC2 = e->AddComponent<SpriteComponent>();
	sC2->SetAnimates(true, false);
	sC2->SetSpriteTex(txrM->m_tileSheets[4], 32, 4);
	sC2->SetOrigin(Vector2f(0.5f, 0.5f));
	sC2->SetColor(Color(255, 150, 255, 255));

	m_entMgr.m_entities.push_back(tm);

	for (int i = 0; i < allT.size(); i++)
	{
		m_entMgr.m_entities.push_back(allT[i]);
	}

	m_entMgr.m_entities.push_back(ent);
	

	m_entMgr.m_entities.push_back(msg);
	m_entMgr.m_entities.push_back(str1);
	m_entMgr.m_entities.push_back(str2);
	m_entMgr.m_entities.push_back(str3);
	m_entMgr.m_entities.push_back(str4);
	m_entMgr.m_entities.push_back(e);
}