## 准确定位二维码位置并识别二维码
- Author: Lu Huaizhi
- Date: 2019-04-09
- Version: 2.0.1
- abstract: 定位二维码并识别
----
### 版本信息
V2.0.1
```
实现对含有十字架的二维码的提取
```
### 依赖
- Opencv 3.4v
- Zbar[识别库]

### 文件结构v
```
├── CMakeLists.txt
├── README.md
├── inc
│   └── detect_qrcode.h
├── picture
│   ├── th1.jpg
|   ├── th2.jpg
|   ├── th3.jpg
│   └── th4.jpg
└── src
    ├── detect_qrcode.cpp
    └── main.cpp
```
### 思路
1. 从图片中截取比较集中的区域
2. 通过找凸包，形成大致形状
3. 角点检测找到五个点
4. 找交点，透视变换
5. 截取  拼接  识别

### 用法
```
mkdir build
cd build
cmake ..
make
./main
```