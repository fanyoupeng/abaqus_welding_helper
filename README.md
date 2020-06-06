# abaqus焊接助手简介
为了简化CAE操作，优雅的进行焊接模拟，于19年12月份中旬开始开发abaqus焊接助手，目前已完成V1.0版本，目前仅能实现生成焊接热分析脚本

# 焊接热分析
## 步骤
使用abaqus焊接助手一键生成python脚本

![avatar](https://gitee.com/ycsfyp/blog_picture/raw/06eb502ae5b7d300d3d735dd6708922e3e58d295/abaqus焊接模拟热分析及应力分析/1.JPG)

点击复制到剪贴板，将脚本粘贴到abaqus如下位置

![avatar](https://gitee.com/ycsfyp/blog_picture/raw/06eb502ae5b7d300d3d735dd6708922e3e58d295/abaqus焊接模拟热分析及应力分析/2.JPG)

焊接热分析工程就建立完毕了，点击submit运行，温度云图如下

![avatar](https://gitee.com/ycsfyp/blog_picture/raw/06eb502ae5b7d300d3d735dd6708922e3e58d295/abaqus焊接模拟热分析及应力分析/9.JPG)

## 主要参数
建模

![avatar](https://gitee.com/ycsfyp/blog_picture/raw/06eb502ae5b7d300d3d735dd6708922e3e58d295/abaqus焊接模拟热分析及应力分析/3.JPG)

材料属性

![avatar](https://gitee.com/ycsfyp/blog_picture/raw/06eb502ae5b7d300d3d735dd6708922e3e58d295/abaqus焊接模拟热分析及应力分析/4.JPG)
![avatar](https://gitee.com/ycs_fyp/blog_picture/raw/06eb502ae5b7d300d3d735dd6708922e3e58d295/abaqus焊接模拟热分析及应力分析/5.JPG)

分析步

![avatar](https://gitee.com/ycsfyp/blog_picture/raw/06eb502ae5b7d300d3d735dd6708922e3e58d295/abaqus焊接模拟热分析及应力分析/6.JPG)

交互

![avatar](https://gitee.com/ycsfyp/blog_picture/raw/06eb502ae5b7d300d3d735dd6708922e3e58d295/abaqus焊接模拟热分析及应力分析/7.JPG)

加载

![avatar](https://gitee.com/ycsfyp/blog_picture/raw/06eb502ae5b7d300d3d735dd6708922e3e58d295/abaqus焊接模拟热分析及应力分析/8.JPG)


热源主要参数
```
v:热源移动速度：8mm/s
q:热源功率：3000000mJ/s
```