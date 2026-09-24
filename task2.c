#include <stdio.h>
#include <ctype.h>

#define ABS_ZERO_C -273.15
#define ABS_ZERO_F -459.67
#define ABS_ZERO_K 0.0

static double to_celsius(double value, char from) {
    switch (from) {
        case 'C': 
            return value;
        case 'F':
            return (value - 32.0) * 5.0 / 9.0;
        case 'K':
            return value - 273.15;
    }
    return value;
}

static double from_celsius(double celsius, char to) {
    switch (to) {
        case 'C':
            return celsius;
        case 'F':
            return celsius * 9.0 / 5.0 + 32.0;
        case 'K':
            return celsius + 273.15;
    }
    return celsius;
}

static char read_scale(const char *prompt) {
    char buf[64];
    char letter;
 
    while (1) {
        printf("%s", prompt);
 
        if (scanf("%63s", buf) != 1) {
            printf("Invalid input. Please try again.\n");
            continue;
        }
 
        letter = (char) toupper((unsigned char) buf[0]);
        if ((letter == 'C' || letter == 'F' || letter == 'K') && buf[1] == '\0') {
            return letter;
        }
 
        printf("Invalid scale \"%s\". Please enter C, F, or K.\n", buf);
    }
}

static double read_numeric_value(void) {
    double value;

    while(1) {
        printf("Enter the temperature value:");

        if (scanf("%lf", &value) == 1) {
            return value;
        }

        int ch; 
        while ((ch = getchar()) != '\n' && ch != EOF) {

        }
        printf("Invalid input. Please enter a numeric value.\n");
    }
}

static int is_physically_valid(double value, char scale) {
    double min_value;
 
    switch (scale) {
        case 'C': min_value = ABS_ZERO_C; break;
        case 'F': min_value = ABS_ZERO_F; break;
        case 'K': min_value = ABS_ZERO_K; break;
        default:  min_value = ABS_ZERO_C; break;
    }
 
    return value >= min_value;
}
 

static void report_category(double celsius) {
    if (celsius < 0) {
        printf("Temperature category: Freezing\n");
        printf("Weather advisory: Wear a heavy coat and watch for ice!\n");
    } else if (celsius < 10) {
        printf("Temperature category: Cold\n");
        printf("Weather advisory: Wear a jacket.\n");
    } else if (celsius < 25) {
        printf("Temperature category: Comfortable\n");
        printf("Weather advisory: Enjoy the nice weather!\n");
    } else if (celsius < 35) {
        printf("Temperature category: Hot\n");
        printf("Weather advisory: Drink lots of water!\n");
    } else {
        printf("Temperature category: Extreme Heat\n");
        printf("Weather advisory: Stay indoors!\n");
    }
}
 
int main(void) {
    double input_value;
    char from_scale, to_scale;
 
    
    while (1) {
        input_value = read_numeric_value();
        from_scale = read_scale("Enter the original scale (C, F, or K): ");
 
        if (is_physically_valid(input_value, from_scale)) {
            break;
        }
 
        printf("Invalid input: %.2f is below absolute zero for scale %c. "
               "Please re-enter the temperature.\n", input_value, from_scale);
    }
 
    to_scale = read_scale("Enter the scale to convert to (C, F, or K): ");
 
    double celsius = to_celsius(input_value, from_scale);
    double converted = from_celsius(celsius, to_scale);
 
    printf("Converted temperature: %.2f %c\n", converted, to_scale);
    report_category(celsius);
 
    return 0;
}