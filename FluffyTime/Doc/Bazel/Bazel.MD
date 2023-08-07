>
> # 1.[Scoop](https://scoop.sh/)
>
> Scoop 是一个适用于 Windows 操作系统的开源软件包管理器。它允许用户通过命令行轻松地安装和管理各种软件包，特别是开发工具和实用程序。Scoop 的目标是简化 Windows 上软件的安装和维护过程，使用户能够更轻松地获取所需的软件。
>
> 使用 Scoop，用户可以通过简单的命令行命令来安装、卸载、更新和列出已安装的软件包。Scoop 的包仓库包含了许多常见的开发工具、实用程序和其他应用程序，同时用户还可以将自己的软件包添加到仓库中.
>
> ```
> 安装软件包：scoop install <package>
> 卸载软件包：scoop uninstall <package>
> 更新软件包：scoop update <package>
> 列出已安装的软件包：scoop list
> ```
> Scoop 使用了一个类似 Linux 系统中的包管理器的概念，使得在 Windows 上安装和管理软件包更加方便和灵活。这对于开发人员和系统管理员来说是一个非常有用的工具。值得注意的是，截至我的知识截止日（2021年9月），Scoop 仍然是一个活跃的项目，可能在未来有更新和改进。如果你有兴趣使用 Scoop，请确保查阅其官方文档以获取最新信息和用法说明。
>
> **安装Scoop**
>
> PowerShell
>
> 1. 以管理员身份运行 PowerShell
> 2. 检查当前执行策略：在管理员权限的 PowerShell 窗口中输入以下命令并按回车键
>
>    ```
>    Get-ExecutionPolicy
>    ```
>    这将显示当前的执行策略。如果显示的是 "Restricted" 或其他限制级别，你将无法运行 Scoop。
>
>    更改执行策略：为了运行 Scoop，你可以将执行策略设置为 "RemoteSigned"。输入以下命令并按回车键：
>
>    ```
>    Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
>    ```
>    此命令将允许当前用户执行本地脚本，并且允许运行 Scoop。
>
>    1. 确认更改：输入 `Y` 然后按回车键，确认执行策略的更改。
> 3. 运行安装Scoop命令(非管理员模式运行 PowerShell)
>
>    ```
>    iex (new-object net.webclient).downloadstring('https://get.scoop.sh')
>    ```
>    请注意，更改执行策略可能会影响你系统的安全性，因为它允许执行本地脚本。如果你对系统安全性有顾虑，可以在安装完成后将执行策略改回原来的设置。输入以下命令将执行策略设置回 "Restricted"（默认值）：
>
>    ```
>    Set-ExecutionPolicy Restricted -Scope CurrentUser
>    ```
>
> # 2.Scoop bazel安装
>
> ```
> scoop install bazel
>
> bazel version
> WARNING: Invoking Bazel in batch mode since it is not invoked from within a workspace (below a directory having a WORKSPACE file).
> Build label: 6.3.1
> Build target: bazel-out/x64_windows-opt/bin/src/main/java/com/google/devtools/build/lib/bazel/BazelServer_deploy.jar
> Build time: Mon Jul 31 16:15:53 2023 (1690820153)
> Build timestamp: 1690820153
> Build timestamp as int: 1690820153
> ```
> # 3.在windows上构建
>
> ## 3.1 使用 MSVC 构建 C++
>
> 1. 安装[Build Tools for Visual Studio 2019](https://aka.ms/buildtools)
>
>    1. Bazel 6.3.1 支持以下 Visual Studio 版本：
>       * Visual Studio 2019
>       * Visual Studio 2017
>    2. 找到下载旧版本，登录账号下载即可
> 2. 配置环境变量
>
>    ```
>    BAZEL_VC=C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC
>
>    PATH:
>    C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64
>
>    ```
>    cmd
>
>    ```
>    C:\Users\vector>cl
>    用于 x64 的 Microsoft (R) C/C++ 优化编译器 19.29.30151 版
>    版权所有(C) Microsoft Corporation。保留所有权利。
>
>    用法: cl [ 选项... ] 文件名... [ /link 链接选项... ]
>    ```
> 3. 构建
>
>    ```
>    bazel build //xxx:xxx
>    ```
>
> ### 3.2 使用Clang构建C++
>
> 要使用 Clang 进行构建，您必须同时安装 [LLVM](http://releases.llvm.org/download.html) 和 Visual C++ 构建工具，因为尽管您使用 `clang-cl.exe` 作为编译器，但仍需要链接到 Visual C++ 库。
>
> 1. 下载[LLVM](https://releases.llvm.org/download.html)
>    在这我下载了最新的LLVM16.0.0
> 2. 添加环境变量
>
>    ```
>    PATH：C:\Program Files\LLVM\bin
>    BAZEL_LLVM = C:\Program Files\LLVM
>    ```
>    ```
>    C:\Users\vector>clang -v
>    clang version 16.0.0
>    Target: x86_64-pc-windows-msvc
>    Thread model: posix
>    InstalledDir: C:\Program Files\LLVM\bin
>    ```
>
