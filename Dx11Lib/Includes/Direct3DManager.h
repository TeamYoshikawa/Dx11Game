#ifndef _Direct3DManager_H
#define _Direct3DManager_H

// 必要なライブラリをリンク
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dx10.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

#define DX_RELEASE(x) {x->Release(); x = nullptr;}

#define ARRAY_RELEASE(x){delete[] x; x = nullptr;}

#define ERROR_MESSAGE(x){MessageBox(NULL,x, L"Error", MB_OK);}

typedef struct Color{
	Color(){
		_red = 0.0f;
		_green = 0.0f;
		_blue = 0.0f;
		_alpha = 0.0f;
	}

	Color(const float red, const float green,
		const float blue, const float alpha)
	{
		_red = red;
		_green = green;
		_blue = blue;
		_alpha = alpha;
	}

	~Color() = default;
	float _red;
	float _green;
	float _blue;
	float _alpha;
};

namespace Dx11{


	class Direct3DManager{

	public:
		Direct3DManager();
		Direct3DManager(const Direct3DManager&);
		~Direct3DManager();

		bool Initialize(POINT screen, bool vsync, HWND hWNd, bool isFullScreen, float screenDepth, float screenNear);

		void Shutdown();

		void BeginScene(Color);
		void EndScene();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();

		void GetProjectionMatrix(D3DXMATRIX&);
		void GetWorldMatrix(D3DXMATRIX&);
		void GetOrthoMatrix(D3DXMATRIX&);

		void GetVideoCardInfo(char*, int&);


	private:
		bool m_vsyncEnabled;
		int m_videoCardMemory;
		char m_videoCardDescription[128];

		IDXGISwapChain* m_swapChain;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;

		ID3D11RenderTargetView* m_renderTargetView;
		ID3D11Texture2D* m_depthStencilBuffer;

		ID3D11DepthStencilState* m_depthStencilState;
		ID3D11DepthStencilView* m_depthStencilView;

		ID3D11RasterizerState* m_rasterState;

		D3DXMATRIX m_projectionMatrix;
		D3DXMATRIX m_worldMatrix;
		D3DXMATRIX m_orthoMatrix;


	};
}
#endif