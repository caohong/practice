Practice for Video Player Development (Android)
===========

1. 使用MediaExtractor接口拿到mp4的第一帧码流
2. 使用MediaCodec接口将一帧码流解码
3. 将MediaCode获取的解码结果，[dump成yuv格式](#dump-yuv)
4. 使用MediaCodec接口将一帧码流解码并显示到窗口上, [将yuv显示到窗口](#显示yuv)


# dump yuv
参考[google CTS代码](http://androidxref.com/6.0.1_r10/xref/cts/tests/tests/media/src/android/media/cts/ImageReaderDecoderTest.java)
    通过getOutputImage接口，获取Image格式的对象。Image.getPlanes()包含了数据，如果格式为`YUV_420_888`, 会有3个Plane，如Plane[0]为Y，Plane[1]和Plane[2]分别为U、V。
    Plane里有两个重要概念: `RowStride`和`PixelStride`。`RowStride`代表了每行像素的字节数, 而`PixelStride`代表了相邻两个像素之间的字节数。如`YUV_420_888`里的U，第[i, j]的值为: data[i * RowStride + PixelStride * j]
    输出的yuv格式可以通过`ffplay`查看：
```
ffplay -s 854x480 -i out.yuv
```
    可以指定pixel format（通过命令行`ffplay -pix_fmt`查看支持的格式）：
```
ffplay -s 854x480 -pix_fmt nv21 -i out.yuv
```

# 显示yuv
参考[stackoverflow: displaying yuv image in android](https://stackoverflow.com/questions/9192982/displaying-yuv-image-in-android)
使用*YuvImage*类, 生成*Bitmap*, 在*ImageView*里显示
