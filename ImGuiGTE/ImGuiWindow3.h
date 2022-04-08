// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2022
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 6.0.2022.01.06

#pragma once

#include <Applications/Window3.h>
#include <Graphics/DX11/DX11Engine.h>
using namespace gte;

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

class ImGuiWindow3 : public Window3
{
public:
    ImGuiWindow3(Parameters& parameters);

    virtual bool OnWindowsMessage(HWND handle, UINT message,
        WPARAM wParam, LPARAM lParam, LRESULT& result) override;

    inline std::shared_ptr<gte::GraphicsEngine> const& GetEngine() const
    {
        return mEngine;
    }
};

template <typename WindowType>
void ImGuiMessagePump(std::shared_ptr<WindowType> const& window, uint32_t flags)
{
    if (window)
    {
        HWND handle = window->GetHandle();
        ShowWindow(handle, SW_SHOW);
        UpdateWindow(handle);

        // ImGui setup.
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplWin32_Init(handle);
        auto engine = dynamic_cast<DX11Engine*>(window->GetEngine().get());
        ImGui_ImplDX11_Init(engine->GetDevice(), engine->GetImmediate());

        for (;;)
        {
            if (flags & WindowSystem::NO_IDLE_LOOP)
            {
                WaitMessage();
            }

            MSG msg;
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    break;
                }

                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                if (!(flags & WindowSystem::NO_IDLE_LOOP))
                {
                    if (!window->IsMinimized())
                    {
                        window->OnIdle();
                    }
                }
            }
        }

        // ImGui cleanup.
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
}