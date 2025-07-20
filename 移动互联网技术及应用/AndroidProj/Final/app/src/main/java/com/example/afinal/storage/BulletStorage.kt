package com.example.afinal.storage

import android.content.Context
import com.example.afinal.model.BulletMessage
import org.json.JSONArray
import org.json.JSONObject
import java.io.File

object BulletStorage {
    private const val FILE_NAME = "bullet_messages.json"

    // 保存留言列表到本地文件
    fun saveMessages(context: Context, messages: List<BulletMessage>) {
        val jsonArray = JSONArray()
        for (msg in messages) {
            val json = JSONObject().apply {
                put("content", msg.content)
                put("timestamp", msg.timestamp)
            }
            jsonArray.put(json)
        }

        val file = File(context.filesDir, FILE_NAME)
        file.writeText(jsonArray.toString())
    }

    // 从本地文件读取留言
    fun loadMessages(context: Context): List<BulletMessage> {
        val file = File(context.filesDir, FILE_NAME)
        if (!file.exists()) return emptyList()

        val content = file.readText()
        val jsonArray = JSONArray(content)
        val result = mutableListOf<BulletMessage>()

        for (i in 0 until jsonArray.length()) {
            val obj = jsonArray.getJSONObject(i)
            result.add(
                BulletMessage(
                    content = obj.getString("content"),
                    timestamp = obj.getLong("timestamp")
                )
            )
        }

        return result
    }
}
