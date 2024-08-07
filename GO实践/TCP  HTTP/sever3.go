package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"sync"
)

type Player struct {
	conn   net.Conn
	reader *bufio.Reader
	choice string
}

func main() {
	listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		fmt.Println("Error listening:", err.Error())
		os.Exit(1)
	}
	defer listener.Close()
	fmt.Println("服务器正在监听端�? 8080...")

	var players [2]*Player
	var wg sync.WaitGroup

	for i := 0; i < 2; i++ {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("Error accepting:", err.Error())
			os.Exit(1)
		}

		reader := bufio.NewReader(conn)
		players[i] = &Player{conn: conn, reader: reader}
		wg.Add(1)

		go func(player *Player) {
			defer wg.Done()
			for {
				choice, err := player.reader.ReadString('\n')
				if err != nil {
					fmt.Println("Error reading from player:", err.Error())
					return
				}
				choice = choice[:len(choice)-1] // 去除换行�?
				player.choice = choice

				// 检查是否两个玩家都已做出选择
				if players[0].choice != "" && players[1].choice != "" {
					result := PlayGame(players[0].choice, players[1].choice)
					sendResult(players[0].conn, players[1].conn, result)

					// 重置玩家选择以准备下一�?
					players[0].choice = ""
					players[1].choice = ""
				}
			}
		}(players[i])
	}

	wg.Wait() // 等待两个goroutine完成
	fmt.Println("游戏结束")
}

func PlayGame(choice1, choice2 string) string {
	choices := map[string]int{
		"石头": 0,
		"剪刀": 1,
		"�?":  2,
	}

	index1 := choices[choice1]
	index2 := choices[choice2]

	diff := (index1 - index2 + 3) % 3
	if diff == 0 {
		return "平局"
	} else if diff == 1 {
		return "玩家1获胜"
	} else {
		return "玩家2获胜"
	}
}

func sendResult(conn1, conn2 net.Conn, result string) {
	conn1.Write([]byte(fmt.Sprintf("结果�?%s\n", result)))
	conn2.Write([]byte(fmt.Sprintf("结果�?%s\n", result)))
}
