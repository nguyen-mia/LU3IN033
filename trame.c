#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversion.h"
#include "trame.h"

void affiche_addr(char * addr_hex, int len_addr){
	char *octet;
    char *del,*add_tmp;
    del = add_tmp = strdup(addr_hex);
    int cpt_tmp = 0; 
    while( ((octet = strsep(&add_tmp," ")) != NULL) && (cpt_tmp != len_addr)) {
       	if(len_addr == 4) {
            printf("%ld", hex_to_dec(octet));
        }else{
            printf("%s", octet);
        }
       	if(cpt_tmp < len_addr -1){
       		printf(".");
       	}
       	cpt_tmp++;
    }
    printf(" ");
    free(del);
    return;
}

void HTTP(char * trame){
    char *trame_tmp;
    trame_tmp = trame;
    printf("\nHYPERTEXT TRANSFER PROTOCOL (7) \n");
    char * octet;
    printf("   | ");
    char derniers_char[5];
    derniers_char[0] = '0';
    derniers_char[1] = '0';
    derniers_char[2] = '0';
    derniers_char[3] = '0'; 
    derniers_char[4] = '\0';
    int fin_entete = 0;
    while( (octet = strsep(&trame_tmp," ")) != NULL && (!fin_entete)) {
        if(!strcmp(octet, "0a") || !strcmp(octet, "0A")){
            printf("%c   | ", (char)hex_to_dec(octet));
        }else{
            printf("%c", (char)hex_to_dec(octet));
        }
        derniers_char[0] = derniers_char[1];
        derniers_char[1] = derniers_char[2];
        derniers_char[2] = derniers_char[3];
        derniers_char[3] = (char)hex_to_dec(octet); 
        if( (derniers_char[0] == '\r') && (derniers_char[1] == '\n') && (derniers_char[2] == '\r') && (derniers_char[3] == '\n') ) {
            fin_entete = 1;
        }
    }printf("\n");
    return;
}

