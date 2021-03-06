#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <array>
#include <fstream>
#include <sstream>
#include "Utilities.h"
#include "SharedContext.h"
#include "BaseState.h"
#include "ScoreBoard.h"
#include "Character.h"

enum Sheet{ Tile_Size = 16, Sheet_Width = 160, Sheet_Height = 160 };

using TileID = unsigned int;

struct TileInfo{
	TileInfo(SharedContext* l_context, 
		const std::string& l_texture = "", TileID l_id = 0)
		: m_context(l_context), m_id(0), m_deadly(false)
	{
		TextureManager* tmgr = l_context->m_textureManager;
		if (l_texture == ""){ m_id = l_id; return; }
		if (!tmgr->RequireResource(l_texture)){ return; }
		m_texture = l_texture;
		m_id = l_id;
		m_sprite.setTexture(*tmgr->GetResource(m_texture));
		sf::IntRect tileBoundaries(m_id % (Sheet::Sheet_Width / Sheet::Tile_Size) * Sheet::Tile_Size,
			m_id / (Sheet::Sheet_Height / Sheet::Tile_Size) * Sheet::Tile_Size,
			Sheet::Tile_Size,Sheet::Tile_Size);
		m_sprite.setTextureRect(tileBoundaries);
	}

	~TileInfo(){
		if (m_texture == ""){ return; }
		m_context->m_textureManager->ReleaseResource(m_texture);
	}

	sf::Sprite m_sprite;

	TileID m_id;
	std::string m_name;
	sf::Vector2f m_friction;
	bool m_deadly;

	SharedContext* m_context;
	std::string m_texture;
};

struct Tile{
	TileInfo* m_properties;
	bool m_warp; // Is the tile a warp.
	// Other flags unique to each tile.
};

using TileMap = std::unordered_map<TileID,Tile*>;
using TileSet = std::unordered_map<TileID,TileInfo*>;

class Map{
public:
	Map(SharedContext* l_context, BaseState* l_currentState);
	~Map();

	Tile* GetTile(unsigned int l_x, unsigned int l_y);
	TileInfo* GetDefaultTile();

	float GetGravity()const;
	unsigned int GetTileSize()const;
	const sf::Vector2u& GetMapSize()const;
	const sf::Vector2f& GetPlayerStart()const;
	const int& GetScore()const;
	std::string Getname();
	void Setname(const std::string& l_name);
	void Scoreinit();
	void UpdateScore();
	void Waveinit();

	void setduringwave(bool l_duringwave);
	void setLevel(int l_level);
	void AddWave(int l_wave);
	void AddKilled(int l_killed);

	void AddEnemy();

	void LoadMap(const std::string& l_path);
	void LoadNext();

	void Update(float l_dT);
	void Draw();

private:
	// Method for converting 2D coordinates to 1D ints.
	unsigned int ConvertCoords(unsigned int l_x, unsigned int l_y);
	void LoadTiles(const std::string& l_path);
	void PurgeMap();
	void PurgeTileSet();

	TileSet m_tileSet;
	TileMap m_tileMap;
	sf::Sprite m_background;
	TileInfo m_defaultTile;
	sf::Vector2u m_maxMapSize;
	sf::Vector2f m_playerStart;
	unsigned int m_tileCount;
	unsigned int m_tileSetCount;
	float m_mapGravity;
	std::string m_nextMap;
	bool m_loadNextMap;
	std::string m_backgroundTexture;
	BaseState* m_currentState;
	SharedContext* m_context;
	ScoreBoard m_scoreMgr;
	Character* m_char;

	int m_score;
	int m_wave;
	int m_oldwave;
	bool duringwave;
	float m_elapsed;
	float m_timepassed;
	int m_opacity;
	bool m_beatwave;
	int m_hitpoints;
	int m_killed;
	int m_oldkilled;
	int m_level;
	int m_Addenemy;
	int m_maxEnemy;
	int m_exp;

	std::string playername;

	sf::Text score_text;
	sf::Text wave_text;
	sf::Font score_font;
	sf::Text m_escape;
};