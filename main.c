#include <stdio.h>
#include <string.h>
struct data{
	char dip[20];
	char oip[20];
	char dudp[20];
	char oudp[20];
	char deal[20];
	
};
int main()
{
	int i,j,rulesCount;
	char Count[3],rules_t[65],rules[100][65],rules_2[6][25];
	const char s[2] = " ";
	printf("%s","请输入规则数 :\n");
	fgets(Count,4,stdin);
	//puts(Count);
	rulesCount = atoi(Count);
	struct data rule[rulesCount];
	char *temp;
	
	for (j = 0;j<rulesCount;j++){
		fgets(rules_t,65,stdin);
		strcpy(rules[j],rules_t);
		for(i=0;i<6;i++)
			{
				temp=strtok(rules[j],s);
				strcpy(rules_2[i],temp); 
			}
		strcpy(rule[j].dip,rules_2[0]);
		strcpy(rule[j].oip,rules_2[1]);
		strcpy(rule[j].dudp,rules_2[2]);
		strcpy(rule[j].oudp,rules_2[3]);
		strcpy(rule[j].deal,rules_2[4]);

	}
	
	puts(rule->dip);
	system("pause");
	return 0;
}
