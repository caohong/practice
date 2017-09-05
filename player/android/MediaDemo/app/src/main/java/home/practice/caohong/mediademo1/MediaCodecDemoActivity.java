package home.practice.caohong.mediademo1;

import android.Manifest;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.ImageFormat;
import android.graphics.Rect;
import android.media.Image;
import android.media.MediaCodec;
import android.media.MediaExtractor;
import android.media.MediaFormat;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;


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
            decoder.configure(format, null, null, 0);
            MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();
            decoder.start();


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
                        String fileName = "/sdcard/Movies/out.dat";
                        dumpFile(fileName, getDataFromImage(image));
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

        for (int i = 0; i < planes.length; i++) {
            rowStride = planes[i].getRowStride();
            pixelStride = planes[i].getPixelStride();
                Log.v(TAG, "plane[" + i + "]");
                Log.v(TAG, "pixelStride " + pixelStride);
                Log.v(TAG, "rowStride " + rowStride);
                Log.v(TAG, "width " + width);
                Log.v(TAG, "height " + height);

            int shift = (i == 0) ? 0 : 1;
            buffer = planes[i].getBuffer();
            int w = crop.width() >> shift;
            int h = crop.height() >> shift;
            buffer.position(rowStride * (crop.top >> shift) + pixelStride * (crop.left >> shift));
            byte[] rowData = new byte[planes[0].getRowStride()];

            for (int row = 0; row < h; row ++) {
                int row_length = (w - 1) * pixelStride + bitsPerPixel/8;
                buffer.get(rowData, 0, row_length);
                for (int col = 0; col < w; col++) {
                    data[offset++] = rowData[col * pixelStride];
                }
                if (row < h - 1) {
                    buffer.position(buffer.position() + rowStride - row_length);
                }
            }
        }
        return data;
    }
}