void TCP(char * trame){
	char *trame_tmp;
	trame_tmp = trame;
	printf("\nTRANSMISSION CONTROL PROTOCOL (4) \n");

	//Source port number
	char tcp_port_s[6];
    memset(tcp_port_s, '\0', 6); 
    strncpy(tcp_port_s, trame_tmp, 5);
    removeChar(tcp_port_s, ' ');
    int port_no_s = hex_to_dec(tcp_port_s);
    printf("   | Source port number: %d (", port_no_s);
    printf("0x %s)\n", tcp_port_s );
    trame_tmp = trame_tmp + 6;

    //Destination port number
	char tcp_port_d[6];
    memset(tcp_port_d, '\0', 6); 
    strncpy(tcp_port_d, trame_tmp, 5);
    removeChar(tcp_port_d, ' ');
    int port_no_d = hex_to_dec(tcp_port_d);
    printf("   | Destination port number: %d (", port_no_d);
    printf("0x %s)\n", tcp_port_d );
    trame_tmp = trame_tmp + 6;

    //Sequence number
    char tcp_seq[12];
    memset(tcp_seq, '\0', 12); 
    strncpy(tcp_seq, trame_tmp, 11);
    removeChar(tcp_seq, ' ');
    printf("   | Sequence number: %ld (", hex_to_dec(tcp_seq));
    printf("0x %s)\n", tcp_seq );
    trame_tmp = trame_tmp + 12;

    //Acknowledgment number
    char tcp_ack_no[13];
    memset(tcp_ack_no, '\0', 13); 
    strncpy(tcp_ack_no, trame_tmp, 12);
    removeChar(tcp_ack_no, ' ');
    printf("   | Acknowledgment number: %ld (", hex_to_dec(tcp_ack_no));
    printf("0x %s)\n", tcp_ack_no );
    trame_tmp = trame_tmp + 12;

    //THL
    char tcp_THL[2];
    memset(tcp_THL, '\0', 2); 
    strncpy(tcp_THL, trame_tmp, 1);
    int THL = hex_to_dec(tcp_THL) * 4;
    printf("   | THL: %d (", THL);
    printf("0x %s) ", tcp_THL );
    if (THL > 20){
        printf("(with option)\n");  
    }else{
        printf("(without option)\n");
    }
    trame_tmp = trame_tmp + 1;

    //Reserved + NS
    char tcp_res[2];
    memset(tcp_res, '\0', 2); 
    strncpy(tcp_res, trame_tmp, 1);
    printf("   | Reserved: %ld (", hex_to_dec(tcp_res));
    printf("0x %s) \n", tcp_res );
    int NS;
    if(tcp_res[0] == '0'){ //= 0000 
        NS = 0;
    }
    if(tcp_res[0] == '1'){ //= 0001 
        NS = 1;
    }
    trame_tmp = trame_tmp + 2;

    //Flags 1
    char tcp_flags[2];
    memset(tcp_flags, '\0', 2); 
    strncpy(tcp_flags, trame_tmp, 1);
    int flags1 = hex_to_dec(tcp_flags);
    printf("   | Flags : \n");
    printf("      | NS  = %d\n", NS);
    int *del,*flags_bin;
    del = flags_bin = decToBinary(flags1);
    printf("      | CWR = %d\n", flags_bin[3]);
    printf("      | ECE = %d\n", flags_bin[2]);
    printf("      | URG = %d\n", flags_bin[1]);
    printf("      | ACK = %d\n", flags_bin[0]);
    free(del);
    trame_tmp = trame_tmp + 1;

    //Flags 2
    strncpy(tcp_flags, trame_tmp, 1);
    int flags2 = hex_to_dec(tcp_flags);
    del = flags_bin = decToBinary(flags2);
    printf("      | PSH = %d\n", flags_bin[3]);
    printf("      | RST = %d\n", flags_bin[2]);
    printf("      | SYN = %d\n", flags_bin[1]);
    printf("      | FIN = %d\n", flags_bin[0]);
    free(del);
    trame_tmp = trame_tmp + 2;

    //Window
    char tcp_win[6];
    memset(tcp_win, '\0', 6); 
    strncpy(tcp_win, trame_tmp, 5);
    removeChar(tcp_win, ' ');
    printf("   | Window: %ld ", hex_to_dec(tcp_win));
    printf("(0x %s)\n", tcp_win );
    trame_tmp = trame_tmp + 5;

    //Checksum
    char tcp_chsum[7];
    memset(tcp_chsum, '\0', 7); 
    strncpy(tcp_chsum, trame_tmp, 6);
    removeChar(tcp_chsum, ' ');
    printf("   | Checksum: %ld ", hex_to_dec(tcp_chsum));
    printf("(0x %s)\n", tcp_chsum );
    trame_tmp = trame_tmp + 7;

    //Urgent Pointer
    char tcp_uptr[6];
    memset(tcp_uptr, '\0', 6); 
    strncpy(tcp_uptr, trame_tmp, 5);
    removeChar(tcp_uptr, ' ');
    printf("   | Urgent pointer: %ld ", hex_to_dec(tcp_uptr));
    printf("(0x %s)\n", tcp_uptr );
    trame_tmp = trame_tmp + 6;

    //Options 
    if (THL > 20){ //avec option
        printf("   | Option : \n");
        int cpt_opt = 0; 
        while(cpt_opt < (THL -20)){
            //Option type
            char ip_op_type[3];
            memset(ip_op_type, '\0', 3); 
            strncpy(ip_op_type, trame_tmp, 2);
            int op_type = hex_to_dec(ip_op_type);
            printf("      | Type : %d - ", op_type);
            switch(op_type){
                case 0 :
                    printf("End of Options List (EOOL)");
                    cpt_opt = cpt_opt + 1;
                    break; 
                case 1 :
                    printf("No Operation (NOP)");
                    cpt_opt = cpt_opt + 1;
                    break; 
                case 2 :
                    printf("Maximum segment size (MSS)");
                    break; 
                case 3 :
                    printf("Window scale");
                    break; 
                case 4 :
                    printf("Selective Acknowledgement permitted");
                    break; 
                case 5 :
                    printf("Selective ACKnowledgement (SACK)");
                    break;
                case 8 :
                    printf("Timestamp and echo of previous timestamp");
                    break; 
                default : 
                    printf("Unknown option");
                    break;
            }
            printf(" (0x %s) \n", ip_op_type );
            trame_tmp = trame_tmp + 3;

            // Option length 
            int op_len;
            if(op_type > 1){
                char ip_op_len[3];
                memset(ip_op_len, '\0', 3); 
                strncpy(ip_op_len, trame_tmp, 2);
                op_len = hex_to_dec(ip_op_len);
                printf("         | Length : %d ", op_len);
                printf(" (0x %s) \n", ip_op_len );
                trame_tmp = trame_tmp + 3;
                trame_tmp = trame_tmp + ((op_len  - 2) * 3);
                cpt_opt = cpt_opt + op_len; 

            }
            
        }
    }
    
    //Data 
    if ((port_no_s == 80) ||  port_no_d == 80){ //HTTP
        HTTP(trame_tmp);
    }
	return;
}

