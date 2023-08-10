

## 注意点：

1.互斥锁
```
// 登录成功，记录用户连接信息
{
    lock_guard<mutex> lock(_connMutex);
    _userConnMap.insert({id, conn});
}
```
![Alt text](imgs/nginx.png)