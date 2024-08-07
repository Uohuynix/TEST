package main

import (
	"encoding/binary"
	"log"
	"net"
	"time"
)

func main() {
	tcpConn, err := net.Dial("tcp", "localhost:8080")
	if err != nil {
		log.Fatalf("Error connecting to TCP server: %v", err)
	}
	defer tcpConn.Close()

	udpAddr, err := net.ResolveUDPAddr("udp", ":0")
	if err != nil {
		log.Fatalf("Error resolving UDP address: %v", err)
	}
	localUDPAddr, err := net.ResolveUDPAddr("udp", "localhost:8081") // Local UDP server to test
	if err != nil {
		log.Fatalf("Error resolving local UDP address: %v", err)
	}
	udpConn, err := net.ListenUDP("udp", udpAddr)
	if err != nil {
		log.Fatalf("Error starting UDP connection: %v", err)
	}
	defer udpConn.Close()

	buf := make([]byte, 32*1024)
	start := time.Now()

	totalSent := 0
	totalReceived := 0
	var totalRTT time.Duration

	// Send 1000 MB in 32 KB chunks
	for i := 0; i < 1000*(1024/32); i++ {
		packetStart := time.Now()
		_, err := udpConn.WriteToUDP(buf, localUDPAddr)
		if err != nil {
			log.Fatalf("Error writing to UDP connection: %v", err)
		}
		totalSent++

		lengthBuf := make([]byte, 4)
		_, err = tcpConn.Read(lengthBuf)
		if err != nil {
			log.Fatalf("Error reading length: %v", err)
		}
		length := binary.BigEndian.Uint32(lengthBuf)
		udpBuf := make([]byte, length)
		_, err = tcpConn.Read(udpBuf)
		if err != nil {
			log.Fatalf("Error reading UDP data: %v", err)
		}

		rtt := time.Since(packetStart)
		totalRTT += rtt

		_, err = udpConn.Write(udpBuf)
		if err != nil {
			log.Fatalf("Error writing to UDP connection: %v", err)
		}
		totalReceived++
	}

	duration := time.Since(start)
	if totalSent > 0 {
		avgRTT := totalRTT / time.Duration(totalSent)
		log.Printf("Transmission time: %v", duration)
		log.Printf("Total sent: %d, total received: %d", totalSent, totalReceived)
		log.Printf("Packet loss rate: %.2f%%", float64(totalSent-totalReceived)/float64(totalSent)*100)
		log.Printf("Average RTT: %v", avgRTT)
	} else {
		log.Printf("No packets were successfully sent.")
	}
}
