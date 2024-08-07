package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"net"
	"strings"
	"time"
)

func HandleConnection(conn net.Conn) {
	defer conn.Close()

	// 为每个客户端创建一个独立的读写器
	reader := bufio.NewReader(conn)
	writer := bufio.NewWriter(conn)

	// 向客户端发送欢迎消息
	writer.WriteString("欢迎来到猜拳游戏！\n")
	writer.Flush()

	// 循环处理客户端的输入
	for {
		// 读取客户端发送的消息
		msg, err := reader.ReadString('\n')
		if err != nil {
			fmt.Println("Error reading:", err)
			return
		}
		msg = strings.TrimSpace(msg)

		// 判断客户端的选择并返回结果
		switch msg {
		case "石头", "剪刀", "布":
			result := playGame(msg)
			writer.WriteString(result + "\n")
			writer.Flush()
		case "exit":
			fmt.Println("Client disconnected")
			return
		default:
			writer.WriteString("无效的选择，请重新输入石头、剪刀或布。\n")
			writer.Flush()
		}
	}
}

func playGame(choice string) string {
	// 随机生成服务器的选择
	rand.Seed(time.Now().UnixNano()) // 使用当前时间作为随机数种子
	choices := []string{"石头", "剪刀", "布"}
	serverChoice := choices[rand.Intn(len(choices))]

	// 判断游戏结果
	if choice == serverChoice {
		return "平局！"
	} else if (choice == "石头" && serverChoice == "剪刀") || (choice == "剪刀" && serverChoice == "布") || (choice == "布" && serverChoice == "石头") {
		return "你赢了！"
	} else {
		return "你输了！"
	}
}

func main() {
	// 监听端口
	listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		fmt.Println("Error listening:", err)
		return
	}
	defer listener.Close()
	fmt.Println("Server listening on port 8080...")

	// 循环接收客户端连接
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("Error accepting connection:", err)
			return
		}

		// 启动一个goroutine处理连接
		go HandleConnection(conn)
	}
}
