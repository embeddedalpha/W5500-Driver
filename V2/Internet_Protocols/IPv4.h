/*
 * IPv4.h
 *
 *  Created on: Oct 21, 2024
 *      Author: ksalvi
 */

#ifndef IPV4_H_
#define IPV4_H_

#include "main.h"

#define ETH_ALEN 6         // Ethernet Address Length
#define ETH_DATA_LEN 1500  // Ethernet Payload Length (maximum)
#define ETH_FRAME_LEN 1514 // Total Ethernet Frame Length (without FCS)

#define ETH_Header_Length 14
#define IPv4_Header_Length 20
#define UDP_Header_Length 8

#define UDP_Frame_Max_Len ETH_DATA_LEN - IPv4_Header_Length - UDP_Header_Length

#define IPv4_Frame_Max_Len ETH_DATA_LEN - IPv4_Header_Length

inline uint16_t swap_bytes(unsigned short value) {
  return (value >> 8) | (value << 8);
}

inline uint16_t swap_bytes_32(unsigned short value) {
  return (value >> 16) | (value << 16);
}

static const struct Ethernet_EtherTypes {
  uint16_t IPv4;                    // 	Internet Protocol version 4
  uint16_t ARP;                     // 	Address Resolution Protocol
  uint16_t Wake_on_LAN;             // 	Used to wake up devices on the network
  uint16_t IPv6;                    // 	Internet Protocol version 6
  uint16_t IPX;                     // 	Internetwork Packet Exchange
  uint16_t VLAN_tagged_frame;       // 	IEEE 802.1Q VLAN tagging
  uint16_t LLDP;                    // 	Link Layer Discovery Protocol
  uint16_t Precision_Time_Protocol; // 	IEEE 1588 Time Synchronization
  uint16_t MACsec;                  // 	IEEE 802.1AE MAC Security
  uint16_t Ethernet_flow_control;   // 	IEEE 802.3x Ethernet Flow Control
  uint16_t
      ATA_over_Ethernet;   // 	Protocol to transport ATA commands over Ethernet
  uint16_t MPLS_unicast;   // 	Multiprotocol Label Switching unicast
  uint16_t MPLS_multicast; // 	Multiprotocol Label Switching multicast
  uint16_t PPPoE_Discovery_Stage; // 	Point to Point Protocol over Ethernet
                                  // Discovery
  uint16_t
      PPPoE_Session_Stage;    // 	Point to Point Protocol over Ethernet Session
  uint16_t EtherCAT_Protocol; // 	Protocol for real time communication in
                              // automation
  uint16_t HomePlug_1_0_MME;  // 	Powerline networking protocol
  uint16_t HomePlug_AV_MME;   // 	Advanced powerline networking protocol
  uint16_t IEEE_802_11ai_Fast_Initial_Link_Setup; // 	Wireless LAN over
                                                  // Ethernet
  uint16_t Loopback;     // 	Used for testing and diagnostics
  uint16_t Ethernet_OAM; // 	Operation, Administration, and Maintenance
  uint16_t TTEthernet;   // 	Time Triggered Ethernet for real time
                         // applications
  uint16_t CobraNet;     // 	Audio and video over Ethernet
  uint16_t Local_Experimental_Ethertype_1;   // 	Used for experimental protocols
                                             // or testing
  uint16_t Fiber_Channel_over_Ethernet_FCoE; // 	Protocol for storage
                                             // area networks
  uint16_t HYPERSCSI;                        // 	SCSI over Ethernet
  uint16_t FCoE_Initialization_Protocol_FIP; // 	Protocol for
                                             // initializing FCoE connections
  uint16_t
      High_availability_Seamless_Redundancy_HSR; // 	Provides redundancy in
                                                 // Ethernet networks
  uint16_t Point_to_Point_Protocol_PPP;          // 	Used in point to point
                                                 // connections over Ethernet

} Ethernet_EtherTypes = {
    .IPv4 = 0x0800,
    .ARP = 0x0806,
    .Wake_on_LAN = 0x0842,
    .IPv6 = 0x86DD,
    .IPX = 0x8137,
    .VLAN_tagged_frame = 0x8100,
    .LLDP = 0x88CC,
    .Precision_Time_Protocol = 0x88F7,
    .MACsec = 0x88E5,
    .Ethernet_flow_control = 0x8808,
    .ATA_over_Ethernet = 0x88A2,
    .MPLS_unicast = 0x8847,
    .MPLS_multicast = 0x8848,
    .PPPoE_Discovery_Stage = 0x8863,
    .PPPoE_Session_Stage = 0x8864,
    .EtherCAT_Protocol = 0x88A4,
    .HomePlug_1_0_MME = 0x88B8,
    .HomePlug_AV_MME = 0x88E1,
    .IEEE_802_11ai_Fast_Initial_Link_Setup = 0x8902,
    .Loopback = 0x9000,
    .Ethernet_OAM = 0x8809,
    .TTEthernet = 0x88D8,
    .CobraNet = 0x8819,
    .Local_Experimental_Ethertype_1 = 0x88DC,
    .Fiber_Channel_over_Ethernet_FCoE = 0x88FD,
    .HYPERSCSI = 0x8906,
    .FCoE_Initialization_Protocol_FIP = 0x8914,
    .High_availability_Seamless_Redundancy_HSR = 0x892F,
    .Point_to_Point_Protocol_PPP = 0x880B,
};

