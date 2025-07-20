package com.example.clock;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;
import androidx.viewpager2.adapter.FragmentStateAdapter;

public class ClockPagerAdapter extends FragmentStateAdapter {

    public ClockPagerAdapter(@NonNull FragmentActivity fa) {
        super(fa);
    }

    @NonNull
    @Override
    public Fragment createFragment(int position) {
        switch (position) {
            case 0:
                return new ClockAnalogFragment();
            case 1:
                return new ClockDigitalFragment();
            case 2:
                return new ClockWorldFragment();
            default:
                return new ClockAnalogFragment();
        }
    }

    @Override
    public int getItemCount() {
        return 3; // 三个页面
    }
}
