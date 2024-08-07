package main

import (
	"log"
	"net"
	"time"
)

func main() {
	serverAddr, err := net.ResolveUDPAddr("udp", "localhost:8080")
	if err != nil {
		log.Fatalf("Error resolving UDP address: %v", err)
	}

	conn, err := net.DialUDP("udp", nil, serverAddr)
	if err != nil {
		log.Fatalf("Error connecting to UDP server: %v", err)
	}
	defer conn.Close()

	buf := make([]byte, 32*1024) // 32 KB
	start := time.Now()

	for i := 0; i < 10000*(1024/32); i++ { // 发送32KB大小的数据包，总共发送1000 MB数据
		_, err := conn.Write(buf)
		if err != nil {
			log.Fatalf("Error writing to UDP connection: %v", err)
		}
	}

	duration := time.Since(start)
	log.Printf("UDP transmission time: %v", duration)
}
