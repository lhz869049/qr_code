## 准确定位二维码位置并识别二维码
- Author: Lu Huaizhi
- Date: 2019-0409
- Version: 2.0.1
- abstract: 定位二维码并识别
----

### 依赖
- Opencv 3.4
- Zbar[识别库]

### 思路
1. 从图片中截取比较集中的区域
2. 通过找凸包，形成大致形状
3. 角点检测找到五个点
4. 找交点，透视变换

### 用法
```
mkdir build
cd build
cmake ..
make
./main
```