// Ethernet Frame Structure
typedef struct Ethernet_Frame_Type {
  uint8_t dest_mac[ETH_ALEN];    // Destination MAC Address
  uint8_t src_mac[ETH_ALEN];     // Source MAC Address
  uint16_t EtherType;            // EtherType or Length (2 bytes)
  uint8_t payload[ETH_DATA_LEN]; // Payload (46 to 1500 bytes)
  // uint32_t fcs;                   // Frame Check Sequence (FCS) (optional in
  // structure)
} __attribute__((__packed__)) Ethernet_Frame_Type;

// Example usage

typedef struct IPv4_Frame_Type {

  uint8_t Version_IHL;
  uint8_t DSCP_ECN;
  uint16_t Total_Length;
  uint16_t Identification;
  uint16_t Flags_Fragment_Offset;
  uint8_t Time_to_Live;
  uint8_t Protocol;
  uint16_t Header_Checksum;
  uint8_t Source_Address[4];
uint8_t Destination_Address[4];
  uint8_t data[IPv4_Frame_Max_Len];
  // uint8_t Acknowledgement_Number[4];
  // uint8_t Option_Flags[2];
  // uint8_t Window_Size[2];
  // uint8_t Checksum[2];
  // uint8_t Urgent_Pointer;

} __attribute__((__packed__)) IPv4_Frame_Type;

typedef struct UDP_Frame_Type {
  uint16_t Source_Port;
  uint16_t Destination_Port;
  uint16_t Length;
  uint16_t Checksum;
  uint8_t data[UDP_Frame_Max_Len];
}__attribute__((__packed__)) UDP_Frame_Type;



typedef struct ARP_Frame_Type{
  uint16_t Hardware_Type;
  uint16_t Protocol_Type;
  uint8_t Hardware_Address_Length;
  uint8_t Protocol_Address_Length;
  uint16_t Operation;
  uint8_t Sender_Hardware_Address[ETH_ALEN];
  uint8_t Sender_IP_Address[4];
  uint8_t Target_Hardware_Address[ETH_ALEN];
  uint8_t Target_IP_Address[4];
}__attribute__((__packed__)) ARP_Frame_Type;


uint8_t *UDP_Packet_Assemble(UDP_Frame_Type *frame, char *buffer,
                             uint16_t *len);

uint8_t *IPv4_Packet_Assemble(IPv4_Frame_Type *frame, uint8_t *buffer,
                              uint16_t *len);

uint8_t *Eth_Packet_Assemble(Ethernet_Frame_Type *frame, char *buffer,
                             uint16_t *len);

void Add_UDP_CRC(uint8_t *buffer, uint16_t len);
void Add_IP_CRC(uint8_t *buffer, uint16_t len);


inline uint16_t calculate_checksum(uint16_t *buf, int nwords) {
    unsigned long sum;

    for (sum = 0; nwords > 0; nwords--) {
        sum += *buf++;
        if (sum & 0xFFFF0000) {
            sum = (sum & 0xFFFF) + (sum >> 16);  // wrap around
        }
    }

    return (uint16_t)(sum);  // one's complement of sum
}

#endif /* IPV4_H_ */
