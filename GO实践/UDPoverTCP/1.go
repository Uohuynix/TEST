package main

import (
	"log"
	"net"

	uot "github.com/justlovediaodiao/udp-over-tcp"
)

func main() {
	l, err := net.Listen("tcp", ":8088")
	if err != nil {
		panic(err)
	}
	defer l.Close()

	var server uot.Server
	log.Println("Server started and listening on :8088")
	for {
		conn, err := l.Accept()
		if err != nil {
			panic(err)
		}
		log.Printf("Client connected: %s\n", conn.RemoteAddr())
		go server.Serve(uot.DefaultInConn(conn))
	}
}
