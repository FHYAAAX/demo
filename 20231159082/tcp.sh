#!/bin/bash

# 创建tmux会话并命名为 "TCP demo"
tmux new-session -d -s "TCP demo"

# 分割窗口布局
tmux split-window -h
tmux split-window -v
tmux select-layout tiled

# 在不同的窗格中运行命令
tmux send-keys -t 0 "./tcpserver" Enter
tmux send-keys -t 1 "./tcpclient" Enter

# 监视网络状态
tmux send-keys -t 2 "watch -n 1 'netstat -antp | grep :12000'" Enter

# 启动tcpdump监视端口12000
tmux send-keys "sudo tcpdump -i lo -vvvnnXSK -s0 port 12000" Enter

# 手动进入tmux会话以查看输出
tmux attach-session -t "TCP demo"

