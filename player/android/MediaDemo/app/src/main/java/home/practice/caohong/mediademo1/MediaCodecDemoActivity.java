package home.practice.caohong.mediademo1;

import android.app.Activity;
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
            MediaExtractor extractor = new MediaExtractor();
            String videoFilePath = "/sdcard/Movies/480-WildLife.mp4";
            File file = new File(videoFilePath);
            extractor.setDataSource(file.toString());
            int i = 0;
            for (; i < extractor.getTrackCount(); i++) {
                MediaFormat format = extractor.getTrackFormat(i);
                String mime = format.getString(MediaFormat.KEY_MIME);
                if (mime.startsWith("video/")) {
                    extractor.selectTrack(i);
                    break;
                }
            }

            ByteBuffer byteBuf = ByteBuffer.allocate(1024 * 1024);
            extractor.readSampleData(byteBuf, 0);

            dumpByteBuffer(byteBuf);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void dumpByteBuffer(ByteBuffer byteBuf) {
        StringBuilder strBuilder = new StringBuilder();
        for (int i = 0; i < 16; i++) {
            strBuilder.append(" ").append(byteBuf.get());
        }
        Log.d(TAG, "buffer: " + strBuilder.toString());
    }
}

