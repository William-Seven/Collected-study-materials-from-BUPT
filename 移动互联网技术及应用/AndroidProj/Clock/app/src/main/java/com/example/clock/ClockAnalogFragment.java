package com.example.clock;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

public class ClockAnalogFragment extends Fragment {

    private boolean isNightMode = false;

    public ClockAnalogFragment() {}

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_clock_analog, container, false);

        AnalogClockView clockView = view.findViewById(R.id.customAnalogClock);
        Button nightModeToggle = view.findViewById(R.id.nightModeToggle);

        nightModeToggle.setOnClickListener(v -> {
            isNightMode = !isNightMode;
            clockView.setNightMode(isNightMode);
            nightModeToggle.setText(isNightMode ? "日间模式" : "夜间模式");
        });

        return view;
    }
}
