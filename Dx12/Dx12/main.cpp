#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

const int Window_Width = 1280;
const int Window_Height = 720;

void DebugOutputFormatString(const char* format, ...) {
#ifdef _DEBUG
    va_list valist;
    va_start(valist, format);
    printf(format, valist);
    va_end(valist);
#endif // _DEBUG

}

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

void InitializeDirect3D() {

    ID3D12Device* _dev = nullptr;
    D3D_FEATURE_LEVEL featureLevel;
    IDXGIFactory6* _dxgiFactory = nullptr;
    IDXGISwapChain4* _swapchain = nullptr;

    const std::vector<D3D_FEATURE_LEVEL> levels
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    std::vector<IDXGIAdapter*> adapters;
    IDXGIAdapter* tmpAdapter = nullptr;
    auto result = CreateDXGIFactory1(IID_PPV_ARGS(&_dxgiFactory));
    for (auto i = 0; _dxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        adapters.push_back(tmpAdapter);
    }

    for (auto adpt : adapters) {
        DXGI_ADAPTER_DESC adesc = { };
        adpt->GetDesc(&adesc);

        std::wstring strDesc = adesc.Description;

        //探したいアダプターの名前を確認
        if (strDesc.find(L"NVIDIA") != std::string::npos) {
            tmpAdapter = adpt;
            break;
        }
    }

    for (auto lv : levels) {
        if (D3D12CreateDevice(tmpAdapter, lv, IID_PPV_ARGS(&_dev)) == S_OK) {
            featureLevel = lv;
            break;
        } else {
            if (lv == levels[levels.size() - 1]) {
                exit(EXIT_FAILURE);
            }
        }
    }


    DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};

    swapchainDesc.Width = Window_Width;
    swapchainDesc.Height = Window_Height;
    swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapchainDesc.Stereo = false;
    swapchainDesc.SampleDesc.Count = 1;
    swapchainDesc.SampleDesc.Quality = 0;
    swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
    swapchainDesc.BufferCount = 2;

    //バッグバッファーは伸び縮み可能
    swapchainDesc.Scaling = DXGI_SCALING_STRETCH;

    //フリップ後は速やかに破棄
    swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    //特に指定なし
    swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

    //ウィンドウとフルスクリーン霧か会え可能
    swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


}

void SpawnDevice(ID3D12Device * _dev, D3D_FEATURE_LEVEL & featureLevel) {
    const std::vector<D3D_FEATURE_LEVEL> levels
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };


    for (auto lv : levels) {
        if (D3D12CreateDevice(nullptr, lv, IID_PPV_ARGS(&_dev)) == S_OK) {
            featureLevel = lv;
            break;
        } else {
            if (lv == levels[levels.size() - 1]) {
                exit(EXIT_FAILURE);
            }
        }
    }
}

#ifdef _DEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE, HISTANCE, LPSTR, int) {
#endif // _DEBUG
    WNDCLASSEX w = {};

    w.cbSize = sizeof(WNDCLASSEX);
    w.lpfnWndProc = (WNDPROC)WindowProcedure;
    w.lpszClassName = _T("DX12Sample");
    w.hInstance = GetModuleHandle(nullptr);

    InitializeDirect3D();

    RegisterClassEx(&w);

    RECT wrc = {0, 0, 1280, 720};

    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

    HWND hwnd = CreateWindow(w.lpszClassName, _T("DX12TEST"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, wrc.right - wrc.left, wrc.bottom - wrc.top, nullptr, nullptr, w.hInstance, nullptr);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {};

    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT) {
            break;
        }
    }

    UnregisterClass(w.lpszClassName, w.hInstance);
}
