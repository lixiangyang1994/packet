#include <stdio.h>
#include <string.h>
  
 //1U�ͱ�ʾ�����޷��ŵ�1���궨����Դ��ε�
#define SET_BIT(x,n)    (x | 1U<<(n-1))   //�������Ҫ������x�ĵ�nλ��bit��n-1��λ����Ϊ1

#define CLEAR_BIT(x,n)    (x & ~(1U<<(n-1))) //�������Ҫ������x�ĵ�nλ��bit��n-1��λ������


#define SET_BITS(x,n,m)    (x | ~(~0U<<(m-n+1))<<(n-1))  //�������Ҫ������x�ĵ�n��mλ��Ϊ1(n�ǵ�λ��m�Ǹ�λ)

struct data{            //������ԪĿ�ṹ 
	char ip_dst[20];   //Ŀ��IP 
	char ip_src[20];	//ԴIP 
	char port_dst[2][20];	//Ŀ�Ķ˿� 
	char port_src[2][20];	//Դ�˿� 
	char protocol[20];	//Э�� 
	int result;
	
};
struct mask{            //������ԪĿ�ṹ 
	unsigned int ip_dst;   //Ŀ��IP 
    unsigned int ip_src;	 //ԴIP 
	unsigned int port_dst;	//Ŀ�Ķ˿� 
	unsigned int port_src;	//Դ�˿� 
	unsigned int protocol;	//Э�� 
	
};


	
int main()
{
	int i,ii,j,rulesDex,offset,rulesCount;
	int Tj,Ti,Tcount;
	char Count[3],rules_in[65];
	char rules_firstDivide[7][25],rules_secondDivide[6][10];
	char *temp1,*temp2;	
	const char s[2] = " ",s2[5]="./:";										
	fgets(Count,4,stdin);    //	��ù������� 
	rulesCount = atoi(Count); 
	char rules[rulesCount][65];    //�����������ԭʼ���� 
	//struct data rule[rulesCount];   
	struct data rule_data[rulesCount];
	struct mask rule_mask[rulesCount];
	offset=0;
	
	for (j = 0;j<rulesCount;j++)
	{
		fgets(rules_in,65,stdin);		
		strcpy(rules[j],rules_in);
		strcpy(rule_data[j].ip_dst,"0x");
		strcpy(rule_data[j].ip_src,"0x");
		temp1=strtok(rules[j],s);    //���ȷ������ԪĿ 
		i = 0;
		while (temp1)
			{
				
				strcpy(rules_firstDivide[i],temp1);	
				temp1 = strtok(NULL,s);	
				i++;						
			}
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
									rulesDex = atoi(rules_secondDivide[ii]);
									sprintf(rules_secondDivide[ii],"%02x",rulesDex);
									
									if(4-ii)
										{
											strcat(rule_data[j].ip_dst,rules_secondDivide[ii]);
										}
									if(ii==4)
										{
											offset = rulesDex;
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
									rulesDex = atoi(rules_secondDivide[ii]);
									sprintf(rules_secondDivide[ii],"%02x",rulesDex);
									if(4-ii)
										{
											strcat(rule_data[j].ip_src,rules_secondDivide[ii]);
										}
									if(ii==4)
										{
											offset = rulesDex;
									
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
									rulesDex = atoi(rules_secondDivide[ii]);
								 	sprintf(rules_secondDivide[ii],"%x",rulesDex);
									strcpy(rule_data[j].port_dst[ii],rules_secondDivide[ii]);
								//	printf("rule_data[j].port_dst=%s\n",rule_data[j].port_dst[ii]);
									rule_mask[j].port_dst = 0xffff;
									break;
								}
							
							case 3:
								{	
									strcpy(rules_secondDivide[ii],temp2);
									rulesDex = atoi(rules_secondDivide[ii]);
									sprintf(rules_secondDivide[ii],"%x",rulesDex);
									strcpy(rule_data[j].port_src[ii],rules_secondDivide[ii]);
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
							case 5:
								{	
								
									strcpy(rules_secondDivide[ii],temp2);
									rule_data[j].result = atoi(rules_secondDivide[0]);
									//strcpy(rule_data[j].result,temp2);
									break;
								}
							default : ;	
							}	
							temp2 = strtok(NULL,s2);
							ii++;
						}
		}

	}
		for(Tj=1;Tj<rulesCount;Tj++)
			for(Ti=0;Ti<2;Ti++)
				{
				printf("data:%s ",rule_data[Tj].ip_dst);
				printf("%s ",rule_data[Tj].ip_src);
				printf("0x%s ",rule_data[Tj].port_dst[Ti]);
				printf("0x%s ",rule_data[Tj].port_src[Ti]);
				printf("%s ",rule_data[Tj].protocol);
				printf("%d\n",rule_data[Tj].result);
				printf("mask:0x%x ",rule_mask[Tj].ip_dst);
				printf("0x%x ",rule_mask[Tj].ip_src);
				printf("0x%x ",rule_mask[Tj].port_dst);
				printf("0x%x ",rule_mask[Tj].port_src);
				printf("0x%x\n",rule_mask[Tj].protocol);
				}
		
		/*	Tj=0;Ti=0;
				printf("data:%s ",rule_data[Tj].ip_dst);
				printf("%s ",rule_data[Tj].ip_src);
				printf("0x%s ",rule_data[Tj].port_dst[Ti]);
				printf("0x%s ",rule_data[Tj].port_src[Ti]);
				printf("%s ",rule_data[Tj].protocol);
				printf("%d\n",rule_data[Tj].result);	
		*/
//	printf("32 32 16 16 8 %d\n",rulesCount);
	system("pause");
	return 0;
}
