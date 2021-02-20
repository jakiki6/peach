void serial_init();
int serial_received();
char serial_read();
int serial_is_transmit_empty();
void serial_write(char c);
void serial_write_string(char *string);
