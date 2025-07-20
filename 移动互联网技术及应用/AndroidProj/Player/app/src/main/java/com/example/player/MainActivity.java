package com.example.player;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {

    private Button btnPlay, btnPause, btnStop, btnExit;
    private SeekBar seekBar;
    private TextView tvCurrentTime, tvTotalTime, tvSongName;

    private MusicService musicService;
    private boolean isBound = false;
    private boolean isPlaying = false;

    private Timer timer;

    private final ServiceConnection serviceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            MusicService.MusicBinder binder = (MusicService.MusicBinder) service;
            musicService = binder.getService();
            isBound = true;
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            isBound = false;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 初始化控件
        btnPlay = findViewById(R.id.btnPlay);
        btnPause = findViewById(R.id.btnPause);
        btnStop = findViewById(R.id.btnStop);
        btnExit = findViewById(R.id.btnExit);

        seekBar = findViewById(R.id.seekBar);
        tvCurrentTime = findViewById(R.id.tvCurrentTime);
        tvTotalTime = findViewById(R.id.tvTotalTime);
        tvSongName = findViewById(R.id.tvSongName);

        Intent intent = new Intent(this, MusicService.class);
        bindService(intent, serviceConnection, BIND_AUTO_CREATE);

        // 播放
        btnPlay.setOnClickListener(v -> {
            if (isBound) {
                musicService.play(MainActivity.this);
                isPlaying = true;
                tvSongName.setText("正在播放: shape of you");
                startTimer();
            }
        });

        // 暂停
        btnPause.setOnClickListener(v -> {
            if (isBound && isPlaying) {
                musicService.pause();
                isPlaying = false;
                stopTimer();
            }
        });

        // 停止
        btnStop.setOnClickListener(v -> {
            if (isBound) {
                musicService.stop();
                isPlaying = false;
                seekBar.setProgress(0);
                tvCurrentTime.setText("00:00");
                stopTimer();
            }
        });

        // 退出应用
        btnExit.setOnClickListener(v -> {
            if (isBound) {
                unbindService(serviceConnection);
                isBound = false;
            }
            finish();
        });

        // 拖动进度条
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            boolean userTouching = false;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser && isBound) {
                    tvCurrentTime.setText(formatTime(progress));
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                userTouching = true;
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                if (isBound && musicService != null) {
                    musicService.seekTo(seekBar.getProgress());
                }
                userTouching = false;
            }
        });
    }

    private void startTimer() {
        timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                if (musicService != null && isPlaying) {
                    int current = musicService.getCurrentPosition();
                    int total = musicService.getDuration();

                    runOnUiThread(() -> {
                        seekBar.setMax(total);
                        seekBar.setProgress(current);
                        tvCurrentTime.setText(formatTime(current));
                        tvTotalTime.setText(formatTime(total));
                    });
                }
            }
        }, 0, 500);
    }

    private void stopTimer() {
        if (timer != null) {
            timer.cancel();
            timer = null;
        }
    }

    private String formatTime(int millis) {
        int min = millis / 1000 / 60;
        int sec = (millis / 1000) % 60;
        return String.format("%02d:%02d", min, sec);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (isBound) {
            unbindService(serviceConnection);
            isBound = false;
        }
        stopTimer();
    }
}
