# Using ImGui in a DirectX 11 Geometric Tools Engine window

This repository contains Microsoft Visual Studio 2022 code for a library wich provides a (somewhat) convenient interface for using [ImGui](https://github.com/ocornut/imgui) 1.87 in a DirectX11 window created by [Geometric Tools Engine](https://github.com/davideberly/GeometricTools) version 6.3.  It also includes an example usage, specifically the BlendedTerrainWindow3 demo from GTE:

![image](https://user-images.githubusercontent.com/12574428/162540085-b9099ae3-e5e9-4dd6-a0a4-5221587427c7.png)

Using the ImGuiGTE library in an existing GTE window mainly involves these changes:
1. Instead of calling <code>TheWindowSystem.MessagePump</code> to handle the Windows message loop, use <code>ImGuiMessagePump</code> with the same arguments (or make the equivalent changes if you have your own custom message loop).
2. Instead of deriving your GTE window class from <code>gte::Window3</code>, derive from <code>ImGuiWindow3</code>.
3. When rendering your GTE window (done in <code>BlendedTerrainWindow3::OnIdle</code> in this example), add your ImGui window by calling <code>StartImGuiFrame()</code> after clearing your render buffers, issuing the ImGui commands for your UI, then call <code>RenderImGui()</code> before calling <code>mEngine->DisplayColorBuffer()</code>.

There are a couple of issues that should be addressed before using any of this code in a real project:
1. Several files included in the ImGuiGTE library are copied directly from the ImGui examples and backend directories. There is probably a better way to structure this. 
2. The paths to the GTE library projects are hard-coded in the solution to D:\GeometricTools\GTE (where they were located on my machine).  You will need to manually add the GTE library projects to your own solution and update the references to them in your project.
