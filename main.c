#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>  
//1U�ͱ�ʾ�����޷��ŵ�1���궨����Դ��ε�
#define SET_BIT(x,n)    (x | 1U<<(n-1))   //�������Ҫ������x�ĵ�nλ��bit��n-1��λ����Ϊ1

#define CLEAR_BIT(x,n)    (x & ~(1U<<(n-1))) //�������Ҫ������x�ĵ�nλ��bit��n-1��λ������

#define SET_BITS(x,n,m)    (x | ~(~0U<<(m-n+1))<<(n-1))  //�������Ҫ������x�ĵ�n��mλ��Ϊ1(n�ǵ�λ��m�Ǹ�λ)


struct data{            //������ԪĿ�ṹ 
	unsigned int ip_dst;   //Ŀ��IP 
	unsigned int ip_src;	//ԴIP 
	long int port_dst[2];	//Ŀ�Ķ˿� 
	long int port_src[2];	//Դ�˿� 
	short int protocol;	//Э�� 
	int result;

};
struct mask{            //������ԪĿ�ṹ 
	unsigned int ip_dst;   //Ŀ��IP 
	unsigned int ip_src;	 //ԴIP 
	long int port_dst;	//Ŀ�Ķ˿� 
	long int port_src;	//Դ�˿� 
	short int protocol;	//Э�� 

};
struct packet0{            //������ԪĿ�ṹ 
	unsigned int ip_dst;   //Ŀ��IP 
	unsigned int ip_src; 	 //ԴIP 
	unsigned int port_dst;	//Ŀ�Ķ˿� 
	unsigned int port_src;	//Դ�˿� 
	short int protocol;	//Э�� 

};
struct Tout{
	struct data Trule_data;
	struct mask Trule_mask;
	unsigned int port_dst;
	unsigned int port_src;
};

int c2i(unsigned char ch)
{

	if (isdigit(ch))
		return ch - 48;


	if (ch < 'A' || (ch > 'F' && ch < 'a') || ch > 'z')
		return -1;


	if (isalpha(ch))
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

	for (i = 2, temp = 0; i<len; i++, temp = 0)
	{

		temp = c2i(*(hex + i));

		bits = (len - i - 1) * 4;
		temp = temp << bits;


		num = num | temp;
	}


	return num;
}


