// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2022
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 6.0.2022.01.06
#include "ImGuiWindow3.h"
#include "imgui_internal.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ImGuiWindow3::ImGuiWindow3(Parameters& parameters)
    :
    Window3(parameters)
{
}

bool ImGuiWindow3::OnWindowsMessage(HWND handle, UINT message, WPARAM wParam, LPARAM lParam, LRESULT& result)
{
    result = ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam);

    auto context = ImGui::GetCurrentContext();
    if (context)
    {
        // If any ImGui window or control is active, we request the GTE window message routing be skipped for this message.
        if (context->ActiveId > 0
            || context->MovingWindow)
        {
            return true;
        }
    }

    return Window3::OnWindowsMessage(handle, message, wParam, lParam, result);
}
