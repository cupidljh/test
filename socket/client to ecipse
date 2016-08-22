#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "hdlc.h"

#define  BUFF_SIZE   1024

int   main( int argc, char *argv[])
{

   size_t buflen;
   char buf[16];
   FILE *in;
   
   hdlc_enc hdlc_enc;
    
   int   client_socket;

   struct sockaddr_in   server_addr;

   char   buff[BUFF_SIZE+5];

   client_socket  = socket( PF_INET, SOCK_STREAM, 0);
   if( -1 == client_socket)
   {
      printf( "socket 생성 실패\n");
      exit( 1);
   }

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons( 4000);
   server_addr.sin_addr.s_addr= inet_addr( "127.0.0.1");

   if( -1 == connect( client_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
   {
      printf( "접속 실패\n");
      exit( 1);
   }

    
   if(( in= fopen(argv[1], "rb")) == NULL){
       fputs("file error\n", stderr);
       exit(1);
   }

   hdlc_enc_init(&hdlc_enc);
   
   while((buflen = fread(buf, sizeof(char), sizeof(buf), in)) != '\0')
   {
   
        hdlc_encode(buf, buflen, &hdlc_enc);

        write( client_socket, &hdlc_enc, sizeof(hdlc_enc));      // +1: NULL까지 포함해서 전송

//        printf("sizeof(&hdlc_enc+1) = %zu\n",sizeof(hdlc_enc));

        printf("Send success\n");
   }

//   read ( client_socket, buff, BUFF_SIZE);
   
   close( client_socket);
   
   return 0;
}
