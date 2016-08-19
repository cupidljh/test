#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "hdlc.h"

#define  BUFF_SIZE   1024

int   main( void)
{
   int   server_socket;
   int   client_socket;
   int   client_addr_size;

   struct sockaddr_in   server_addr;
   struct sockaddr_in   client_addr;

   hdlc_enc hdlc_enc;
   hdlc_dec hdlc_dec;

   char   buff_rcv[BUFF_SIZE+5];
   char   buff_snd[BUFF_SIZE+5];



   server_socket  = socket( PF_INET, SOCK_STREAM, 0);
   if( -1 == server_socket)
   {
      printf( "server socket 생성 실패\n");
      exit( 1);
   }

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons( 4000);
   server_addr.sin_addr.s_addr= htonl( INADDR_ANY);

   if( -1 == bind( server_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
   {
      printf( "bind() 실행 에러\n");
      exit( 1);
   }

   if( -1 == listen(server_socket, 5))
   {
      printf( "listen() 실행 실패\n");
      exit( 1);
   }

   while(1)
   {
      client_addr_size  = sizeof( client_addr);
      client_socket     = accept( server_socket, (struct sockaddr*)&client_addr, &client_addr_size);

      if ( -1 == client_socket)
      {
         printf( "클라이언트 연결 수락 실패\n");
         exit( 1);
      }

      read ( client_socket, &hdlc_enc, sizeof(hdlc_enc));

      printf("receive data : ");
      printf("%02X ",hdlc_enc.start_flag);
      for(int i =0;i<hdlc_enc.size;i++)
      {
          printf("%02X ",hdlc_enc.info[i]);
      }
      printf("%02X %02X ",hdlc_enc.crcH,hdlc_enc.crcL);
      printf("%02X\n",hdlc_enc.finish_flag);

/*      printf("sizeof(&hdlc_enc+1)= %zu\n",sizeof(hdlc_enc));

      printf("hdlc_enc->start_flag = %02x\n",hdlc_enc.start_flag);

      for(int i=0;i<sizeof(hdlc_enc);i++)
         printf("hdlc_enc->info[%d] = %02X\n",i,hdlc_enc.info[i]);

      printf("hdlc_enc->fcs = %02x %02x\n ", hdlc_enc.crcH,hdlc_enc.crcL);
      printf("hdlc_enc->finish_flag = %02X\n",hdlc_enc.finish_flag);
*/
      hdlc_dec_init(&hdlc_dec);
      hdlc_decode(&hdlc_enc, &hdlc_dec);

      close( client_socket);
   }
}
