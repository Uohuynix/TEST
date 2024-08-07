package main

import (
	"encoding/binary"
	"io"
	"log"
	"net"
	"time"
)

func main() {
	listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		log.Fatalf("Error starting TCP server: %v", err)
	}
	defer listener.Close()
	log.Println("TCP server is listening on port 8080")

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Printf("Error accepting connection: %v", err)
			continue
		}
		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
	defer conn.Close()
	udpAddr, err := net.ResolveUDPAddr("udp", "localhost:8081") // Target UDP server
	if err != nil {
		log.Printf("Error resolving UDP address: %v", err)
		return
	}
	udpConn, err := net.DialUDP("udp", nil, udpAddr)
	if err != nil {
		log.Printf("Error connecting to UDP server: %v", err)
		return
	}
	defer udpConn.Close()

	totalReceived := 0
	totalSent := 0
	var totalRTT time.Duration

	for {
		lengthBuf := make([]byte, 4)
		_, err := io.ReadFull(conn, lengthBuf)
		if err != nil {
			log.Printf("Error reading length: %v", err)
			break
		}
		length := binary.BigEndian.Uint32(lengthBuf)
		udpBuf := make([]byte, length)
		_, err = io.ReadFull(conn, udpBuf)
		if err != nil {
			log.Printf("Error reading UDP data: %v", err)
			break
		}

		totalReceived++
		start := time.Now()

		_, err = udpConn.Write(udpBuf)
		if err != nil {
			log.Printf("Error writing to UDP connection: %v", err)
			break
		}

		responseBuf := make([]byte, 1024)
		n, _, err := udpConn.ReadFromUDP(responseBuf)
		if err != nil {
			log.Printf("Error reading from UDP connection: %v", err)
			break
		}

		rtt := time.Since(start)
		totalRTT += rtt

		length = uint32(n)
		binary.BigEndian.PutUint32(lengthBuf, length)
		_, err = conn.Write(lengthBuf)
		if err != nil {
			log.Printf("Error writing length: %v", err)
			break
		}
		_, err = conn.Write(responseBuf[:n])
		if err != nil {
			log.Printf("Error writing response data: %v", err)
			break
		}

		totalSent++
	}

	if totalReceived > 0 {
		avgRTT := totalRTT / time.Duration(totalReceived)
		log.Printf("Total received: %d, total sent: %d", totalReceived, totalSent)
		log.Printf("Packet loss rate: %.2f%%", float64(totalReceived-totalSent)/float64(totalReceived)*100)
		log.Printf("Average RTT: %v", avgRTT)
	} else {
		log.Printf("No packets were successfully received.")
	}
}
