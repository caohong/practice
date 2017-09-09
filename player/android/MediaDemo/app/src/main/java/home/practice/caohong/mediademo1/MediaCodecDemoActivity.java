package home.practice.caohong.mediademo1;

import android.Manifest;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageFormat;
import android.graphics.Rect;
import android.graphics.YuvImage;
import android.media.Image;
import android.media.MediaCodec;
import android.media.MediaExtractor;
import android.media.MediaFormat;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

import static android.media.MediaExtractor.SEEK_TO_CLOSEST_SYNC;


public class MediaCodecDemoActivity extends Activity {

    private static final String TAG = "MediaCodecDemoActivity";
    private static final String [] RUNTIME_PERMISSIONS = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        for (String runtimePermission : RUNTIME_PERMISSIONS) {
            Log.d(TAG, "Checking permissions for: " + runtimePermission);
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                if (checkSelfPermission(runtimePermission) != PackageManager.PERMISSION_GRANTED) {
                    Log.d(TAG, "return for denied by user");
                    requestPermissions(new String[]{runtimePermission}, 1);
                }
            }
        }

        doWork();
    }

    private void doWork() {
        try {
            //
            // read a sample
            MediaExtractor extractor = new MediaExtractor();
            String videoFilePath = "/sdcard/Movies/480-WildLife.mp4";
            MediaFormat format = null;
            String mime = "";
            File file = new File(videoFilePath);
            extractor.setDataSource(file.toString());
            int i = 0;
            for (; i < extractor.getTrackCount(); i++) {
                format = extractor.getTrackFormat(i);
                mime = format.getString(MediaFormat.KEY_MIME);
                if (mime.startsWith("video/")) {
                    extractor.selectTrack(i);
                    break;
                }
            }

            //
            // instantiate a decoder
            MediaCodec decoder = MediaCodec.createDecoderByType(mime);
            Log.d(TAG, "supported color format:");
            for (int c : decoder.getCodecInfo().getCapabilitiesForType(mime).colorFormats) {
                Log.d(TAG, "\t" + c);
            }

            decoder.configure(format, null, null, 0);
            MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();
            decoder.start();

            //extractor.seekTo(21 * 1000 * 1000, MediaExtractor.SEEK_TO_NEXT_SYNC);

            //
            // try to get image
            for (; ; ) {
                int inputBufferId = decoder.dequeueInputBuffer(0);
                if (inputBufferId >= 0) {
                    ByteBuffer inputBuffer = decoder.getInputBuffer(inputBufferId);
                    int sampleSize = 0;
                    long sampleTime = 0;
                    if (inputBuffer != null) {
                        sampleSize = extractor.readSampleData(inputBuffer, 0);
                        sampleTime = extractor.getSampleTime();
                        Log.d(TAG, "inputbuffer(" + inputBufferId + "): " + sampleTime);
                    }
                    if (extractor.advance() && sampleSize > 0) {
                        decoder.queueInputBuffer(inputBufferId, 0, sampleSize, extractor.getSampleTime(), 0);
                    } else {
                        Log.d(TAG, "input buffer EOS");
                    }
                }

                int outputBufferId = decoder.dequeueOutputBuffer(bufferInfo, 0);
                if (outputBufferId >= 0) {
                    Log.d(TAG, "outputbuffer: " + outputBufferId);
                    Image image = decoder.getOutputImage(outputBufferId);
                    if (image != null) {
                        Log.d(TAG, "image format: " + image.getFormat());
                        Log.d(TAG, "timestamp: " + image.getTimestamp() / 1000);
                        int width = image.getCropRect().width();
                        int height = image.getCropRect().height();
                        showImage(getDataFromImage(image), width, height);
                        //String fileName = "/sdcard/Movies/out.yuv";
                        //dumpFile(fileName, getDataFromImage(image));
                        image.close();
                    }
                    break;
                }
            }

        } catch (Exception e) {
            e.printStackTrace();

        }
    }

    private void dumpFile(String fileName, byte[] data) {
        FileOutputStream outStream;
        try {
            outStream = new FileOutputStream(fileName);
            outStream.write(data);
            outStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void showImage(byte[] imageData, int width, int height) {
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        YuvImage yuvImage = new YuvImage(imageData, ImageFormat.NV21, width, height, null);
        yuvImage.compressToJpeg(new Rect(0, 0, width, height), 80, out);
        byte[] imageBytes = out.toByteArray();
        Bitmap bitmap = BitmapFactory.decodeByteArray(imageBytes, 0, imageBytes.length);

        /*
        Bitmap bitmap = Bitmap.createBitmap(decodeYUV420SP(imageData, width, height), width, height, Bitmap.Config.ARGB_8888);
         */
        ImageView iv = (ImageView) findViewById(R.id.imageView5);
        iv.setImageBitmap(bitmap);
    }

    private int[] decodeYUV420SP(byte[] yuv, int width, int height) {
        final int frameSize = width * height;
        int[] rgba = new int[frameSize];

        for (int j = 0, yp = 0; j < height; j++) {
            int uvp = frameSize + (j >> 1) * width, u = 0, v = 0;
            //int vp = frameSize + (j >> 1) * (width >> 1);
            //int up = frameSize + (frameSize >> 2) + (j >> 1) * (width >> 1);
            for (int i = 0; i < width; i++, yp++) {
                int y = (0xff & ((int) yuv[yp])) - 16;
                if (y < 0)
                    y = 0;

                if ((i & 1) == 0) {
                    v = (0xff & yuv[uvp++]) - 128;
                    u = (0xff & yuv[uvp++]) - 128;
                }

                int y1192 = 1192 * y;
                int r = (y1192 + 1634 * v);
                int g = (y1192 - 833 * v - 400 * u);
                int b = (y1192 + 2066 * u);

                if (r < 0)
                    r = 0;
                else if (r > 262143)
                    r = 262143;
                if (g < 0)
                    g = 0;
                else if (g > 262143)
                    g = 262143;
                if (b < 0)
                    b = 0;
                else if (b > 262143)
                    b = 262143;

                // rgb[yp] = 0xff000000 | ((r << 6) & 0xff0000) | ((g >> 2) &
                // 0xff00) | ((b >> 10) & 0xff);
                // rgba, divide 2^10 ( >> 10)
                rgba[yp] = ((r << 14) & 0xff000000) | ((g << 6) & 0xff0000)
                        | ((b >> 2) | 0xff00);
            }
        }
        return rgba;
    }

    /*
     * get NV21 data from Image
     */
    private byte[] getDataFromImage(Image image) {
        Image.Plane[] planes = image.getPlanes();
        int format = image.getFormat();
        Rect crop = image.getCropRect();
        int width = crop.width();
        int height = crop.height();
        int bitsPerPixel = ImageFormat.getBitsPerPixel(format);
        Log.d(TAG, "rect: " + crop);
        Log.d(TAG, "data: length = " + planes.length);
        Log.d(TAG, "bits/pixel = " + bitsPerPixel);

        byte[] data = new byte[width * height * ImageFormat.getBitsPerPixel(format) / 8];
        int offset = 0;

        int rowStride, pixelStride;
        ByteBuffer buffer = null;

        //Y
        rowStride = planes[0].getRowStride();
        pixelStride = planes[0].getPixelStride();
        buffer = planes[0].getBuffer();
        buffer.position(rowStride * crop.top + pixelStride * crop.left);
        for (int row = 0; row < height; row++) {
            int length = width * (bitsPerPixel / 8);
            buffer.get(data, offset, length);
            offset += length;
        }

        //UV
        ByteBuffer bufferU = planes[1].getBuffer();
        ByteBuffer bufferV = planes[2].getBuffer();
        int w = width / 2, h = height / 2;
        int length = (w - 1) * pixelStride + bitsPerPixel / 8;
        byte[] rowU = new byte[length];
        byte[] rowV = new byte[length];
        for (int row = 0; row < h; row++) {
            bufferU.get(rowU, 0, length);
            bufferV.get(rowV, 0, length);
            for (int col = 0; col < w; col++) {
                data[offset++] = rowV[col * pixelStride];
                data[offset++] = rowU[col * pixelStride];
            }
            if (row < h - 1) {
                bufferU.position(bufferU.position() + planes[1].getRowStride() - length);
                bufferV.position(bufferV.position() + planes[2].getRowStride() - length);
            }
        }

        return data;
    }
}

