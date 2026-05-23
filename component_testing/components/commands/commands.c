#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_console.h"
#include "argtable3/argtable3.h"
#include "commands.h"

int increment(int argc, char** argv){
    int n = atoi(argv[2]);
    ++n;
    printf("%i\n", n);
    return 0;
}

void repl_init(){
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    repl_config.prompt = ">";
    repl_config.max_cmdline_length = 512;

    //args:
    arg_int_t *numbers = arg_int1("n", "number", "<int>", "Input number");
    arg_end_t *end = arg_end(20);
    void* argtable[] = {numbers, end};

    esp_console_cmd_t incr = (esp_console_cmd_t){
                            .command = "INCR",
                            .help = NULL,
                            .hint = NULL,
                            .func = increment,
                            .argtable = argtable
                        };
    esp_console_cmd_register(&incr);
    esp_console_register_help_command();
    esp_console_dev_uart_config_t hw_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_console_new_repl_uart(&hw_config, &repl_config, &repl));
    ESP_ERROR_CHECK(esp_console_start_repl(repl));
}
