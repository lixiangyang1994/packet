#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>  
 //1U就表示的是无符号的1，宏定义可以传参的
#define SET_BIT(x,n)    (x | 1U<<(n-1))   //这里就是要把数字x的第n位（bit（n-1）位）置为1

#define CLEAR_BIT(x,n)    (x & ~(1U<<(n-1))) //这里就是要把数字x的第n位（bit（n-1）位）清零

#define SET_BITS(x,n,m)    (x | ~(~0U<<(m-n+1))<<(n-1))  //这里就是要把数字x的第n到m位置为1(n是低位，m是高位)


struct data{            //定义五元目结构 
	char ip_dst[20];   //目的IP 
	char ip_src[20];	//源IP 
    long int port_dst[2];	//目的端口 
    long int port_src[2];	//源端口 
	char protocol[20];	//协议 
	int result;
	
};
struct mask{            //定义五元目结构 
	unsigned int ip_dst;   //目的IP 
    unsigned int ip_src;	 //源IP 
    long int port_dst;	//目的端口 
	long int port_src;	//源端口 
	unsigned int protocol;	//协议 
	
};
struct packet0{            //定义五元目结构 
	char ip_dst[20];   //目的IP 
	char ip_src[20];	 //源IP 
	long int port_dst;	//目的端口 
	long int port_src;	//源端口 
	int protocol;	//协议 
	
};
struct Tout{
	struct data Trule_data;
	struct mask Trule_mask;

};
int c2i(char ch)  
{  
        
        if(isdigit(ch))  
                return ch - 48;  
  
      
        if( ch < 'A' || (ch > 'F' && ch < 'a') || ch > 'z' )  
                return -1;  
  
       
        if(isalpha(ch))  
                return isupper(ch) ? ch - 55 : ch - 87;  
  
        return -1;  
}  
unsigned int hex2dec(char *hex)  
{  
        int len;  
       unsigned int num = 0;  
       unsigned int temp;  
        int bits;  
        int i;  
          
       
        len = strlen(hex);  
  			
        for (i=2, temp=0; i<len; i++, temp=0)  
        {  
                
                temp = c2i( *(hex + i) );  
              
                bits = (len - i - 1) * 4;  
                temp = temp << bits;  
  
               
                num = num | temp;  
        }  
  
       
        return num;  
}

	
int main()
{
	int i,ii,j,rulesDex1,rulesDex2,rulesCount,pktCount;
	int Tj,Ti,TCount,offset;
	char Count[6],rules_in[65],pkt[45];
	char rules_firstDivide[7][25],rules_secondDivide[6][10];
	char *temp1,*temp2;	
	const char s[2] = " ",s2[5]="./:";
									
	gets(Count);    //	获得规则总数 
	rulesCount = atoi(Count);
	char rules[rulesCount][65];    //储存输入规则原始数据 
	//struct data rule[rulesCount];   
	struct data rule_data[rulesCount];
	struct mask rule_mask[rulesCount];

	for (j = 0;j<rulesCount;j++)
	{	
		strcpy(rule_data[j].ip_dst,"0x");
		strcpy(rule_data[j].ip_src,"0x");
		scanf("%s %s %s %s %s %d",&rules_firstDivide[0],&rules_firstDivide[1],&rules_firstDivide[2],&rules_firstDivide[3],&rules_firstDivide[4],&rule_data[j].result);	
		getchar(); 
		i=5;	
				while(i--)
				{
					temp2 = strtok(rules_firstDivide[i],s2);
					ii = 0;
					while(temp2)
								{	
									
									switch(i)
									{
									
									case 0:
										{	
											strcpy(rules_secondDivide[ii],temp2);
											rulesDex1 = atoi(rules_secondDivide[ii]);
											sprintf(rules_secondDivide[ii],"%02x",rulesDex1);
											
		
											if(4-ii)
												{
													
													strcat(rule_data[j].ip_dst,rules_secondDivide[ii]);
												}
											if(ii==4)
												{
													offset = rulesDex1;
													//printf("offset = %d\n",offset);
													rule_mask[j].ip_dst = 0xffffffff;
													offset = 33-offset;
												//	rule_mask[j].ip_dst = SET_BITS(rule_mask[j].ip_dst,offset,32);
													while(--offset)
													rule_mask[j].ip_dst = CLEAR_BIT(rule_mask[j].ip_dst,offset);
												}
									
											break;
										}
									case 1:
										{	
											strcpy(rules_secondDivide[ii],temp2);
											rulesDex1 = atoi(rules_secondDivide[ii]);
											sprintf(rules_secondDivide[ii],"%02x",rulesDex1);
											
											if(4-ii)
												{
													strcat(rule_data[j].ip_src,rules_secondDivide[ii]);
												}
											if(ii==4)
												{
													offset = rulesDex1;
											
													rule_mask[j].ip_src = 0xffffffff;
													offset = 33-offset;
											
													while(--offset)
													rule_mask[j].ip_src = CLEAR_BIT(rule_mask[j].ip_src,offset);
												}
									
											break;
										}
									case 2:
										{	
											strcpy(rules_secondDivide[ii],temp2);
										//	rulesDex = atoi(rules_secondDivide[ii]);
										// 	sprintf(rules_secondDivide[ii],"%x",rulesDex);
											rule_data[j].port_dst[ii]=atoi(rules_secondDivide[ii]);
										//	printf("rule_data[j].port_dst=%s\n",rule_data[j].port_dst[ii]);
											rule_mask[j].port_dst = 0xffff;
											break;
										}
									
									case 3:
										{	
											strcpy(rules_secondDivide[ii],temp2);
										//	rulesDex = atoi(rules_secondDivide[ii]);
										//	sprintf(rules_secondDivide[ii],"%x",rulesDex);
											rule_data[j].port_src[ii]=atoi(rules_secondDivide[ii]);
											rule_mask[j].port_src = 0xffff;
											break;
										}
									case 4:
										{	
											strcpy(rules_secondDivide[ii],temp2);
											strcpy(rule_data[j].protocol,rules_secondDivide[0]);
											rule_mask[j].protocol = 0xff;
											break;
										}
								
									default : ;	
									}	
									temp2 = strtok(NULL,s2);
									ii++;
								}
				}
	}
	
	gets(Count);
	pktCount = atoi(Count);
	struct packet0 packet[pktCount];
	int match_result[pktCount]; 
	for (j = 0;j<pktCount;j++)
	{	match_result[j]=0;	
		strcpy(packet[j].ip_dst,"0x");
		strcpy(packet[j].ip_src,"0x");
		scanf("%s %s %d %d %d",&rules_firstDivide[0],&rules_firstDivide[1],&packet[j].port_dst,&packet[j].port_src,&packet[j].protocol);
		getchar(); 
						temp1 = strtok(rules_firstDivide[0],s2);
						
						while(temp1)
						{
								
					
									strcpy(rules_secondDivide[0],temp1);
									
									rulesDex1 = atoi(rules_secondDivide[0]);
									sprintf(rules_secondDivide[0],"%02x",rulesDex1);
									
									if(4-ii)
										{
											strcat(packet[j].ip_dst,rules_secondDivide[0]);
											
										}
									temp1 = strtok(NULL,s2);
							
									
									
						}
						temp2 = strtok(rules_firstDivide[1],s2);
						
						while(temp2)
						{
									strcpy(rules_secondDivide[1],temp2);
									
									rulesDex2 = atoi(rules_secondDivide[1]);
									sprintf(rules_secondDivide[1],"%02x",rulesDex2);
									
									if(4-ii)
										{
											strncat(packet[j].ip_src,rules_secondDivide[1],2);
										}
									temp2 = strtok(NULL,s2);
							
									
									
						}
		
	}
		
		TCount = 0;
		//int *port_bits;
		for(j=0;j<rulesCount;j++)
			{	
				
				Tj=rule_data[j].port_dst[0];
				Ti=rule_data[j].port_src[0];
				int n = (rule_data[j].port_dst[1] - rule_data[j].port_dst[0]+1);
				
					while(n>0) 
					{
						long step0 = Tj & (0-Tj);
						while (step0 > n) step0 /= 2;
						Tj += step0;
						n -= step0;
						int m = (rule_data[j].port_src[1] - rule_data[j].port_src[0]+1);	
						while(m>0)
							{
								long step1 = Ti & (0-Ti);
								while (step1 > m) step1 /= 2;
								Ti += step1;
								m -= step1;
								
								TCount++;
							
							
							}
					}
			}
		
		printf("32 32 16 16 8 %d\n",TCount); //total rules bits	
		struct Tout Tout1[TCount];  
		int TCount1=0;
		int TPortdst,TPortsrc;
		for(j=0;j<rulesCount;j++)
			{				
					Tj=rule_data[j].port_dst[0];
					
					int n = (rule_data[j].port_dst[1] - rule_data[j].port_dst[0]+1);
				
					while(n>0) 
					{
						long step0 = Tj & (0-Tj);
						while (step0 > n) step0 /= 2;
						TPortdst = Tj;
						 Tj += step0;
						 n -= step0;
						 int Tpmask0 = log(step0)/log(2)+1; 
						while(--Tpmask0)
							rule_mask[j].port_dst = CLEAR_BIT(rule_mask[j].ip_src,Tpmask0);
						int m = (rule_data[j].port_src[1] - rule_data[j].port_src[0]+1);
						Ti=rule_data[j].port_src[0];
						while(m>0)
						{
								long step1 = Ti & (0-Ti);
								while (step1 > m) step1 /= 2;
								TPortsrc = Ti;
								Ti += step1;
								m -= step1;
								int Tpmask1 = log(step0)/log(2)+1;
								while(--Tpmask1)
									rule_mask[j].port_src = CLEAR_BIT(rule_mask[j].ip_src,Tpmask1);
							Tout1[TCount1].Trule_data = rule_data[j];
							Tout1[TCount1].Trule_mask = rule_mask[j];
							Tout1[TCount1].Trule_data.port_dst[0] = TPortdst;
							Tout1[TCount1].Trule_data.port_src[0] = TPortsrc;
							printf("data:%s ",Tout1[TCount1].Trule_data.ip_dst);
							printf("%s ",Tout1[TCount1].Trule_data.ip_src);
							printf("0x%x ",Tout1[TCount1].Trule_data.port_dst[0]);
							printf("0x%x ",Tout1[TCount1].Trule_data.port_src[0]);
							printf("%s ",Tout1[TCount1].Trule_data.protocol);
							printf("%d\n",Tout1[TCount1].Trule_data.result);
							printf("mask:0x%x ",Tout1[TCount1].Trule_mask.ip_dst);
							printf("0x%x ",Tout1[TCount1].Trule_mask.ip_src);
							printf("0x%x ",Tout1[TCount1].Trule_mask.port_dst);
							printf("0x%x ",Tout1[TCount1].Trule_mask.port_src);
							printf("0x%x\n",Tout1[TCount1].Trule_mask.protocol);
					 		TCount1++;
					 	
						}
					}
						
			}
		
		    unsigned int and_ip1,and_ip2,and_port1,and_port2,and_protocol,and_result,Tp;   
			for(Tp=0;Tp<pktCount;Tp++)
			{	
				for(Tj=0;Tj<TCount;Tj++)
				{
				
								and_ip1=hex2dec(Tout1[Tj].Trule_data.ip_dst)&Tout1[Tj].Trule_mask.ip_dst;
								and_ip2=hex2dec(packet[Tp].ip_dst)&Tout1[Tj].Trule_mask.ip_dst;
								and_result = (and_ip1==and_ip2)?1:0;
								if(and_result)
									{
										and_ip1=(hex2dec(Tout1[Tj].Trule_data.ip_src)&Tout1[Tj].Trule_mask.ip_src);
										and_ip2=(hex2dec(packet[Tp].ip_src)&Tout1[Tj].Trule_mask.ip_src);
										and_result = (and_ip1==and_ip2)?1:0;
										if(and_result)
										{
											and_port1=(Tout1[Tj].Trule_data.port_dst[0]&Tout1[Tj].Trule_mask.port_dst);
											and_port2=(packet[Tp].port_dst&Tout1[Tj].Trule_mask.port_dst);
											and_result = (and_port1==and_port2)?1:0;
												if(and_result)
												{
													and_port1=(Tout1[Tj].Trule_data.port_src[0]&Tout1[Tj].Trule_mask.port_src);
													and_port2=(packet[Tp].port_src&Tout1[Tj].Trule_mask.port_src);
													and_result = (and_port1==and_port2)?1:0;
													if(and_result)
													 if(hex2dec(Tout1[Tj].Trule_data.protocol)==packet[Tp].protocol)
														{
														
															match_result[Tp]=Tout1[Tj].Trule_data.result;
															break;
														
														}
										 		}
									    }
									
									}
								else if(Tj==TCount)
									match_result[Tp] = 0;
																			
															
				}
			
			printf("%d\n",match_result[Tp]);		
				
			}
		

	return 0;
}
