package com.example.afinal.network

import okhttp3.*
import okhttp3.MediaType.Companion.toMediaType
import okhttp3.RequestBody.Companion.toRequestBody
import org.json.JSONArray
import org.json.JSONObject
import java.io.IOException
import android.util.Log

object KimiApi {

    private const val API_KEY = "sk-ducWVUBtJWpwHpMw59gr8UrZG6A3D4pmu0m6ABtKoD2BMKwX"
    private const val ENDPOINT = "https://api.moonshot.cn/v1/chat/completions"

    private val client = OkHttpClient()

    // 异步发送消息，返回AI回复
    fun sendMessage(userMessage: String, callback: (String?) -> Unit) {
        val messageArray = JSONArray().apply {
            // 添加“系统提示词”，告诉模型你是校庆智能助手
            put(JSONObject().apply {
                put("role", "system")
                put("content", """
                    你是北京邮电大学70周年校庆活动的智能助手。以下是2025年校庆活动安排：
                    开幕式：12月22日 09:00，地点：学校操场。
                    校友见面会：12月22日 14:00，地点：教三长年报告厅。
                    文艺汇演：12月22日 19:00，地点：科学会堂。
                    校园开放日：12月23日 09:00，地点：校园各主要楼宇。
                    科技成果展：12月23日 10:30，地点：北邮体育馆一楼。
                    百年校史图片展：12月23日 13:00，地点：校史馆。
                    主题讲座：AI与未来教育：12月23日 15:00，地点：教三-339。
                    校庆运动会：12月24日 08:00，地点：北邮田径场。
                    师生合唱团专场演出：12月24日 19:30，地点：音乐喷泉广场。
                    校庆纪念品义卖：12月25日 10:00，地点：主楼前广场。
                    校友创业论坛：12月25日 14:00，地点：经济管理学院多功能厅。
                    闭幕式暨晚宴：12月25日 18:00，地点：校友中心。
                    书画摄影作品展：6月3日 10:00，地点：主干道两侧。
                    请根据以上信息回答用户的问题，并保持简洁、友好。
                """.trimIndent())
            })
            // 用户问题
            put(JSONObject().apply {
                put("role", "user")
                put("content", userMessage)
            })
        }

        val json = JSONObject().apply {
            put("model", "moonshot-v1-32k")
            put("messages", messageArray)
            put("temperature", 0.3)
        }

        val mediaType = "application/json".toMediaType()
        val body = json.toString().toRequestBody(mediaType)

        val request = Request.Builder()
            .url(ENDPOINT)
            .header("Authorization", "Bearer $API_KEY")
            .header("Content-Type", "application/json")
            .post(body)
            .build()

        client.newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e("KimiApi", "请求失败：${e.message}", e)  // 输出异常日志
                callback(null)
            }

            override fun onResponse(call: Call, response: Response) {
                val responseBody = response.body?.string()
                Log.d("KimiApi", "返回内容：$responseBody")  // 输出完整响应内容
                val reply = try {
                    val choices = JSONObject(responseBody).getJSONArray("choices")
                    choices.getJSONObject(0).getJSONObject("message").getString("content")
                } catch (e: Exception) {
                    Log.e("KimiApi", "解析失败：${e.message}", e)  // 输出解析失败原因
                    null
                }
                callback(reply)
            }
        })
    }
}