int main()
{
	unsigned int i, ii, j, rulesDex1, rulesDex2, rulesCount, pktCount;
	unsigned int Tj, Ti,Tp, TCount, offset;
	char rules_firstDivide[7][25], rules_secondDivide[6][10];
	char *temp1, *temp2, Count[4];
	const char s[2] = " ", s2[5] = "./:";

	gets(Count);    //	��ù������� 
	rulesCount = atoi(Count);
	//	char rules[512][65];    //�����������ԭʼ���� 
	//struct data rule[rulesCount];   
	struct data rule_data[512];
	struct mask rule_mask[512];

	for (j = 0; j<rulesCount; j++)
	{

		scanf("%s %s %s %s %s %d", &rules_firstDivide[0], &rules_firstDivide[1], &rules_firstDivide[2], &rules_firstDivide[3], &rules_firstDivide[4], &rule_data[j].result);
		getchar();
		i = 5;
		while (i--)
		{
			temp2 = strtok(rules_firstDivide[i], s2);
			ii = 0;
			while (temp2)
			{

				switch (i)
				{

				case 0:
				{
					strcpy(rules_secondDivide[ii], temp2);
					rulesDex1 = atoi(rules_secondDivide[ii]);
					//	sprintf(rules_secondDivide[ii],"%02x",rulesDex1);


					if (4 - ii)
					{

						rule_data[j].ip_dst = (rule_data[j].ip_dst * 256 + atoi(rules_secondDivide[ii]));
					}
					if (ii == 4)
					{
						offset = rulesDex1;
						//printf("offset = %d\n",offset);
						rule_mask[j].ip_dst = 0xffffffff;
						offset = 33 - offset;
						//	rule_mask[j].ip_dst = SET_BITS(rule_mask[j].ip_dst,offset,32);
						while (--offset)
							rule_mask[j].ip_dst = CLEAR_BIT(rule_mask[j].ip_dst, offset);
					}

					break;
				}
				case 1:
				{
					strcpy(rules_secondDivide[ii], temp2);
					rulesDex1 = atoi(rules_secondDivide[ii]);
					//	sprintf(rules_secondDivide[ii],"%02x",rulesDex1);

					if (4 - ii)
					{
						rule_data[j].ip_src = (rule_data[j].ip_src * 256 + atoi(rules_secondDivide[ii]));
					}
					if (ii == 4)
					{
						offset = rulesDex1;

						rule_mask[j].ip_src = 0xffffffff;
						offset = 33 - offset;

						while (--offset)
							rule_mask[j].ip_src = CLEAR_BIT(rule_mask[j].ip_src, offset);
					}

					break;
				}
				case 2:
				{
					strcpy(rules_secondDivide[ii], temp2);

					rule_data[j].port_dst[ii] = atoi(rules_secondDivide[ii]);
					//	printf("rule_data[j].port_dst=%s\n",rule_data[j].port_dst[ii]);
					rule_mask[j].port_dst = 0xffff;
					break;
				}

				case 3:
				{
					strcpy(rules_secondDivide[ii], temp2);

					rule_data[j].port_src[ii] = atoi(rules_secondDivide[ii]);
					rule_mask[j].port_src = 0xffff;
					break;
				}
				case 4:
				{
					strcpy(rules_secondDivide[ii], temp2);
					rule_data[j].protocol = hex2dec(rules_secondDivide[0]);
					rule_mask[j].protocol = hex2dec(rules_secondDivide[1]);
					break;
				}

				default:;
				}
				temp2 = strtok(NULL, s2);
				ii++;
			}
		}
	}

	gets(Count);
	pktCount = atoi(Count);
	struct packet0 packet[100];
	int match_result[100];
	for (j = 0; j<pktCount; j++)
	{
		match_result[j] = 0;
		scanf("%s %s %d %d %d", &rules_firstDivide[0], &rules_firstDivide[1], &packet[j].port_dst, &packet[j].port_src, &packet[j].protocol);
		getchar();
		temp1 = strtok(rules_firstDivide[0], s2);

		while (temp1)
		{


			strcpy(rules_secondDivide[0], temp1);

			rulesDex1 = atoi(rules_secondDivide[0]);


			if (4 - ii)
			{
				packet[j].ip_dst = (packet[j].ip_dst * 256 + atoi(rules_secondDivide[0]));

			}
			temp1 = strtok(NULL, s2);



		}
		temp2 = strtok(rules_firstDivide[1], s2);

		while (temp2)
		{
			strcpy(rules_secondDivide[1], temp2);

			rulesDex2 = atoi(rules_secondDivide[1]);


			if (4 - ii)
			{
				packet[j].ip_src = (packet[j].ip_src * 256 + atoi(rules_secondDivide[1]));
			}
			temp2 = strtok(NULL, s2);



		}

	}

	TCount = 0;
	//int *port_bits;
	for (j = 0; j<rulesCount; j++)
	{

		Tj = rule_data[j].port_dst[0];
		
		int n = (rule_data[j].port_dst[1] - rule_data[j].port_dst[0] + 1);

		while (n>0)
		{
			long step0 = Tj & (0 - Tj);
			while (step0 > n) step0 /= 2;
			Tj += step0;
			n -= step0;
			int m = (rule_data[j].port_src[1] - rule_data[j].port_src[0] + 1);
			Ti = rule_data[j].port_src[0];
			while (m>0)
			{
				long step1 = Ti & (0 - Ti);
				while (step1 > m) step1 /= 2;
				Ti += step1;
				m -= step1;

				TCount++;


			}
		}
	}

	printf("32 32 16 16 8 %d\n", TCount); //total rules bits	
	struct Tout Tout1[512];
	int TCount1 = 0;
	int TPortdst, TPortsrc;
	unsigned int and_ip1, and_ip2, and_result;
	int and_port1, and_port2;
	for (j = 0; j<rulesCount; j++)
	{
		Tout1[j].Trule_data = rule_data[j];
		Tout1[j].Trule_mask = rule_mask[j];
		Tj = rule_data[j].port_dst[0];

		int n = (rule_data[j].port_dst[1] - rule_data[j].port_dst[0] + 1);

		while (n>0)
		{
			long int step0 = Tj & (0 - Tj);
			while (step0 > n) step0 /= 2;
			TPortdst = Tj;
			Tj += step0;
			n -= step0;
			int Tpmask0 = log(step0) / log(2) + 1;
			Tout1[j].Trule_mask.port_dst = rule_mask[j].port_dst;
			while (--Tpmask0)
				Tout1[j].Trule_mask.port_dst = CLEAR_BIT(Tout1[j].Trule_mask.port_dst, Tpmask0);
			int m = (rule_data[j].port_src[1] - rule_data[j].port_src[0] + 1);
			Ti = rule_data[j].port_src[0];
			while (m>0)
			{
				long int step1 = Ti & (0 - Ti);
				while (step1 > m) step1 /= 2;
				TPortsrc = Ti;
				Ti += step1;
				m -= step1;
				int Tpmask1 = log(step1) / log(2) + 1;
				Tout1[j].Trule_mask.port_src = rule_mask[j].port_src;
				while (--Tpmask1)
					Tout1[j].Trule_mask.port_src = CLEAR_BIT(Tout1[j].Trule_mask.port_src, Tpmask1);

				Tout1[j].port_dst = TPortdst;
				Tout1[j].port_src = TPortsrc;
				//	
				//	
				printf("data:0x%x ", Tout1[j].Trule_data.ip_dst);
				printf("0x%x ", Tout1[j].Trule_data.ip_src);
				printf("0x%x ", Tout1[j].port_dst);
				printf("0x%x ", Tout1[j].port_src);
				printf("0x%x ", Tout1[j].Trule_data.protocol);
				printf("%d\n", Tout1[j].Trule_data.result);
				printf("mask:0x%x ", Tout1[j].Trule_mask.ip_dst);
				printf("0x%x ", Tout1[j].Trule_mask.ip_src);
				printf("0x%x ", Tout1[j].Trule_mask.port_dst);
				printf("0x%x ", Tout1[j].Trule_mask.port_src);
				printf("0x%x\n", Tout1[j].Trule_mask.protocol);
				//	TCount1++;

				for (Tp = 0; Tp<pktCount; Tp++)
				{

					and_ip1 = (Tout1[j].Trule_data.ip_dst&Tout1[j].Trule_mask.ip_dst);
					and_ip2 = (packet[Tp].ip_dst&Tout1[j].Trule_mask.ip_dst);
					and_result = (and_ip1 == and_ip2) ? 1 : 0;
					if (and_result)
					{
						and_ip1 = (Tout1[j].Trule_data.ip_src&Tout1[j].Trule_mask.ip_src);
						and_ip2 = (packet[Tp].ip_src&Tout1[j].Trule_mask.ip_src);
						and_result = (and_ip1 == and_ip2) ? 1 : 0;
						if (and_result)
						{
							and_port1 = (Tout1[j].port_dst&Tout1[j].Trule_mask.port_dst);
							and_port2 = (packet[Tp].port_dst&Tout1[j].Trule_mask.port_dst);
							and_result = (and_port1 == and_port2) ? 1 : 0;
							if (and_result)
							{
								and_port1 = (Tout1[j].port_src&Tout1[j].Trule_mask.port_src);
								and_port2 = (packet[Tp].port_src&Tout1[j].Trule_mask.port_src);
								and_result = (and_port1 == and_port2) ? 1 : 0;
								if (and_result)
									if (Tout1[j].Trule_data.protocol == packet[Tp].protocol)
									{

										if (match_result[Tp])
											match_result[Tp] = match_result[Tp];
										else
											match_result[Tp] = Tout1[j].Trule_data.result;

									}
							}
						}

					}

				}


			}
		}

	}


	for (Tp = 0; Tp<pktCount; Tp++)
	{
		printf("%d\n", match_result[Tp]);

	}

	return 0;
}
