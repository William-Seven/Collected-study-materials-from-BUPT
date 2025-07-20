package com.example.clock;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Handler;
import android.util.AttributeSet;
import android.view.View;

import java.util.Calendar;

public class AnalogClockView extends View {

    private int width, height;
    private Paint paint = new Paint();
    private Handler handler = new Handler();
    private boolean isNightMode = false;

    public AnalogClockView(Context context, AttributeSet attrs) {
        super(context, attrs);
        startClock();
    }

    public void setNightMode(boolean nightMode) {
        this.isNightMode = nightMode;
        invalidate(); // 重绘
    }

    private void startClock() {
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                invalidate();
                handler.postDelayed(this, 1000);
            }
        }, 1000);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        width = getWidth() / 2;
        height = getHeight() / 2;
        float radius = Math.min(width, height) - 20;

        // 设置颜色
        int bgColor = isNightMode ? Color.BLACK : Color.WHITE;
        int fgColor = isNightMode ? Color.WHITE : Color.BLACK;
        int secColor = isNightMode ? Color.YELLOW : Color.RED;

        // 设置背景
        canvas.drawColor(bgColor);

        paint.setAntiAlias(true);
        paint.setStyle(Paint.Style.STROKE);
        paint.setStrokeWidth(8);
        paint.setColor(fgColor);

        // 表盘圆
        canvas.drawCircle(width, height, radius, paint);

        // 刻度线
        drawTicks(canvas, radius, fgColor);

        // 画数字（1~12）
        paint.setStyle(Paint.Style.FILL);
        paint.setTextSize(40);
        paint.setTextAlign(Paint.Align.CENTER);
        for (int i = 1; i <= 12; i++) {
            double angle = Math.toRadians(i * 30 - 90);
            float x = (float) (width + (radius - 60) * Math.cos(angle));
            float y = (float) (height + (radius - 60) * Math.sin(angle)) + 15;
            canvas.drawText(String.valueOf(i), x, y, paint);
        }

        // 获取当前时间
        Calendar calendar = Calendar.getInstance();
        int hour = calendar.get(Calendar.HOUR);
        int minute = calendar.get(Calendar.MINUTE);
        int second = calendar.get(Calendar.SECOND);

        // 时针
        paint.setColor(fgColor);
        float hourAngle = (hour + minute / 60f) * 30;
        drawHand(canvas, hourAngle, radius * 0.4f, 12);

        // 分针
        float minuteAngle = (minute + second / 60f) * 6;
        drawHand(canvas, minuteAngle, radius * 0.6f, 8);

        // 秒针
        paint.setColor(secColor);
        float secondAngle = second * 6;
        drawHand(canvas, secondAngle, radius * 0.7f, 4);
    }

    private void drawTicks(Canvas canvas, float radius, int color) {
        paint.setColor(color);
        paint.setStrokeWidth(4);
        for (int i = 0; i < 60; i++) {
            double angle = Math.toRadians(i * 6);
            float start = (i % 5 == 0) ? radius - 30 : radius - 15; // 每5分钟刻度长
            float xStart = (float) (width + start * Math.cos(angle));
            float yStart = (float) (height + start * Math.sin(angle));
            float xEnd = (float) (width + radius * Math.cos(angle));
            float yEnd = (float) (height + radius * Math.sin(angle));
            canvas.drawLine(xStart, yStart, xEnd, yEnd, paint);
        }
    }

    private void drawHand(Canvas canvas, float angle, float length, float strokeWidth) {
        paint.setStrokeWidth(strokeWidth);
        float rad = (float) Math.toRadians(angle - 90);
        float x = (float) (width + length * Math.cos(rad));
        float y = (float) (height + length * Math.sin(rad));
        canvas.drawLine(width, height, x, y, paint);
    }
}
