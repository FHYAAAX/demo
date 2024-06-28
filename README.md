# demo
# TCP和UDP服务器与客户端演示

本文档演示了如何使用Bash脚本和C语言编写的程序来创建和运行TCP和UDP服务器与客户端，以及如何使用tmux进行多窗格管理和网络监视。

## TCP 示例

### 环境设置

确保您的系统支持tmux和C编译环境。

### 服务器端

```bash
# 创建tmux会话并命名为 "TCP demo"
tmux new-session -d -s "TCP demo"

# 分割窗口布局
tmux split-window -h
tmux split-window -v
tmux select-layout tiled

# 在各个窗格中运行命令
tmux send-keys -t 0 "./tcpserver" Enter
tmux send-keys -t 1 "./tcpclient" Enter

# 监视网络状态
tmux send-keys -t 2 "watch -n 1 'netstat -antp | grep :12000'" Enter

# 新建一个窗格进行抓包并显示详细的抓包信息
tmux split-window -v
tmux send-keys -t 3 "sudo tcpdump -i lo -vvvnnXSK -s0 port 12000" Enter

# 手动进入tmux会话以查看输出
tmux attach-session -t "TCP demo"

