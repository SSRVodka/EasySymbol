# Easy Symbol

## 简介

你有没有过这样的苦恼：当你想要在编写文档时，输入一些特殊符号（写科技文章时常常遇到的数学符号、希腊字母等）、emoji 表情，却常常由于输入法不给力，花很长时间寻找特定的符号或表情。这样的经历固然让人恼火，最麻烦的是，很多输入法的词组自定义功能还不是那么的好用，或者说各种插件十分臃肿。

于是，基于以上需求，Easy Symbol 应运而生。

这个项目的结构非常简单，您可以自定义一些符号（称为 `target`）和提示词（称为 `hint`）的对应关系。这样在程序中，您只需导入您自定义的字典，并进行搜索，就能快速找到您所需要的符号，双击即可复制到剪切板。

您只需将程序启动绑定到系统快捷键，即可简单快速地获取符号。

## 优势

- 系统占用小；

- 快捷键启动，符号查找迅速；

- 复制方便，加速您的符号编辑；

- 自行定制的词典映射。

## 快速开始

您可以在 Release 中下载您操作系统对应的二进制程序。之后可以设置快捷键启动，操作方法如下：

### Windows

为可执行程序（exe）右键创建快捷方式。右键该快捷方式，"shortcut" -> "shortcut key".

### Linux

以 Ubuntu 22 为例，打开 Settings -> Keyboard -> Keyboard Shortcuts -> View and Customize Shortcuts -> Custom Shortcuts.

## 源码编译

此外，您也可以自行编译源码。以下是开发环境：

- Qt 5.x (and C++ dev kits)

- GNU make, cmake

运行以下指令（以 Linux 为例）：

```bash
cmake -B build
cd build
make
```

可以使用 `-Ddebug=1` 启用调试 flag：

```bash
cmake -B build -Ddebug=1
```
