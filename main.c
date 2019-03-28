#include <stdio.h>
#include <string.h>
struct data{            //定义五元目结构 
	char ip_dst[20];   //目的IP 
	char ip_src[20];	//源IP 
	char port_dst[20];	//目的端口 
	char port_src[20];	//源端口 
	char protocol[20];	//协议 
	
};
int main()
{
	int i,j,rulesCount,rules_D;
	char Count[3],rules_temp[65],rules_firstDivide[6][25],rules_secondDivide[5][10];
	const char s[2] = " ",s2[3]="./";										
	fgets(Count,4,stdin);    //	获得规则总数 
	//puts(Count);
	rulesCount = atoi(Count); 
	struct data rule[rulesCount];   //储存输入规则原始数据 
	struct data rule_data[rulesCount];
	char rules[rulesCount][65],*temp1,*temp2;
	for (j = 0;j<rulesCount;j++){
		fgets(rules_temp,65,stdin);
		strcpy(rules[j],rules_temp);
		strcpy(rule_data[j].ip_dst,"0x");
		i = 0;
		temp1=strtok(rules[j],s);
		
		while (temp1)
			{
				
				strcpy(rules_firstDivide[i],temp1);
				
				temp1 = strtok(NULL,s);	
				temp2 = strtok(rules_firstDivide[i],s2);
				while(temp2)
					{
						strcpy(rules_secondDivide[i],temp2);
						temp2 = strtok(NULL,s2);
					}
				i++;						
			}	
		/*
		strcpy(rule[j].ip_dst,rules_firstDivide[0]);
		strcpy(rule[j].ip_src,rules_firstDivide[1]);
		strcpy(rule[j].port_dst,rules_firstDivide[2]);
		strcpy(rule[j].port_src,rules_firstDivide[3]);
		strcpy(rule[j].protocol,rules_firstDivide[4]);
		
		i = 0;
		temp2 = strtok(rule[j].ip_dst,s2);
		while(temp2)
			{
				strcpy(rules_secondDivide[i],temp2);
				strcat(rule_data[j].ip_dst,rules_secondDivide[i]);
				temp2 = strtok(NULL,s2);
				i++;
			}*/
	
	}
	
	printf("%s\n",rule->ip_dst);
	printf("%s\n",rule_data->ip_dst);
	system("pause");
	return 0;
}
