package com.example.afinal

import androidx.compose.material3.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.*
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.foundation.layout.padding
import androidx.compose.ui.graphics.vector.ImageVector
import com.example.afinal.screen.HomeScreen
import com.example.afinal.screen.ChatScreen
import com.example.afinal.screen.BulletScreen
import com.example.afinal.screen.MapScreen


@Composable
fun MainScreen() {
    // 当前选中的索引
    var selectedIndex by remember { mutableStateOf(0) }

    // 底部导航按钮内容
    val items = listOf(
        NavItem("首页", Icons.Default.Home),
        NavItem("助手", Icons.Default.Send),
        NavItem("留言", Icons.Default.Favorite),
        NavItem("地图", Icons.Default.Place)
    )

    Scaffold(
        bottomBar = {
            NavigationBar {
                items.forEachIndexed { index, item ->
                    NavigationBarItem(
                        icon = { Icon(item.icon, contentDescription = item.label) },
                        label = { Text(item.label) },
                        selected = selectedIndex == index,
                        onClick = { selectedIndex = index }
                    )
                }
            }
        }
    ) { innerPadding ->
        // 根据选中项切换页面
        when (selectedIndex) {
            0 -> HomeScreen(modifier = Modifier.padding(innerPadding))
            1 -> ChatScreen(modifier = Modifier.padding(innerPadding))
            2 -> BulletScreen(modifier = Modifier.padding(innerPadding))
            3 -> MapScreen(modifier = Modifier.padding(innerPadding))
        }
    }
}

// 底部导航栏项的数据结构
data class NavItem(val label: String, val icon: ImageVector)
