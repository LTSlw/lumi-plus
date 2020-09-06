# model.dd详解

## 更新日志

v1.0.1.0-v1.0.23  
添加对于不同清晰度的支持

## model.dd的作用

model.dd是外部资源列表，外部的ndf的链接，bug反馈地址都记录在其中，人工桌面每次启动时会加载更新（如果有的话）这个文件，所以更改这个文件可以达到更改资源列表的效果

## 文件解析

整个文件分为`data`,`message`,`retcode`三个键，后两个不需要知道什么意思，不过可以简单推测一下，这个记录了和服务器通信的结果，服务器给人工桌面返回的结果是一个消息"OK"和一个返回值(`retcode`)0应该是成功的意思  
我们主要需要讨论的是`data`

`data`里面有三个键:`group_videos`,`sweet_conf`,`web_conf`。还是先挑简单的说，`web_conf`存储了一些网址信息，目前只有一个问题反馈地址，可以推测，把这个网址换掉就可以跳转到自己的问题反馈地址(对于以后的魔改可能有所帮助)

### group_videos

此处存储了对应鹿鸣练习室的部分（实际可以说是对应没有逻辑单个视频播放的部分的视频，实际上我们可以自定义多个鹿鸣练习室）

`group_videos`里面有两个键:`min_version`,`video_groups`  
`min_version`可能是最低支持的程序版本（仅推测，最近支持不同清晰度的更新支持了我的猜测，`sweet_conf`中`min_version`从19提高到了79）

然后是重点部分，修改此部分可以修改人工桌面的资源  
`video_groups`下的[]中可以包含多个{}，每一个{}对应人工桌面里的一个视频组，这里修改可以达到增删视频组的目的  
*`video_groups`应当认为是视频组组包含一个或多个视频组，比如鹿鸣练习室可以认为是一个视频组*

下面对一个视频组的配置进行解析  
一个视频组里包含4个键:`is_shown_default`,`key`,`lang_name`,`videos`

+ `is_shown_default`: 频道控制中是否显示的默认值
+ `key`: 推测为一个视频组的唯一标识，所以可能不可以重复（没有实验）
+ `lang_name`: 对应不同语言下的显示名称，看一下应该就知道怎么改，不解释。

之后的`videos`比较重要，同理视频组组包含多个视频组，这个按照类似的方式包含多个视频，这里修改可以达到增删视频组中的视频的目的

下面对一个视频的配置进行解析  
一个视频包含8个键:`cover`,`lang_name`,`sharpness_videos`,`sign`,`size`,`type`,`vid`,`video`  
*提示：人工桌面不验证链接来源，可以从自己服务器拉取数据*

+ `cover`: 封面ndf链接
+ `lang_name`: 对应不同语言下的显示名称
+ `sign`: 视频ndf的md5值
+ `size`: 视频ndf的字节数
+ `type`: 目前只知道有一个值叫`VideoTypeVoiced`有声视频的意思，没有找到其他的例子，可以尝试一下`VideoTypeSlience`或者其他什么猜猜看
+ `vid`:猜测是video id的意思，可能是视频唯一标识，不能重复（推测）可以以自己的命名系统命名
+ `video`: 视频默认ndf链接

单个视频的配置中有一个`sharpness_videos`键，是一组不同清晰度的视频  
`sharpness_videos`的一个视频中有7个键:`duration`,`file_name`,`sharpness`,`sign`,`size`,`upload_at`,`video`

+ `duration`: 视频长度，可为小数，单位：秒
+ `file_name`: 视频未修改前还为mp4时的名称，可能只是米忽悠调试时用的吧
+ `sharpness`: 视频的清晰度，已知"Sp2K"->2K,"Sp1920"->1080p
+ `sign`: 当前清晰度视频ndf的md5值
+ `size`: 当前清晰度视频ndf的字节数
+ `upload_at`: 上传时间，1970年1月1日到现在的秒数（unix时间戳去掉后三位）
+ `video`: 当前清晰度视频ndf链接

### sweet_conf

这里面存储了有逻辑的部分（各种坐吊篮）的资源。  
不过没搞懂为什么用sweet这个名字，sweet是甜蜜、小甜心的意思，米忽悠真把鹿鸣当闺女养?(doge)不过也可能是我不清楚sweet这个词有没有什么其他引申义

sweet_conf有5个键:`min_version`,`resources`,`triple_list`,`version`,`web_script`  
这个还没有研究特别透,简单看了一下，连蒙带猜

+ `min_version`:最低程序版本
+ `version`: sweet_conf版本?
+ `web_script`: player下载地址

`resources`是不同`style`ndf下载地址列表，可以将ndf对应到key，包含多个风格  
每个风格内有8个键: `cover`,`cover_sign`,`is_default`,`lang_name`,`sharpness_videos`,`size`,`style`,`videos`

+ `cover`: 封面ndf地址
+ `cover_sign`: 封面md5值（仅推测），现都为空
+ `is_default`: 是否为人工桌面默认风格，值:true/false，所有风格中只有一个为true
+ `lang_name`: 不同语言下的名称，同`group_videos`下的`lang_name`
+ `size`: `videos`键中所有ndf的总字节数
+ `style`: 风格名

`sharpness_videos`是相同风格下不同清晰度的视频列表  
一个清晰度内有3个键:`sharpness`,`size`,`videos`

+ `sharpness`: 清晰度，Sp2K->2K,Sp1920->1080p
+ `size`: videos中视频的总大小

`videos`是一个视频列表，单个视频中有6个键:`cover`,`duration`,`key`,`sign`,`size`,`video`

+ `cover`: 视频封面，似乎没有大用，会不会视频加载慢的时候先给个封面看看?
+ `duration`: 视频时长，似乎这里都设为0，0是目前这个参数没有意义还是指设置为0则将视频播完
+ `key`: 视频的唯一标识
+ `sign`: 视频ndf的md5值
+ `video`: 视频的地址

`resources`中的`videos`与此完全相同

`triple_list`应该是key和不同`style`的ndf对应表，待研究
