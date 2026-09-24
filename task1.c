#include <stdio.h>

static void print_combinations(int score) {
    int a, b, c, d, e, remainder;
    int found = 0;
    
    printf("Possible combinations of scoring plays if a team's score is %d:\n", score);

    for (a = 0; 8 * a <= score; a++) {
        for (b = 0; 8 * a + 7 * b <= score; b++) {
            for (c = 0; 8 * a + 7 * b + 6 * c <= score; c++) {
                for (d = 0; 8 * a + 7 + b  + 6 * c + 3 * d <= score; d++) {
                    remainder = score - (8 * a + 7 * b + 6 * c + 5 * d);
                    if (remainder < 0) {
                        continue;
                    }
                    if (remainder % 2 == 0) {
                        e = remainder / 2;
                        printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                            a, b, c, d, e); 
                        found = 1;
                    }
                }
            }
        }
    }
    if (!found) {
        printf("No possible combinations of scoring plays produc this score. \n");
    }

}

static int read_score(int *value) {
    int result = scanf("%d", value);

    if (result != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {

        }
        return 0;
    }
    return 1;
}

int main(void) {
    int score;

    while (1) {
        printf("Enter the NFL score (Enter 1 to stop): ");

        if (!read_score(&score)) {
            printf("Invalid input. Please enter a whole number. \n");
            continue;
        }

        if (score == 1) {
            break;
        }

        if (score < 0) {
            printf("Invalid input: the score cannot be negative. \n");
        }

        print_combinations(score);
    }

    printf("Goodbye!\n");
    return 0;
}