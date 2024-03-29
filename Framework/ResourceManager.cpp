//=====================================
//
//リソースマネージャ処理[ResourceManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ResourceManager.h"
#include "MeshContainer.h"

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
メッシュ読み込み処理
***************************************/
void ResourceManager::LoadMesh(const char* tag, const char* path)
{
	string tagStr = string(tag);

	//タグの重複確認
	if (meshPool.count(tagStr) != 0)
		SAFE_DELETE(meshPool[tagStr]);

	//メッシュコンテナを生成してロード
	meshPool[tagStr] = new MeshContainer();
	meshPool[tagStr]->Load(path);
}

/**************************************
メッシュ解放処理
***************************************/
void ResourceManager::ReleaseMesh(const char* tag)
{
	string tagStr = string(tag);

	//タグの登録確認
	if (meshPool.count(tagStr) == 0)
		return;

	//メッシュコンテナを削除
	SAFE_DELETE(meshPool[tagStr]);
	meshPool.erase(tagStr);
}

/**************************************
メッシュ取得処理
***************************************/
bool ResourceManager::GetMesh(const char* tag, MeshContainer** pOut)
{
	string tagStr = string(tag);

	//登録確認
	if (meshPool.count(tagStr) == 0)
		return false;

	//メッシュへの参照を格納
	*pOut = meshPool[tagStr];
	return true;
}

/**************************************
テクスチャ読み込み処理
***************************************/
void ResourceManager::LoadTexture(const char *tag, const char* path)
{
	string tagStr = string(tag);

	//タグの重複確認
	if (texturePool.count(tagStr) != 0)
		SAFE_RELEASE(texturePool[tagStr]);

	//テクスチャロード
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, path, &texturePool[tagStr]);
}

/**************************************
テクスチャ解放処理
***************************************/
void ResourceManager::ReleaseTexture(const char* tag)
{
	string tagStr = string(tag);

	//タグの登録確認
	if (texturePool.count(tagStr) == 0)
		return;

	//メッシュコンテナを削除
	SAFE_RELEASE(texturePool[tagStr]);
	texturePool.erase(tagStr);
}

/**************************************
メッシュ参照処理
***************************************/
bool ResourceManager::GetTexture(const char* tag, LPDIRECT3DTEXTURE9 *pOut)
{
	string tagStr = string(tag);

	//登録確認
	if (texturePool.count(tagStr) == 0)
		return false;

	//メッシュへの参照を格納
	*pOut = texturePool[tagStr];
	return true;
}

/**************************************
全リソース解放処理
***************************************/
void ResourceManager::AllRelease()
{
	for (auto& pair : meshPool)
	{
		SAFE_DELETE(pair.second);
	}
	meshPool.clear();
}