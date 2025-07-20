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
import java.util.TimeZone;

public class ClockWorldFragment extends Fragment {

    private TextView timeBeijing, timeSingapore, timeLondon;
    private final Handler handler = new Handler(Looper.getMainLooper());

    private final Runnable updateTimeRunnable = new Runnable() {
        @Override
        public void run() {
            updateWorldTimes();
            handler.postDelayed(this, 1000);
        }
    };

    private void updateWorldTimes() {
        timeBeijing.setText("Beijing: " + getTimeInTimeZone("Asia/Shanghai"));
        timeSingapore.setText("Singapore: " + getTimeInTimeZone("Asia/Singapore"));
        timeLondon.setText("London: " + getTimeInTimeZone("Europe/London"));
    }

    private String getTimeInTimeZone(String timeZoneId) {
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss", Locale.getDefault());
        sdf.setTimeZone(TimeZone.getTimeZone(timeZoneId));
        return sdf.format(new Date());
    }

    public ClockWorldFragment() {
        // Required empty public constructor
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_clock_world, container, false);
        timeBeijing = view.findViewById(R.id.timeBeijing);
        timeSingapore = view.findViewById(R.id.timeSingapore);
        timeLondon = view.findViewById(R.id.timeLondon);
        return view;
    }

    @Override
    public void onResume() {
        super.onResume();
        handler.post(updateTimeRunnable);
    }

    @Override
    public void onPause() {
        super.onPause();
        handler.removeCallbacks(updateTimeRunnable);
    }
}
