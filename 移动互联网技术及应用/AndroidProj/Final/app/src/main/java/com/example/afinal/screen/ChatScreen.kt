package com.example.afinal.screen

import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import com.example.afinal.model.ChatMessage
import com.example.afinal.model.Sender
import com.example.afinal.network.KimiApi

@Composable
fun ChatScreen(modifier: Modifier = Modifier) {
    var input by remember { mutableStateOf("") }
    var messages by remember { mutableStateOf(listOf<ChatMessage>()) }
    var isLoading by remember { mutableStateOf(false) }

    Column(modifier = modifier.fillMaxSize().padding(16.dp)) {
        // 聊天消息展示区
        LazyColumn(
            modifier = Modifier.weight(1f),
            verticalArrangement = Arrangement.spacedBy(8.dp)
        ) {
            items(messages) { msg ->
                MessageBubble(msg)
            }

            if (isLoading) {
                item {
                    Text("Kimi 正在输入...", style = MaterialTheme.typography.bodyMedium)
                }
            }
        }

        Spacer(modifier = Modifier.height(8.dp))

        // 输入框 + 发送按钮
        Row(modifier = Modifier.fillMaxWidth()) {
            TextField(
                value = input,
                onValueChange = { input = it },
                modifier = Modifier.weight(1f),
                placeholder = { Text("请输入问题...") }
            )
            Spacer(modifier = Modifier.width(8.dp))
            Button(
                onClick = {
                    if (input.isNotBlank()) {
                        val userMsg = ChatMessage(Sender.USER, input)
                        messages = messages + userMsg
                        isLoading = true

                        // 调用 Kimi 接口
                        KimiApi.sendMessage(input) { reply ->
                            isLoading = false
                            if (reply != null) {
                                val botMsg = ChatMessage(Sender.BOT, reply)
                                messages = messages + botMsg
                            } else {
                                val errorMsg = ChatMessage(Sender.BOT, "出错了，请稍后再试。")
                                messages = messages + errorMsg
                            }
                        }

                        input = ""
                    }
                }
            ) {
                Text("发送")
            }
        }
    }
}

@Composable
fun MessageBubble(message: ChatMessage) {
    val alignment = if (message.sender == Sender.USER) Arrangement.End else Arrangement.Start
    val bgColor = if (message.sender == Sender.USER) MaterialTheme.colorScheme.primary else MaterialTheme.colorScheme.surfaceVariant
    val textColor = if (message.sender == Sender.USER) MaterialTheme.colorScheme.onPrimary else MaterialTheme.colorScheme.onSurface

    Row(
        modifier = Modifier.fillMaxWidth(),
        horizontalArrangement = alignment
    ) {
        Surface(
            color = bgColor,
            shape = MaterialTheme.shapes.medium,
            modifier = Modifier.padding(4.dp)
        ) {
            Text(
                text = message.content,
                color = textColor,
                modifier = Modifier.padding(8.dp)
            )
        }
    }
}
