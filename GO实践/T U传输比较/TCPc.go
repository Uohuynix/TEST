package main

import (
	"log"
	"net"
	"time"
)

func main() {
	conn, err := net.Dial("tcp", "localhost:8080")
	if err != nil {
		log.Fatalf("Error connecting to TCP server: %v", err)
	}
	defer conn.Close()

	buf := make([]byte, 32*1024) // 1 MB buffer
	start := time.Now()

	for i := 0; i < 10000*(1024/32); i++ { // Send 1000 MB
		_, err := conn.Write(buf)
		if err != nil {
			log.Fatalf("Error writing to TCP connection: %v", err)
		}
	}

	duration := time.Since(start)
	log.Printf("TCP transmission time: %v", duration)
}
