-- 修改root用户密码以使用系统
ALTER USER 'root'@'localhost' IDENTIFIED BY 'new_root_password';

-- 创建新用户
CREATE USER 'llzj'@'localhost' IDENTIFIED BY 'Lxy20040513';

-- 设置用户密码永不过期
ALTER USER 'llzj'@'localhost' PASSWORD EXPIRE NEVER;

-- 确保用户使用 mysql_native_password 认证插件
ALTER USER 'llzj'@'localhost' IDENTIFIED WITH mysql_native_password BY 'Lxy20040513';

-- 刷新权限
FLUSH PRIVILEGES;

-- 删除原有重名数据库
DROP DATABASE IF EXISTS charge_db;

-- 创建需要的数据库
CREATE DATABASE charge_db CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- 授权给新用户
GRANT ALL PRIVILEGES ON charge_db.* TO 'llzj'@'localhost';

-- 刷新权限
FLUSH PRIVILEGES;