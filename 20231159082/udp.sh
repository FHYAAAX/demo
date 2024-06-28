#!/bin/bash

# 创建tmux会话并命名为 "UDP demo"
tmux new-session -d -s "UDP demo"

# 分割窗口布局
tmux split-window -h
tmux split-window -v
tmux select-layout tiled

# 在不同的窗格中运行UDP服务器和客户端
tmux send-keys -t 0 "./udpserver" Enter
tmux send-keys -t 1 "./udpclient" Enter

# 监视网络状态（可选）
tmux send-keys -t 2 "watch -n 1 'netstat -anu | grep :12000'" Enter

# 手动进入tmux会话以查看输出
tmux attach-session -t "UDP demo"

