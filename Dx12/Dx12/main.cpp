#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <functional>
#include <iostream>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace std;

const int Window_Width = 1280;
const int Window_Height = 720;

#define TEST_FUNTION 0

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

void SpawnDevice(ID3D12Device* _dev, D3D_FEATURE_LEVEL& featureLevel) {
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
        }
        else {
            if (lv == levels[levels.size() - 1]) {
                exit(EXIT_FAILURE);
            }
        }
    }
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
        }
        else {
            if (lv == levels[levels.size() - 1]) {
                exit(EXIT_FAILURE);
            }
        }
    }

    ID3D12CommandAllocator* _cmdAllocator = nullptr;
    ID3D12GraphicsCommandList* _cmdList = nullptr;
    ID3D12CommandQueue* _cmdQueue = nullptr;

    result = _dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_cmdAllocator));

    result = _dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAllocator, nullptr, IID_PPV_ARGS(&_cmdList));

    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
    cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE; // タイムアウトなし
    cmdQueueDesc.NodeMask = 0; // アダプターを一つしか使わない時は0
    cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL; // 特に指定なし
    cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT; // コマンドリストに合わせる

    result = _dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&_cmdQueue));

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


#if !TEST_FUNTION
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
#endif

#define TEST_FUNC 0
#define TEST_POINTER 1

#if TEST_FUNTION

void Add(int& a) {
    ++a;
}

template<typename T>
void Print(T s) {
    cout << s << endl;
}

int main() {
#if TEST_FUNC
    std::vector<std::function<void(void)>> commandList; // コマンドリストを模したもの

    commandList.push_back([]() {
        cout << "GPU Set RTV-1" << endl; // 命令1
                          });

    cout << "CPU Set Command-2" << endl;

    commandList.push_back([]() {
        cout << "GPU Clear RTV-3" << endl; // 命令2
                          });

    cout << "GPU Clear RTV-4" << endl;

    commandList.push_back([]() {
        cout << "GPU Close RTV-5" << endl; // 命令3
                          });

    cout << "GPU Close RTV-6" << endl;

    cout << endl;

    for (auto& cmd : commandList) {
        cmd();
    }

    getchar();

    return 0;
#endif

#if TEST_POINTER
    int a = 0;
    Print(a);
    Add(a);
    Print(a);
    return 0;
#endif
}
#endif