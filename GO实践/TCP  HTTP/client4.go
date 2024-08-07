package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"strings"
)

func main() {
	// 连接服务器
	conn, err := net.Dial("tcp", "localhost:8080")
	if err != nil {
		fmt.Println("Error connecting:", err)
		return
	}
	defer conn.Close()

	// 创建读写器
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(conn)

	// 读取服务器发送的欢迎消息
	msg, err := bufio.NewReader(conn).ReadString('\n')
	if err != nil {
		fmt.Println("Error reading:", err)
		return
	}
	fmt.Print(msg)

	// 循环进行猜拳游戏
	for {
		fmt.Print("请输入你的选择（石头、剪刀、布）或输入exit退出游戏： ")
		choice, _ := reader.ReadString('\n')
		choice = strings.TrimSpace(choice)

		// 将用户的选择发送给服务器
		_, err := writer.WriteString(choice + "\n")
		if err != nil {
			fmt.Println("Error writing:", err)
			return
		}
		writer.Flush()

		// 读取服务器的响应
		resp, err := bufio.NewReader(conn).ReadString('\n')
		if err != nil {
			fmt.Println("Error reading:", err)
			return
		}
		fmt.Print(resp)

		// 如果用户选择退出，则关闭连接
		if choice == "exit" {
			fmt.Println("游戏结束，再见！")
			return
		}
	}
}
