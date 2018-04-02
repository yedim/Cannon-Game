#pragma once

#define TEXTURE_POOL_SIZE 32
class CTexture
{
public:
	explicit CTexture(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual ~CTexture();

	int LoadTexture(const TCHAR* filename);
	void ReleaseTexture(int slotId);

	LPDIRECT3DTEXTURE9 GetTexture(int slotId) const
	{
		if (slotId < TEXTURE_POOL_SIZE)
			return m_Textures[slotId];
		return NULL;
	}
private:
	int GetEmptySlot() const;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPDIRECT3DTEXTURE9 m_Textures[TEXTURE_POOL_SIZE];

};

