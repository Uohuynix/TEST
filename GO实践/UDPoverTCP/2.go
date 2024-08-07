package main

import (
	"log"
	"net"

	uot "github.com/justlovediaodiao/udp-over-tcp"
)

func main() {
	// Listen for UDP packets on port 9090
	conn, _ := net.ListenPacket("udp", ":9090")

	// Create a client for UDP over TCP
	client := uot.Client{
		Dialer: func(addr string) (uot.Conn, error) {
			conn, err := net.Dial("tcp", addr)
			if err != nil {
				return nil, err
			}
			log.Printf("Connected to server: %s\n", addr)
			return uot.DefaultOutConn(conn), nil
		},
	}

	// Serve UDP over TCP on port 8088
	client.Serve(uot.DefaultPacketConn(conn), "127.0.0.1:8088")
}