void IPv4(char * trame){
	char *trame_tmp = trame;
	printf("\nINTERNET PROTOCOL VERSION 4 (3) \n");
	
	//Version
	char ip_ver[2];
    memset(ip_ver, '\0', 2); 
    strncpy(ip_ver, trame_tmp, 1);
    printf("   | Version: %ld (", hex_to_dec(ip_ver));
    printf("0x %s)\n", ip_ver );
    trame_tmp = trame_tmp + 1;

    //IP Header Length
    char ip_IHL[2];
    memset(ip_IHL, '\0', 2); 
    strncpy(ip_IHL, trame_tmp, 1);
    int IHL = hex_to_dec(ip_IHL) * 4;
    printf("   | IP Header Length: %d (", IHL);
    printf("0x %s) ", ip_IHL );
    if (IHL > 20){
    	printf("(with option)\n");	
    }else{
    	printf("(without option)\n");
    }
    trame_tmp = trame_tmp + 2;

    //Type Of Service
    char ip_TOS[4];
    memset(ip_TOS, '\0', 4); 
    strncpy(ip_TOS, trame_tmp, 3);
    printf("   | Type Of Service: Ox%s\n", ip_TOS );
    trame_tmp = trame_tmp + 3;

    //Total Length 
    char ip_TtLen[7];
    memset(ip_TtLen, '\0', 7); 
    strncpy(ip_TtLen, trame_tmp, 6);
    removeChar(ip_TtLen, ' ');
    printf("   | Total Length: %ld (", hex_to_dec(ip_TtLen));
    printf("0x %s)\n", ip_TtLen );
    trame_tmp = trame_tmp + 6;

    //Identification 
    char ip_Id[7];
    memset(ip_Id, '\0', 7); 
    strncpy(ip_Id, trame_tmp, 6);
    removeChar(ip_Id, ' ');
    printf("   | Identification: %ld (", hex_to_dec(ip_Id));
    printf("0x %s)\n", ip_Id );
    trame_tmp = trame_tmp + 6;

    //Flags
    char ip_Fl[2];
    memset(ip_Fl, '\0', 2); 
    strncpy(ip_Fl, trame_tmp, 1);
    removeChar(ip_Fl, ' ');
    int * del, *flags_bin;
    del = flags_bin = decToBinary(hex_to_dec(ip_Fl));
    printf("   | Flags :(0x %s)\n", ip_Fl);
    printf("      | DF = %d\n", flags_bin[2]);
    printf("      | MF = %d\n", flags_bin[1]);
    int frag = flags_bin[0];    
    free(del);
    trame_tmp = trame_tmp + 1;

    //Fragment Offset
    char ip_Fr[5];
    memset(ip_Fr, '\0', 5); 
    strncpy(ip_Fr, trame_tmp, 4);
    removeChar(ip_Fr, ' ');
    printf("   | Fragment Offset : %ld ", hex_to_dec(ip_Fr) + frag*4096);
    printf("(0x %s)\n", ip_Fr);
    trame_tmp = trame_tmp + 5;
 	

    //TTL 
    char ip_TTL[3];
    memset(ip_TTL, '\0', 3); 
    strncpy(ip_TTL, trame_tmp, 2);
    printf("   | TTL : %ld (0x ", hex_to_dec(ip_TTL));
    printf("%s)\n", ip_TTL);
    trame_tmp = trame_tmp + 3;

    //Protocol
    char ip_Prtc[3];
    memset(ip_Prtc, '\0', 3); 
    strncpy(ip_Prtc, trame_tmp, 2);
    int Protocol = hex_to_dec(ip_Prtc);
    printf("   | Protocol : %d ", Protocol);
    switch (Protocol){
    	case 1 :
    		printf("- ICMP ");
    		break; 
    	case 6 : 
    		printf("- TCP ");
    		break; 
    	case 17 :  
    		printf("- UDP");
    		break;
    	default : 
    		printf("Unknown protocol \n");
    }
    printf("(0x %s)\n", ip_Prtc);
    trame_tmp = trame_tmp + 3;

    //Header Checksum
    char ip_HCheck[6]; 
   	memset(ip_HCheck, '\0', 6); 
    strncpy(ip_HCheck, trame_tmp, 5);
    printf("   | Header Checksum : %ld ", hex_to_dec(ip_HCheck));
    printf("(0x %s)\n",ip_HCheck);
    trame_tmp = trame_tmp + 6;

    //Source Address
    char ip_add_s[12];
    memset(ip_add_s, '\0', 12); 
    strncpy(ip_add_s, trame_tmp, 11);
    printf("   | Source IP address : ");
    affiche_addr(ip_add_s, 4);
    printf(" (0x %s) \n", ip_add_s );
    trame_tmp = trame_tmp + 12;

    //Destination Address
    char ip_add_d[12];
    memset(ip_add_d, '\0', 12); 
    strncpy(ip_add_d, trame_tmp, 11);
    printf("   | Destination IP address : ");
    affiche_addr(ip_add_d, 4);
    printf(" (0x %s) \n", ip_add_d );
    trame_tmp = trame_tmp + 12;

    //Options 
    if (IHL > 20){ //avec option
    	printf("   | Option : \n");
    	int cpt_opt = 0; 
    	while(cpt_opt < (IHL -20)){
    		//Option type
    		char ip_op_type[3];
		    memset(ip_op_type, '\0', 3); 
		    strncpy(ip_op_type, trame_tmp, 2);
		    int op_type = hex_to_dec(ip_op_type);
		    printf("      | Type : %d - ", op_type);
		    switch(op_type){
		    	case 0 :
		    		printf("End of Options List (EOOL)");
		    		cpt_opt = cpt_opt + 1;
		    		break; 
		    	case 1 :
		    		printf("No Operation (NOP)");
		    		break; 
		    	case 7 :
		    		printf("Record Route (RR)");
		    		break; 
		    	case 68 :
		    		printf("Time Stamp (TS)");
		    		break; 
		    	case 131 :
		    		printf("Loose Source Route (LSR)");
		    		break; 
		    	case 137 :
		    		printf("Strict Source Route (SSR)");
		    		break; 
		    	default : 
		    		printf("Unknown option");
		    		break;
		    }
		    printf(" (0x %s) \n", ip_op_type );
		    trame_tmp = trame_tmp + 3;

		    // Option length 
		    int op_len;
		    if(op_type != 0){
			    char ip_op_len[3];
			    memset(ip_op_len, '\0', 3); 
			    strncpy(ip_op_len, trame_tmp, 2);
			    op_len = hex_to_dec(ip_op_len);
			    printf("         | Length : %d ", op_len);
			    printf(" (0x %s) \n", ip_op_len );
		    	trame_tmp = trame_tmp + 3;
		    	trame_tmp = trame_tmp + ((op_len  - 2) * 3);
				cpt_opt = cpt_opt + op_len; 

		    }
		    
    	}
    }

    //Data 
    if(Protocol == 6){
        TCP(trame_tmp);
    }else{
        printf("\nProtocol not supported\n");
    }
    return; 
}

