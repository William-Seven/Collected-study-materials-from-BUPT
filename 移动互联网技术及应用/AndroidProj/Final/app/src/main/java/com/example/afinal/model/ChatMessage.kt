package com.example.afinal.model

// 表示一条聊天消息，区分是用户说的还是AI回复
data class ChatMessage(
    val sender: Sender,
    val content: String
)

enum class Sender {
    USER, BOT
}
