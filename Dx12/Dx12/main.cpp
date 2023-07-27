﻿#include <Windows.h>
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

/// <summary>
/// Create Dx12 device.
/// </summary>
/// <param name="tmpAdapter">Dx Adapter (Needed intialize before use.)</param>
/// <param name="featureLevel">Return level that suitable for created device.(Needed pointer for Out.)</param>
/// <returns>Created Dx12 device</returns>
ID3D12Device* CreateD12Device(IDXGIAdapter* tmpAdapter, D3D_FEATURE_LEVEL& featureLevel) {
    ID3D12Device* device = nullptr;

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
        if (D3D12CreateDevice(tmpAdapter, lv, IID_PPV_ARGS(&device)) == S_OK) {
            featureLevel = lv;
            break;
        }
        else {
            if (lv == levels[levels.size() - 1]) {
                exit(EXIT_FAILURE);
            }
        }
    }

    return device;
}

/// <summary>
/// Initialize Dx12 for Using.
/// </summary>
void InitializeDirect3D() {


}

void EnableDebugLayer() {
    ID3D12Debug* debugLayer = nullptr;
    auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
    debugLayer->EnableDebugLayer();
    debugLayer->Release();
}

#if !TEST_FUNTION
#ifdef _DEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE, HISTANCE, LPSTR, int) {
#endif // _DEBUG
    WNDCLASSEX w = {};

    ID3D12Device* _dev = nullptr;
    D3D_FEATURE_LEVEL featureLevel;
    IDXGIFactory6* _dxgiFactory = nullptr;
    IDXGISwapChain4* _swapchain = nullptr;
    std::vector<IDXGIAdapter*> adapters;
    IDXGIAdapter* tmpAdapter = nullptr;

    ID3D12CommandAllocator* _cmdAllocator = nullptr;
    ID3D12GraphicsCommandList* _cmdList = nullptr;
    ID3D12CommandQueue* _cmdQueue = nullptr;

    w.cbSize = sizeof(WNDCLASSEX);
    w.lpfnWndProc = (WNDPROC)WindowProcedure;
    w.lpszClassName = _T("DX12Sample");
    w.hInstance = GetModuleHandle(nullptr);

    RegisterClassEx(&w);


    RECT wrc = {0, 0, 1280, 720};

    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

    HWND hwnd = CreateWindow(w.lpszClassName, _T("DX12TEST"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, wrc.right - wrc.left, wrc.bottom - wrc.top, nullptr, nullptr, w.hInstance, nullptr);
#ifdef _DEBUG
    EnableDebugLayer();
#endif

#ifdef _DEBUG
    auto result = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&_dxgiFactory));
#else
    auto result = CreateDXGIFactory1(IID_PPV_ARGS(&_dxgiFactory));
#endif // _DEBUG

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
    _dev = CreateD12Device(tmpAdapter, featureLevel);

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
    swapchainDesc.Scaling = DXGI_SCALING_STRETCH; //バッグバッファーは伸び縮み可能
    swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//フリップ後は速やかに破棄
    swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;//特に指定なし
    swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;//ウィンドウとフルスクリーン霧か会え可能

    result = _dxgiFactory->CreateSwapChainForHwnd(_cmdQueue, hwnd, &swapchainDesc, nullptr, nullptr, (IDXGISwapChain1**)&_swapchain);

    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    heapDesc.NodeMask = 0;
    heapDesc.NumDescriptors = 2;
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    ID3D12DescriptorHeap* rtvHeaps = nullptr;
    result = _dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeaps));
    DXGI_SWAP_CHAIN_DESC swcDesc = {};
    result = _swapchain->GetDesc(&swcDesc);
    std::vector<ID3D12Resource*> _backBuffers(swcDesc.BufferCount);
    D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();
    for (int idx = 0; idx < swcDesc.BufferCount; ++idx) {
        result = _swapchain->GetBuffer(idx, IID_PPV_ARGS(&_backBuffers[idx]));
        handle.ptr += idx * _dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        _dev->CreateRenderTargetView(_backBuffers[idx], nullptr, handle);
    }

    ID3D12Fence* _fence = nullptr;
    UINT64 _fenceVal = 0;
    result = _dev->CreateFence(_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence));

    ShowWindow(GetConsoleWindow(), SW_HIDE);
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

        auto bbIdx = _swapchain->GetCurrentBackBufferIndex();

        D3D12_RESOURCE_BARRIER BarrierDesc = {};
        BarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        BarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        BarrierDesc.Transition.pResource = _backBuffers[bbIdx];
        BarrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
        BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        _cmdList->ResourceBarrier(1, &BarrierDesc);

        auto rtvH = rtvHeaps->GetCPUDescriptorHandleForHeapStart();
        rtvH.ptr += bbIdx * _dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        _cmdList->OMSetRenderTargets(1, &rtvH, true, nullptr);

        float clearColor[] = {1.0f,1.0f,0.0f,1.0f};
        _cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

        BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
        BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        _cmdList->ResourceBarrier(1, &BarrierDesc);

        _cmdList->Close();

        ID3D12CommandList* cmdlists[] = {_cmdList};
        _cmdQueue->ExecuteCommandLists(1, cmdlists);

        _cmdQueue->Signal(_fence, ++_fenceVal);

        if (_fence->GetCompletedValue() != _fenceVal) {
            auto event = CreateEvent(nullptr, false, false, nullptr);

            _fence->SetEventOnCompletion(_fenceVal, event);

            WaitForSingleObject(event, INFINITE);

            CloseHandle(event);
        }

        _cmdAllocator->Reset();
        _cmdList->Reset(_cmdAllocator, nullptr);

        _swapchain->Present(1, 0);

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