void ethernet(char * trame){
	char *trame_tmp;
    trame_tmp = trame;
   
	printf("\nETHERNET (2) \n");
    
    //Destination address
    char eth_add[18];
    memset(eth_add, '\0', 18); 
    strncpy(eth_add, trame_tmp, 17);
    printf("   | Destination MAC address : ");
    affiche_addr(eth_add, 6);
    printf("(0x %s)\n", eth_add);
    trame_tmp = trame_tmp + 18;

    //Source address
    strncpy(eth_add, trame_tmp, 17);
    printf("   | Source MAC address : ");
    affiche_addr(eth_add, 6);
    printf("(0x %s)\n", eth_add);
    trame_tmp = trame_tmp + 18;

    //Type 
    char eth_type[7];
    memset(eth_type, '\0', 7); 
    strncpy(eth_type, trame_tmp, 6);
    printf("   | EtherType : ");
    int ipV4 = 0;
   	if (!strcmp(eth_type, "08 00 ")){
   		printf("Internet Protocol version 4 - IPv4 (0x 08 00)\n");
        ipV4 = 1;
   	}
    if (!strcmp(eth_type, "86 DD ")){
        printf("Internet Protocol version 6 - IPv6 (0x 86 DD)\n");
    }
    if (!strcmp(eth_type, "86 dd ")){
        printf("Internet Protocol version 6 - IPv6 (0x 86 dd)\n");
    }
   	if (!strcmp(eth_type, "08 06 ")){
   		printf("Address Resolution Protocol - ARP (0x 08 06)\n");
   	}
    trame_tmp = trame_tmp + 6;

    //Data (IPv4)
    if(ipV4){
        IPv4(trame_tmp);
    }else{
        printf("\nProtocol not supported\n");
    }
	return; 
}


