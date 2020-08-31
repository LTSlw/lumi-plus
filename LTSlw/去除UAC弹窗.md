# 人工桌面开机自启不显示UAC弹窗最终解决方案

## Step 1 - 强行取消要求的管理员权限

首先需要强行取消要求的管理员权限​
在注册表编辑器(Win+R输入regedit​)里
HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers里加入字符串值​，字符串值的名称设置为N0vaDesktop.exe的路径(一般为C:\Program Files\N0vaDesktop\N0vaDesktop.exe取决于安装时的设置)
数据设置为RunAsInvoker

## Step 2 - 放通人工桌面所需文件夹的修改权限(已放通权限请忽略)

人工桌面要求管理员权限主要是为了下载和修改数据文件夹
在数据文件夹​属性-安全选项卡下添加运行人工桌面的用户的完全控制，这样人工桌面才可以下载新的桌面素材
