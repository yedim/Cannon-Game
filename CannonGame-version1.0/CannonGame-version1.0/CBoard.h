#pragma once

#define BLOCK_MAX 10
#define BK_FAIL 0
#define BK_READY 1
#define BK_HIT 2
#define BK_PC 3
#define BK_AI 4
#define BK_MAX 5
class CBoard
{
private:
	float m_fBlockWidth;
	float m_fBlockHeight;
	float m_fBlockCX;
	float m_fBlockCY;
	int m_playerId;
	int m_HitScore;
	int m_ComboCount;
	int m_ShipBlockCount;

	float m_fStartX;
	float m_fStartY;

	CSprite* m_Board[BLOCK_MAX][BLOCK_MAX];
	int m_BoardState[BLOCK_MAX][BLOCK_MAX];

	LPDIRECT3DTEXTURE9 m_Textures[BK_MAX];

	void PutSmallShip(int x, int y, int shipId);
	void PutMediumShip(int x, int y, int shipId);
	void PutLargeShip(int x, int y, int shipId);
public:
	explicit CBoard(LPDIRECT3DDEVICE9 pD3DDevice
		, float cx, float cy,int playerId);
	virtual ~CBoard();

	void SetPosition(float sx, float sy);
	void SetTexture(int slotId, LPDIRECT3DTEXTURE9 texture);
	void ClearBoard();
	
	void Draw();
	void HitTest(float mx, float my, int& rx, int& ry);
	void ChangeBlockState(int x, int y);

	bool PutShip(int x, int y, int shipId);
	bool IsValidPos(int x, int y, int shipId);//!!! bool형과 매개변수
	bool FindShipHead(int x, int y, int& shipId, int& startX);
	void ClearShip(int x, int y, int shipId);

	bool Attack(int x, int y);
	bool IsClicked(int x, int y);
	bool GetBlockPosition(int x, int y, D3DXVECTOR3 vecPos);//!!! bool형

	int GetHitScore() { return m_HitScore; }
	int GetBlockCount() { return m_ShipBlockCount; }

	void Cheat(bool bON);
	
};

