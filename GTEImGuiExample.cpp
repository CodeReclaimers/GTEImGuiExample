#include <iostream>
#include "BlendedTerrainWindow3.h"
#include "ImGuiGTE/ImGuiWindow3.h"


int32_t main()
{
    try
    {
        Window::Parameters parameters(L"BlendedTerrainWindow3", 0, 0, 768, 768);
        auto window = TheWindowSystem.Create<BlendedTerrainWindow3>(parameters);
        ImGuiMessagePump(window, TheWindowSystem.DEFAULT_ACTION);
        TheWindowSystem.Destroy(window);
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
