#include "stdafx.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "CSprite.h"

#include "CBoard.h"


CBoard::CBoard(LPDIRECT3DDEVICE9 pD3DDevice,
	float cx, float cy, int playerId)
	: m_fBlockWidth(cx*2-1)
	, m_fBlockHeight(cy*2-1)
	, m_fBlockCX(cx)
	, m_fBlockCY(cy)
	, m_PlayerId(playerId)
{
	for (int y = 0; y < BLOCK_MAX; ++y)
	{
		for (int x = 0; x < BLOCK_MAX; ++x)
		{
			m_Board[y][x] = new CSprite(pD3DDevice, NULL, cx, cy);
			m_Board[y][x]->SetPosition(m_fBlockWidth*x,m_fBlockHeight*y);
			m_BoardState[y][x] = 0;
		}
	}
}


CBoard::~CBoard()
{
	for (int y = 0; y < BLOCK_MAX; ++y)
	{
		for (int x = 0; x < BLOCK_MAX; ++x)
		{
			delete m_Board[y][x];
		}
	}

}

void CBoard::ClearBoard()
{
	for (int y = 0; y < BLOCK_MAX; ++y)
	{
		for (int x = 0; x < BLOCK_MAX; ++x)
		{
			m_Board[y][x]->SetTexture(m_Textures[BK_READY]);
			m_BoardState[y][x] = 0;
		}
	}

}
void CBoard::Draw()
{
	for (int y = 0; y < BLOCK_MAX; ++y)
	{
		for (int x = 0; x < BLOCK_MAX; ++x)
		{
			m_Board[y][x]->Draw();
		}
	}
}

void CBoard::SetTexture(int slotId, LPDIRECT3DTEXTURE9 texture)
{
	m_Textures[slotId] = texture;
}

void CBoard::SetPosition(float sx, float sy)
{
	for (int y = 0; y < BLOCK_MAX; ++y)
	{
		for (int x = 0; x < BLOCK_MAX; ++x)
		{
			m_Board[y][x]->SetPosition(sx + m_fBlockWidth * x, sy + m_fBlockHeight * y);
		}
	}
	m_fStartX = sx;
	m_fStartY = sy;
}
void CBoard::HitTest(float mx, float my, int& rx, int& ry)
{
	float localX = mx - (m_fStartX - m_fBlockCX);
	float localY = my - (m_fStartY - m_fBlockCY);
	int sizeX = (int)(m_fBlockCX * 2);
	int sizeY = (int)(m_fBlockCY * 2);

	rx = ((int)localX) / sizeX;
	ry = ((int)localY) / sizeY;

	if (rx<0 || rx>=BLOCK_MAX)
		rx = -1;
	if (ry<0 || ry>=BLOCK_MAX)
		ry = -1;	
}

void CBoard::ChangeBlock(int x, int y)
{
	m_Board[y][x]->SetTexture(m_Textures[BK_HIT]);
}