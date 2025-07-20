package com.example.afinal.screen

import android.content.Context
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Card
import androidx.compose.material3.Text
import androidx.compose.material3.CardDefaults
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import com.example.afinal.model.Event
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import org.json.JSONArray
import java.io.BufferedReader
import java.io.InputStreamReader

@Composable
fun HomeScreen(modifier: Modifier = Modifier) {
    val context = LocalContext.current
    var events by remember { mutableStateOf<List<Event>>(emptyList()) }

    // 加载 JSON 数据
    LaunchedEffect(true) {
        events = loadEventsFromJson(context)
    }

    // 展示活动列表
    LazyColumn(
        modifier = modifier
            .fillMaxSize()
            .padding(16.dp),
        verticalArrangement = Arrangement.spacedBy(12.dp)
    ) {
        items(events) { event ->
            EventCard(event)
        }
    }
}

@Composable
fun EventCard(event: Event) {
    Card(
        elevation = CardDefaults.cardElevation(4.dp),
        modifier = Modifier.fillMaxWidth()
    ) {
        Column(modifier = Modifier.padding(16.dp)) {
            Text(text = "【${event.title}】", style = androidx.compose.material3.MaterialTheme.typography.titleMedium)
            Text(text = "时间：${event.time}")
            Text(text = "地点：${event.location}")
            Spacer(modifier = Modifier.height(8.dp))
            Text(text = event.description)
        }
    }
}

// 读取 raw/events.json 文件并解析为 List<Event>
suspend fun loadEventsFromJson(context: Context): List<Event> = withContext(Dispatchers.IO) {
    val inputStream = context.resources.openRawResource(
        context.resources.getIdentifier("events", "raw", context.packageName)
    )
    val reader = BufferedReader(InputStreamReader(inputStream))
    val jsonString = reader.readText()
    reader.close()

    val jsonArray = JSONArray(jsonString)
    val result = mutableListOf<Event>()
    for (i in 0 until jsonArray.length()) {
        val obj = jsonArray.getJSONObject(i)
        result.add(
            Event(
                title = obj.getString("title"),
                time = obj.getString("time"),
                location = obj.getString("location"),
                description = obj.getString("description")
            )
        )
    }
    result
}
