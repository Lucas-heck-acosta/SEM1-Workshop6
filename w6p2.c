

#define _CRT_SECURE_NO_WARNINGS
#define ITEM_LIMIT  10
#include <stdio.h>

int main(void)
{

    int flag, item_number;
    double income, sum = 0;
    const int min_income = 500, max_income = 400000;
    const double min_cost = 100.00;
    int item = 0;
    int years, months, filter, financing_possible = 0;

    double cost[ITEM_LIMIT];
    int priority[ITEM_LIMIT];
    char finance[ITEM_LIMIT];


    printf("+--------------------------+\n");
    printf("+   Wish List Forecaster   |\n");
    printf("+--------------------------+\n");


    do 
    {
        flag = 0;
        printf("\n");
        printf("Enter your monthly NET income: $");
        scanf("%lf", &income);

        if (income < min_income)
        {
            printf("ERROR: You must have a consistent monthly income of at least $500.00\n");
            flag = 1;
        }
        else if (income > max_income)
        {
            printf("ERROR: Liar! I'll believe you if you enter a value no more than $400000.00\n");
            flag = 1;
        }
       
    } while (flag == 1);


    do
    {
        flag = 0;
        printf("\n");
        printf("How many wish list items do you want to forecast?: ");
        scanf("%d", &item_number);

        if (item_number < 1 || item_number > ITEM_LIMIT)
        {
            printf("ERROR: List is restricted to between 1 and %d items.\n", ITEM_LIMIT);
            flag = 1;
        }

    } while (flag == 1);

    for (; item < item_number; item++)
    {
        printf("\n");
        printf("Item-%d Details:\n", (item + 1));

        do
        {
            flag = 0;
            printf("   Item cost: $");
            scanf("%lf", &cost[item]);

            if (cost[item] < min_cost)
            {
                printf("      ERROR: Cost must be at least $%.2lf\n", min_cost);
                flag = 1;
            }
        } while (flag == 1);

        do
        {
            flag = 0;
            printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
            scanf("%d", &priority[item]);

            if (priority[item] <= 0 || priority[item] > 3)
            {
                printf("      ERROR: Value must be between 1 and 3\n");
                flag = 1;
            }
        } while (flag == 1);

        do
        {
            flag = 0;
            printf("   Does this item have financing options? [y/n]: ");
            scanf("%s", &finance[item]);

            if (finance[item] != 'y' && finance[item] != 'n')
            {
                printf("      ERROR: Must be a lowercase 'y' or 'n'\n");
                flag = 1;
            }
        } while (flag == 1);
    }

    printf("\n");
    printf("Item Priority Financed        Cost\n");
    printf("---- -------- -------- -----------\n");
    for (item = 0; item < item_number; item++)
    {
        printf("%3d %6d %8c %14.2lf\n", (item + 1), priority[item], finance[item], cost[item]);
        sum += cost[item];
    }
    printf("---- -------- -------- -----------\n");
    printf("                      $%11.2lf\n\n", sum);





    do
    {
        printf("How do you want to forecast your wish list?\n");
        printf(" 1. All items (no filter)\n");
        printf(" 2. By priority\n");
        printf(" 0. Quit/Exit\n");
        printf("Selection: ");
        scanf("%d", &flag);
        printf("\n");

        financing_possible = 0;
        if (flag == 1 || flag ==2)
        {

            if (flag == 2)
            {
                printf("What priority do you want to filter by? [1-3]: ");
                scanf("%d", &filter);
                printf("\n");
            }
            printf("====================================================\n");

            if (flag == 1)
            {
                printf("Filter:   All items\n");
                sum = 0;
                for (item = 0; item < item_number; item++)
                {
                    sum += cost[item];
                    if (finance[item] == 'y')
                    {
                        financing_possible = 1;
                    }
                }

            }
            else if (flag == 2)
            {
                printf("Filter:   by priority (%d)\n", filter);
                sum = 0;
                for (item = 0; item < item_number; item++)
                {
                    if (priority[item] == filter)
                    {
                        sum += cost[item];
                        if (finance[item] == 'y')
                        {
                            financing_possible = 1;
                        }
                    }
                }
            }
            printf("Amount:   $%.2lf\n", sum);

            years = (int)(sum / income) / 12;
            months = (int)(sum / income + 0.9) % 12 ;
            printf("Forecast: %d years, %d months\n", years, months);

            if (financing_possible == 1)
            {
                printf("NOTE: Financing options are available on some items.\n      You can likely reduce the estimated months.\n");
            }
            printf("====================================================\n");


        }
        else if (flag == 0)
        {
            printf("Best of luck in all your future endeavours!\n");
        }
        else
        {
            printf("ERROR: Invalid menu selection.\n");
        }

        printf("\n");

    } while (flag != 0);

    return 0;
}