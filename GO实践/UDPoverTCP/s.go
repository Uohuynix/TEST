package main

import (
	"github.com/justlovediaodiao/udp-over-tcp"
	"net"
)

func main() {

	conn, _ := net.ListenPacket("udp", ":9090")

	client := uot.Client{
		Dialer: func(addr string) (uot.Conn, error) {
			conn, err := net.Dial("tcp", addr)
			if err != nil {
				return nil, err
			}
			return uot.DefaultOutConn(conn), nil
		},
	}

	client.Serve(uot.DefaultPacketConn(conn), "127.0.0.1:8088")
}
