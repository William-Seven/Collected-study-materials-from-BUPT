package com.example.afinal.screen

import androidx.compose.foundation.layout.*
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import com.example.afinal.model.BulletMessage
import com.example.afinal.storage.BulletStorage
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import androidx.compose.animation.core.*
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.IntOffset
import kotlin.random.Random


@Composable
fun BulletScreen(modifier: Modifier = Modifier) {
    val context = LocalContext.current
    val scope = rememberCoroutineScope()

    var input by remember { mutableStateOf("") }
    var messages by remember { mutableStateOf<List<BulletMessage>>(emptyList()) }
    val activeBullets = remember { mutableStateListOf<String>() }

    LaunchedEffect(true) {
        messages = BulletStorage.loadMessages(context)
    }




    // 加载历史留言
    LaunchedEffect(Unit) {
        while (true) {
            if (messages.isNotEmpty()) {
                val nextMessage = messages.random() // 从留言中随机取一条
                activeBullets.add(nextMessage.content)

                // 延迟一段时间再发下一条弹幕
                kotlinx.coroutines.delay(1500L)
            } else {
                // 如果还没留言就等久一点
                kotlinx.coroutines.delay(3000L)
            }
        }
    }

    Column(modifier = modifier
        .fillMaxSize()
        .padding(16.dp)) {

        // 弹幕展示（基础形式：竖向滚动）
        Text("🎉 校庆祝福墙 🎉", style = MaterialTheme.typography.titleLarge)
        Spacer(modifier = Modifier.height(8.dp))

        Box(
            modifier = Modifier
                .weight(1f)
                .fillMaxWidth()
        ) {
            activeBullets.forEach { msg ->
                AnimatedBullet(msg) {
                    activeBullets.remove(msg) // 播放完后自动移除
                }
            }
        }



        Spacer(modifier = Modifier.height(8.dp))

        // 输入框 + 按钮
        Row(modifier = Modifier.fillMaxWidth()) {
            TextField(
                value = input,
                onValueChange = { input = it },
                placeholder = { Text("写下你的祝福...") },
                modifier = Modifier.weight(1f)
            )
            Spacer(modifier = Modifier.width(8.dp))
            Button(onClick = {
                if (input.isNotBlank()) {
                    val newMessage = BulletMessage(input, System.currentTimeMillis())
                    val updatedList = messages + newMessage
                    messages = updatedList
                    input = ""
                    scope.launch(Dispatchers.IO) {
                        BulletStorage.saveMessages(context, updatedList)
                    }
                }
            }) {
                Text("发送")
            }
        }
    }
}

@Composable
fun AnimatedBullet(
    message: String,
    onAnimationEnd: () -> Unit
) {
    val screenWidth = 1000
    val yOffset = remember { Random.nextInt(0, 600) }
    val duration = remember { Random.nextInt(6000, 10000) }

    val offsetX = remember { Animatable(screenWidth.toFloat()) }

    LaunchedEffect(Unit) {
        offsetX.animateTo(
            targetValue = -screenWidth.toFloat(),
            animationSpec = tween(durationMillis = duration, easing = LinearEasing)
        )
        // 动画播放完后通知父组件删除该弹幕
        onAnimationEnd()
    }

    Box(
        modifier = Modifier
            .offset { IntOffset(offsetX.value.toInt(), yOffset) }
            .background(Color(0x33000000))
    ) {
        Text(
            text = message,
            color = Color.White,
            style = MaterialTheme.typography.bodyMedium,
            modifier = Modifier.padding(horizontal = 12.dp, vertical = 4.dp)
        )
    }
}


