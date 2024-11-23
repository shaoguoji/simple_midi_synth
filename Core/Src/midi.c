#include "midi.h"
#include "drv_uart.h"

static void midi_msg_dump(void)
{
    uint8_t rx_data[256];
    uint16_t rx_len;
    uint16_t rx_available = drv_uart_midi_available();
    if (rx_available > 0) {
        rx_len = drv_uart_midi_read(&rx_data, rx_available);
        // Echo back received data
        // drv_uart_debug_write(&rx_data, rx_len);
        // Convert hex to decimal string and print
        printf("[MIDI Msg Received] ");
        for (uint16_t i = 0; i < rx_len; i++) {
            char dec_str[8];
            sprintf(dec_str, "%d ", rx_data[i]);
            printf("%s", dec_str);
        }
        // Add newline at end
        printf("\r\n");
    }
}

void midi_init(void)
{
    
}

void midi_main(void)
{
    midi_msg_dump();
}