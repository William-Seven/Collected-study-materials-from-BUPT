package com.example.clock;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager2.widget.ViewPager2;

import com.google.android.material.tabs.TabLayout;
import com.google.android.material.tabs.TabLayoutMediator;

public class MainActivity extends AppCompatActivity {

    private ViewPager2 viewPager;
    private ClockPagerAdapter pagerAdapter;
    private TabLayout tabLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        viewPager = findViewById(R.id.viewPager);
        tabLayout = findViewById(R.id.tabLayout);

        pagerAdapter = new ClockPagerAdapter(this);
        viewPager.setAdapter(pagerAdapter);

        // 页面指示器绑定
        new TabLayoutMediator(tabLayout, viewPager,
                (tab, position) -> {
                    tab.setCustomView(R.layout.item_dot_tab);
                }).attach();
    }
}
