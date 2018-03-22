#pragma once

#define BLOCK_MAX 10

#define BK_FAIL 0
#define BK_READY 1
#define BK_HIT 2
#define BK_HEAD 3
#define BK_BODY 4
#define BK_TAIL 5
#define BK_MAX 6

class CSprite;
class CBoard
{
private :
	float m_fBlockWidth;
	float m_fBlockHeight;
	float m_fBlockCX;
	float m_fBlockCY;
	int m_PlayerId;

	float m_fStartX;
	float m_fStartY;

	CSprite* m_Board[BLOCK_MAX][BLOCK_MAX];
	int m_BoardState[BLOCK_MAX][BLOCK_MAX];

	LPDIRECT3DTEXTURE9 m_Textures[BK_MAX];

public:
	explicit CBoard(LPDIRECT3DDEVICE9 pD3DDevice,
		float cx, float cy, int playerId);
	virtual ~CBoard();

	void SetTexture(int slotId, LPDIRECT3DTEXTURE9 texture);//slotId에 텍스쳐 넣기
	void ClearBoard();
	void SetPosition(float sx, float sy);

	void Draw();
	void HitTest(float mx, float my, int& rx, int& ry);

	void ChangeBlock(int x, int y);
	
};

