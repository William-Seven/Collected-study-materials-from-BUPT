package com.example.clock;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class ClockDigitalFragment extends Fragment {

    private TextView digitalClockText;
    private final Handler handler = new Handler(Looper.getMainLooper());
    private final SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm:ss", Locale.getDefault());

    private final Runnable updateTimeRunnable = new Runnable() {
        @Override
        public void run() {
            String currentTime = timeFormat.format(new Date());
            if (digitalClockText != null) {
                digitalClockText.setText(currentTime);
            }
            handler.postDelayed(this, 1000); // 每秒更新一次
        }
    };

    public ClockDigitalFragment() {
        // Required empty public constructor
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_clock_digital, container, false);
        digitalClockText = view.findViewById(R.id.digitalClockText);
        return view;
    }

    @Override
    public void onResume() {
        super.onResume();
        handler.post(updateTimeRunnable); // 开始更新时间
    }

    @Override
    public void onPause() {
        super.onPause();
        handler.removeCallbacks(updateTimeRunnable); // 停止更新时间
    }
}
