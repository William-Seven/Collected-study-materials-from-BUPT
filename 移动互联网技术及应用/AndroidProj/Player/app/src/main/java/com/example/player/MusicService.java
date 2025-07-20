package com.example.player;

import android.app.Service;
import android.content.Intent;
import android.content.Context;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.IBinder;


public class MusicService extends Service {

    private MediaPlayer mediaPlayer;
    private final IBinder binder = new MusicBinder();
    private boolean isPaused = false;


    public class MusicBinder extends Binder {
        public MusicService getService() {
            return MusicService.this;
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return binder;
    }

    public void play(Context context) {
        if (mediaPlayer != null && isPaused) {
            // 如果是暂停状态，继续播放
            mediaPlayer.start();
            isPaused = false;
        } else {
            // 正常情况：重新创建播放器
            if (mediaPlayer != null) {
                mediaPlayer.release();
            }

            mediaPlayer = MediaPlayer.create(context, R.raw.shapeofyou);
            if (mediaPlayer != null) {
                mediaPlayer.start();
                isPaused = false;

                mediaPlayer.setOnCompletionListener(mp -> {
                    stop();  // 播放结束
                });
            }
        }
    }


    public void pause() {
        if (mediaPlayer != null && mediaPlayer.isPlaying()) {
            mediaPlayer.pause();
            isPaused = true;
        }
    }


    public void stop() {
        if (mediaPlayer != null) {
            mediaPlayer.stop();
            mediaPlayer.release();
            mediaPlayer = null;
            isPaused = false; // 清除暂停状态
        }
    }


    public int getDuration() {
        return mediaPlayer != null ? mediaPlayer.getDuration() : 0;
    }

    public int getCurrentPosition() {
        return mediaPlayer != null ? mediaPlayer.getCurrentPosition() : 0;
    }

    public void seekTo(int position) {
        if (mediaPlayer != null) {
            mediaPlayer.seekTo(position);
        }
    }

    @Override
    public void onDestroy() {
        if (mediaPlayer != null) {
            mediaPlayer.release();
            mediaPlayer = null;
        }
    }
}

