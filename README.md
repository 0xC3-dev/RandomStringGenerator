# Random String Generator
Generate Random Strings in Style with ease

## Setup
* No external dependencies needed
* ```C++ Language Standard: ISO C++20 Standard (/std:c++20)```
* ```C Language Standard: ISO C17 (2018) Standard (/std:c17)```
* ```Character Set: Use Multi-Byte Character Set```
* ```Optimizations have been enabled with the preset of favoring speed```

## UPDATE
* Update #1 : 11/07/23 | Updated Codebase. Combined UI_Layout.hpp into UI.cpp. Also added Includes.hpp so all headers are cleaned up. Also satisfied all warnings with the exception of the WinMain param warnings.
* Update #2 : 11/07/23 | Also fixed an issue with ImGui::LogToClipboard copying the Notify message to the clipboard as well. Replaced it with an ImGui::LogBegin() and ImGui::LogFinish().
* Update #3 : 11/07/23 | Changed Sub System type from Console to Windows so the Console App does not show regardless if your on Windows 10 or 11.
* Update #4 : 11/07/23 | Finally added version info to the application.
* Update #5 : 11/07/23 | Added tooltip for Slider Design button.
* Update #6 : 06/27/24 | Cleaned up codebase. Included D3D11 SDK in the project. Added updated program pictures.

## Credits
* Dear ImGui Framework - ocornut / https://github.com/ocornut/imgui
* DirectX 11 Framework - Microsoft / https://www.microsoft.com/en-us/download/details.aspx?id=6812

## Features
* Generate Random Strings with varying lengths
* Custom UI using ImGui Library Framework ( Added Custom Sliders )
* Lightweight Application
* Copy Generated Strings right to your Clipboard

## NOTE
* Bugs may be present. This will only run on Windows OS. If you wish to improve upon the codebase, feel free to make pull requests. Meaningful contributions are always welcome!
* Shortcuts: Press Home Key to Exit.

## Preview
![RSG1](https://i.imgur.com/fU9U9W9.png)
![RSG2](https://i.imgur.com/OQE5c5F.png)
![RSG3](https://i.imgur.com/6XxxogP.png)