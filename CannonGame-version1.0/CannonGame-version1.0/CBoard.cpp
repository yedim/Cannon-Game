#include "stdafx.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "CSprite.h"
#include "CBoard.h"


CBoard::CBoard(LPDIRECT3DDEVICE9 pD3DDevice
	, float cx, float cy,int playerId)
	:m_fBlockWidth(cx*2-1)
	, m_fBlockHeight(cy*2-1)
	,m_fBlockCX(cx)
	,m_fBlockCY(cy)
	,m_playerId(playerId)
	,m_ShipBlockCount(0)
	,m_ComboCount(0)
	,m_HitScore(0)
{
	for (int y = 0; y < BLOCK_MAX; ++y)
	{
		for (int x = 0; x < BLOCK_MAX; ++x)
		{
			m_Board[y][x] = new CSprite(pD3DDevice, NULL, cx, cy);
			m_Board[y][x]->SetPosition(x*m_fBlockWidth, y*m_fBlockHeight);
			m_BoardState[y][x] = 0;
		}
	}
}


CBoard::~CBoard()
{
	for (int y = 0; y < BLOCK_MAX; ++y)
		for (int x = 0; x < BLOCK_MAX; ++x)
			delete m_Board[y][x];
}


void CBoard::SetPosition(float sx, float sy)
{
	for (int y = 0; y < BLOCK_MAX; ++y)
	{
		for (int x = 0; x < BLOCK_MAX; ++x)
		{
			m_Board[y][x]->SetPosition(sx + x * m_fBlockWidth, sy + y * m_fBlockHeight);
		}
	}
	m_fStartX = sx;
	m_fStartY = sy;
}
void CBoard::SetTexture(int slotId, LPDIRECT3DTEXTURE9 texture)
{
	m_Textures[slotId] = texture;
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
	m_ShipBlockCount = 0;
	m_ComboCount = 0;
	m_HitScore = 0;
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
void CBoard::HitTest(float mx, float my, int& rx, int& ry)
{
	float localX = mx - (m_fStartX - m_fBlockCX);
	float localY = my - (m_fStartY - m_fBlockCY);

	int sizeX = (int)m_fBlockCX * 2;
	int sizeY = (int)m_fBlockCY * 2;

	rx = ((int)localX) / sizeX;
	ry = ((int)localY) / sizeY;

	if (rx < 0 || rx >= BLOCK_MAX)
		rx = -1;

	if (ry < 0 || ry >= BLOCK_MAX)
		ry = -1;
}
void CBoard::ChangeBlockState(int x, int y)
{
	m_Board[y][x]->SetTexture(m_Textures[BK_HIT]);
}

int _GetTailCount(int shipId)
{
	switch (shipId)
	{
	case 1:
	case 2:
		return 1;
	case 3:
	case 4:
		return 2;
	case 5:
		return 3;
	}
	return -1;
}
void CBoard::PutSmallShip(int x, int y, int shipId)
{
	if (m_playerId == 0)
	{
		m_Board[y][x]->SetTexture(m_Textures[BK_PC]);
		m_Board[y][x+1]->SetTexture(m_Textures[BK_PC]);
	}
	m_BoardState[y][x] = shipId;
	m_BoardState[y][x+1] = shipId;
	m_ShipBlockCount += 2;
}
void CBoard::PutMediumShip(int x, int y, int shipId)
{
	if (m_playerId == 0)
	{
		m_Board[y][x]->SetTexture(m_Textures[BK_PC]);
		m_Board[y][x + 1]->SetTexture(m_Textures[BK_PC]);
		m_Board[y][x + 2]->SetTexture(m_Textures[BK_PC]);
	}
	m_BoardState[y][x] = shipId;
	m_BoardState[y][x + 1] = shipId;
	m_BoardState[y][x + 2] = shipId;
	m_ShipBlockCount += 3;
}
void CBoard::PutLargeShip(int x, int y, int shipId)
{
	if (m_playerId == 0)
	{
		m_Board[y][x]->SetTexture(m_Textures[BK_PC]);
		m_Board[y][x + 1]->SetTexture(m_Textures[BK_PC]);
		m_Board[y][x + 2]->SetTexture(m_Textures[BK_PC]);
		m_Board[y][x + 3]->SetTexture(m_Textures[BK_PC]);
	}
	m_BoardState[y][x] = shipId;
	m_BoardState[y][x + 1] = shipId;
	m_BoardState[y][x + 2] = shipId;
	m_BoardState[y][x + 3] = shipId;
	m_ShipBlockCount += 4;
}

bool CBoard::PutShip(int x, int y, int shipId)
{
	int nTailCnt = _GetTailCount(shipId);

	if (x >= 0 && (x + nTailCnt) < BLOCK_MAX 
		&&y >= 0 && y < BLOCK_MAX)
	{
		switch (shipId)
		{
		case 1:
		case 2:
			PutSmallShip(x, y, shipId);
			break;
		case 3:
		case 4:
			PutMediumShip(x, y, shipId);
			break;
		case 5:
			PutLargeShip(x, y, shipId);
			break;
		}
		return true;
	}
	return false;
}
bool CBoard::IsValidPos(int x, int y, int shipId)
{
	int nTailCnt = _GetTailCount(shipId);

	if (x >= 0 && (x + nTailCnt) < BLOCK_MAX 
		&& y >= 0 && y < BLOCK_MAX)
	{
		for (int i = x; i <= (x + nTailCnt); ++i) //!!! <=
		{
			if (m_BoardState[y][i] != 0)
				return false;
		}
		return true;
	}
	return false;
}

void CBoard::ClearShip(int x, int y, int shipId)
{
	int nTailCnt = _GetTailCount(shipId);

	if (x >= 0 && (x + nTailCnt) < BLOCK_MAX && y >= 0 && y < BLOCK_MAX)
	{
		for (int i = x; i <= (x + nTailCnt); ++i) //!!! <=
		{
			m_Board[y][i]->SetTexture(m_Textures[BK_READY]);
			m_BoardState[y][i] = 0;
		}
		m_ShipBlockCount -= (nTailCnt + 1);
	}
}

bool CBoard::FindShipHead(int x, int y, int& shipId, int& startX)
{
	shipId = -1;//-1을 넣고 시작.
	startX = -1;

	if (x >= 0 && x< BLOCK_MAX && y >= 0 && y < BLOCK_MAX)
	{
		if (m_BoardState[y][x] >= 1 && m_BoardState[y][x] <= 5)
		{
			shipId = m_BoardState[y][x];

			int n = x;
			while (n > 0 && m_BoardState[y][n - 1] == shipId)
				n--;
			startX = n;
			return true;
		}
	}
	return false;
}
bool CBoard::Attack(int x, int y)
{
	if (m_BoardState[y][x] >= 1 && m_BoardState[y][x] <= 5)
	{
		m_Board[y][x]->SetTexture(m_Textures[BK_HIT]);
		
		if (m_playerId == 1)
		{
			m_HitScore += 100;

			if (m_ComboCount > 0)
				m_HitScore += m_ComboCount * 50;
			m_ComboCount++;//!!! 연속공격성공!
		}
		else
		{
			m_HitScore += 5;
		}
		m_BoardState[y][x] += 100;
		m_ShipBlockCount--;
		return true;
	}
	else if (m_BoardState[y][x] == 0)
	{
		m_Board[y][x]->SetTexture(m_Textures[BK_FAIL]);
		m_BoardState[y][x] = -1;
		m_ComboCount = 0;
		return true;
	}
	return false;
}
bool CBoard::IsClicked(int x, int y)
{
	int state = m_BoardState[y][x];

	if (state==-1 || state>100)//fail이거나 hit이면
		return true;
	return false;
}
bool CBoard::GetBlockPosition(int x, int y, D3DXVECTOR3& vecPos)
{
	if (x >= 0 && x < BLOCK_MAX && y >= 0 && y < BLOCK_MAX)
	{
		vecPos = m_Board[y][x]->GetPosition();
		return true;
	}
	return false;
}
void CBoard::Cheat(bool bON)
{
	if (bON == true)
	{
		for (int y = 0; y < BLOCK_MAX; ++y)
			for (int x = 0; x < BLOCK_MAX; ++x)
				if (m_BoardState[y][x] > 0 && m_BoardState[y][x] < 100)
					m_Board[y][x]->SetTexture(m_Textures[BK_AI]);
	}
	else
	{
		for (int y = 0; y < BLOCK_MAX; ++y)
			for (int x = 0; x < BLOCK_MAX; ++x)
				if (m_BoardState[y][x] > 0 && m_BoardState[y][x] < 100)
					m_Board[y][x]->SetTexture(m_Textures[BK_READY]);
	}
}