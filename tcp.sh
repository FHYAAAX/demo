#!/bin/bash

# 创建tmux会话并命名为 "TCP demo"
tmux new-session -d -s "TCP demo"

# 分割窗口布局
tmux split-window -h
tmux split-window -v
tmux select-layout tiled

# 在不同的窗格中运行命令
tmux send-keys -t 0 "python3 tcpServer.py" Enter
tmux send-keys -t 1 "python3 tcpClient.py" Enter
tmux send-keys -t 2 "watch -tn.1 'ss -ant \"( sport == 12000 or dport == 12000 )\"'" Enter
tmux send-keys -t 3 "sudo tcpdump -ilo -vvvnnxXSK -s0 port 12000" Enter

# 进入tmux会话
tmux attach-session -t "TCP demo"

