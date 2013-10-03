#ifndef CONFIG_H
#define CONFIG_H

typedef struct config_value {
    char *option, *value;    
} config_value;

config_value* cv_parseLine(char* string);

void load_configuration();
#endif
