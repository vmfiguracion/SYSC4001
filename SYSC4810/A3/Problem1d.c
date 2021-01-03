/*
Problem1d.c
Access control mechanism
Roles are categorized as follows
0: Regular Client
1: Premium Client
2: Financial Advisor
3: Financial Planner
4: Teller
5: Investment Analyst
6: Compliance Officer
7: Technical Support
*/

#include <stdio.h>
#include <stdlib.h>
/*TODO
	Incorporate other files into this (ie the roles)

*/
int main(){

	int role;
	/*Test*/
	printf("Enter number between 0-7: ");
	scanf("%d", &role);
	/**/
	char* rolename;
	char* msg;
	
	switch(role){
		case 0:
			rolename = "Regular Client";
			msg = "VIEW\nClient Information\nAccount Balance\nInvestment Portfolio\nFinancial Analyst contact details";
			break;
		case 1:
			rolename = "Premium Client";
			msg = "VIEW\t\t\t\t\tMODIFY\nClient Information\t\t\tInvestment Portfolio\nAccount Balance\nInvestment Portfolio\nFinancial Planner contact details\nInvestment Analyst contact details";
			break;
		case 2:
			rolename = "Financial Advior";
			msg = "VIEW\t\t\t\t\tMODIFY\nClient Information\t\t\tInvestment Portfolio\nAccount Balance\nInvestment Portfolio\nPrivate Consumer Instrument";
			break;
		case 3:
			rolename = "Financial Planner";
			msg = "VIEW\t\t\t\t\tMODIFY\nClient Information\t\t\tInvestment Portfolio\nAccount Balance\nInvestment Portfolio\nPrivate Consumer Instrument\nMoney Market Instrument";
			break;
		case 4:
			rolename = "Teller";
			msg = "VIEW\nClient Information\nAccount Balance\nInvestment Portfolio";
			break;
		case 5:
			rolename = "Investment Analyst";
			msg = "VIEW\t\t\t\t\tMODIFY\nClient Information\t\t\tInvestment Portfolio\nAccount Balance\nInvestment Portfolio\nPrivate Consumer Instrument\nMoney Market Instrument\nDerivaives Trading\nInterest Instruments";
			break;
		case 6:
			rolename = "Compliance Officer";
			msg = "VIEW\t\t\t\t\tOWN\nClient Information\t\t\tInvestment Portfolio\nAccount Balance\nInvestment Portfolio";
			break;
		case 7:
			rolename = "Technical Support";
			msg = "VIEW\t\t\t\t\tMODIFY\nClient Information\t\t\tClientAccount";
			break;
		default:
			msg = "Unauthorized Access.";
			break;
	}
	
	printf("Signed in as %s\n", rolename);
	printf("%s\n", msg);
	return 0;

}


