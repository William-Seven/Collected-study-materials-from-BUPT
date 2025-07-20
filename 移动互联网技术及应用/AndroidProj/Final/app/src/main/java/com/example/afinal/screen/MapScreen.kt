package com.example.afinal.screen

import androidx.compose.foundation.Image
import androidx.compose.foundation.gestures.detectTransformGestures
import androidx.compose.foundation.layout.*
import androidx.compose.material3.Text
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.graphicsLayer
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.dp
import androidx.compose.ui.input.pointer.pointerInput
import com.example.afinal.R

@Composable
fun MapScreen(modifier: Modifier = Modifier) {
    var scale by remember { mutableStateOf(1f) }

    Column(
        modifier = modifier
            .fillMaxSize()
            .padding(16.dp)
    ) {
        Text(
            text = "🏫 校园地图",
            style = androidx.compose.material3.MaterialTheme.typography.titleLarge
        )
        Spacer(modifier = Modifier.height(8.dp))

        Box(
            modifier = Modifier
                .fillMaxSize()
                .pointerInput(Unit) {
                    detectTransformGestures { _, _, zoom, _ ->
                        // 只更新缩放比例
                        scale = (scale * zoom).coerceIn(0.5f, 4f)
                    }
                },
            contentAlignment = androidx.compose.ui.Alignment.Center
        ) {
            Image(
                painter = painterResource(id = R.drawable.campus_map),
                contentDescription = "校园地图",
                contentScale = ContentScale.Fit,
                modifier = Modifier
                    .graphicsLayer(
                        scaleX = scale,
                        scaleY = scale
                    )
            )
        }
    }
}
