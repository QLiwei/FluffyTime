> [Bazel官网](https://bazel.build/?hl=zh-cn)

# 1.安装Bazel

## 2.[Build Tools for Visual Studio 2019](https://aka.ms/buildtools)

1. 访问Visual Studio下载页面：https://visualstudio.microsoft.com/downloads/ 

2. 下载Visual Studio Community版（免费）或者Professional版（付费）。 3

3. 运行安装程序，选择"使用Visual Studio Installer安装更多组件"。 

4.  在"工作负载"选项卡中，选择"C++桌面开发"。这将会安装包括VCVARSALL.BAT, cl.exe, link.exe, lib.exe, ml64.exe在内的C++构建工具。 

5. 点击"安装"按钮开始安装。 

   安装完成后，你应该能在"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build"

https://bazel.build/configure/windows?hl=zh-cn#using

配置系统环境变量

```
BAZEL_VC = C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC
BAZEL_VS = C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools
```

