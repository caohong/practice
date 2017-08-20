package home.practice.caohong.mediademo1;

import android.app.Activity;
import android.media.Image;
import android.media.MediaCodec;
import android.media.MediaExtractor;
import android.media.MediaFormat;
import android.os.Bundle;
import android.util.Log;

import java.io.File;
import java.nio.ByteBuffer;


public class MediaCodecDemoActivity extends Activity {

    private static final String TAG = "MediaCodecDemoActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

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
            for (;;) {
                int inputBufferId = decoder.dequeueInputBuffer(0);
                if (inputBufferId >= 0) {
                    ByteBuffer inputBuffer = decoder.getInputBuffer(inputBufferId);
                    int sampleSize = extractor.readSampleData(inputBuffer, 0);
                    if (extractor.advance() && sampleSize > 0) {
                        decoder.queueInputBuffer(inputBufferId, 0, sampleSize, extractor.getSampleTime(), 0);
                    } else {
                        Log.d(TAG, "input buffer EOS");
                    }
                }

                int outputBufferId = decoder.dequeueOutputBuffer(bufferInfo, 0);
                if (outputBufferId >= 0) {
                    Image image = decoder.getOutputImage(outputBufferId);
                    Log.d(TAG, "image format: " + image.getFormat());
                    image.close();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

